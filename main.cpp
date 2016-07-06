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
	fstream input, doc_id, doc_title;
	string acc, url, last_read = "", aux, buffer, temp;
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
	doc_title.open(DOC_TITLE_FILE_NAME, ios::out);


	// cout << "reading (ms),tokenizing (ms),indexing (ms),#files,total time (s), sorting, voc dump" << endl;

	for (string file : files){
		input.open(DIRNAME+file, ios::in);

		cout << "File: " << DIRNAME+file << endl;

		state = 0;

		if (input.is_open()){
		
			aux="";

			while(!input.eof() || buffer.size() > 0){
				
				input >> aux;

				if (aux.size() > 0){
					buffer+=aux+" ";
				}
				// cout << aux;

				if (state == 0){
					found = buffer.find("|||");

					if (found != std::string::npos){
						buffer.erase(0,found+3);

						state = 1;
					} else {
						if(input.eof()){
							buffer = "";
						}
					}
				}

				if (state == 1){

					// if (buffer.size() > 0){
					// 	while(isspace(buffer.at(0))){
					// 		buffer.erase(0,1);
					// 	}
					// }

					buffer.erase(buffer.begin(), std::find_if(buffer.begin(), buffer.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

					found = buffer.find("|");

					if (found != std::string::npos){
						// cout << "State 1" << endl;
						url = buffer;
						url.erase(found, buffer.size());
						// cout << url;
						buffer.erase(0, found+1);
						// cout << "\t" << buffer << endl;
						state = 2;
					}
				}

				if (state == 2){
					// cout << "State 2" << endl;

					temp = buffer;
					transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

					found = temp.find("<html");
					alt_found = temp.find("<!doctype");

					if (found != std::string::npos || alt_found != std::string::npos){
						temp = "";
						state = 3;

						if (alt_found != std::string::npos){
							found = alt_found;
						}

						if(found > 0){
							buffer.erase(0,found);
							// cout << "\t" << buffer << endl;
						}

						// acc = buffer;
					}
					temp = "";
				}

				if (state == 3){
					// cout << "State 3" << endl;
					// acc+=buffer;
					temp = buffer;
					transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

					found = temp.find("</html>");

					if (found != std::string::npos){
						temp = "";
						acc = buffer;
						acc.erase(found+7, acc.size());
						buffer.erase(0,found+7);
						// cout << buffer << endl;

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

						state = 0;
						acc = "";
						url = "";
						aux = "";
						doc_title << doc.get_title() << endl;
						// cout << doc.get_title() << endl;
						doc.print();
						// exit(0);
					}
					temp = "";
				}

			}
		}

		input.close();
		cout << "File: " << DIRNAME+file << " finished" << endl;
		index.sorted_index("temp/");
		anchor_index.sorted_index("temp/");

		network.dump("temp/");
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
