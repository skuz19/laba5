#include "TextureManager.hpp"
#include <iostream>

TextureManager& TextureManager::instance()
{
    static TextureManager tm;
    return tm;
}

void TextureManager::load(TextureID id, const std::string& file)
{
    sf::Texture tex;
    if (!tex.loadFromFile(file))
    {
        std::cerr << "FAILED TO LOAD TEXTURE: " << file << std::endl;
        return;
    }
    textures[id] = tex;
}

const sf::Texture& TextureManager::get(TextureID id)
{
    auto it = textures.find(id);
    if (it == textures.end())
    {
        if (fallback.getSize().x == 0)
        {
            fallback.create(32, 32);
        }

        std::cerr << "TEXTURE NOT FOUND, ID = " << (int)id << std::endl;
        return fallback;
    }
    return it->second;
}