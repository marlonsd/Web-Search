#include "vectorialsearch.h"

VectorialSearch::VectorialSearch(bool a){
	ifstream input;

	if (a){
		this->w_d = NULL;

		Search(true);
		input.open(ANCHOR_DOC_WD_FILE_NAME, ios::in);
		this->load_w_d(input);
	} else {
		Search(false);
		input.open(DOC_WD_FILE_NAME, ios::in);
		this->load_w_d(input);
	}

	input.close();
}

void VectorialSearch::read_line(int& word_id, int& doc_id, int& freq, int& pos, ifstream& index){
	index.read((char*) &word_id, sizeof(word_id));
	index.read((char*) &doc_id, sizeof(doc_id));
	index.read((char*) &freq, sizeof(freq));
	index.read((char*) &pos, sizeof(pos));
}


PriorityQueue VectorialSearch::search(string query){
	string token;
	ifstream index;
	PriorityQueue top;

	double w_t, w_dt;
	int previous_doc_id = 0;
	int word_id, doc_id, freq, pos;

	unordered_map<unsigned int, double> acc;

	std::cout << "Processing query: " << query  << std::endl;

	Tokenizer t(query, Stopwords::instance()->get_value());

	if (this->anchor){
		index.open(ANCHOR_INDEX_SORTED_FILE_NAME, ios::in | ios::binary);
	} else {
		std::cout << "Opening text index" << std::endl;
		index.open(INDEX_SORTED_FILE_NAME, ios::in | ios::binary);
	}

	this->reset_distance();

	// Calculating tfidf for each word in query
	// TODO: Accumulate tfidf of documents in order to have vectorial product
	while(t.size() > 0){
		token = t.getToken();
		std::cout << "\tProcessing token: " << token << std::endl;

		if(token.size() > 0){

			if(!((*this->vocabulary).find(token) == (*this->vocabulary).end())){
				// idf
				w_t = log2(1.0 + (*this->total_docs / (*this->vocabulary)[token].idf));

				index.seekg (0, index.beg);
				index.seekg((*this->vocabulary)[token].file_pos);

				std::cout << "Position: " << (*this->vocabulary)[token].file_pos << std::endl;

				this->read_line(word_id, doc_id, freq, pos, index);

				// Every first line in the index starts with a number different than 0
				// Every other line refering to the same token will have 0
				word_id = 0;

				previous_doc_id = 0;

				while(!word_id && !index.eof()){
					cout << word_id << " " << doc_id << " " << freq << " " << pos << endl;
					// Restoring doc_id
					doc_id += previous_doc_id;

					//w_d,t
					w_dt = (1.0 + log2(freq)) * w_t;

					// Ad <- Ad + log2 (1 + fdt) * wt
					if(acc.find(doc_id) == acc.end()){
						acc[doc_id] = 0.0;
					}
					acc[doc_id] += w_dt;

					for (int i = 0; i < (freq - 1) && !index.eof(); i++){
						this->read_line(word_id, doc_id, freq, pos, index);
						std::cout << "\t";
						cout << word_id << " " << doc_id << " " << freq << " " << pos << endl;
					}

					previous_doc_id = doc_id;

					this->read_line(word_id, doc_id, freq, pos, index);
				}

				for (auto item : acc){
					Ranking rank;
					// item.first => doc_id
					// item.second => acc[doc_id]

					rank.id = item.first;
					rank.rank = acc[rank.id] / this->w_d[rank.id];
					std::cout << "rank value: " << item.second << " " << (w_d[rank.id]) << std::endl;
					std::cout << "rank value: " << acc[rank.id] / this->w_d[rank.id] << std::endl;

					top.push(rank);

				}
			}
		}
	}

	index.close();

	return top;
}

void VectorialSearch::load_w_d(ifstream& input){
	int id, size;
	double value;

	if (input.is_open()){

		input >> size;

		this->w_d = new double[size];

		// Just to be sure that all documents will have some w_d
		for (int i; i < size; i++){
			this->w_d[i] = 0.0;
		}

		while(!input.eof()){
			input >> id >> value;
			this->w_d[id] = value;
			std::cout << "id: " << id << " value: " << value << std::endl;
		}
	}
}
