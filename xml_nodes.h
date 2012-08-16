#ifndef XML_NODES_H
#define XML_NODES_H
#include <list>
#include <string>
#include "xml_node.h"

class xml_nodes {
private:
	//members
	std::list<xml_node *> nodes;
	std::string xpath;
	std::string xpath_with_id;
	std::string outstring;
	//constructors not used
	xml_nodes(const xml_nodes &) {}								//pre-emptive definition, avoid copy construction for now
	xml_nodes & operator=(const xml_nodes &) { return *this; }	//pre-epmtive definition, avoid construction by assignment
	//internal methods
	void shorten_outstring();
	void shorten_xpath();
	void shorten_xpath_with_id();

public:
	//constructors
	xml_nodes();
	//destructor
	~xml_nodes();
	//methods
	void push_back(xml_node *);
	xml_node * back();
	void remove_last();
	std::string current_xpath(bool with_id = false);
	std::string xml_nodes::current_outstring();
	//overloaded operators
	friend std::ostream & operator<<(std::ostream &, xml_nodes &);

};
#endif
