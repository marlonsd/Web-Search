#ifndef SEARCH_H
#define SEARCH_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/PriorityQueue.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

using namespace std;

class Search {
protected:
	/* < word,
			< word id,
				word,
				Word's position in index file,
				Total number of docs that contains "word"
				"word"'s idf
			>
		>
	*/
	unordered_map<string, Vocabulary>* vocabulary;

	unordered_map<string, Vocabulary> text_vocabulary;
	unordered_map<string, Vocabulary> anchor_vocabulary;

	int previous[4];

	unsigned int* total_docs;
	unsigned int text_total_docs;
	unsigned int anchor_total_docs;

	bool anchor;

	void import_vocabulary();
	void set_searcher();
	void change_researcher();

	void reset_distance();
	void distance_rest(vector<int>& v);

public:
	Search(bool a = false);
	
	virtual PriorityQueue search(string querry);
};

#endif