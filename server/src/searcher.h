#ifndef SEARCHER_H
#define SEARCHER_H

#include "util/func.h"			// Defines are here

#include "util/Tokenizer.h"

#include "vectorialsearch.h"

using namespace std;

class Searcher {
private:
	VectorialSearch searcher;

	void load();
public:

	Searcher();

	vector<int> search(string query, double alpha = 0.0, double gamma = 0.0);
};

#endif