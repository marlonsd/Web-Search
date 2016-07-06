#include "searcher.h"

Searcher::Searcher(){
	
}


vector<int> Searcher::search(string query, double alpha, double gamma) {
	int loop = 0;
	vector<int> url;
	priority_queue<Ranking, vector<Ranking>, comp> t = this->searcher.search(query, alpha, gamma);

	while(t.size()>0 && loop < 5){
		Ranking item = t.top();
		url.push_back(item.id);
		loop++;
		t.pop();
	}

	return url;

}

void Searcher::load(){
	
}