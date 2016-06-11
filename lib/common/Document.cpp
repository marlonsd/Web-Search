#include "Document.h"

Document::Document(){
	this->url = "";
	this->text = "";
	this->links = {};
}

Document::Document(const string& doc, const string url){
	Document();
	this->url = url;
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

					// cout << "Anchor Text: " << anchor_text << endl;

					string normal_url = htmlcxx::HTML::convert_link(attrib.second, url);
					// cout << "URL: " << normal_url << endl << endl;

					this->links[normal_url] = anchor_text;

					// if (links_.find(normal_url)==links_.end()) {
					//     links_[normal_url] = "";
					// }
					// links_[normal_url] = " ";
					// links_[normal_url] += anchor_text;
					// text_ += " ";
					// text_ += anchor_text;
				}
			}
		}
	}
}




string Document::get_url(){
	return this->url;
}

string Document::get_text(){
	return this->text;
}

// <URL, Anchor text>
unordered_map<string, string> Document::get_links(){
	return this->links;
}