#include "vectorialsearch.h"

VectorialSearch::VectorialSearch(bool a){
	if (a){
		Search(true);
	} else {
		Search(false);
	}
}

PriorityQueue VectorialSearch::search(string query){
	string token;

	ifstream index;

	PriorityQueue top;

	double w_t, w_dt;
	int previous_doc_id = 0;
	int word_id, doc_id, freq, pos;

	unordered_map<unsigned int, double> acc;
	unordered_map<unsigned int, double> w_d;

	Tokenizer t(query, Stopwords::instance()->get_value());

	if (this->anchor){
		index.open(ANCHOR_INDEX_SORTED_FILE_NAME, ios::in | ios::binary);
	} else {
		index.open(INDEX_SORTED_FILE_NAME, ios::in | ios::binary);
	}

	this->reset_distance();


	// Calculating tfidf for each word in query
	// TODO: Accumulate tfidf of documents in order to have vectorial product
	while(t.size() > 0){
		token = t.getToken();

		if(token.size() > 0){

			if(!((*this->vocabulary).find(token) == (*this->vocabulary).end())){
				// idf
				w_t = log2(1.0 + (*this->total_docs / (*this->vocabulary)[token].idf));

				index.seekg (0, index.beg);
				index.seekg((*this->vocabulary)[token].file_pos);

				index >> word_id >> doc_id >> freq >> pos;

				// Every first line in the index starts with a number different than 0
				// Every other line refering to the same token will have 0
				word_id = 0;

				previous_doc_id = 0;

				while(!word_id && !index.eof()){
					// Restoring doc_id
					doc_id += previous_doc_id;

					//w_d,t
					w_dt = (1.0 + log2(freq)) * w_t;

					// Ad <- Ad + log2 (1 + fdt) * wt
					if(acc.find(doc_id) == acc.end()){
						acc[doc_id] = 0.0;
					}
					acc[doc_id] += w_dt;

					// Acc W_d
					if(w_d.find(doc_id) == w_d.end()){
						w_d[doc_id] = 0.0;
					}

					w_d[doc_id] += pow(w_dt, 2.0);

					for (int i = 0; i < freq && !index.eof(); i++){
						index >> word_id >> doc_id >> freq >> pos;
					}

					previous_doc_id = doc_id;
				}

				for (auto item : acc){
					Ranking rank;
					// item.first => doc_id
					// item.second => acc[doc_id]

					rank.id = item.first;
					rank.rank = acc[rank.id] / sqrt(w_d[rank.id]);

					top.push(rank);

				}
			}
		}
	}

	index.close();

	return top;
}