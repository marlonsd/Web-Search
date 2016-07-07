#include "vectorialsearch.h"

VectorialSearch::VectorialSearch(bool a){
	Search();
	this->w_d_anchor = {};
	this->w_d_text = {};
	this->pagerank = {};
	cout << "Loading wd" << endl;
	this->load_w_d();
	cout << "Done loading wd" << endl;
	cout << "Loading pagerank" << endl;
	this->load_pagerank();
	cout << "Done loading pagerank" << endl;
}

void VectorialSearch::read_line(int& word_id, int& doc_id, int& freq, int& pos, ifstream& index){
	index.read((char*) &word_id, sizeof(word_id));
	index.read((char*) &doc_id, sizeof(doc_id));
	index.read((char*) &freq, sizeof(freq));
	index.read((char*) &pos, sizeof(pos));
}

void VectorialSearch::load_pagerank(){
	int id;
	double value;
	ifstream input;

	input.open(PAGERANK_FILENAME, ios::in);

	while(!input.eof()){
		input >> id >> value;

		this->pagerank[id] = value;
	}


}


PriorityQueue VectorialSearch::search(string query, double alpha, double gamma){
	string token;
	ifstream index;
	PriorityQueue top;

	// cout << alpha << " " << gamma << endl;

	double w_t, w_dt;
	int previous_doc_id = 0;
	int word_id, doc_id, freq, pos;

	unordered_map<unsigned int, double> acc_text;
	unordered_map<unsigned int, double> acc_anchor;

	ifstream input;

	Tokenizer t(query, Stopwords::instance()->get_value());

	// this->reset_distance();

	// Calculating tfidf for each word in query
	// TODO: Accumulate tfidf of documents in order to have vectorial product
	while(t.size() > 0){
		token = t.getToken();

		if(token.size() > 0){

			std::cout << "\tProcessing token: " << token << std::endl;

			this->set_text_search();

			if(!((*this->vocabulary).find(token) == (*this->vocabulary).end())){
				this->cossine_similarity(token, acc_text, INDEX_SORTED_FILE_NAME);
			}

			this->set_anchor_search();

			if(!((*this->vocabulary).find(token) == (*this->vocabulary).end())){
				this->cossine_similarity(token, acc_anchor, INDEX_SORTED_FILE_NAME);
			}
		}
	}

	for (auto item : acc_text){
		Ranking rank;
		// item.first => doc_id
		// item.second => acc[doc_id]

		rank.id = item.first;

		rank.rank = 0.0;

		if(this->w_d_text.find(rank.id) == this->w_d_text.end()){
			this->w_d_text[rank.id] = 0.0;
		} else {
			rank.rank = this->w_d_text[rank.id] > 0 ? (acc_text[rank.id] / this->w_d_text[rank.id]) : 0.0;
		}

		if(this->w_d_anchor.find(rank.id) == this->w_d_anchor.end()){
			this->w_d_anchor[rank.id] = 0.0;
		} else {
			double sum = this->w_d_anchor[rank.id] ? (alpha*((acc_anchor[rank.id] / this->w_d_anchor[rank.id]))) : 0.0;
			rank.rank += sum;
		}

		if (this->pagerank.find(rank.id) != this->pagerank.end()){
			rank.rank += (gamma*this->pagerank[rank.id]);
		}

		top.push(rank);

	}

	return top;
}

void VectorialSearch::load_w_d(){
	int id, size;
	double value;

	ifstream input;

	cout << "\tLoading ANCHOR wd" << endl;
	input.open(ANCHOR_DOC_WD_FILE_NAME, ios::in);
	if (input.is_open()){

		input >> size;

		this->w_d_anchor.clear();

		while(!input.eof()){
			input >> id >> value;
			this->w_d_anchor[id] = sqrt(value);
			// std::cout << "id: " << id << " value: " << sqrt(value) << std::endl;
		}
	}
	input.close();
	cout << "\tLDone loading ANCHOR wd" << endl;
	cout << "\tLoading TEXT wd" << endl;
	input.open(DOC_WD_FILE_NAME, ios::in);
	if (input.is_open()){

		this->w_d_text.clear();

		input >> size;

		// cout << size << endl;

		for(int i = 0; i < size && !input.eof(); i++){
			input >> id >> value;
			if (!input.eof()){
				// std::cout << "id: " << id << " value: " << sqrt(value) << std::endl;
				this->w_d_text[id] = sqrt(value);
			}
		}
	}
	input.close();
	cout << "\tDone loading TEXT wd" << endl;
}

void VectorialSearch::cossine_similarity(string token, unordered_map<unsigned int, double>& acc, string filename){
	ifstream index;
	double w_t, w_dt;
	int previous_doc_id = 0;
	int word_id, doc_id, freq, pos;

	// idf
	w_t = log2(1.0 + (*this->total_docs / (*this->vocabulary)[token].idf));
	// cout << "w_t = " << *this->total_docs << " " << (*this->vocabulary)[token].idf << endl;

	index.open(filename, ios::in | ios::binary);

	index.seekg (0, index.beg);
	index.seekg((*this->vocabulary)[token].file_pos);

	// this->read_line(word_id, doc_id, freq, pos, index);
	index.read((char*) &word_id, sizeof(word_id));
	index.read((char*) &doc_id, sizeof(doc_id));
	index.read((char*) &freq, sizeof(freq));
	index.read((char*) &pos, sizeof(pos));

	// std::cout << "Position: " << (*this->vocabulary)[token].file_pos << std::endl;

	// Every first line in the index starts with a number different than 0
	// Every other line refering to the same token will have 0
	word_id = 0;

	previous_doc_id = 0;

	// cout << token << endl;

	while(!word_id && !index.eof()){
		// cout << word_id << " " << doc_id << " " << freq << " " << pos << endl;
		// Restoring doc_id
		doc_id += previous_doc_id;

		//w_d,t
		w_dt = (1.0 + log2(freq)) * w_t;

		// Ad <- Ad + log2 (1 + fdt) * wt
		if(acc.find(doc_id) == acc.end()){
			acc[doc_id] = 0.0;
		}
		acc[doc_id] += w_dt;

		// cout << "\t" << doc_id << " " << w_dt << endl;

		for (int i = 0; i < (freq - 1) && !index.eof(); i++){
			this->read_line(word_id, doc_id, freq, pos, index);
			// std::cout << "\t";
			// cout << word_id << " " << doc_id << " " << freq << " " << pos << endl;
		}

		previous_doc_id = doc_id;

		this->read_line(word_id, doc_id, freq, pos, index);
	}

	index.close();
}
