#include "linkmap.h"

LinkMap::LinkMap(){
	this->link_map = {};
	this->inverse = {};
	this->count = 0;
}


unsigned int LinkMap::get_value(const string url){
	string new_url = getNormalizedUrl(url);

	if (this->link_map.find(new_url) == this->link_map.end()){
		this->add_value(new_url);
	}

	return this->link_map[new_url].id;
}

ProcessedFile LinkMap::get_node(string url){
	string new_url = getNormalizedUrl(url);

	if (this->link_map.find(new_url) == this->link_map.end()){
		this->add_value(new_url);
	}

	return this->link_map[new_url];
}

bool LinkMap::get_processed_situation(string url){
	string new_url = getNormalizedUrl(url);

	if (this->link_map.find(new_url) == this->link_map.end()){
		this->add_value(new_url);
	}

	return this->link_map[new_url].processed;	
}

string LinkMap::get_value(unsigned int url){
	if (url >= this->count){
		return "";
	}

	return this->inverse[url];
}

void LinkMap::add_value(string url, bool processed){
	string new_url = getNormalizedUrl(url);

	if (this->link_map.find(new_url) != this->link_map.end()){
		return;
	}
	
	this->link_map[new_url].id = this->count;
	this->link_map[new_url].processed = processed;

	this->inverse.push_back(new_url);

	this->count++;

}

void LinkMap::clear(){
	this->link_map.clear();
	this->inverse.clear();

	LinkMap();
}

void LinkMap::print(){

	for (string link : inverse){
		cout << link << " " << this->link_map[link].processed << '\n';
	}

}

void LinkMap::dump(){
	ofstream f;

	f.open(ANCHOR_DOC_ID_FILE_NAME, ios::out);

	// for (auto link : link_map){
	// 	f << link.first << " " << link.second.processed << " " << link.second.id <<  '\n';
	// }

	for (string link : inverse){
		f << link << " " << this->link_map[link].processed << '\n';
	}

	f.close();

	// this->clear();
}

void LinkMap::load(){
	bool b;
	ifstream f;
	string aux = "";

	this->clear();

	f.open(ANCHOR_DOC_ID_FILE_NAME, ios::in);

	if(f.is_open()){
		while(!f.eof()){
			f >> aux >> b;
			this->add_value(aux, b);
			this->count++;
		}
	}

	f.close();	
}