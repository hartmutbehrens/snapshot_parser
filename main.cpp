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
	std::string xml_file;
	std::vector<std::string> xpath;
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help","produce help message")
			("xpath,x", po::value< std::vector<std::string> >(), "xpath('s) to search" )
			("input-file", po::value< std::string >(), "xml input file")
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
			xml_file = vm["input-file"].as<std::string>();
			if (! fs::exists(xml_file)) {
				std::cout << "Input file \"" << xml_file << "\" does not exist!" <<std::endl;
				return 1;
			}
		}
		else {
			std::cout << "Input file is required!" << std::endl;
			return 1;
		}
		if (vm.count("xpath")) {
			xpath = vm["xpath"].as< std::vector<std::string> >();
		}
		else {
			std::cout << "At least one xpath is required!" << std::endl;
			return 1;
		}

	}
	catch(std::exception &e) {
		std::cout << "Ding dong ding dong, something went wrong: "<< e.what() << std::endl;
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

	xc::DocumentHandler* doc_handler = new snapshot_handler(xpath);	//HandlerBase provides default empty implementation of all required methods
	xc::ErrorHandler* err_handler = (xc::ErrorHandler*) doc_handler;
	parser->setDocumentHandler(doc_handler);
	parser->setErrorHandler(err_handler);

	try {
		std::cout << "Parsing " << xml_file << std::endl;
		parser->parse(xml_file.c_str());
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