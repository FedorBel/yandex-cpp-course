#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
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
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
