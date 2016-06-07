#include "Inverted_Index.h"

InvertedIndex::InvertedIndex(){
	this->memory_usage = 0;
	this->word_index = 0;
	this->total_token = 0;
	this->total_size_index = 0;
	this->n_dumps = 0;

	this->total_docs = 0;

	this->vocabulary = {};
	this->inverted_index = {};

	this->vocabulary_order = {};

	for (int i = 0; i < 4; i++){
		this->previous[i] = 0;
	}

}

InvertedIndex::InvertedIndex(Tokenizer& t, int index){
	InvertedIndex();
	this->indexing(t, index);
}

void InvertedIndex::reset_distance(){
	for (int i = 0; i < 4; i++){
		this->previous[i] = 0;
	}
}

void InvertedIndex::write_line(int word_id, int doc_id, int freq, int pos, fstream& file){
	// file << word_id << doc_id << freq << pos;
	file.write((const char*) &word_id, sizeof(word_id));
	file.write((const char*) &doc_id, sizeof(doc_id));
	file.write((const char*) &freq, sizeof(freq));
	file.write((const char*) &pos, sizeof(pos));
}

void InvertedIndex::write_line(vector<int> values, fstream& file, vector<int>::size_type min){
	vector<int> aux;

	if (values.size() > min){
		std::copy(values.begin(), min+values.begin(), std::back_inserter(aux));
	} else {
		aux = values;		
	}


	for (int value : aux){
		file.write((char*) &value, sizeof(value));	
	}
}

bool InvertedIndex::read_line(fstream& file, vector<int>& v, int it){
	bool test = true;
	int aux;
	// int i = 0;

	v.clear();

	for (int i = 0; ((i < it) && test); i++){

		if(file.read((char*) &aux, sizeof(aux))){
			v.push_back(aux);
			test = true;
		} else {
			test = false;
		}
	}

	// while(file.read((char*) &aux, sizeof(aux)) && i < it){
	// 	v.push_back(aux);
	// 	i++;
	// }

	return test;
}

void InvertedIndex::indexing(Tokenizer& t, int index){
	unordered_set<string> docs_words;


	/* A file must be indexed entirely, so it is possible to calculate total number of terms in a same file.
		To do so, it is calculate the necessaary space to store this one file and the actual size of index.
		If it is going to be bigger than memory size, dump index first.
	*/
	if ((this->memory_usage) && (((t.size()*INDEX_LINE_SIZE)+this->memory_usage) >= MEMORY_LIMITE)){
		this->memory_dump();
	}

	if (t.size() > 0){
		this->total_docs++;
	}

	// Iterating through tokens
	int word_id = 0;
	while (t.size() > 0){
		string token = t.getToken();

		if (token.size()) {
			this->total_token++;

			docs_words.insert(token);

			// Testing if token is not already in the vocabulary
			auto search = this->vocabulary.find(token);
			if (search == this->vocabulary.end()){
				this->vocabulary[token] = this->word_index;

				Vocabulary item;
				item.word = token;
				item.pos = this->word_index;
				item.total_docs = 0;
				this->vocabulary_order.push_back(item);

				this->word_index++;
			}

			// this->vocabulary_order[this->vocabulary[token]].total++;

			// Testing if token is not already in the index
			auto search2 = this->inverted_index.find(token);

			// Testing if token had already been seen in document index
			if (search2 != this->inverted_index.end() &&					// Testing if token is in index
				this->inverted_index[token].size() > 0 &&
				this->inverted_index[token].back().file_index == index) {
					this->inverted_index[token].back().position.push_back(word_id);
			}
			else {
				FileList list;
				list.file_index = index;
				list.position.push_back(word_id);

				this->inverted_index[token].push_back(list);
			}

			this->memory_usage+=INDEX_LINE_SIZE;

			word_id++;

			if (this->memory_usage >= MEMORY_LIMITE){
				this->memory_dump();
			}
		}
	}

	for (string word : docs_words){
		this->vocabulary_order[this->vocabulary[word]].total_docs++;
	}
}

