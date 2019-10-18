#include "Image.h"
#include <random>
#include <algorithm>
// Constructor
Image::Image()
{
	this->_character = NULL;
	this->_fileName = "";
	this->background = FOREGROUND;
	this->foreground = BACKGROUND;
	this->textSurface = NULL;
	this->_directory = SAVING_DIRECTORY;
	TTF_Init();
}

// Copy constructor
Image::Image(const Image& other)
{
	*this = other;
}

// Copy constructor
Image::Image(const std::string& fileName, const char& character, const Font& font)
{
	this->_character = character;
	this->_fileName = fileName;
	this->background =  FOREGROUND;
	this->foreground = BACKGROUND;
	this->_font = font;
	this->textSurface = NULL;
}

// Destructor
Image::~Image()
{
	SDL_FreeSurface(this->textSurface);
}

// Setter of the font
const void Image::setFont(const Font& _font)
{
	this->_font = _font;
}

// Setter of the character
const void Image::setCharacter(const char& character)
{
	this->_character = character;
}

// Setter of the directory
const void Image::setDirectory(const std::string& directory)
{
	this->_directory = directory;
}

// Setter of the file name
const void Image::setFileName(const char& character)
{
	this->_fileName = character;
}

// Setter of the SDL Surface
const void Image::setTextSurface(SDL_Surface* other)
{
	this->textSurface = other;
}

// Getter of the file name
const std::string& Image::getFileName() const
{
	return this->_fileName;
}

// Getter of the directory
const std::string& Image::getDirectory() const
{
	return this->_directory;
}

const std::string& Image::getPicturePixels() const
{
	return this->_picturePixels;
}

// Getter of the font
const Font& Image::getFont() const
{
	return this->_font;
}

// Getter of the FOREGROUND macro
const SDL_Color& Image::getForeground() const
{
	return BACKGROUND;
}

// Getter of the BACKGROUND macro
const SDL_Color& Image::getBackground() const
{
	return FOREGROUND;
}

// Getter of the text surface (SDL function)
const SDL_Surface* Image::getTextSurface() const
{
	return this->textSurface;
}

// Getter of the character
const char& Image::getCharacter() const
{
	return this->_character;
}

// Overloading = operator
const Image& Image::operator=(const Image& other)
{
	this->_character = other._character;
	this->_fileName = other._fileName;
	this->_font = other._font;
	this->_directory = other._directory;

	this->background =  FOREGROUND;
	this->foreground = BACKGROUND;

	this->textSurface = NULL;

	return *this;
}

// Creating the image
// Rendering the text (characters) into the SDL Surface
const void Image::createImage()
{
	this->textSurface = TTF_RenderText_Blended(this->_font.getFont(), &this->_character, this->foreground);
}

// Getter of the surface
SDL_Surface* Image::getTextSurface()
{
	return this->textSurface;
}

// Saving the image into the specified directory
// If the directory isn't found, it will create it
// The file name is created this way
// The rendered character
// Type ( lower, upper, number)
// And the font name
const void Image::saveImage(std::vector<bool>vect, int option = 0)
{
	std::string nnm = &this->_character;

	if (option == 0) {
		if (this->_character >= 97 && this->_character <= 122)
		{
			nnm.append("_lower_");
		}
		else if (this->_character >= 65 && this->_character <= 90)
		{
			nnm.append("_upper_");
		}
		else if (this->_character >= 48 && this->_character <= 57)
		{
			nnm.append("_number_");
		}
	}
	else {
		nnm.append("_garbage_");
	}

	this->_fileName.append(nnm);

	this->_fileName.append(this->_font.getFileName());

	// Creating the "saving" directory if it isn't already created.
		if (!std::experimental::filesystem::is_directory(option==0?SAVING_DIRECTORY:SAVING_DIRECTORY_GARBAGE) || !std::experimental::filesystem::exists(option == 0 ? SAVING_DIRECTORY : SAVING_DIRECTORY_GARBAGE)) {
			std::experimental::filesystem::create_directory(option == 0 ? SAVING_DIRECTORY : SAVING_DIRECTORY_GARBAGE);
			std::cout << "The location was created succesfuly\n";
		}

	

	// Erasing the last 4 characters from the font filename (the file extension).
	std::string newString = this->_fileName.substr(this->_fileName.length() - 4, this->_fileName.length());
	this->_fileName.erase(this->_fileName.length() - 4, this->_fileName.length());

	if (newString.compare(".ttf") != 0
		&& newString.compare(".otf") != 0
		&& newString.compare(".fon") != 0) {
		std::cout << "Mismatch";
	}
	else 
	{
		std::string path = this->_directory + "\\" + this->_fileName + ".bmp";
		this->scaleImage();
		this->generatePixels(vect, option);
		SDL_SaveBMP(this->textSurface, path.c_str());
	}
}

