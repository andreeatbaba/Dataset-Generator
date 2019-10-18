#pragma once

#include <SDL_ttf.h>
#include <SDL.h>

#include <fstream>

class Font
{
public:

#pragma region Constructors
	Font();
	Font(const Font& _other);
	Font(const std::string& fileName, const std::size_t& size, const std::string& directory, TTF_Font* font);
#pragma endregion
#pragma region Destructor
	~Font();
#pragma endregion

#pragma region Operators
	friend std::ifstream& operator >>(std::ifstream& is, Font& other);

	const Font& operator =(const Font& font) ;
	const bool& operator ==(const Font& font) const;
#pragma endregion

#pragma region Setters
	const void setFileName(const std::string& fileName);
	const void setSize(const std::size_t& size);
	const void setDirectory(const std::string& directory);
	const void setFont(TTF_Font* font);
#pragma endregion
#pragma region Getters
	TTF_Font* getFont() const;
	const std::string& getFileName() const;
	const std::string& getDirectory() const;
	const std::size_t& getSize() const;
#pragma endregion
	
#pragma region Methods
	const void createFont();
#pragma endregion
private:
	std::string _fileName;
	std::size_t _size;
	std::string _directory;
	TTF_Font* _font;
};

