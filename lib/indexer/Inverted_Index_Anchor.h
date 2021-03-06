#ifndef INVERTED_INDEX_ANCHOR_H
#define INVERTED_INDEX_ANCHOR_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/Stopwords.h"

#include "Tokenizer.h"
#include "Inverted_Index.h"

using namespace std;

class InvertedIndexAnchor : public InvertedIndex {
protected:
	void vocabulary_init(string temp_name);
	void memory_dump();

	void wd_computing(string temp_name="");

public:
	InvertedIndexAnchor();
	InvertedIndexAnchor(Document doc);

	void indexing(Tokenizer& t, unsigned int index = 0);
	void indexing(Document doc);

	void sorted_index(string temp_name = "");
	
	void vocabulary_dump(Vocabulary item, streampos pos, string temp_name="");

	vector<FileList> get_list(string& token);

	void load_vocabulary();

	void rest();

	void to_text();

};

#endif
