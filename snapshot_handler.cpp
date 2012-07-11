#include "snapshot_handler.h"
#include <algorithm>
#include <iterator>


//constructor
snapshot_handler::snapshot_handler() {}
//destructor
snapshot_handler::~snapshot_handler() {}

//handlers for the SAX DocumentHandler interface
void snapshot_handler::startElement(const XMLCh * const name, xc::AttributeList &  attributes) {
	xml_node *xn = new xml_node(name,attributes);
	nodes.push_back(xn);
	
}

void snapshot_handler::endElement(const XMLCh * const name) {
	xml_node *xn = nodes.back();		//get pointer to last xml_node
	nodes.pop_back();					//pop pointer off
	delete xn;							//free memory
}

void snapshot_handler::characters(const XMLCh* const characters, const XMLSize_t length) {
}

std::string snapshot_handler::get_xpath() {
	std::string xpath;
	std::list<xml_node *>::iterator it;
	for(it = nodes.begin(); it != nodes.end(); ++it) {
		xpath = xpath + "/" + (**it).get_tag();
	}
	return xpath;
}

bool snapshot_handler::is_xpath(const char *to_compare) {
	bool isval = false;
	std::string xpath = get_xpath();
	if (xpath.compare(to_compare) == 0) {
		isval = true;
	}
	return isval;
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