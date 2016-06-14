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

void Graph::node(const unsigned int url){

	if(this->links.find(url) == this->links.end()){
		Node aux;
		aux.in_links = 0;
		aux.out_links = {};
		aux.collected = false;

		this->links[url] = aux;
	}

}

void Graph::increase_inlink(const unsigned int url){

	this->node(url);

	this->links[url].in_links++;

}

void Graph::add_url(Document doc){
	unsigned int url = doc.get_url();

	if (url <= 0){
		return;
	}

	this->node(url);

	this->links[url].collected = true;

	for (auto e : doc.get_links()){
		this->links[url].out_links.push_back(e.first);
		this->increase_inlink(e.first);
	}

}


vector<unsigned int> Graph::get_outbound_links(unsigned int url){

	if (this->links.find(url) == this->links.end()){
		return {};
	}

	if (!this->links[url].collected){
		return {};
	}

	return this->links[url].out_links;
}

vector<unsigned int> Graph::get_outbound_links(Document doc){
	return this->get_outbound_links(doc.get_url());
}


unsigned int Graph::get_number_inbound_links(unsigned int url){
	if(this->links.find(url) == this->links.end()){
		return 0;
	}

	if (!this->links[url].collected){
		return 0;
	}

	return this->links[url].in_links;
}

unsigned int Graph::get_number_inbound_links(Document doc){
	return this->get_number_inbound_links(doc.get_url());
}

unsigned int Graph::get_number_outbound_links(unsigned int url){
	if(this->links.find(url) == this->links.end()){
		return 0;
	}

	if (!this->links[url].collected){
		return 0;
	}

	return this->links[url].out_links.size();
}

unsigned int Graph::get_number_outbound_links(Document doc){
	return this->get_number_outbound_links(doc.get_url());
}

Node Graph::get_node(unsigned int url){

	if(this->links.find(url) == this->links.end()){
		return {};
	}

	if (!this->links[url].collected){
		return {};
	}

	return this->links[url];
}

Node Graph::get_node(Document doc){
	return this->get_node(doc.get_url());
}

unordered_map<unsigned int, Node> Graph::get_links(){
	return this->links;
}

void Graph::print(){

	for (auto e : this->links){
		cout << e.first << "\n";
		cout << "\t In links: " << e.second.in_links << endl;
		cout << "\t Out links ["<< e.second.out_links.size() <<"] : " << endl;
		for (unsigned int link : e.second.out_links){
			cout << "\t\t" << link <<endl;
		}
		cout << endl;
 	}
 	cout << endl;

}
