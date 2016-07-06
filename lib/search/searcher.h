#ifndef SEARCHER_H
#define SEARCHER_H

#include "../common/func.h"			// Defines are here
#include "../common/Document.h"
#include "../common/Stopwords.h"
#include "../common/linkmap.h"
#include "../common/PriorityQueue.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

#include "vectorialsearch.h"

using namespace std;

class Searcher {
private:
	static Searcher *s_instance;
	
	Tokenizer tokens;

	VectorialSearch searcher;


	Searcher();
public:

	string search();

	static Searcher *instance(){
		if (!s_instance){
			s_instance = new Searcher();
		}

		return s_instance;
	}
};

#endif