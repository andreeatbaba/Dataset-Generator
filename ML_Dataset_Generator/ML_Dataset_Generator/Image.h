#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <filesystem>

#include "Font.h"

#pragma region MACROS
#define SAVING_DIRECTORY "Dataset"
#define SAVING_DIRECTORY_GARBAGE "Garbage"

#define BACKGROUND {255, 255, 255}
#define FOREGROUND {0, 0, 0}

#define PIXEL_HEIGHT 28
#define PIXEL_WIDTH 28

#define NO_FLAGS 0
#pragma endregion

class Image
{
public:

#pragma region Constructors
	Image();
	Image(const Image& other);
	Image(const std::string& fileName,
		const char& character,
		const Font& font);
#pragma endregion
#pragma region Destructor
	~Image();
#pragma endregion

#pragma region Setters
	const void setFont(const Font& _font);
	const void setCharacter(const char& character);
	const void setDirectory(const std::string& directory);
	const void setFileName(const char& character);
	const void setTextSurface(SDL_Surface* other);
#pragma endregion
#pragma region Getters
	const std::string& getFileName() const;
	const std::string& getDirectory() const;
	const std::string& getPicturePixels() const;

	const Font& getFont() const;

	const SDL_Color& getForeground() const;
	const SDL_Color& getBackground() const;

	SDL_Surface* getTextSurface();
	const SDL_Surface* getTextSurface() const;

	const char& getCharacter() const;
#pragma endregion

#pragma region Operators
	const Image& operator =(const Image& other);
#pragma endregion

#pragma region Methods
	const void createImage();
	const void saveImage(std::vector<bool>vect, int option);
	const void scaleImage();
	const void generatePixels(std::vector<bool>vect, int option);
#pragma endregion

private:
	std::string _fileName;
	std::string _directory;
	std::string _picturePixels;

	Font _font;

	SDL_Color foreground;
	SDL_Color background;

	SDL_Surface* textSurface;

	char _character;
};

