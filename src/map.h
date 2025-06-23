#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

class Map {
private:
    std::vector<std::string> grid;  // Lưu trữ bản đồ dạng text
    sf::Vector2f tileSize;          // Kích thước mỗi tile
    std::vector<sf::Sprite> tiles;  // Thay đổi từ RectangleShape sang Sprite
    sf::Vector2f playerStartPos;    // Vị trí bắt đầu của player

    std::unordered_map<char, sf::Texture> tileTextures; // Map texture cho từng loại tile

public:
    Map();
    bool loadTexture(char tileChar, const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPlayerStartPos() const;
    sf::Vector2f getMapSize() const;
    std::vector<sf::FloatRect> getSolidTiles() const;
    std::vector<sf::FloatRect> getNearbyTiles(const sf::FloatRect& area) const;
    const sf::Vector2f& getTileSize() const { return tileSize; }
};