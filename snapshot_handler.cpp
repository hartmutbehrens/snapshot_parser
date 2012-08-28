#include "snapshot_handler.h"
#include <iterator>

//constructor
snapshot_handler::snapshot_handler(std::vector<std::string> &xp) {
	for(std::vector<std::string>::iterator it = xp.begin() ; it != xp.end(); it++) {
		wanted[*it] = 1;
	}
}
//destructor
snapshot_handler::~snapshot_handler() {}

//handlers for the SAX DocumentHandler interface
void snapshot_handler::startElement(const XMLCh * const name, xc::AttributeList &  xc_attributes) {
	//create map of attributes
	std::map<std::string,std::string> attributes;
	for (XMLSize_t i = 0; i < xc_attributes.getLength(); i++) {
		char *name = xc::XMLString::transcode(xc_attributes.getName(i));
		char *value = xc::XMLString::transcode(xc_attributes.getValue(i));
		
		attributes[name] = value;

		xc::XMLString::release(&name);
		xc::XMLString::release(&value);
	}
	//create new xml_node and push onto nodes list
	char *ctag = xc::XMLString::transcode(name);
	xml_node *xn = new xml_node(ctag,attributes);
	nodes.push_back(xn);
	xc::XMLString::release(&ctag);
}

void snapshot_handler::endElement(const XMLCh * const name) {
	if ( ( wanted.find(nodes.xpath) != wanted.end() ) || ( wanted.find(nodes.xpath_with_id) != wanted.end() ) ) {
		std::cout << nodes << std::endl;	
		//std::cout << nodes.xpath_with_id << std::endl;
	}
	xml_node *xn = nodes.remove_last();				//get reference to last xml_node added
	delete xn;										//reclaim memory
}

void snapshot_handler::characters(const XMLCh* const ch, const XMLSize_t length) {
	if (length > 1) {
		char *cchar = xc::XMLString::transcode(ch);
		nodes.back()->add_characters(cchar);	//update characters of last node
		xc::XMLString::release(&cchar);
	}
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

//own methods
template <typename T>
void snapshot_handler::message(const char * which, const T & exception) {
	char * id = xc::XMLString::transcode(exception.getSystemId());
	char * msg = xc::XMLString::transcode(exception.getMessage());
	std::cerr << std::endl << which << " at file " << id << ", line " << exception.getLineNumber() << ", char " << exception.getColumnNumber() << "\n  Message: " << msg << std::endl;
	xc::XMLString::release(&id);
	xc::XMLString::release(&msg);
}
