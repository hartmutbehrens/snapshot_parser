#ifndef XML_NODE_H
#define XML_NODE_H
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <iostream>
#include <map>
#include <string>

namespace xc = xercesc;

class xml_node {
private:
	//members
	std::string tag;
	std::string characters;
	std::map<std::string,std::string> attributes;	
	//constructors not used
	xml_node(const xml_node &) {}								//pre-emptive definition, avoid copy construction for now
	xml_node & operator=(const xml_node &) { return *this; }	//pre-epmtive definition, avoid construction by assignment
public:
	//constructors
	xml_node(const XMLCh * const, xc::AttributeList &);
	xml_node(const XMLCh * const, std::map<std::string,std::string> &);
	//member functions
	void add_characters(const XMLCh *const);
	std::string get_attribute(const char *);
	std::string get_characters();
	std::string get_tag();
	//overloaded operators
	friend std::ostream & operator<<(std::ostream &, xml_node &);
	//destructor
	~xml_node();
};
#endif
