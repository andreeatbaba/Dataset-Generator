#include "Font.h"

// Overload of the >> operator to be able to read a Font object
std::ifstream& operator>>(std::ifstream& is, Font& other)
{
	std::string file; std::string director = "Checked_Fonts"; std::size_t size=72;
	is >> file;
	other._directory.clear();
	other._fileName.clear();
	other._directory.insert(0, director);
	other._fileName.insert(0, file);
	other._size = size;
	return is;
}

// The main constructor, called everytime an instance of a Font is created
Font::Font()
{
	this->_directory = "";
	this->_fileName = "";
	this->_size = 0;
	this->_font = NULL;
}

// The copy constructor, called by the system when is need it
Font::Font(const Font& _other)
{
	*this = _other;
}

// Another form of a copy constructor
Font::Font(const std::string& fileName, const std::size_t& size, const std::string& directory, TTF_Font* font)
{
	this->_fileName = fileName;
	this->_size = size;
	this->_directory = directory;
	this->_font = font;
}

// The "user" - defined destructor
Font::~Font()
{
	this->_fileName = std::string::npos;
	this->_size = NULL;
	this->_directory = std::string::npos;
	this->_font = nullptr;
}

// Overload of the = operator. This will give us the permision to equal a font with another
const Font& Font::operator=(const Font& font)
{
	this->_directory = font._directory;
	this->_fileName = font._fileName;
	this->_font = font._font;
	this->_size = font._size;
	return *this;
}

// Overload of the == operator. This will give us the permision to see if a font is equal to another font.
const bool& Font::operator==(const Font& font) const
{
	if (this->_directory == font._directory
		&& this->_fileName == font._fileName
		&& this->_size == font._size
		&& this->_font == font._font)
		return true;
	return false;
}

// Setter of the file name
const void Font::setFileName(const std::string& fileName)
{
	this->_fileName = fileName;
}

// Setter of the size
const void Font::setSize(const std::size_t& size)
{
	this->_size = size;
}

// Setter of the directory
const void Font::setDirectory(const std::string& directory)
{
	this->_directory = directory;
}

// Setter of the tff font
const void Font::setFont(TTF_Font* font)
{
	this->_font = font;
}

// Getter of the font
TTF_Font* Font::getFont() const
{
	return this->_font;
}

// Getter of the file name
const std::string& Font::getFileName() const
{
	return this->_fileName;
}

// Getter of the directory
const std::string& Font::getDirectory() const
{
	return this->_directory;
}

// Getter of the size
const std::size_t& Font::getSize() const
{
	return this->_size;
}

// Builds the font 
// This function will be called after reading a font from the .txt file
const void Font::createFont()
{
	std::string path = "Fonts\\" + this->_directory + "\\" + this->_fileName;
	this->_font = TTF_OpenFont(path.c_str(), this->_size);
}