#include <iostream>
#include <string>
using namespace std;

#include "errors.h"

void printSDLErrorToTerminal(string errorMsg, string sdlError) {
	cerr << errorMsg << ": " << sdlError << endl;
}