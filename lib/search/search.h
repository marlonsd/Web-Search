#ifndef SEARCH_H
#define SEARCH_H

#include "../common/func.h"
#include "../common/Document.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

using namespace std;

struct Ranking{
	unsigned int id;
	double rank;
};

struct rank_comp {
	bool operator()(Ranking A, Ranking B) {
		return (A.rank > B.rank);
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
	unordered_map<string, Vocabulary> vocabulary;	
	int previous[4];

	priority_queue<Ranking, vector<Ranking>, rank_comp> top_docs;

	void import_vocabulary();

	void reset_distance();
	void distance_rest(vector<int>& v);

public:
	Search();
	
	virtual priority_queue<Ranking, vector<Ranking>, rank_comp> search(string querry);
};

#endif