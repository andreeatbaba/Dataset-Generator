#pragma once

#include <fstream>
#include <vector>
#include <SDL_ttf.h>
#include <thread>
#include <time.h>
#include <thread>
#include <filesystem>

#include "Font.h"
#include "Image.h"

#pragma region MACROS
#define NO_SPLITS 10
#pragma endregion

class Generator
{
public:

#pragma region Constructors
	Generator();
	Generator(const Generator& other);
	Generator(const Font& font, const Image& image);
#pragma endregion

#pragma region Setters
	const void setImage(const Image& image);
	const void setFont(const Font& font);
	const void setPixels(const std::vector<std::string>& pixels);
#pragma endregion
#pragma region Getters
	const Image& getImage() const;
	const Font& getFont() const;
	const std::vector<std::string>& getPixels() const;
#pragma endregion

#pragma region Operators
	const Generator& operator=(const Generator& other);
#pragma endregion

#pragma region Methods
	const void run();
	const void garbage();
private:
	const void initialize();
	//const void thr(std::vector<Font>, std::size_t, std::size_t, std::vector<char>, std::vector<std::string>&);

#pragma endregion

private:
	Font _font;
	Image _image;
	std::vector<char> _characters;
	std::vector<Font> _fonts;
	std::vector<std::thread> _threads;
	std::vector<std::string> pixels;
};
