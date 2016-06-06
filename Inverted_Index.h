#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "func.h"
#include "Tokenizer.h"

using namespace std;

class InvertedIndex{
private:
	string vocabulary_buffer;
	int memory_usage;
	int total_size_index;
	int word_index;
	int total_token;
	int n_dumps;
	int previous[4];

	unordered_map<string, int> vocabulary;					// <word, id>
	unordered_map<string,vector<FileList>> inverted_index;	// <id_word, list of occurrences>

	void memory_dump();
	vector<string> get_vocabulary();
	void load_vocabulary();
	void load_full_index();
	void reset_distance();

	void distance_diff(vector<int>& v);
	void distance_rest(vector<int>& v);

	void write_line(int word_id, int doc_id, int freq, int pos, fstream& file);
	void write_line(vector<int> values, fstream& file, vector<int>::size_type min = 4);

	bool read_line(fstream& file, vector<int>& v, int it = 4);

public:
	InvertedIndex();
	InvertedIndex(Tokenizer& t, int index = 0);

	void indexing(Tokenizer& t, int index = 0);
	void sorted_index();
	void vocabulary_dump();
	void load_index();
	vector<FileList> get_list(string& token);

	void rest();

	void to_text();

};

#endif