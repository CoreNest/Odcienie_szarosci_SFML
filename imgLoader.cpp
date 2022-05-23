#include "ImgLoader.h"

sf::Image imgLoader::img = sf::Image();
bool imgLoader::loaded = 0;
sf::Sprite imgLoader::sprite = sf::Sprite();
sf::Texture imgLoader::texture = sf::Texture();
std::string imgLoader::name_ = std::string();