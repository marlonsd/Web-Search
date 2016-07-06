#ifndef SEARCH_H
#define SEARCH_H

#include "util/func.h"
// #include "util/Document.h"
#include "util/Tokenizer.h"

// #include "../indexer/Inverted_Index.h"
// #include "../indexer/Inverted_Index_Anchor.h"

using namespace std;

struct mVocabulary{
	int id;				// word id
	string word;		// Current Word
	streampos file_pos;	// Word's position in index file
	int total_docs;		// Total number of docs that contains "word"
	double idf;			// "word"'s idf
};

struct Ranking{
	unsigned int id;
	double rank;
};

struct comp {
	bool operator()(Ranking A, Ranking B) {
		return (A.rank < B.rank);
	}
};


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
	unordered_map<string, mVocabulary>* vocabulary;

	unordered_map<string, mVocabulary> text_vocabulary;
	unordered_map<string, mVocabulary> anchor_vocabulary;

	int previous[4];

	unsigned int* total_docs;
	unsigned int text_total_docs;
	unsigned int anchor_total_docs;

	bool anchor;

	void import_vocabulary();
	void set_searcher();
	void change_researcher();

	void set_text_search();
	void set_anchor_search();

	void reset_distance();
	void distance_rest(vector<int>& v);

public:
	Search(bool a = false);
	
	priority_queue<Ranking, vector<Ranking>, comp> search(string querry);
};

#endif