#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "snapshot_handler.h"

//namespaces
namespace xc = xercesc;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
//function prototypes
template <typename T>
int show_exception(const T &, const int); 
//main - really ??
int main(int ac, char* av[]) {
	std::vector<std::string> xpath;
	std::vector<std::string> files;
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help","produce help message")
			("xpath,x", po::value< std::vector<std::string> >(), "xpath('s) to search" )
			("input-file", po::value< std::vector<std::string> >(), "xml input file")
		;
		po::positional_options_description p;
		p.add("input-file",-1);
		
		po::variables_map vm;
		po::store(po::command_line_parser(ac,av).options(desc).positional(p).run(),vm);
		po::notify(vm);

		if ( (vm.count("help")) || (ac < 2) ) {
			std::cout << desc << std::endl;
			return 1;
		}
		if (vm.count("input-file")) {
			files = vm["input-file"].as< std::vector<std::string> >();
		}
		else {
			std::cerr << "At least one input file is required!" << std::endl;
			return 1;
		}
		if (vm.count("xpath")) {
			xpath = vm["xpath"].as< std::vector<std::string> >();
		}
		else {
			std::cerr << "At least one xpath is required!" << std::endl;
			return 1;
		}

	}
	catch(std::exception &e) {
		std::cerr << "Ding dong ding dong, something went wrong: "<< e.what() << std::endl;
		return 1;
	}
	
	try {
		xc::XMLPlatformUtils::Initialize();
	}
	catch (const xc::XMLException & to_catch) {
		show_exception(to_catch,1);
	}

	//actual work with Xerces-C++
	xc::SAXParser* parser = new xc::SAXParser();
	parser->setValidationScheme(xc::SAXParser::Val_Never);				//could also be Val_Auto or Val_Always

	xc::DocumentHandler* doc_handler = new snapshot_handler(xpath);		//HandlerBase provides default empty implementation of all required methods
	xc::ErrorHandler* err_handler = (xc::ErrorHandler*) doc_handler;
	parser->setDocumentHandler(doc_handler);
	parser->setErrorHandler(err_handler);

	try {
		for(std::vector<std::string>::iterator it = files.begin() ; it != files.end(); it++) {	
			if (! fs::exists(*it)) {
				std::cerr << "Input file \"" << *it << "\" does not exist!" <<std::endl;
				return 1;
			}
			std::cout << "Parsing " << *it << std::endl;
			parser->parse(it->c_str());
		}
	}
	catch (const xc::XMLException & to_catch) {
		show_exception(to_catch,-1);
	}
	catch (const xc::SAXParseException & to_catch) {
		show_exception(to_catch,-1);
	}
	catch (...) {
		std::cerr << "Unexpected Exception" << std::endl;
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
	std::cerr << "Exception message is: \n" << message << "\n";
	xc::XMLString::release(&message);
	return rv;
}
