#include "search.h"

Search::Search(){
	this->vocabulary = {};
	this->import_vocabulary();
}

void Search::import_vocabulary(){
	ifstream f;
	unsigned int word_index = 0;

	f.open(VOCABULARY_FILE_NAME, ios::in);

	if (f.is_open()){

		InvertedIndex();

		while (!f.eof()){
			Vocabulary item;
			int pos;

			// word, index position, ni, N/ni
			f >> item.word >> pos >> item.total_docs >> item.idf;
			item.file_pos = (streampos) pos;
			
			if (item.word.size()){
				item.id = word_index;
				
				this->vocabulary[item.word] = item;

				word_index++;

			}
		}
	}

	f.close();
}