#include "json.h"

using namespace std;
using namespace json;

Node::Node(vector<Node> array) : as_array(move(array)) {
}

Node::Node(map<string, Node> map) : as_map(move(map)){
}

Node::Node(double value) : as_int(value), as_double(value) {
}

Node::Node(string value) : as_string(move(value)) {
}

const vector<Node>& Node::AsArray() const {
  return as_array;
}

const map<string, Node>& Node::AsMap() const {
  return as_map;
}

int Node::AsInt() const {
  return as_int;
}

double Node::AsDouble() const {
	return as_double;
}

const string& Node::AsString() const {
  return as_string;
}

Document::Document(Node root) : root(move(root)) {
}

const Node& Document::GetRoot() const {
  return root;
}

Node LoadNode(istream& input);

Node LoadArray(istream& input) {
  vector<Node> result;

  for (char c; input >> c && c != ']'; ) {
    if (c != ',') {
      input.putback(c);
    }
    result.push_back(LoadNode(input));
  }

  return Node(move(result));
}

Node LoadNum(istream& input) {
  double result = 0;
  int sign = 1;
  if (input.peek() == '-')
  {
	  sign = -1;
	  input.ignore();
  }
  while (isdigit(input.peek())) {
    result *= 10;
    result += input.get() - '0';
  }
  if (input.peek() == '.')
  {
	  input.ignore();
	  double drob_chast = 0;
	  int counter = 0;
	  while (isdigit(input.peek())) {
		  drob_chast *= 10;
		  drob_chast += input.get() - '0';
		  counter++;
	  }
	  drob_chast /= pow(10, counter);
	  result += drob_chast;
  }
  result *= sign;
  return Node(result);
}

Node LoadString(istream& input) {
  string line;
  getline(input, line, '"');
  return Node(move(line));
}

Node LoadDict(istream& input) {
  map<string, Node> result;

  for (char c; input >> c && c != '}'; ) {
    if (c == ',') {
      input >> c;
    }

    string key = LoadString(input).AsString();
    input >> c;
    result.insert({move(key), LoadNode(input)});
  }

  return Node(move(result));
}

Node LoadNode(istream& input) {
  char c;
  input >> c;

  if (c == '[') {
    return LoadArray(input);
  } else if (c == '{') {
    return LoadDict(input);
  } else if (c == '"') {
    return LoadString(input);
  } else {
    input.putback(c);
    return LoadNum(input);
  }
}

Document Load(istream& input) {
  return Document{LoadNode(input)};
}

