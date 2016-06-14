#include "lib/common/func.h"			// Defines are here
#include "lib/common/Document.h"
#include "lib/common/Stopwords.h"

#include "lib/indexer/Inverted_Index.h"

#include "lib/search/graph.h"

#include <html/ParserDom.h>
#include <html/utils.h>
#include <html/Uri.h>

void resetingOutputFiles();
void parsing(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords);
void parsing_anchor_text(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords, string url);

Stopwords *Stopwords::s_instance = 0;

int main(int argc, const char* argv[]) {  
	vector<string> files;
	fstream input, doc_id;
	string acc, url, last_read = "";
	int state = 0, file_index = 0;
	size_t found, alt_found;
	unordered_set<string> stopwords = Stopwords::instance()->get_value();
	InvertedIndex index;
	InvertedIndex anchor_index;
	double duration;
	// Graph network;
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

		if (input.is_open()){
			while (!input.eof()){
				string aux;
				input >> aux;
				// Finite Automata. See report's Figure 3
				switch(state){
					case 0:
						if (aux == "|||"){
							state = 1;
						}

						break;

					case 1:
						if (aux == "|"){
							state = 2;
						} else {
							url+=aux+" ";
						}

						break;

					case 2:
						transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

						found = aux.find("<html");
						alt_found = aux.find("<!doctype");

						if ((found != std::string::npos && found == 0) ||
							(alt_found != std::string::npos && alt_found == 0)){
							acc = aux+" ";
							state = 3;
						}

						if (aux == "|||"){
							state = 1;
							url = "";
						}

						break;

					case 3:

						found = aux.find("</html>");

						acc+=aux+" ";

						// 7 is "</html>" size
						if (found != std::string::npos && (aux.size() - found) == 7){
							state = 4;
						}

						break;

					case 4:

						if (aux == "|||"){

							doc_id << url << endl;

							// parsing_anchor_text(acc, t, stopwords, url);

							// parsing(acc, t, stopwords);

							Document doc(acc, url);
							
							// network.add_url(doc);

							Tokenizer t(doc.get_text(), stopwords);
							index.indexing(t, file_index);

							for (auto link : doc.get_links()){
								Tokenizer l(link.second, stopwords);
								// TODO: Change URLs id
								anchor_index.indexing(l, file_index);
							}

							file_index++;

							state = 1;
							acc = "";
							url = "";
						}

						break;
				}
			}
		}

		input.close();
	}

	doc_id.close();

	cout << "Done indexing" << endl;

	// index.vocabulary_dump();
	index.sorted_index();
	anchor_index.sorted_index();

	exit(0);
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