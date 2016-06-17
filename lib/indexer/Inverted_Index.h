#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/Stopwords.h"

#include "Tokenizer.h"

using namespace std;

struct Vocabulary{
	int id;				// word id
	string word;		// Current Word
	streampos file_pos;	// Word's position in index file
	int total_docs;		// Total number of docs that contains "word"
	double idf;			// "word"'s idf
};

class InvertedIndex{
protected:
	int memory_usage;
	int total_size_index;
	int word_index;
	int total_token;
	int n_dumps;
	int previous[4];

	int total_docs;

	unordered_map<string, int> vocabulary;					// <word, id>
	unordered_map<string,vector<FileList>> inverted_index;	// <id_word, list of occurrences>

	deque<Vocabulary> vocabulary_order;

	void memory_dump();

	void load_full_index();
	void reset_distance();

	void distance_diff(vector<int>& v);
	void distance_rest(vector<int>& v);

	void write_line(int word_id, int doc_id, int freq, int pos, fstream& file);
	void write_line(int word_id, int doc_id, int freq, int pos, ofstream& file);

	void write_line(vector<int> values, fstream& file, vector<int>::size_type min = 4);
	void write_line(vector<int> values, ofstream& file, vector<int>::size_type min = 4);

	bool read_line(fstream& file, vector<int>& v, streampos pos = 0, int it = 4);
	bool read_line(ifstream& file, vector<int>& v, streampos pos = 0, int it = 4);

	void vocabulary_init();


public:
	InvertedIndex();
	InvertedIndex(Tokenizer& t, int index = 0);
	InvertedIndex(Document doc, int index = 0);

	void indexing(Tokenizer& t, int index = 0);
	void indexing(Document doc, int index = 0);

	void sorted_index();
	
	void vocabulary_dump(Vocabulary item, streampos pos);

	vector<FileList> get_list(string& token);

	void load_vocabulary();

	void rest();

	void to_text();

};

#endif
