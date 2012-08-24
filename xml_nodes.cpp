#include "xml_nodes.h"

//constructors
xml_nodes::xml_nodes() {}
//destructor
xml_nodes::~xml_nodes() {}
//methods
void xml_nodes::push_back(xml_node *xn) {
	//update xpaths
	std::string tag = xn->get_tag();
	std::string id = xn->get_attribute("id");
	xpath = xpath + "/" + tag;
	xpath_with_id = xpath_with_id + "/" + tag;
	if (!id.empty()) {
		if (outstring.length() > 0) {
			outstring += "\t";
		}
		xpath_with_id = xpath_with_id + "[@id='" + id + "']";
		outstring = outstring + tag + "=" + id;
	}
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
	std::string id = xn->get_attribute("id");
	if (!id.empty()) {												//shortening only required when id is present
		size_t pos = outstring.find_last_of("\t");
		if (pos != std::string::npos) {
			outstring = outstring.substr(0,pos);
		}
		else {
			outstring.clear();
		}
	}
}

void xml_nodes::shorten_xpath() {
	xml_node *xn = nodes.back();							//get pointer to last xml_node
	std::string tag = xn->get_tag();
	int len = tag.length() + 1;							//number of characters to remove from xpath +1 for the "/" character
	xpath = xpath.substr(0,xpath.length() - len);	
}

void xml_nodes::shorten_xpath_with_id() {
	xml_node *xn = nodes.back();							//get pointer to last xml_node
	std::string tag = xn->get_tag();

	int len = tag.length() + 1;
	int id_len = 0;
	
	std::string id = xn->get_attribute("id");
	if (!id.empty()) {
		id_len = id.length() + 8;						//also include the [@id='...'] bits
	}
	xpath_with_id = xpath_with_id.substr(0,xpath_with_id.length() - (len + id_len) );
}

std::ostream & operator<<(std::ostream & os, xml_nodes & xn) {
	std::string tag = xn.back()->get_tag();
	std::string ch = xn.back()->get_characters();
	os << xn.current_outstring();
	if (!ch.empty()) {
		os << "\t" << tag << "=" << ch;
	}
	return os;
}
