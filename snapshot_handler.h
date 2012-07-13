#ifndef SNAPSHOT_HANDLER_H
#define SNAPSHOT_HANDLER_H
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "xml_nodes.h"

namespace xc = xercesc;

class snapshot_handler : public xc::HandlerBase {
private:
	//members
	//std::list<xml_node *> nodes;												//path of xml_nodes that have been seen leading up to and including current xml_node - e.g. /snapshot/RNC/INode will include 3 nodes
	xml_nodes nodes;
	std::map<std::string,int> wanted;											//map of xpaths that need to be retrieved
	//constructors not used
	snapshot_handler(const snapshot_handler & ) {}								//pre-emptive definition, avoid copy construction
	snapshot_handler & operator=(const snapshot_handler & ) { return *this; }	//pre-emptive definition, avoid object creation by assignment
public:
	//constructors
	snapshot_handler(std::vector<std::string> &);
	//destructor
	~snapshot_handler();
	//handlers for the SAX DocumentHandler interface - override HandlerBase empty method
	void startElement(const XMLCh * const, xc::AttributeList &);
	void endElement(const XMLCh * const);
	void characters(const   XMLCh* const, const XMLSize_t);
	//handlers for the SAX ErrorHandler interface - override HandlerBase empty method
	void warning(const xc::SAXParseException &);
	void error(const xc::SAXParseException &);
	void fatalError(const xc::SAXParseException &);
	//own methods
	template <typename T>
	void message(const char * , const T & );
	
};

#endif