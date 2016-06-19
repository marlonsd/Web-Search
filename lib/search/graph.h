#ifndef GRAPH_H
#define GRAPH_H

#include "../common/func.h"
#include "../common/Document.h"
#include "../common/linkmap.h"

// #include "../indexer/Inverted_Index_Anchor.h"

using namespace std;

struct Node{
	bool collected;
	vector<unsigned int> out_links;
	unordered_set<unsigned int> in_links;
};

class Graph {
protected:
	unordered_map<unsigned int, Node> links; 		// <URL, <Count inbound link, List of outbound links>>

	// unordered_map<string, unsigned int> links_map;
	// unsigned int global_links_counter;

	void node(const unsigned int url);
	void increase_inlink(const unsigned int url, const unsigned int origin);

public:
	Graph();
	Graph(const Document doc);
	Graph(const vector<Document> docs);

	void add_url(Document doc);

	unordered_map<unsigned int, Node> get_links();

	vector<unsigned int> get_outbound_links(unsigned int url);
	vector<unsigned int> get_outbound_links(Document doc);

	unsigned int get_number_inbound_links(unsigned int url);
	unsigned int get_number_inbound_links(Document doc);

	unsigned int get_number_outbound_links(unsigned int url);
	unsigned int get_number_outbound_links(Document doc);

	Node get_node(unsigned int url);
	Node get_node(Document doc);

	void print();

	void dump();
	void restore();

};

#endif