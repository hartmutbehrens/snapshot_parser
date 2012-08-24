#include <iostream>
#include "xml_node.h"

xml_node::xml_node(const XMLCh *const name, xc::AttributeList & attrib) {
	char *ctag = xc::XMLString::transcode(name);
	tag.assign(ctag);
	xc::XMLString::release(&ctag);

	for (XMLSize_t i = 0; i < attrib.getLength(); i++) {
		char *name = xc::XMLString::transcode(attrib.getName(i));
		char *value = xc::XMLString::transcode(attrib.getValue(i));
		std::string n(name);
		std::string v(value);
		attributes[n] = v;
		xc::XMLString::release(&name);
		xc::XMLString::release(&value);
	}
	//std::cout << "map:" <<std::endl;
	//for(std::map<std::string,std::string>::iterator it = attributes.begin() ; it != attributes.end(); it++) {
	//	std::cout << it->first << " : " << it->second << std::endl;
	//}
}

xml_node::xml_node(const XMLCh * const name, std::map<std::string,std::string> & attrib) : attributes(attrib) {
	char *ctag = xc::XMLString::transcode(name);
	tag.assign(ctag);
	xc::XMLString::release(&ctag);
}

void xml_node::add_characters(const XMLCh *const ch) {
	char *cchar = xc::XMLString::transcode(ch);
	characters.assign(cchar);
	xc::XMLString::release(&cchar);
}

std::string xml_node::get_characters() {
	return characters;
}

std::string xml_node::get_attribute(const char * which) {
	std::string value;
	std::map<std::string, std::string>::iterator it = attributes.find(which);
	if ( it != attributes.end() ) {
		value = it->second.c_str();
	}
	return value;
}

std::string xml_node::get_tag() {
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
