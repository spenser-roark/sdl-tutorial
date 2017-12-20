#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <string>
using namespace std;

// these keys are arbitrary, maybe I can change them to something meaningful later on
// Break this into its own file if it starts getting too large
const map<int, string> errorMessages = {
	{0, "SDL Surface load error"},
	{1, "Could not create texture from surface"}
};

const int screen_width = 1024;
const int screen_height = 768;
const int tile_size = 40;

#endif