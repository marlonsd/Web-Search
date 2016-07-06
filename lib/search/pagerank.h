#ifndef PAGERANK_H
#define PAGERANK_H

#include "../common/func.h"
// #include "../common/Document.h"
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
	unordered_map<unsigned int, Page> graph; 		// <URL, <rank, # outbound links, list of inlinks>>
	double d;
	double epsilon;
	double initial_value;

	void load_graph();
	void compute_rank(unsigned int max_it = 0);

	bool condition(double error, unsigned int it = 0, unsigned int max_it = 0);

public:

	Pagerank(double initial_value = 1.0, double d = 0.85, double epsilon = 0.0001, unsigned int max_it = 0);

	double get_rank(unsigned int page);
	Page get_page(unsigned int page);

	void dump();

};

#endif
