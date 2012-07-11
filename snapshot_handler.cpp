#include "snapshot_handler.h"
#include "xml_node.h"
//constructor
snapshot_handler::snapshot_handler() {}
//destructor
snapshot_handler::~snapshot_handler() {}

//handlers for the SAX DocumentHandler interface
void snapshot_handler::startElement(const XMLCh * const name, xc::AttributeList &  attributes) {
	
	xml_node *xn = new xml_node(name,attributes);
	if ( (*xn).is_tag("RNC") ) {
		std::cout << *xn;
	}
	delete xn;
	
}

void snapshot_handler::endElement(const XMLCh * const name) {
	char *tag = xc::XMLString::transcode(name);
	//if ( xc::XMLString::equals(tag,"RNC") ) {
	//	std::cout << "RNC End element found " << std::endl;
	//}
	xc::XMLString::release(&tag);
}

void snapshot_handler::characters(const XMLCh* const characters, const XMLSize_t length) {
}

//handlers for the SAX ErrorHandler interface
//note: naming of methods inconsistent with own naming scheme
void snapshot_handler::error(const xc::SAXParseException& e) {
	snapshot_handler::message("Error", e);
}

void snapshot_handler::fatalError(const xc::SAXParseException& e) {
	snapshot_handler::message("Fatal Error", e);
}

void snapshot_handler::warning(const xc::SAXParseException& e) {
	snapshot_handler::message("Warning", e);
}

template <typename T>
void snapshot_handler::message(const char * which, const T & exception) {
	char * id = xc::XMLString::transcode(exception.getSystemId());
	char * msg = xc::XMLString::transcode(exception.getMessage());
	std::cerr << std::endl << which << " at file " << id << ", line " << exception.getLineNumber() << ", char " << exception.getColumnNumber() << "\n  Message: " << msg << std::endl;
	xc::XMLString::release(&id);
	xc::XMLString::release(&msg);
}