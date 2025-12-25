#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class TextureID
{
    Closed,
    Opened,
    Flag,
    Mine,
    Explode,
    One, Two, Three, Four, Five, Six, Seven, Eight,
    Background
};

class TextureManager
{
public:
    static TextureManager& instance();

    void load(TextureID id, const std::string& file);
    const sf::Texture& get(TextureID id);

private:
    std::map<TextureID, sf::Texture> textures;
    sf::Texture fallback;
};