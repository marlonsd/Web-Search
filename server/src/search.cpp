#include "search.h"

Search::Search(bool a){
	this->text_total_docs = 0;
	this->anchor_total_docs = 0;

	this->text_vocabulary = {};
	this->anchor_vocabulary = {};

	this->anchor = a;

	this->reset_distance();
	this->import_vocabulary();

	this->set_searcher();
}

void Search::set_searcher(){
	if (this->anchor){
		this->vocabulary = &this->anchor_vocabulary;
		this->total_docs = &this->anchor_total_docs;
	} else {
		this->vocabulary = &this->text_vocabulary;
		this->total_docs = &this->text_total_docs;
	}
}

void Search::change_researcher(){
	this->anchor = !this->anchor;
	this->set_searcher();
}

void Search::reset_distance(){
	for (int i = 0; i < 4; i++){
		this->previous[i] = 0;
	}
}

void Search::set_anchor_search(){
	this->anchor = true;
	this->set_searcher();
}

void Search::set_text_search(){
	this->anchor = false;
	this->set_searcher();
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

	f.open(ANCHOR_VOCABULARY_FILE_NAME, ios::in);

	if (f.is_open()){

		if (!f.eof()){
			f >> this->anchor_total_docs;
		}

		while (!f.eof()){
			mVocabulary item;
			int pos;

			// word, index position, ni, N/ni
			f >> item.word >> pos >> item.total_docs >> item.idf;
			item.file_pos = (streampos) pos;
			
			if (item.word.size()){
				item.id = word_index;
				
				this->anchor_vocabulary[item.word] = item;

				word_index++;

			}
		}
	}

	f.close();

	f.open(VOCABULARY_FILE_NAME, ios::in);

	if (f.is_open()){

		if (!f.eof()){
			f >> this->text_total_docs;
		}

		while (!f.eof()){
			mVocabulary item;
			int pos;

			// word, index position, ni, N/ni
			f >> item.word >> pos >> item.total_docs >> item.idf;
			item.file_pos = (streampos) pos;
			
			if (item.word.size()){
				item.id = word_index;
				
				this->text_vocabulary[item.word] = item;

				word_index++;

			}
		}
	}

	f.close();
}