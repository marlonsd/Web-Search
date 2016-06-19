#ifndef PAGERANK_H
#define PAGERANK_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/linkmap.h"

#include "graph.h"

using namespace std;

struct Page {
	double value;
	unsigned int out_links;
	vector<unsigned int> in_links;
};

class Pagerank {
private:
	unordered_map<unsigned int, Page> graph; 		// <URL, <Count inbound link, List of outbound links>>
	double d;
	double initial_value;

	void load_graph();
	void compute_rank();
	void compute_rank(int max_it);

public:

	Pagerank(double initial_value = 1.0, double d = 0.85, int max_it = -1);

};

#endif