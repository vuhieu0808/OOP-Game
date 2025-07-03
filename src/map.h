#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <tinyxml2.h>

class Map {
private:
    std::vector<std::vector<int>> backgroundBackGrid;    // Lưu trữ layer background_back
    std::vector<std::vector<int>> backgroundFrontGrid;   // Lưu trữ layer background_front
    std::vector<std::vector<int>> mapGrid;              // Lưu trữ layer map (có va chạm)
    sf::Vector2f tileSize;                              // Kích thước mỗi tile
    std::vector<sf::Sprite> backgroundBackTiles;        // Tiles cho layer background_back
    std::vector<sf::Sprite> backgroundFrontTiles;       // Tiles cho layer background_front
    std::vector<sf::Sprite> mapTiles;                  // Tiles cho layer map
    sf::Vector2f playerStartPos;                        // Vị trí bắt đầu của player
    std::vector<sf::FloatRect> solids;                 // Các tile có va chạm
    std::unordered_map<int, sf::Texture> tileTextures;  // Map texture cho từng tile ID

    bool loadTileset(tinyxml2::XMLElement* tilesetElement, const std::string& tmxPath);
    bool loadLayer(tinyxml2::XMLElement* layerElement, std::vector<std::vector<int>>& grid);
    bool loadObjectLayer(tinyxml2::XMLElement* objectGroupElement);

public:
    Map();
    bool loadTexture(const std::string& filename, int tileId);
    bool loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPlayerStartPos() const;
    sf::Vector2f getMapSize() const;
    std::vector<sf::FloatRect> getSolidTiles() const;
    std::vector<sf::FloatRect> getNearbyTiles(const sf::FloatRect& area) const;
    const sf::Vector2f& getTileSize() const { return tileSize; }
};