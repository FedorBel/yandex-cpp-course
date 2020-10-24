#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include <chrono>

#include "profile.h"
#include "split_into_words.h"

SearchServer::SearchServer(istream& document_input) {
	UpdateEmptyDocumentBase(document_input);
}

void SearchServer::UpdateEmptyDocumentBase(istream& document_input) {
	InvertedIndex new_index;

	for (string current_document; getline(document_input, current_document); ) {
		new_index.Add(move(current_document));
	}

	swap(index.GetAccess().ref_to_value, new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	if (index.GetAccess().ref_to_value.GetDocsSize() == 0)
	{
		UpdateEmptyDocumentBase(document_input);
	}
	else
	{
		vector<string> docs;
		for (string current_document; getline(document_input, current_document); ) {
			docs.push_back(move(current_document));
		}
		thread(&SearchServer::UpdateDocumentBaseSingleThread, this, move(docs)).detach();
	}	
}

void SearchServer::UpdateDocumentBaseSingleThread(vector<string> documents) {
	InvertedIndex new_index;
	for (string doc : documents ) {
		new_index.Add(move(doc));
	}

	swap(index.GetAccess().ref_to_value, new_index);
}

void SearchServer::AddQueriesStream(
	istream& query_input, ostream& search_results_output
) 
{
	//thread(&SearchServer::AddQueriesStreamSingleThread, this, ref(query_input), ref(search_results_output)).detach();
	//this_thread::sleep_for(chrono::microseconds(10));
	//AddQueriesStreamSingleThread(query_input, search_results_output);
	futures_.push_back(async(&SearchServer::AddQueriesStreamSingleThread, this, ref(query_input), ref(search_results_output)));
}

void SearchServer::AddQueriesStreamSingleThread(
	istream& query_input, ostream& search_results_output
)
{
	vector<size_t> docid_count;
	vector<int64_t> docids;

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	for (string current_query; getline(query_input, current_query); ) {
		

		const auto words = SplitIntoWords(current_query);
		
		docid_count.assign(docid_count.size(), 0);

		{
			auto access = index.GetAccess();

			const size_t doc_count = access.ref_to_value.GetDocsSize();
			docid_count.assign(doc_count, 0);
			docids.resize(doc_count);


			for (const auto& word : words) {
				for (const auto&[docid, count] : access.ref_to_value.Lookup(word)) {
					docid_count[docid] += count;
				}
			}
		}
		

		iota(docids.begin(), docids.end(), 0);

		partial_sort(
			begin(docids),
			Head(docids, 5).end(),
			end(docids),
			[&docid_count](int64_t lhs, int64_t rhs) {
			return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
		}
		);

		search_results_output << current_query << ':';
		for (size_t docid : Head(docids, 5)) {
			// рейтинг
			const size_t hit_count = docid_count[docid];
			// если рейтинг==0, то не будем добавлять в поток
			if (hit_count == 0) {
				break;
			}
			search_results_output << " {"
				<< "docid: " << docid << ", "
				<< "hitcount: " << hit_count << '}';
		}
		search_results_output << '\n';
	}
}

void InvertedIndex::Add(string document) {
	/*
	У меня есть документ
	Надо собрать все слова их него в одну мапу
	word -> {docid, count}
	*/

	docs.push_back(move(document));

	size_t docid = docs.size() - 1;

	for (string_view word : SplitIntoWords(docs.back())) {
		/* после того как SplitIntoWords вернула нам из документа вектор слов
		 * запускаем цикл по обработке каждого слова
		 * */
		 /*
		  * получаем ссылку на вектор значений для слова
		  * */

		auto& docids = index[word];
		// если вектор Id/рейтинг не пустой и мы до сих пор в том де файле
		if (!docids.empty() && docids.back().first == docid) {
			docids.back().second++;
		}
		else {
			docids.push_back({ docid, 1 });
		}
	}

}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(string_view word) const {
	static vector<pair<size_t, size_t>> result;
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	}
	else {
		return result;
	}
}
