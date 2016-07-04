#include "pagerank.h"

Pagerank::Pagerank(double initial_value, double d, double epsilon, unsigned int max_it){
	this->d = d;
	this->graph = {};
	this->epsilon = epsilon;
	this->initial_value = initial_value;

	this->load_graph();

	this->compute_rank(max_it);
}

void Pagerank::load_graph(){
	bool c;
	string aux;
	ifstream f;
	int link, loop = 0;
	unsigned int in_link;

	f.open(GRAPH_FILENAME, ios::out);

	if(f.is_open()){
		Graph();

		while(!f.eof()){
			Page node;

			f >> aux;

			if (aux == "*"){
				f >> link;
				f >> c;

				f >> node.out_links;
				for(int i = 0; i < node.out_links; i++){
					f >> in_link;
				}

				f >> loop;
				for(int i = 0; i < loop; i++){
					f >> in_link;
					node.in_links.push_back(in_link);
				}

				node.value = this->initial_value;
				this->graph[link] = node;
			}
		}
	}

	f.close();
}

void Pagerank::compute_rank(unsigned int max_it){
	double sum_rank, error;
	unordered_map<unsigned int, Page> new_graph = this->graph;

	bool cond = true;
	unsigned int it = 0;

	while(cond){
		cond = false;
		error = 0.0;

		for (auto page : this->graph){
			sum_rank = 0.0;

			for (unsigned int i : page.second.in_links){
				sum_rank += (this->graph[i].value / this->graph[i].out_links);
			}

			new_graph[page.first].value = (this->d * sum_rank) + (1.0 - this->d);

			error += abs(new_graph[page.first].value - this->graph[page.first].value);
		}

		this->graph = new_graph;

		cond = this->condition(error, it, max_it);

		it++;
	}

}

// Calculates stop criteria:
//    abs(PR_i+1 - PR_i) <= epsilon
bool Pagerank::condition(double error, unsigned int it, unsigned int max_it){
	bool cond = error <= this->epsilon;

	if (max_it > 0){
		cond = cond | (it >= max_it);
	}

	return !cond;
}

double Pagerank::get_rank(unsigned int page){
	return this->graph[page].value;
}

Page Pagerank::get_page(unsigned int page){
	return this->graph[page];
}

void Pagerank::dump(){
	ofstream out;

	out.open(PAGERANK_FILENAME, ios::out);

	// LinkMap::instance()->load();
	
	for (auto link : this->graph){
		// out << link.first << " " << LinkMap::instance()->get_value(link.first) << " ";
		out << link.first << " ";
		out << link.second.value;
		out << '\n';
	}

	out.close();
}
