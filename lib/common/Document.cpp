#include "Document.h"

Document::Document(){
	this->url = "";
	this->text = "";
	this->links = {};
}

Document::Document(const string& doc, const string url){
	Document();
	this->url = url;

	LinkMap::instance()->add_value(url, true);

	this->parser(doc);
}

void Document::parser(const string& doc){
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
			}
		}

		if ((!it->isTag()) && (!it->isComment())) {
			this->text += it->text() + " ";
		} else {
			string tag_name = it->tagName();
			transform(tag_name.begin(), tag_name.end(), tag_name.begin(), ::tolower);
			if (tag_name == "a"){
				it->parseAttributes();

				pair<bool, std::string> attrib = it->attribute("rel");

				if(!(attrib.first == true && attrib.second == "nofollow")){
					attrib = it->attribute("href");
					string anchor_text;
					int children = it.number_of_children();
					for(int i=0; i<children; i++){
						it++;

						if(it == dom.end()){
							return;
						}

						if(!it->isTag()){
							anchor_text += it->text();
						}
					}
					unsigned int normal_url = LinkMap::instance()->get_value(htmlcxx::HTML::convert_link(attrib.second, url));

					// Initialize normal_url, in case it doesnt existe already
					if (this->links.find(normal_url) == this->links.end()) {
						this->links[normal_url] = "";
					}

					// Adds anchor text referent to normal_url
					this->links[normal_url] += anchor_text + " ";

					// Adds anchor text referent to document's text
					this->text += anchor_text + " ";
				}
			} else{
				if(tag_name == "title"){
					it++;
					if(!(it == dom.end())){
						this->title = it->text();
					}
				}
			}
		}
	}
}


// unsigned int Document::get_url(){
// 	return LinkMap::instance()->get_value(this->url);
// }

string Document::get_url(){
	return this->url;
}

string Document::get_text(){
	return this->text;
}

string Document::get_title(){
	return this->title;
}

// <URL, Anchor text>
unordered_map<unsigned int, string> Document::get_links(){
	return this->links;
}

void Document::print(){
	cout << "Printing doc" << endl;

	cout << "URL: " << this->url << endl;
	cout << "Title: " << this->title << endl;
	cout << "Content: " << this->text << endl;
	cout << "Links:" << endl;
	for (auto link : this->links){
		cout << '\t';
		cout << link.first << " => " << link.second << endl;

	}
	cout << endl;
}