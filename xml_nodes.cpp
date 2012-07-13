#include "xml_nodes.h"

//constructors
xml_nodes::xml_nodes() {}
//destructor
xml_nodes::~xml_nodes() {}
//methods
void xml_nodes::push_back(xml_node *xn) {
	//update xpaths
	char * tag = (*xn).get_tag();
	char * id = (*xn).get_id();
	xpath = xpath + "/" + tag;
	xpath_with_id = xpath_with_id + "/" + tag;
	if (id) {
		if (outstring.length() > 0) {
			outstring += "\t";
		}
		xpath_with_id = xpath_with_id + "[@id='" + id + "']";
		outstring = outstring + tag + "=" + id;
		delete id;
	}
	delete tag;
	//add xml_node to list
	nodes.push_back(xn);
}

xml_node * xml_nodes::back() {
	return nodes.back();
}

void xml_nodes::remove_last() {
	shorten_xpath();
	shorten_xpath_with_id();
	shorten_outstring();
	xml_node *xn = nodes.back();			//get pointer to last xml_node
	delete xn;
	nodes.pop_back();						//remove pointer to last node
}

std::string xml_nodes::current_xpath(bool with_id) {
	if (with_id) {
		return xpath_with_id;
	}
	else {
		return xpath;
	}
}

std::string xml_nodes::current_outstring() {
	return outstring;
}

void xml_nodes::shorten_outstring() {
	xml_node *xn = nodes.back();							//get pointer to last xml_node
	char * id = (*xn).get_id();
	if (id) {												//shortening only required when id is present
		char * tag = (*xn).get_tag();
		int len = std::strlen(tag) + 1;
		int id_len = std::strlen(id);
		if (nodes.size() > 1) {
			id_len++;										//account for tab character;
		}
		outstring = outstring.substr(0,outstring.length() - (len + id_len));
		delete id;
		delete tag;
	}
	
}

void xml_nodes::shorten_xpath() {
	xml_node *xn = nodes.back();							//get pointer to last xml_node
	char * tag = (*xn).get_tag();
	int len = std::strlen(tag) + 1;							//number of characters to remove from xpath +1 for the "/" character
	delete tag;
	xpath = xpath.substr(0,xpath.length() - len);	
}

void xml_nodes::shorten_xpath_with_id() {
	xml_node *xn = nodes.back();							//get pointer to last xml_node
	char * tag = (*xn).get_tag();

	int len = std::strlen(tag) + 1;
	int id_len = 0;
	char * id = (*xn).get_id();
	if (id) {
		id_len = std::strlen(id) + 8;						//also include the [@id='...'] bits
		delete id;
	}
	delete tag;
	xpath_with_id = xpath_with_id.substr(0,xpath_with_id.length() - (len + id_len) );
}

std::ostream & operator<<(std::ostream & os, xml_nodes & xn) {
	char *tag = xn.back()->get_tag();
	char *ch = xn.back()->get_characters();
	os << xn.current_outstring() + "\t" + tag;
	if (ch) {
		os << "=" << ch;
		delete ch;
	}
	delete tag;
	return os;
}