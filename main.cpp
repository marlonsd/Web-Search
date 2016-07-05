#include "lib/common/func.h"			// Defines are here
#include "lib/common/Document.h"
#include "lib/common/Stopwords.h"

#include "lib/indexer/Inverted_Index.h"
#include "lib/indexer/Inverted_Index_Anchor.h"

#include "lib/search/graph.h"
#include "lib/search/pagerank.h"

#include <html/ParserDom.h>
#include <html/utils.h>
#include <html/Uri.h>

void resetingOutputFiles();
void parsing(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords);
void parsing_anchor_text(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords, string url);

Stopwords *Stopwords::s_instance = 0;
LinkMap *LinkMap::s_instance = 0;

int main(int argc, const char* argv[]) {
	vector<string> files;
	fstream input, doc_id;
	string acc, url, last_read = "", aux;
	int state = 0, file_index = 0;
	size_t found, alt_found;
	char c;
	// unordered_set<string> stopwords = Stopwords::instance()->get_value();
	InvertedIndex index;
	InvertedIndexAnchor anchor_index;
	double duration;
	Graph network;
	// Tokenizer t;

	/* Search */
	// string token = "papa";

	// cout << "Loading vocabulary" << endl;
	// index.load_vocabulary();
	// cout << "Vocabulary loaded" << endl;

	// cout << "Consulting query \""<< token << "\"" << endl;
	// vector<FileList> query = index.get_list(token);
	// cout << "Done consulting" << endl;

	// for (FileList list : query){
	// 	cout << "Document #" << list.file_index << ":\n\t";
	// 	for (int id : list.position){
	// 		cout << id << " ";
	// 	}
	// 	cout << endl << endl;
	// }

	// exit(0);
	/* */

	resetingOutputFiles();

	files = list_dir_files(DIRNAME);

	doc_id.open(DOC_ID_FILE_NAME, ios::out);

	// cout << "reading (ms),tokenizing (ms),indexing (ms),#files,total time (s), sorting, voc dump" << endl;

	for (string file : files){
		input.open(DIRNAME+file, ios::in);

		cout << "File: " << DIRNAME+file << endl;

		state = 0;

		if (input.is_open()){
			while (!input.eof()){
				input.get(c);
				aux += c;

				// cout << "-- " << aux << " " << state << endl;
				// Finite Automata. See report's Figure 3
				switch(state){
					case 0:
						if (aux == "|||"){
							state = 1;
							aux = "";
						}

						break;

					case 1:
						if (c == '|'){
							state = 2;
							aux = "";
						} else {
							url+=c;
						}

						break;

					case 2:
						transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

						found = aux.find("<html");
						alt_found = aux.find("<!doctype");


						if (found != std::string::npos || alt_found != std::string::npos){
							while(found != 0 && alt_found != 0){
								aux.erase(0,1);

								found = aux.find("<html");
								alt_found = aux.find("<!doctype");

							}

							acc = aux;
							state = 3;
							aux = "";

						}

						found = aux.find("|||");

						if (found != std::string::npos && found >= (aux.size() - 3)){
							state = 1;
							url = "";
							aux = "";
						}

						break;

					case 3:

						found = aux.find("</html>");

						acc+=c;

						// 7 is "</html>" size
						if (found != std::string::npos && (aux.size() - found) == 7){
							state = 4;
							aux = "";
						}

						break;

					case 4:

						found = aux.find("|||");

						if (found != std::string::npos && found >= (aux.size() - 3)){

							if(url.back() == ' '){
								url.pop_back();
							}

							doc_id << url << endl;

							// parsing_anchor_text(acc, t, stopwords, url);

							// parsing(acc, t, stopwords);

							Document doc(acc, url);

							network.add_url(doc);

							// Tokenizer t(doc.get_text(), Stopwords::instance()->get_value());
							index.indexing(doc, file_index);
							anchor_index.indexing(doc);

							file_index++;

							state = 1;
							acc = "";
							url = "";
							aux = "";
							doc.print();
						}

						break;
				}
			}
		}

		input.close();
	}

	doc_id.close();

	cout << "Done indexing" << endl;

	index.sorted_index();
	anchor_index.sorted_index();

	// network.print();
	network.dump();

	Pagerank pagerank;

	pagerank.dump();

	// LinkMap::instance()->print();


	return 0;
}

void resetingOutputFiles(){
	ofstream output;

	output.open(INDEX_AUX_FILE_NAME, ios::out);
	output.close();

	output.open(INDEX_SORTED_FILE_NAME, ios::out);
	output.close();

	output.open(VOCABULARY_FILE_NAME, ios::out);
	output.close();

	output.open(ANCHOR_DOC_ID_FILE_NAME, ios::out);
	output.close();
}
