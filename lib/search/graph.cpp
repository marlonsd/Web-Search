#include "graph.h"

Graph::Graph(){
	this->links = {};
}

Graph::Graph(const Document doc){
	Graph();
	this->add_url(doc);
}

Graph::Graph(const vector<Document> docs){
	Graph();

	for (Document doc : docs){
		this->add_url(doc);		
	}
}

void Graph::increase_inlink(const string url){

	if(this->links.find(url) == this->links.end()){
		Node aux;
		aux.in_links = 0;
		aux.out_links = {};
		aux.collected = false;

		this->links[url] = aux;
	}

	this->links[url].in_links++;

}

void Graph::add_url(Document doc){
	string url = doc.get_url();

	if (!url.size()){
		return;
	}

	if(this->links.find(url) == this->links.end()){
		Node aux;
		aux.in_links = 0;
		aux.out_links = {};

		this->links[url] = aux;
	}

	this->links[url].collected = true;

	for (auto e : doc.get_links()){
		this->links[url].out_links.push_back(e.first);
		this->increase_inlink(e.first);
	}

}


vector<string> Graph::get_outbound_links(string url){

	if(this->links.find(url) == this->links.end()){
		return {};
	}

	return this->links[url].out_links;
}

vector<string> Graph::get_outbound_links(Document doc){
	return this->get_outbound_links(doc.get_url());
}


unsigned int Graph::get_number_inbound_links(string url){
	if(this->links.find(url) == this->links.end()){
		return 0;
	}

	return this->links[url].in_links;
}

unsigned int Graph::get_number_inbound_links(Document doc){
	return this->get_number_inbound_links(doc.get_url());
}

unsigned int Graph::get_number_outbound_links(string url){
	if(this->links.find(url) == this->links.end()){
		return 0;
	}

	return this->links[url].out_links.size();
}

unsigned int Graph::get_number_outbound_links(Document doc){
	return this->get_number_outbound_links(doc.get_url());
}

Node Graph::get_node(string url){

	if(this->links.find(url) == this->links.end()){
		return {};
	}

	return this->links[url];
}

Node Graph::get_node(Document doc){
	return this->get_node(doc.get_url());
}

unordered_map<string, Node> Graph::get_links(){
	return this->links;
}

void Graph::print(){

	for (auto e : this->links){
		cout << e.first << "\n";
		cout << "\t In links: " << e.second.in_links << endl;
		cout << "\t Out links ["<< e.second.out_links.size() <<"] : " << endl;
		for (string link : e.second.out_links){
			cout << "\t\t" << link <<endl;
		}
		cout << endl;
 	}
 	cout << endl;

}
