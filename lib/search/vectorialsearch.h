#ifndef VECTORIALSEARCH_H
#define VECTORIALSEARCH_H

#include "../search/search.h"

using namespace std;

class VectorialSearch : public Search {
public:
	VectorialSearch(bool a = false);
	
	PriorityQueue search(string query);
};

#endif