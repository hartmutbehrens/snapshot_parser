#include "xml_nodes.h"

//constructors
xml_nodes::xml_nodes() {}
//destructor
xml_nodes::~xml_nodes() {}
//methods

void xml_nodes::push_back(xml_node *xn) {
	//update xpaths
	xpath += xn->xp_fragment;
	xpath_with_id += xn->xp_id_fragment;
	//add xml_node to list
	nodes.push_back(xn);
}

xml_node * xml_nodes::back() {
	return nodes.back();
}

xml_node * xml_nodes::remove_last() {
	shorten_strings();
	xml_node *xn = nodes.back();			//get pointer to last xml_node
	nodes.pop_back();						//remove pointer to last node
	return xn;
}

void xml_nodes::shorten_strings() {
	xml_node *xn = nodes.back();
	//xpath shortening
	xpath = xpath.substr(0,xpath.length() - xn->xp_fragment.length());		//shorten xpath
	xpath_with_id = xpath_with_id.substr(0,xpath_with_id.length() - xn->xp_id_fragment.length());
}


std::ostream & operator<<(std::ostream & os, xml_nodes & xn) {
	for(std::list<xml_node *>::iterator it = xn.nodes.begin() ; it != xn.nodes.end(); it++) {
		std::string *id = (*it)->get_attribute("id");
		if (id != NULL) {
			os << (*it)->tag << "=" << *id << "\t";
		}
	}
	xml_node *back = xn.back();
	if (!back->characters.empty()) {
		os << back->tag << "=" << back->characters;
	}
	return os;
}
