#include <iostream>
#include "xml_node.h"

xml_node::xml_node(char *ctag, std::map<std::string,std::string> & attrib) : attributes(attrib), tag(ctag) {
	xp_fragment = xp_id_fragment = "/" + tag;
	std::string *id = get_attribute("id");
	if (id != NULL) {
		xp_id_fragment += "[@id='" + *id + "']";
	}
}

void xml_node::add_characters(char *cchar) {
	std::cout << "adding: " << cchar << std::endl;
	characters.assign(cchar);
}

std::string * xml_node::get_attribute(const char * which) {
	std::map<std::string, std::string>::iterator it = attributes.find(which);
	if ( it != attributes.end() ) {
		return &it->second;
	}
	return NULL;
}


std::ostream & operator<<(std::ostream & os, xml_node & x) {
	os << x.xp_id_fragment;
	return os;
}

xml_node::~xml_node() {
}
