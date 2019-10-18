/*
ML_Dataset_Generator

This project is programmed to generate all the letters (uppercase and lowercase) and digits
from "Characters.txt" in all the fonts declared in "Fonts.txt".

All the generated images will be saved in the "Dataset" directory. If you don't have this directory it will be created automatically.
It will generate a file Pixels.csv with all the pixels information and classes.

You can find these files in the Resources directory.
The fonts must be in the following formats: .ttf, .otf and .fon

If you want to add more fonts you should respect the following format in Fonts.txt (Format + Example):
File Name + extension lowercase
Ex:
Times.ttf

BEST TIME: 3 seconds for 61 fonts and 61 characters
WORST TIME: 7 seconds for 61 fonts and 61 characters

BEST TIME: 193 seconds for 909 fonts and 61 characters
*/
#include "Generator.h"

#undef main

int main() 
{
	std::ofstream write("Pixels.csv");
	Generator application;
	application.run();
	auto from = application.getPixels().begin();
	auto to = application.getPixels().end();

	for (auto i = from; i != to; ++i) {
		write << (*i);
	}
	return 0;
}