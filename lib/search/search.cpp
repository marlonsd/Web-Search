#include "search.h"

Search::Search(){
	this->vocabulary = {};
	this->top_docs = {};
	this->reset_distance();
	this->import_vocabulary();
}

void Search::reset_distance(){
	for (int i = 0; i < 4; i++){
		this->previous[i] = 0;
	}
}

void Search::distance_rest(vector<int>& v){

	if (v[1] != 0){
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	if (v[0] != 0){
		this->previous[1] = 0;
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	for (int i = 0; i < 4; i++){
		v[i] = v[i] + this->previous[i];
		this->previous[i] = v[i];
	}

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