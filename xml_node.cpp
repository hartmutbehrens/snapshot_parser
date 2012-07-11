#include <iostream>
#include <string>
#include "xml_node.h"

xml_node::xml_node(const XMLCh *const name, xc::AttributeList & attributes) {
	id = characters = NULL;							//initialize pointers that might not be populated with xml data
	tag = xc::XMLString::transcode(name);
	const XMLCh *ident = attributes.getValue("id");
	if (ident) {
		id = xc::XMLString::transcode(ident);
	}
}

bool xml_node::is_tag(const char * value) {
	bool same = false;
	if (strcmp(tag,value)== 0) {
		same = true;
	}
	return same;
}

bool xml_node::is_id(const char * value) {
	bool same = false;
	if (strcmp(id,value)== 0) {
		same = true;
	}
	return same;
}

bool xml_node::has_characters() {
	bool has = false;
	if (characters) {
		has = true;
	}
	return has;
}

char * xml_node::get_characters() {
	char *pstr = NULL;
	if (characters) {
		pstr = new char[std::strlen(characters)+1];
		std::strcpy(pstr,characters);
	}
	return pstr;
}

char * xml_node::get_tag() {
	char *pstr = NULL;
	if (tag) {
		pstr = new char[std::strlen(tag)+1];
		std::strcpy(pstr,tag);
	}
	return pstr;
}

std::ostream & operator<<(std::ostream & os, const xml_node & x) {
	os << "/" << x.tag;
	if (x.id) {
		os << "[@id='" << x.id << "']";
	}
	//if (x.characters) {
	//	os << " characters=" << x.characters;
	//}
	return os;
}

xml_node::~xml_node() {
	xc::XMLString::release(&tag);
	if (id) {
		xc::XMLString::release(&id);
	}
	if (characters) {
		xc::XMLString::release(&characters);
	}
}