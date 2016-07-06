// #include "searcher.h"

// Searcher::Searcher(){
// 	this->load();
// }

// void Searcher::load(){
// 	bool b;
// 	ifstream f;
// 	string aux = "";

// 	this->link_map.clear();

// 	string filename = "../";
// 	filename += +ANCHOR_DOC_ID_FILE_NAME;

// 	f.open(filename, ios::in);

// 	if(f.is_open()){
// 		while(!f.eof()){
// 			f >> aux >> b;
// 			this->add_value(aux, b);
// 			this->count++;
// 		}
// 	}

// 	f.close();	
// }


// string Searcher::search(string query, double alpha, double gamma) {
// 	int loop = 0;
// 	string url = "";
// 	PriorityQueue t = this->searcher(query, alpha, gamma);

// 	while(t.size()>0 && loop < 5){
// 		Ranking item = t.pop();
// 		url += (LinkMap::instance()->get_value(item.id)+'\0');
// 		loop++;
// 	}

// 	return url;

// }

// void Searcher::add_value(string url, bool processed){
// 	if (this->link_map.find(url) != this->link_map.end()){
// 		return;
// 	}
	
// 	this->link_map[url].id = this->count;
// 	this->link_map[url].processed = processed;

// 	this->inverse.push_back(url);

// 	this->count++;

// }
