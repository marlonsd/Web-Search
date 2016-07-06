#ifndef FUNC_H
#define FUNC_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <dirent.h>

#define MEMORY_LIMITE 1000000000 // (bytes)
// #define MEMORY_LIMITE 160 // (bytes)

/* <word id, doc id, frequency of word, position>
 * <int, int, int, int>
 * 4*4
 * 36
*/
#define INDEX_LINE_SIZE 32

#define LOCAL_VOCABULARY_SIZE 30000 //(bytes)

#define VOCABULARY_FILE_NAME "info/vocabulary"
#define DOC_ID_FILE_NAME "info/doc_id"
#define DOC_TITLE_FILE_NAME "info/doc_title"
#define DOC_WD_FILE_NAME "info/w_d"

#define INDEX_SORTED_FILE_NAME "info/sorted_index"

#define PAGERANK_FILENAME "info/pagerank"


#define ANCHOR_VOCABULARY_FILE_NAME "info/vocabulary_anchor"
#define ANCHOR_DOC_ID_FILE_NAME "info/doc_id_anchor"
#define ANCHOR_DOC_TITLE_FILE_NAME "info/doc_title_anchor"
#define ANCHOR_DOC_WD_FILE_NAME "info/w_d_anchor"

#define ANCHOR_INDEX_SORTED_FILE_NAME "info/sorted_index_anchor"

#define STOPWORDS_PATH "info/stopwords"


using namespace std;

struct FileList {
	int file_index;
	vector<int> position;

	bool operator==(const FileList &other) const {
		return (file_index == other.file_index
				&& position == other.position);
	}
};

void split(const string& s, char c, vector<string>& v);
void cleaningWord(string& str);
vector<string> list_dir_files(string path);
unordered_set<string> load_stop_words(string path);
string getNormalizedUrl(const string url);

// unsigned int link_map(string url);

#endif
