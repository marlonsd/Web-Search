#include <sstream>
#include "../common/func.h"			// Defines are here
#include "../common/Stopwords.h"
#include "../common/linkmap.h"
#include "../common/PriorityQueue.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

#include "../search/vectorialsearch.h"

#define ANCHOR_TEXT 0.25
#define PAGERANK 0.3


Stopwords *Stopwords::s_instance = 0;
LinkMap *LinkMap::s_instance = 0;

string getclause();

int main(int argc, const char* argv[]) {
	string query, token;
	std::size_t found;
	InvertedIndex index;
	Tokenizer tokens;
	vector<FileList> list;
	vector<int> all_files;
	bool first = true;
	vector<string> doc_id;
	VectorialSearch searcher;
	// Graph network;

	LinkMap::instance()->load();

	cout << "Query: ";
	query = getclause();

	while(query != "-q"){
		// query = "pease";

		cout << query << endl;

		PriorityQueue t = searcher.search(query, ANCHOR_TEXT, PAGERANK);

		if (!t.size()){
			cout << "No document found." << endl;
		}


		while (t.size()){
			Ranking item = t.pop();
			cout << LinkMap::instance()->get_value(item.id) << " " << item.rank << endl;
		}
		cout << endl << endl;

		cout << "Query: ";
		query = getclause();
	}

	return 0;
}


string getclause() {
  string c;
  string cl="";
  std::string line;
  std::getline(cin, line);
  std::istringstream iss(line);
  while ( iss >> c) {    
    cl+=(c+ " ");
  }
  cl.pop_back();
  return cl;
}