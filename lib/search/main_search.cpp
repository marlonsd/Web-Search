#include "../common/func.h"			// Defines are here
#include "../common/Document.h"
#include "../common/Stopwords.h"

#include "../indexer/Inverted_Index.h"
#include "../indexer/Inverted_Index_Anchor.h"

#include "../search/graph.h"
#include "../search/search.h"

int main(int argc, const char* argv[]) {  
	string query, token;
	std::size_t found;
	InvertedIndex index;
	Tokenizer tokens;
	vector<FileList> list;
	vector<int> all_files;
	bool first = true;
	vector<string> doc_id;
	Search* searcher;

	searcher = new Search();
}