void InvertedIndex::memory_dump(){

	bool test;
	int count = 0, index_size = this->inverted_index.size();
	fstream f, sorted_f;

	f.open(INDEX_AUX_FILE_NAME, ios::out | ios::binary);

	// Generating tuples and saving in file
	// < word_id, doc_id, freq, pos >
	for (auto word : this->vocabulary){
		for (auto document : this->inverted_index[word.first]){
			int list_size = document.position.size();
			for (int pos : document.position){
				this->write_line(word.second, document.file_index, list_size, pos, f);
				count++;
			}
		}
	}

	f.close();

	this->inverted_index.clear();
	this->memory_usage = 0;

	f.open(INDEX_AUX_FILE_NAME, ios::in | ios::binary);
	sorted_f.open(INDEX_BACKUP_FILE_NAME+to_string(this->n_dumps)+".bin", ios::out | ios::binary);

	string value;
	vector<vector<int>> all_lines;

	// Loading tuples
	for (int i = 0; i < count; i++){
		vector<int> aux;

		test = this->read_line(f, aux);

		if (test){
			all_lines.push_back(aux);
		}
	}

	// Sorting tuples
	sort(begin(all_lines), end(all_lines),
		[](const vector<int>& A, vector<int>& B) {
			return (
				(A[0] < B[0]) ||									// Sorting by word id
				((A[0] == B[0]) && (A[1] < B[1])) ||				// Sorting by document id
				((A[0] == B[0]) && (A[1] == B[1]) && (A[3] < B[3]))	// Sorting by position
				);
		});

	// Saving sorted tuples
	for (vector<int> s : all_lines){
		this->write_line(s, sorted_f);
	}

	f.close();
	sorted_f.close();

	this->total_size_index += count;
	this->n_dumps++;
}

void InvertedIndex::sorted_index(){
	int value, i = 0;
	vector<int> aux(5);
	bool test, final = false;
	priority_queue<vector<int>, vector<vector<int>>, comparator> min_heap;

	if (this->memory_usage){
		memory_dump();
	}

	cout << "Total of files evaluated: " << this->total_docs << endl;
	cout << "Total tokens: " << this->total_size_index << " " << this->total_token << endl;
	cout << "Memory Limit: " << (MEMORY_LIMITE/INDEX_LINE_SIZE) << endl;
	cout << "Total of files: " << this->n_dumps << endl;


	while(i < this->n_dumps){
		int n_files;
		fstream out;

		// Testing wether is possible to open all files at once
		if ((this->n_dumps - i) <= (MEMORY_LIMITE/INDEX_LINE_SIZE) && ((this->n_dumps - i) < (MAX_OS_OPEN_FILE - 1000))){
			// If true, needs saving final sorted index
			n_files = this->n_dumps - i;
			out.open(INDEX_SORTED_FILE_NAME, ios::out | ios::binary);
			final = true;
		} else {
			// Intercalation
			n_files = ((MAX_OS_OPEN_FILE - 1) < (MEMORY_LIMITE/INDEX_LINE_SIZE) ? 
						MAX_OS_OPEN_FILE - 1 :
						(MEMORY_LIMITE/INDEX_LINE_SIZE));

			out.open(INDEX_BACKUP_FILE_NAME+to_string(this->n_dumps)+".bin", ios::out | ios::binary);
			this->n_dumps++;
		}

		

		fstream p[n_files];

		// Evaliating from t to i+n_files
		for (int j = 0; j < n_files; j++){
			p[j].open(INDEX_BACKUP_FILE_NAME+to_string(i)+".bin", ios::in | ios::binary);
			i++;

			test = this->read_line(p[j], aux);

			if (test){
				aux.push_back(j); // Locating read file
				min_heap.push(aux);
			}
		}

		this->reset_distance();

		while (min_heap.size()){

			// Getting smallest tuple
			aux = min_heap.top();
			min_heap.pop();

			// If last file:
			// add word to vocabulary;
			// do compression
			if (final){
				if (this->vocabulary_order.size() && this->vocabulary_order[0].pos == aux[0]){			
					// Each line occupates 16 bytes
					this->vocabulary_dump(this->vocabulary_order[0], out.tellp());
					this->vocabulary_order.pop_front();
				}

				// this->distance_diff(aux);
			}
			
			// Saving smallest tuple
			this->write_line(aux, out);

			// Test if file have finished
			if (!p[aux[4]].eof()){
				int position = aux[4];

				test = this->read_line(p[position], aux);

				// Test if file have finished
				if (test){
					aux.push_back(position);
					min_heap.push(aux);
				}
			}
		}


		for (int j = 0; j < n_files; j++){
			p[j].close();

			// Deleting temp files
			string filename = INDEX_BACKUP_FILE_NAME+to_string(i-n_files+j);
			remove(filename.c_str());				
		}

		out.close();
	}

	this->to_text();
}

