#include "BaseUI.hpp"

BaseUI::BaseUI()
{
	initFont();
}

BaseUI::~BaseUI()
{
	delete font;
}

void BaseUI::initFont()
{
	font = new sf::Font();
	if (!font->loadFromFile("arial.ttf")) {
		throw std::invalid_argument("Could not load Font: arial.ttf");
	}
}
