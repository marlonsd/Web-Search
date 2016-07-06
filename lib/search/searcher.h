#ifndef SEARCHER_H
#define SEARCHER_H

#include "../common/func.h"			// Defines are here
// #include "../common/Document.h"
#include "../common/Stopwords.h"
#include "../common/linkmap.h"
#include "../common/PriorityQueue.h"

// #include "../indexer/Inverted_Index.h"
// #include "../indexer/Inverted_Index_Anchor.h"
#include "../indexer/Tokenizer.h"

#include "vectorialsearch.h"
// #include "pagerank.h"

using namespace std;

class Searcher {
private:
	VectorialSearch searcher;
	unordered_map<string, ProcessedFile> link_map;

	// Pagerank pagerank;
	void load();
	void add_value(string url, bool processed);
public:

	Searcher();

	string search(string query, double alpha = 0.0, double gamma = 0.0);
};

#endif