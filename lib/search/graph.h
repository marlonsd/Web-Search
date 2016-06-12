#ifndef GRAPH_H
#define GRAPH_H

#include "../common/func.h"
#include "../common/Document.h"

using namespace std;

struct Node{
	int in_links;
	vector<string> out_links;
};

class Graph {
private:
	unordered_map<string, Node> links; 		// <URL, <Count inbound link, List of outbound links>>

	void increase_inlink(const string url);

public:
	Graph();
	Graph(const Document doc);
	Graph(const vector<Document> docs);

	void add_url(Document doc);

	unordered_map<string, Node> get_links();

	vector<string> get_outbound_links(string url);
	vector<string> get_outbound_links(Document doc);

	unsigned int get_number_inbound_links(string url);
	unsigned int get_number_inbound_links(Document doc);

	unsigned int get_number_outbound_links(string url);
	unsigned int get_number_outbound_links(Document doc);

	Node get_node(string url);
	Node get_node(Document doc);

	void print();

};

#endif