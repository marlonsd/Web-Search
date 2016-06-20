#include "../common/func.h"			// Defines are here
#include "../common/Document.h"
#include "../common/Stopwords.h"
#include "../common/linkmap.h"
#include "../common/PriorityQueue.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

#include "../search/graph.h"
#include "../search/search.h"
#include "../search/vectorialsearch.h"
#include "../search/pagerank.h"

Stopwords *Stopwords::s_instance = 0;
LinkMap *LinkMap::s_instance = 0;

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
	Graph network;
	// Pagerank pagerank(1.0, 0.85, 0.0001, 15);

	// network.restore();

	cout << "Doing research" << endl;

	PriorityQueue t = searcher.search("porridge");

	while (t.size()){
		Ranking item = t.pop();
		cout << item.id << " " << item.rank << endl;
	}

	return 0;
}
