#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <future>

vector<string> SplitIntoWords(const string& line) {
	istringstream words_input(line);
	return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

SearchServer::SearchServer(istream& document_input) {
	UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBaseSingleThread(InvertedIndex& new_index, vector<string> lines)
{
	for (string& current_document : lines) {
		new_index.Add(move(current_document));
	}
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	InvertedIndex new_index;

	vector<future<void>> futures;

	const size_t max_batch_size = 50;

	vector<string> batch;
	batch.reserve(max_batch_size);

	for (string current_document; getline(document_input, current_document); ) {
		batch.push_back(move(current_document));
		if (batch.size() >= max_batch_size) {
			futures.push_back(
				async(&SearchServer::UpdateDocumentBaseSingleThread, this, std::ref(new_index), std::move(batch))
			);
			batch.reserve(max_batch_size);
		}
	}

	if (!batch.empty())
	{
		UpdateDocumentBaseSingleThread(new_index, move(batch));
	}

	for (auto& f : futures)
	{
		f.get();
	}

	index = move(new_index);
	index.BuildOrdinaryMap();
}

void SearchServer::AddQueriesStreamSingleThread(ostream& search_results_output, vector<string> lines)
{
	for (string& current_query : lines) {
		const auto words = SplitIntoWords(current_query);

		map<size_t, size_t> docid_count;
		for (const auto& word : words) {
			for (const size_t docid : index.Lookup(word)) {
				docid_count[docid]++;
			}
		}

		vector<pair<size_t, size_t>> search_results(
			make_move_iterator(docid_count.begin()), make_move_iterator(docid_count.end())
		);
		sort(
			begin(search_results),
			end(search_results),
			[](pair<size_t, size_t>& lhs, pair<size_t, size_t>& rhs) {
			int64_t lhs_docid = lhs.first;
			auto& lhs_hit_count = lhs.second;
			int64_t rhs_docid = rhs.first;
			auto& rhs_hit_count = rhs.second;
			return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
		}
		);

		search_results_output << current_query << ':';
		for (auto[docid, hitcount] : Head(search_results, 5)) {
			search_results_output << " {"
				<< "docid: " << docid << ", "
				<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	}
}

void SearchServer::AddQueriesStream(
	istream& query_input, ostream& search_results_output
) {

	vector<future<void>> futures;

	const size_t max_batch_size = 50;

	vector<string> batch;
	batch.reserve(max_batch_size);

	for (string current_query; getline(query_input, current_query); ) {
		batch.push_back(move(current_query));
		if (batch.size() >= max_batch_size) {
			futures.push_back(
				async(&SearchServer::AddQueriesStreamSingleThread, this, std::ref(search_results_output), std::move(batch))
			);
			batch.reserve(max_batch_size);
		}
	}

	if (!batch.empty())
	{
		AddQueriesStreamSingleThread(search_results_output, move(batch));
	}
}

void InvertedIndex::Add(const string& document) {
	size_t docid = 0;
	{
		auto access = docs.GetAccess();
		access.ref_to_value.push_back(document);
		docid = access.ref_to_value.size() - 1;
	}

	for (const auto& word : SplitIntoWords(document)) {
		index_multi_th[word].ref_to_value.push_back(docid);
	}
}

vector<size_t> InvertedIndex::Lookup(const string& word) const {
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	}
	else {
		return {};
	}
}

void InvertedIndex::BuildOrdinaryMap()
{
	index = index_multi_th.BuildOrdinaryMap();
}
