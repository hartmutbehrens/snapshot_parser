#include "snapshot_handler.h"
#include <iterator>

//constructor
snapshot_handler::snapshot_handler() {
	wanted["/snapshot/RNC/NodeB/FDDCell/attributes/cellId"] = 1;
	wanted["/snapshot/RNC/NodeB/FDDCell/attributes/locationAreaCode"] = 1;
	wanted["/snapshot/RNC/NodeB/FDDCell/attributes/primaryScramblingCode"] = 1;
	wanted["/snapshot/RNC/NodeB/FDDCell/attributes/routingAreaCode"] = 1;
	wanted["/snapshot/RNC/NodeB/FDDCell/attributes/serviceAreaCode"] = 1;
}
//destructor
snapshot_handler::~snapshot_handler() {}

//handlers for the SAX DocumentHandler interface
void snapshot_handler::startElement(const XMLCh * const name, xc::AttributeList &  attributes) {
	xml_node *xn = new xml_node(name,attributes);
	nodes.push_back(xn);
}

void snapshot_handler::endElement(const XMLCh * const name) {
	std::string xpath = nodes.current_xpath();
	
	if (wanted.find(xpath) != wanted.end() ) {
		std::cout << nodes << std::endl;
	}
	nodes.remove_last();				//remove last xml_node added and reclaim memory
}

void snapshot_handler::characters(const XMLCh* const ch, const XMLSize_t length) {
	if (length > 1) {
		nodes.back()->add_characters(ch);	//update characters of last node
	}
}


template <typename T>
void snapshot_handler::message(const char * which, const T & exception) {
	char * id = xc::XMLString::transcode(exception.getSystemId());
	char * msg = xc::XMLString::transcode(exception.getMessage());
	std::cerr << std::endl << which << " at file " << id << ", line " << exception.getLineNumber() << ", char " << exception.getColumnNumber() << "\n  Message: " << msg << std::endl;
	xc::XMLString::release(&id);
	xc::XMLString::release(&msg);
}

//handlers for the SAX ErrorHandler interface
void snapshot_handler::error(const xc::SAXParseException& e) {
	snapshot_handler::message("Error", e);
}

void snapshot_handler::fatalError(const xc::SAXParseException& e) {
	snapshot_handler::message("Fatal Error", e);
}

void snapshot_handler::warning(const xc::SAXParseException& e) {
	snapshot_handler::message("Warning", e);
}