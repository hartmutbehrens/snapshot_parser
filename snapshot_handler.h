#ifndef SNAPSHOT_HANDLER_H
#define SNAPSHOT_HANDLER_H
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <array>
#include <iostream>
#include <list>
#include <string>
#include "xml_node.h"

namespace xc = xercesc;

class snapshot_handler : public xc::HandlerBase {
private:
	//members
	std::list<xml_node *> nodes;
	//constructors not used
	snapshot_handler(const snapshot_handler & ) {}								//pre-emptive definition, avoid copy construction
	snapshot_handler & operator=(const snapshot_handler & ) { return *this; }	//pre-emptive definition, avoid object creation by assignment
public:
	//constructors
	snapshot_handler();
	//destructios
	~snapshot_handler();
	//handlers for the SAX DocumentHandler interface
	//note: naming of methods inconsistent with own naming scheme
	void startElement(const XMLCh * const, xc::AttributeList &);
	void endElement(const XMLCh * const);
	void characters(const   XMLCh* const, const XMLSize_t);
	
	//handlers for the SAX ErrorHandler interface
	//note: naming of methods inconsistent with own naming scheme
	void warning(const xc::SAXParseException &);
	void error(const xc::SAXParseException &);
	void fatalError(const xc::SAXParseException &);
	//other methods
	std::string get_xpath();
	bool is_xpath(const char *);
	template <typename T>
	void message(const char * , const T & );
	
};

#endif