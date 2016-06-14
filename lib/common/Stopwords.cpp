#include "Stopwords.h"

Stopwords::Stopwords(string path){
	this->load_words(path);
}


unordered_set<string> Stopwords::get_value() {
	return this->words;
}

void Stopwords::set_value(string path){
	this->load_words(path);
}

void Stopwords::load_words(string path){
	string word;
	fstream input;
	vector<string> files;
	
	files = list_dir_files(path);

	for (string file : files){
		input.open(path+file, ios::in);
		if (input.is_open()){
			while (!input.eof()){
				input >> word;

				// Cleaning words just like in the Tokenizer
				cleaningWord(word);
				word.erase(std::remove_if(word.begin(), word.end(),[](char x){return std::isspace(x);}),word.end());

				if(word.size() > 1){
					this->words.insert(word);
				}
			}
		}
		input.close();
	}
}