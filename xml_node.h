#ifndef XML_NODE_H
#define XML_NODE_H
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <iostream>

namespace xc = xercesc;

class xml_node {
private:
	//members
	char *tag;
	char *id;
	char *characters;
	//constructors not used
	xml_node(const xml_node &) {}								//pre-emptive definition, avoid copy construction for now
	xml_node & operator=(const xml_node &) { return *this; }	//pre-epmtive definition, avoid construction by assignment
public:
	//constructors
	xml_node(const XMLCh * const, xc::AttributeList &);
	//member functions
	bool is_tag(const char *);
	bool is_id(const char *);
	//overloaded operators
	friend std::ostream & operator<<(std::ostream &, const xml_node &);
	//destructor
	~xml_node();
};
#endif
