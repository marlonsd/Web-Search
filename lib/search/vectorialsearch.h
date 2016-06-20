#ifndef VECTORIALSEARCH_H
#define VECTORIALSEARCH_H

#include "../search/search.h"

using namespace std;

class VectorialSearch : public Search {
private:
	void read_line(int& word_id, int& doc_id, int& freq, int& pos, ifstream& index);

public:
	VectorialSearch(bool a = false);

	PriorityQueue search(string query);
};

#endif
