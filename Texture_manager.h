#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>

class TextureManager
{
    public:
        TextureManager();

        void loadTexture(const std::string& name, const std::string &filename);

        sf::Texture& getRef(const std::string& texture);
    private:
        std::map<std::string, sf::Texture> textures;
};

#endif
