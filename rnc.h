#ifndef RNC_H_
#define RNC_H_
#include <string>

class rnc {
private:
	std::string name;
	//constructors not used
	rnc(const rnc & ) {}								//pre-emptive definition, avoid copy construction
	rnc & operator=(const rnc & ) { return *this; }	//pre-emptive definition, avoid object creation by assignment
public:
	//constructors
	rnc(std::string &);
	//destructor
	~rnc();
};

#endif