// Blitting White surface with text surface
const void Image::scaleImage()
{
	// Creating the output surface
	SDL_Surface* out = SDL_CreateRGBSurface(
		SDL_SWSURFACE,
		PIXEL_WIDTH,
		PIXEL_HEIGHT,
		this->getTextSurface()->format->BitsPerPixel,
		this->getTextSurface()->format->Rmask,
		this->getTextSurface()->format->Gmask, 
		this->getTextSurface()->format->Bmask, 
		0);

	
	// Establishing values to scale the text properly
	SDL_Rect offset;
	offset.w = (this->getTextSurface()->w * PIXEL_HEIGHT) / this->getTextSurface()->h;
	offset.x = (PIXEL_WIDTH - offset.w)/2;
	offset.y = 0;
	offset.h = out->h - 2;
	
	// Filling the output surface with black
	SDL_FillRect(out, NULL, (Uint32)((this->background.r << 16) + (this->background.b << 8) + (this->background.b << 0)));

	// Scaling the text surface onto the output surface
	SDL_BlitScaled(this->textSurface, NULL, out, &offset);

	// Setting this text surface with the expected output
	this->setTextSurface(out);
}

const void Image::generatePixels(std::vector<bool>vect, int option = 0)
{
	auto uppercaseLetters = 65;
	auto lowercaseLetters = 71;
	auto digits = 4;
	auto garbageClass = 62;

	std::shuffle(vect.begin(), vect.end(), std::default_random_engine{});
	this->_picturePixels = "";
	for (auto x = 0; x < PIXEL_HEIGHT; ++x) 
	{
		for (auto y = 0; y < PIXEL_WIDTH; ++y) 
		{
			Uint8 smth;
			if (vect[x * PIXEL_HEIGHT + y] == true) {
				smth = std::rand()%256;
				SDL_LockSurface(this->textSurface);

				Uint32* pixels = (Uint32*)this->textSurface->pixels;
				Uint32 val = pixels[(x * textSurface->w) + y];
				val = smth >> 16;
				pixels[(x * textSurface->w) + y] = val;

				SDL_UnlockSurface(this->textSurface);
			}
			else {

				SDL_LockSurface(this->textSurface);

				Uint32* pixels = (Uint32*)this->textSurface->pixels;
				Uint32 val = pixels[(x * textSurface->w) + y];
				smth = val >> 16;

				SDL_UnlockSurface(this->textSurface);
			}

			this->_picturePixels.append(std::to_string(smth/255.0));
			this->_picturePixels.append(",");
			
		}
	}
	std::string asdf = this->_picturePixels;
	int position = -1;
	if (option == 0) {
		if (this->_character >= 'A' && this->_character <= 'Z') {
			position = this->_character - uppercaseLetters;
		}
		if (this->_character >= 'a' && this->_character <= 'z') {
			position = this->_character - lowercaseLetters;
		}
		if (this->_character >= '0' && this->_character <= '9') {
			position = this->_character + digits;
		}
	}
	else {
		position = garbageClass; //garbage
	}
	for (int i = 0; i <= garbageClass; ++i)
	{
		if (position == i) {
			this->_picturePixels.append("1");
		}
		else {
			this->_picturePixels.append("0");
		}
		this->_picturePixels.append(",");
	}
	this->_picturePixels[this->_picturePixels.length() - 1] = '\n';


}
