#include "Generator.h"


// Overloading = operator
const Generator& Generator::operator=(const Generator& other)
{
	this->_image = other._image;
	
	for (std::size_t index = 0; index < other._fonts.size(); ++index) {
		this->_fonts[index] = other._fonts[index];
	}

	return *this;
}

// Runs the threads
const void Generator::run()
{
	std::cout << "Initializing the program...\n";
	this->initialize();
}

// It creates an image with the font and character specified and saves it in the
// "Dataset" directory
const void Generator::initialize()
{
	std::size_t numberOfFonts = this->_fonts.size();
	std::size_t numberOfThreads = numberOfFonts / (numberOfFonts/NO_SPLITS);
	numberOfThreads += numberOfFonts % (numberOfFonts / NO_SPLITS) == 0 ? 0 : 1;
	this->pixels.reserve(this->_characters.size() * this->_fonts.size());

	auto startNumb = 0;
	bool arabic = false;
	std::cout << "Generating the dataset...\n";

	clock_t clockRend = clock();

	for (char chara : this->_characters) {
		arabic = false;
		int numb = 0;
		std::vector<bool> stmth(156, true);
		stmth.insert(stmth.begin(), 706 - 78, false);
		std::vector<bool> fals(784, false);
		for (auto font : this->_fonts) {
			if (font.getFileName() == "AfricanDesign.ttf") {
				arabic = true;
			}
		    Image img;
			img.setFont(font);
			img.setCharacter(chara);
			img.createImage();
			if (img.getTextSurface() == NULL) continue;
			if (arabic == false) {
				if (numb <= 80) {
					img.saveImage(stmth, 0);
				}
				else {
					img.saveImage(fals, 0);
				}
			}
			else {
				if (chara >= '0' && chara <= '9') continue;
				img.saveImage(fals, 1);
			}
			std::string str = img.getPicturePixels();
			pixels.push_back(str);
			++numb;
		}
	}

	std::cout << "The time spent on generating the dataset: " << (clock() - clockRend) / CLOCKS_PER_SEC << " seconds\n";
}

// Constructor
Generator::Generator()
{
	std::ifstream readCharacters("Resources\\Characters.txt");
	std::ifstream read("Resources\\Fonts.txt");

	char x;
	while (readCharacters >> x) {
		this->_characters.push_back(x);
	}


	Font font;
	while (read >> font) {
		font.createFont();
		this->_fonts.push_back(font);
	}
}

// Copy constructor
Generator::Generator(const Generator& other)
{
	*this = other;
}

// Copy constructor
Generator::Generator(const Font& font, const Image& image)
{
	this->_image = image;
	this->_font = font;
}

// Setter of the image
const void Generator::setImage(const Image& image)
{
	this->_image = image;
}

// Setter of the font
const void Generator::setFont(const Font& font)
{
	this->_font = font;
}

const void Generator::setPixels(const std::vector<std::string>& pixels)
{
	this->pixels = pixels;
}

// Getter of the image
const Image& Generator::getImage() const
{
	return this->_image;
}

// Getter of the font
const Font& Generator::getFont() const
{
	return this->_font;
}

const std::vector<std::string>& Generator::getPixels() const
{
	return this->pixels;
}