void InvertedIndex::vocabulary_dump(Vocabulary item, streampos pos){

	fstream f;

	f.open(VOCABULARY_FILE_NAME, ios::out | ios::app);

	// word, index position, ni, N/ni
	f << item.word << " " << pos << " " << item.total_docs << " " << (float) this->total_docs/item.total_docs << endl;

	// cout << this->total_docs << " " << item.total_docs << endl;
		
	f.close();

}

vector<string> InvertedIndex::get_vocabulary(){
	string word;
	vector<string> vocabulary;
	fstream f;

	f.open(VOCABULARY_FILE_NAME, ios::in);

	if (f.is_open()){
		while (!f.eof()){
			Vocabulary item;
			f >> item.word >> item.pos >> item.total_docs ;

			vocabulary.push_back(item.word);
		}
	}

	f.close();

	return vocabulary;
}

void InvertedIndex::load_vocabulary(){
	fstream f;
	int word_index = 0;

	f.open(VOCABULARY_FILE_NAME, ios::in);

	if (f.is_open()){
		this->vocabulary_order = {};
		this->vocabulary = {};

		while (!f.eof()){
			Vocabulary item;
			float idf;

			// word, index position, ni, N/ni
			f >> item.word >> item.pos >> item.total_docs >> idf;

			if (item.word.size()){

				this->vocabulary[item.word] = word_index;
				this->vocabulary_order.push_back(item);

				word_index++;
			}
		}
	}

	f.close();
}

void InvertedIndex::load_index(){
	this->load_vocabulary();
}

vector<FileList> InvertedIndex::get_list(string& token){
	vector<FileList> list = {};
	vector<int> line = {-1,-1,-1,-1};
	ifstream f;
	string s = "";

	this->reset_distance();

	auto search = this->vocabulary.find(token);
	if (search != this->vocabulary.end()){
		string filename = INDEX_SORTED_FILE_NAME;
		f.open(filename+"_text");

		while(line[0] <= vocabulary[token] && !f.eof()){

			for (int i = 0; i < 4; i++){
				f >> s;
				line[i] = stoi(s);
			}

			this->distance_rest(line);

			if (line[0] == vocabulary[token]){
				FileList temp;
				int rep = line[2];
				temp.file_index = line[1];
				temp.position.push_back(line[3]);

				if (!f.eof()){
					for (int r = 0; r < rep - 1; r++ ){				
						for (int i = 0; i < 4; i++){
							f >> s;
							line[i] = stoi(s);
						}

						this->distance_rest(line);

						temp.position.push_back(line[3]);						
					}
				}

				list.push_back(temp);
			} else {
				for (int r = 0; r < line[2]-1; r++){
					for (int i = 0; i < 4; i++){
						f >> s;
					}
				}
			}
		}

	}

	return list;
}

void InvertedIndex::distance_diff(vector<int>& v){

	// v[0] = Term index
	// v[1] = Doc index
	// v[2] = Term freq at doc 
	// v[3] = Pos at doc

	if (v[1] != this->previous[1]){
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	if (v[0] != this->previous[0]){
		this->previous[1] = 0;
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	for (int i = 0; i < 4; i++){
		v[i] = v[i] - this->previous[i];
		this->previous[i] = this->previous[i] + v[i];

	}

}

void InvertedIndex::distance_rest(vector<int>& v){

	if (v[1] != 0){
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	if (v[0] != 0){
		this->previous[1] = 0;
		this->previous[2] = 0;
		this->previous[3] = 0;
	}

	for (int i = 0; i < 4; i++){
		v[i] = v[i] + this->previous[i];
		this->previous[i] = v[i];
	}

}

void InvertedIndex::rest(){
	ifstream f;
	vector<int> aux(4);
	int s;

	string filename = INDEX_SORTED_FILE_NAME;

	f.open(filename+"_text");

	this->reset_distance();

	while(!f.eof()){
		for (int i = 0; i < 4; i++){
			f >> s;
			aux[i] = s;
		}

		if (!f.eof()){
			distance_rest(aux);

			for (int i = 0; i < 3; i++){
				cout << aux[i] << " ";
			}

			cout << aux[3] << endl;
		}

	}

	f.close();
}

void InvertedIndex::to_text(){
	fstream output;
	fstream input;
	vector<int> line;
	bool test;

	string filename = INDEX_SORTED_FILE_NAME;

	output.open(filename+"_text", ios::out);
	input.open(filename, ios::in | ios::binary);

	test = this->read_line(input,line);

	while(test){
		for (int i = 0; i < line.size()-1; i++){
			output << line[i] << " ";
		}

		output << line[line.size()-1] << '\n';

		test = this->read_line(input,line);
	}


	input.close();
	output.close();
}