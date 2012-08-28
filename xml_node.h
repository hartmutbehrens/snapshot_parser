#ifndef XML_NODE_H
#define XML_NODE_H
#include <iostream>
#include <map>
#include <string>

class xml_node {
private:
	//members
	std::map<std::string,std::string> attributes;	
	//constructors not used
	xml_node(const xml_node &) {}								//pre-emptive definition, avoid copy construction for now
	xml_node & operator=(const xml_node &) { return *this; }	//pre-epmtive definition, avoid construction by assignment
public:
	//members
	std::string tag;
	std::string characters;
	std::string xp_id_fragment;
	std::string xp_fragment;
	//constructors
	xml_node(char *, std::map<std::string,std::string> &);
	//member functions
	void add_characters(char *);
	std::string * get_attribute(const char *);
	std::string to_string();
	//overloaded operators
	friend std::ostream & operator<<(std::ostream &, xml_node &);
	//destructor
	~xml_node();
};
#endif
