#ifndef VECTORIALSEARCH_H
#define VECTORIALSEARCH_H

#include "search.h"

#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>


using namespace std;

class VectorialSearch : public Search {
private:
	unordered_map<unsigned int, double> w_d_text;
	unordered_map<unsigned int, double> w_d_anchor;
	unordered_map<unsigned int, double> pagerank;

	void read_line(int& word_id, int& doc_id, int& freq, int& pos, ifstream& index);
	void load_w_d();
	void load_pagerank();

	void cossine_similarity(string token, unordered_map<unsigned int, double>& acc, string filename);

public:
	VectorialSearch(bool a = false);

	priority_queue<Ranking, vector<Ranking>, comp> search(string query, double alpha = 0.0, double gamma = 0.0);
};

#endif
