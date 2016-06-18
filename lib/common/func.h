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
#include <dirent.h>

#define MEMORY_LIMITE 250000000 // (bytes)
// #define MEMORY_LIMITE 160 // (bytes)

/* <word id, doc id, frequency of word, position>
 * <int, int, int, int>
 * 4*4 
 * 36
*/
#define INDEX_LINE_SIZE 32

#define LOCAL_VOCABULARY_SIZE 30000 //(bytes)

#define DIRNAME "util/htmls/"

#define STOPWORDS_PATH "util/stopwords/"

// Regular text
#define INDEX_AUX_FILE_NAME "util/index/aux_index.bin"
#define INDEX_BACKUP_FILE_NAME "util/index/split/backup_index"
#define INDEX_SORTED_FILE_NAME "util/index/sorted_index.bin"

#define VOCABULARY_FILE_NAME "util/index/vocabulary"

#define DOC_ID_FILE_NAME "util/index/doc_id"

// Anchor text
#define ANCHOR_INDEX_AUX_FILE_NAME "util/index/anchor/aux_index.bin"
#define ANCHOR_INDEX_BACKUP_FILE_NAME "util/index/anchor/split/backup_index"
#define ANCHOR_INDEX_SORTED_FILE_NAME "util/index/anchor/sorted_index.bin"

#define ANCHOR_VOCABULARY_FILE_NAME "util/index/anchor/vocabulary"
 
#define ANCHOR_DOC_ID_FILE_NAME "util/index/anchor/doc_id"

#define GRAPH_FILENAME "util/pagerank/graph"

// Max OS open files
#define MAX_OS_OPEN_FILE 4000


using namespace std;

struct comparator {
	bool operator()(vector<int> A, vector<int> B) {
		return (
				(A[0] > B[0]) ||									// Sorting by word id
				((A[0] == B[0]) && (A[1] > B[1])) ||				// Sorting by document id
				((A[0] == B[0]) && (A[1] == B[1]) && (A[3] > B[3]))	// Sorting by position
				);
	}
};

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
string getNormalizedUrl(string url);

// unsigned int link_map(string url);

#endif
