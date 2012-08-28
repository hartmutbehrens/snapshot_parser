#include "xml_nodes.h"

//constructors
xml_nodes::xml_nodes() {}
//destructor
xml_nodes::~xml_nodes() {}
//methods
void xml_nodes::push_back(xml_node *xn) {
	//update xpaths
	std::string tag = xn->get_tag();
	std::string *id = xn->get_attribute("id");
	xpath = xpath + "/" + tag;
	xpath_with_id = xpath_with_id + "/" + tag;
	if (id != NULL) {
		if (outstring.length() > 0) {
			outstring += "\t";
		}
		xpath_with_id = xpath_with_id + "[@id='" + *id + "']";
		outstring = outstring + tag + "=" + *id;
	}
	//add xml_node to list
	nodes.push_back(xn);
}

xml_node * xml_nodes::back() {
	return nodes.back();
}

xml_node * xml_nodes::remove_last() {
	//shorten_xpath();
	//shorten_xpath_with_id();
	//shorten_outstring();
	shorten_strings();
	xml_node *xn = nodes.back();			//get pointer to last xml_node
	nodes.pop_back();						//remove pointer to last node
	return xn;
}

void xml_nodes::shorten_strings() {
	xml_node *xn = nodes.back();

	std::string tag = xn->get_tag();
	int len = tag.length() + 1;
	xpath = xpath.substr(0,xpath.length() - len);		//shorten xpath

	//std::cout << "d xp: " << xpath << std::endl;

	std::string *id = xn->get_attribute("id");
	int id_len = 0;
	if (id != NULL) {
		//outstring shortening
		size_t pos = outstring.find_last_of("\t");
		if (pos != std::string::npos) {
			outstring = outstring.substr(0,pos);
		}
		else {
			outstring.clear();
		}
		//std::cout << "d co: " << outstring << std::endl;
		id_len = id->length() + 8;						//also include the [@id='...'] bits
	}
	//xpath with id shortening
	xpath_with_id = xpath_with_id.substr(0,xpath_with_id.length() - (len + id_len) );
}

std::string * xml_nodes::current_xpath(bool with_id) {
	if (with_id) {
		return &xpath_with_id;
	}
	else {
		return &xpath;
	}
}

std::string * xml_nodes::current_outstring() {
	return &outstring;
}

std::ostream & operator<<(std::ostream & os, xml_nodes & xn) {
	std::string tag = xn.back()->get_tag();
	std::string ch = xn.back()->get_characters();
	std::string *co = xn.current_outstring();
	os << *co;
	if (!ch.empty()) {
		os << "\t" << tag << "=" << ch;
	}
	return os;
}
