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
		aux.in_links = {};
		aux.out_links = {};
		aux.collected = false;

		this->links[url] = aux;
	}

}

void Graph::increase_inlink(const unsigned int url, const unsigned int origin){

	this->node(url);

	// this->links[url].in_links++;
	this->links[url].in_links.insert(origin);

}

void Graph::add_url(Document doc){
	unsigned int url = LinkMap::instance()->get_value(doc.get_url());

	this->node(url);

	this->links[url].collected = true;

	for (auto e : doc.get_links()){
		this->links[url].out_links.push_back(e.first);
		this->increase_inlink(e.first, url);
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
	return this->get_outbound_links(LinkMap::instance()->get_value(doc.get_url()));
}


unsigned int Graph::get_number_inbound_links(unsigned int url){
	if(this->links.find(url) == this->links.end()){
		return 0;
	}

	if (!this->links[url].collected){
		return 0;
	}

	return this->links[url].in_links.size();
}

unsigned int Graph::get_number_inbound_links(Document doc){
	return this->get_number_inbound_links(LinkMap::instance()->get_value(doc.get_url()));
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
	return this->get_number_outbound_links(LinkMap::instance()->get_value(doc.get_url()));
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
	return this->get_node(LinkMap::instance()->get_value(doc.get_url()));
}

unordered_map<unsigned int, Node> Graph::get_links(){
	return this->links;
}

void Graph::print(){

	cout << "Printing graph" << endl << endl;

	for (auto e : this->links){
		cout << e.first << "\n";
		cout << "\t In links ["<< e.second.in_links.size() <<"] : " << endl;
		for (unsigned int link : e.second.in_links){
			cout << "\t\t<-- " << link <<endl;
		}
		cout << "\t Out links ["<< e.second.out_links.size() <<"] : " << endl;
		for (unsigned int link : e.second.out_links){
			cout << "\t\t--> " << link <<endl;
		}
		cout << endl;
 	}
 	cout << endl;

}

void Graph::dump(string temp_name){
	ofstream out;

	out.open(temp_name+GRAPH_FILENAME, ios::out);

	// for (auto link : this->links){
	// 	out << "*" << " " << link.first << '\n';
	// 	out << link.second.collected << '\n';
	// 	out << link.second.in_links << '\n';
	// 	out << link.second.out_links.size() << '\n';
	// 	for (auto out_link : link.second.out_links){
	// 		out << out_link << '\n';
	// 	}
	// }

	for (int i = this->links.size()-1; i >= 0; i--){
		Node link = this->links[i]; 
		if (link.collected){
			out << "*" << " " << i << '\n';
			out << link.collected << '\n';
			out << link.out_links.size() << '\n';
			for (unsigned int out_link : link.out_links){
				if (this->links[out_link].collected){
					out << out_link << '\n';
				}
			}
			out << link.in_links.size() << '\n';
			for (unsigned int in_link : link.in_links){
				if (this->links[in_link].collected){
					out << in_link << '\n';
				}
			}
		}
	}

	out.close();
}

void Graph::restore(){
	string aux;
	ifstream f;
	int link, out_link, loop = 0;

	f.open(GRAPH_FILENAME, ios::out);

	if(f.is_open()){
		Graph();

		while(!f.eof()){
			Node node;

			f >> aux;

			if (aux == "*"){
				f >> link;
				f >> node.collected;
				// f >> node.in_links;
				f >> loop;
				for(int i = 0; i < loop; i++){
					f >> out_link;
					node.out_links.push_back(out_link);
				}
				f >> loop;
				for(int i = 0; i < loop; i++){
					f >> out_link;
					node.in_links.insert(out_link);
				}

				this->links[link] = node;
			}
		}
	}

	f.close();
}