#ifndef LINKMAP_H
#define LINKMAP_H

#include "../common/func.h"

using namespace std;

struct ProcessedFile{
	bool processed;
	unsigned int id;
};

class LinkMap {
private:
	unordered_map<string, ProcessedFile> link_map;
	vector<string> inverse;
	unsigned int count;

	static LinkMap *s_instance;

	LinkMap();

	void clear();

public:

	void add_value(string url, bool processed = false);

	unsigned int get_value(const string url);
	string get_value(unsigned int url);

	ProcessedFile get_node(string url);

	bool get_processed_situation(string url);

	void load(string rest_path = "");

	void dump();

	void print();

	static LinkMap *instance(){
		if (!s_instance){
			s_instance = new LinkMap();
		}

		return s_instance;
	}

};

#endif