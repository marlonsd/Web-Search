#include "pagerank.h"

Pagerank::Pagerank(double initial_value, double d, int max_it){
	this->graph = {};
	this->initial_value = initial_value;
	this->d = d;

	this->load_graph();

	if (max_it > 0){
		this->compute_rank(max_it);
	} else {
		this->compute_rank();
	}
}

void Pagerank::load_graph(){
	bool c;
	string aux;
	unsigned int out_link;
	int link, loop = 0, trash;

	ifstream f;

	f.open(GRAPH_FILENAME, ios::out);

	if(f.is_open()){
		Graph();

		while(!f.eof()){
			Page node;

			f >> aux;

			if (aux == "*"){
				node.value = this->initial_value;

				f >> link;
				f >> c;
				f >> trash;

				f >> node.out_links;
				for(int i = 0; i < node.out_links; i++){
					f >> out_link;
				}

				f >> loop;
				for(int i = 0; i < loop; i++){
					f >> out_link;
					node.in_links.push_back(out_link);
				}

				this->links[link] = node;
			}
		}
	}

	f.close();
}

void Pagerank::compute_rank(){
	double sum_rank;
	unordered_map<unsigned int, Page> new_graph;

	bool cond = true;
	int it = 0;

	while(cond){
		cond = false;

		for (auto page : this->graph){
			sum_rank = 0.0;

			for (unsigned int i : page.second.in_links){
				sum_rank += (this->graph[i].value / this->graph[i].out_links);
			}

			new_graph[page.first] = (this->d * sum_rank) + (1.0 - this->d);

			cond = cond | (new_graph[page.first] != this->graph[page.first]);
		}



		this->graph.clear();
		this->graph = new_graph;
	}

}

void Pagerank::compute_rank(int max_it){
	
}