#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <deque>
#include "../common/func.h"

#include <html/ParserDom.h>
#include <html/utils.h>
#include <html/Uri.h>


using namespace std;

class Document{
private:
	string url;
	string text;
	string title;
	unordered_map<string, string> links; 		// <URL, Anchor text>

	void parser(const string& doc);

public:
	Document();
	Document(const string& doc, const string url);

	string get_url();
	string get_text();
	string get_title();
	unordered_map<string, string> get_links();	// <URL, Anchor text>

};

#endif