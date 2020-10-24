#pragma once

#include "concurrent_map_str.h"
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <thread>

using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
  vector<size_t> Lookup(const string& word) const;

  const string& GetDocument(size_t id) {
    return docs.GetAccess().ref_to_value[id];
  }

  void BuildOrdinaryMap();

private:
	map<string, vector<size_t>> index;
	ConcurrentMapStr<string, vector<size_t>> index_multi_th;
	Synchronized<vector<string>> docs;
	//vector<string> docs;
	//mutex m;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBaseSingleThread(InvertedIndex& new_index, vector<string> lines);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStreamSingleThread(ostream & search_results_output, vector<string> lines);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
