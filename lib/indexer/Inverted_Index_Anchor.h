#ifndef INVERTED_INDEX_ANCHOR_H
#define INVERTED_INDEX_ANCHOR_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/Stopwords.h"

#include "Tokenizer.h"
#include "Inverted_Index.h"

using namespace std;

struct ProcessedFile{
	bool processed;
	string filename;
};

class InvertedIndexAnchor : public InvertedIndex {
protected:
	unsigned int anchor_id;

	unordered_map<string, unsigned int> links_map;

	vector<ProcessedFile> sorted_map;

public:
	InvertedIndexAnchor();
	InvertedIndexAnchor(Tokenizer& t, string url);
	InvertedIndexAnchor(Document doc);

	void indexing(Tokenizer& t, int index = 0);
	void indexing(Tokenizer& t, string url);
	void indexing(Document doc);

	void sorted_index();
	
	void vocabulary_dump(Vocabulary item, streampos pos);

	vector<FileList> get_list(string& token);

	void load_vocabulary();

	void rest();

	void to_text();

};

#endif
