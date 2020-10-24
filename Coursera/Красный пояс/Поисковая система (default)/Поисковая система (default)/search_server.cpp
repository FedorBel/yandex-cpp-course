#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include "profile.h"

void LeftStrip(string_view& sv) {
	// ������� ������ ������� �����
	while (!sv.empty() && isspace(sv[0])) {
		sv.remove_prefix(1);
	}
}
string_view ReadToken(string_view& sv) {
	LeftStrip(sv);
	// ���� ������
	// �.�. ������� ����� ����� - �� ���� ������� ������� �������
	auto pos = sv.find(' ');
	// ������� �����
	auto word = sv.substr(0, pos);
	// ������� ����� �
	sv.remove_prefix(pos != sv.npos ? pos : sv.size());
	return word;
}

vector<string_view> SplitIntoWords(string_view line) {
	vector<string_view> value;
	/* ������ ������(���������� �����
	 * �� ���� �������� ������ �����
	 * ��������� ����� � ������
	 * */
	for (string_view word = ReadToken(line); !word.empty(); word = ReadToken(line)) {
		value.push_back(word);
	}
	return value;
}


SearchServer::SearchServer(istream& document_input) {
	UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	InvertedIndex new_index;

	for (string current_document; getline(document_input, current_document); ) {
		new_index.Add(move(current_document));
	}

	index = move(new_index);
}

void SearchServer::AddQueriesStream(
	istream& query_input, ostream& search_results_output
) {
	//LOG_DURATION("Total");

	vector<size_t> docid_count(index.GetDocsSize());
	vector<int64_t> docids(index.GetDocsSize());

	//vector<pair<size_t, size_t>> search_results;
	//search_results.reserve(index.GetDocsSize());

	/*for (size_t i = 0; i < index.GetDocsSize(); i++)
	{
		search_results.push_back({ i,0 });
	}*/

	//vector<pair<size_t, size_t>> search_results_sorted(5);

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	for (string current_query; getline(query_input, current_query); ) {
		const auto words = SplitIntoWords(current_query);

		//vector<size_t> docid_count(50000);
		//map<size_t, size_t> docid_count;
		docid_count.assign(docid_count.size(), 0);

		// ������ ���-�� � ����
		//{
		//	//LOG_DURATION("docid_count");

			for (const auto& word : words) {
				for (const auto&[docid, count] : index.Lookup(word)) {
					docid_count[docid] += count;
				}
			}
		//}

		//vector<pair<size_t, size_t>> search_results(docid_count.begin(), docid_count.end());



		/*for (size_t i = 0; i < docid_count.size(); i++)
		{
			search_results[i].second = docid_count[i];
		}*/
		iota(docids.begin(), docids.end(), 0);

		partial_sort(
			begin(docids),
			Head(docids, 5).end(),
			end(docids),
			[&docid_count](int64_t lhs, int64_t rhs) {
			return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
		}
		);


		/*
		{
			//LOG_DURATION("sort");
			auto middle = search_results.size() >= 5 ? (search_results.begin() + 5) : search_results.end();
			partial_sort(
				search_results.begin(),
				middle,
				search_results.end(),
				[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
				int64_t lhs_docid = lhs.first;
				auto lhs_hit_count = lhs.second;
				int64_t rhs_docid = rhs.first;
				auto rhs_hit_count = rhs.second;
				return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
			}
			);
		} */

		search_results_output << current_query << ':';
		for (size_t docid : Head(docids, 5)) {
			// �������
			const size_t hit_count = docid_count[docid];
			// ���� �������==0, �� �� ����� ��������� � �����
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
	� ���� ���� ��������
	���� ������� ��� ����� �� ���� � ���� ����
	word -> {docid, count}
	*/

	docs.push_back(move(document));

	size_t docid = docs.size() - 1;

	//size_t count = 0;

	//map<string_view, size_t> words_count;


	//for (auto word : SplitIntoWords(docs.back())) {
	//	words_count[word]++;
	//	// index[word].push_back(docid);
	//}

	//for (auto& el : words_count)
	//{
	//	index[el.first].push_back({ docid, el.second });
	//}

	for (string_view word : SplitIntoWords(docs.back())) {
		/* ����� ���� ��� SplitIntoWords ������� ��� �� ��������� ������ ����
		 * ��������� ���� �� ��������� ������� �����
		 * */
		 /*
		  * �������� ������ �� ������ �������� ��� �����
		  * */

		auto& docids = index[word];
		// ���� ������ Id/������� �� ������ � �� �� ��� ��� � ��� �� �����
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
