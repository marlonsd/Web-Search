#include <html/ParserDom.h>
#include "Inverted_Index.h"
#include "func.h"			// Defines are here

void resetingOutputFiles();
void parsing(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords);
void parsing_anchor_text(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords);

int main(int argc, const char* argv[]) {  

	vector<string> files;
	fstream input, doc_id;
	string acc, url, last_read = "";
	int state = 0, file_index = 0;
	size_t found, alt_found;
	unordered_set<string> stopwords = load_stop_words(STOPWORDS_PATH);
	InvertedIndex index;
	double duration;
	Tokenizer t;

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

							// parsing_anchor_text(acc, t, stopwords);

							parsing(acc, t, stopwords);

							// index.indexing(t, file_index);

							file_index++;

							state = 1;
							acc = "";
							url = "";

							exit(0);

							string s;
							cout << endl << "-------------" << endl;
							cout << "Enter value: ";
							cin >> s;
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

	exit(0);
}

void resetingOutputFiles(){
	fstream output;
	
	output.open(INDEX_AUX_FILE_NAME, ios::out);
	output.close();

	output.open(INDEX_SORTED_FILE_NAME, ios::out);
	output.close();

	output.open(VOCABULARY_FILE_NAME, ios::out);
	output.close();
}

//Parse doc's html code
void parsing(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords){
	htmlcxx::HTML::ParserDom parser;
	tree<htmlcxx::HTML::Node> dom = parser.parseTree(doc);

	tree<htmlcxx::HTML::Node>::iterator it = dom.begin();

	for (; it != dom.end(); ++it) {
		if(it.node != 0 && dom.parent(it) != NULL){
			string tag_name = dom.parent(it)->tagName();
			transform(tag_name.begin(), tag_name.end(), tag_name.begin(), ::tolower);

			// Skipping code embedded in html
			if ((tag_name == "script") ||
				(tag_name == "noscript") ||
				(tag_name == "style") ||
				(tag_name == "textarea") ||
				(tag_name == "img")
				){
				it.skip_children();
				continue;
			} else {
				if (tag_name == "a"){
					cout << "-----" << endl;
					it->parseAttributes();
					cout << it->text() << endl;
					cout << it->closingText() << endl;
					std::map<std::string, std::string> attributes = it->attributes();

					for (auto i : attributes){
						cout << i.first << " " << i.second << endl;
					}
					cout << "-----" << endl << endl;
				}	
			}
		}

		if ((!it->isTag()) && (!it->isComment())) {
			t.addTokens(it->text(), stopwords);
		}
	}
}

void parsing_anchor_text(const string& doc, Tokenizer& t, const unordered_set<string>& stopwords){
	htmlcxx::HTML::ParserDom parser;
	tree<htmlcxx::HTML::Node> dom = parser.parseTree(doc);

	cout << dom << endl;

	tree<htmlcxx::HTML::Node>::iterator it = dom.begin();

	for (; it != dom.end(); ++it) {
		// if(it.node != 0 && dom.parent(it) != NULL){
		// 	string tag_name = dom.parent(it)->tagName();
		// 	transform(tag_name.begin(), tag_name.end(), tag_name.begin(), ::tolower);

		// 	// Skipping code embedded in html
		// 	if ((tag_name == "script") ||
		// 		(tag_name == "noscript") ||
		// 		(tag_name == "style") ||
		// 		(tag_name == "textarea")
		// 		){
		// 		it.skip_children();
		// 		continue;
		// 	}
		// }

			
	}
}