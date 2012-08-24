#include <iostream>
#include "xml_node.h"

xml_node::xml_node(char *ctag, std::map<std::string,std::string> & attrib) : attributes(attrib), tag(ctag) {
}

void xml_node::add_characters(char *cchar) {
	characters.assign(cchar);
}

std::string xml_node::get_characters() const {
	return characters;
}

std::string xml_node::get_attribute(const char * which) {
	std::string value;
	std::map<std::string, std::string>::iterator it = attributes.find(which);
	if ( it != attributes.end() ) {
		value = it->second;
	}
	return value;
}

std::string xml_node::get_tag() const {
	return tag;
}

std::ostream & operator<<(std::ostream & os, xml_node & x) {
	os << "/" << x.get_tag();
	std::string id = x.get_attribute("id");
	if (!id.empty()) {
		os << "[@id='" << id << "']";
	}
	return os;
}

xml_node::~xml_node() {
}
