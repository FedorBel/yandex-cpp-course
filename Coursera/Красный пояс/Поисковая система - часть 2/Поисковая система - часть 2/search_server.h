#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>

#include "synchronized.h"
using namespace std;

class InvertedIndex {
public:
  void Add(string document);
  vector<pair<size_t, size_t>> Lookup(string_view word) const;

  /*const string& GetDocument(size_t id) const {
    return docs[id];
  }*/

  const size_t GetDocsSize() const {
	  return docs.size();
  }

private:
  map<string_view, vector<pair<size_t, size_t>>> index;
  list<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateEmptyDocumentBase(istream & document_input);
  void UpdateDocumentBase(istream& document_input);
  void UpdateDocumentBaseSingleThread(vector<string> documents);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

  void AddQueriesStreamSingleThread(istream & query_input, ostream & search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> futures_;
};
