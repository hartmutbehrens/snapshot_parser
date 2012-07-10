#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <string>
#include "snapshot_handler.h"

namespace xc = xercesc;
//function prototypes
template <typename T>
int show_exception(const T &, const int); 
//main - really ??
int main(int argc, char* argv[]) {
	try {
		xc::XMLPlatformUtils::Initialize();
	}
	catch (const xc::XMLException & to_catch) {
		show_exception(to_catch,1);
	}

	//actual work with Xerces-C++
	char * xml_file = "UTRAN-SNAP.xml";
	xc::SAXParser* parser = new xc::SAXParser();
	parser->setValidationScheme(xc::SAXParser::Val_Never);		//could also be Val_Auto or Val_Always

	xc::DocumentHandler* doc_handler = new snapshot_handler();	//HandlerBase provides default empty implementation of all required methods
	xc::ErrorHandler* err_handler = (xc::ErrorHandler*) doc_handler;
	parser->setDocumentHandler(doc_handler);
	parser->setErrorHandler(err_handler);

	try {
		std::cout << "Trying " << std::endl;
		parser->parse(xml_file);
	}
	catch (const xc::XMLException & to_catch) {
		show_exception(to_catch,-1);
		
	}
	catch (const xc::SAXParseException & to_catch) {
		show_exception(to_catch,-1);
	}
	catch (...) {
		std::cout << "Unexpected Exception" << std::endl;
		return -1;
	}

	delete parser;
	delete doc_handler;

	//terminate
	xc::XMLPlatformUtils::Terminate();
	return 0;
}
//function definitions
template <typename T>
int show_exception(const T & to_catch, const int rv) {
	char* message = xc::XMLString::transcode(to_catch.getMessage());
	std::cout << "Exception message is: \n" << message << "\n";
	xc::XMLString::release(&message);
	return rv;
}