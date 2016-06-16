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

class Search {
private:
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

	void import_vocabulary();
public:
	Search();
	
	virtual vector<Ranking> search(string querry);
};

#endif