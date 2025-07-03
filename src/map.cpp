#include "map.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <tinyxml2.h>

Map::Map() : tileSize(18.f, 18.f) { // Đặt tileSize thành 16x16 dựa trên tileset
}

bool Map::loadTexture(const std::string& filename, int tileId) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load texture for tile ID " << tileId << ": " << filename << std::endl;
        return false;
    }
    tileTextures[tileId] = texture;
    std::cout << "Loaded texture for tile ID " << tileId << ": " << filename << std::endl;
    return true;
}

bool Map::loadTileset(tinyxml2::XMLElement* tilesetElement, const std::string& tmxPath) {
    int firstGid = tilesetElement->IntAttribute("firstgid");
    std::string source = tilesetElement->Attribute("source");
    tinyxml2::XMLDocument tsxDoc;
    std::string fullPath = tmxPath.substr(0, tmxPath.find_last_of("/\\")) + "/" + source;
    if (tsxDoc.LoadFile(fullPath.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load tileset file: " << fullPath << std::endl;
        return false;
    }

    tinyxml2::XMLElement* tsxTileset = tsxDoc.FirstChildElement("tileset");
    tinyxml2::XMLElement* imageElement = tsxTileset->FirstChildElement("image");
    std::string imageSource = imageElement->Attribute("source");
    std::string imagePath;

    // Điều chỉnh đường dẫn dựa trên tên tileset
    if (source.find("tileset-tiles.tsx") != std::string::npos) {
        imagePath = "media/map/Tilemap/tilemap_packed.png"; // Đường dẫn mới cho tileset-tiles.tsx
    } else if (source.find("tileset-characters.tsx") != std::string::npos) {
        imagePath = "media/map/Tilemap/tilemap-characters_packed.png"; // Đường dẫn mới cho tileset-characters.tsx
    } else {
        std::cerr << "Unknown tileset source: " << source << std::endl;
        return false;
    }
    std::cout << "Attempting to load tileset image from: " << imagePath << std::endl; // Log để debug

    int tileWidth = tsxTileset->IntAttribute("tilewidth");
    int tileHeight = tsxTileset->IntAttribute("tileheight");
    int tileCount = tsxTileset->IntAttribute("tilecount");
    int columns = tsxTileset->IntAttribute("columns");

    // Tải texture từ hình ảnh tileset và cắt thành từng tile
    sf::Image tilesetImage;
    if (!tilesetImage.loadFromFile(imagePath)) {
        std::cerr << "Failed to load tileset image: " << imagePath << std::endl;
        return false;
    }
    tilesetImage.createMaskFromColor(sf::Color::Magenta); // Loại bỏ màu magenta làm nền trong suốt

    for (int i = 0; i < tileCount; ++i) {
        int tileId = firstGid + i;
        int x = (i % columns) * tileWidth;
        int y = (i / columns) * tileHeight;
        sf::Texture texture;
        texture.loadFromImage(tilesetImage, sf::IntRect(x, y, tileWidth, tileHeight));
        tileTextures[tileId] = texture;
        // std::cout << "Loaded tile ID " << tileId << " from " << imagePath << std::endl;
    }

    return true;
}

bool Map::loadLayer(tinyxml2::XMLElement* layerElement, std::vector<std::vector<int>>& grid) {
    int width = layerElement->IntAttribute("width");
    int height = layerElement->IntAttribute("height");
    tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
    if (!dataElement) {
        std::cerr << "No data in layer: " << layerElement->Attribute("name") << std::endl;
        return false;
    }

    std::string data = dataElement->GetText();
    std::stringstream ss(data);
    std::string value;
    grid.clear();
    grid.resize(height, std::vector<int>(width, 0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::getline(ss, value, ',');
            try {
                grid[y][x] = std::stoi(value);
            } catch (const std::exception& e) {
                std::cerr << "Invalid tile ID in layer " << layerElement->Attribute("name") 
                          << " at (" << x << "," << y << "): " << value << std::endl;
                grid[y][x] = 0;
            }
        }
    }
    std::cout << "Loaded layer '" << layerElement->Attribute("name") << "' with size " << width << "x" << height << std::endl;
    return true;
}

bool Map::loadObjectLayer(tinyxml2::XMLElement* objectGroupElement) {
    tinyxml2::XMLElement* objectElement = objectGroupElement->FirstChildElement("object");
    while (objectElement) {
        if (std::string(objectElement->Attribute("name")) == "player_start") {
            playerStartPos.x = objectElement->FloatAttribute("x");
            playerStartPos.y = objectElement->FloatAttribute("y");
            std::cout << "Found player start position: (" << playerStartPos.x << "," << playerStartPos.y << ")" << std::endl;
            break;
        }
        objectElement = objectElement->NextSiblingElement("object");
    }
    return true;
}

bool Map::loadFromFile(const std::string& filename) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load map file: " << filename << std::endl;
        return false;
    }

    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "Invalid TMX file: no map element" << std::endl;
        return false;
    }

    // Kiểm tra tile size
    float tileWidth = mapElement->FloatAttribute("tilewidth");
    float tileHeight = mapElement->FloatAttribute("tileheight");
    if (tileWidth != tileSize.x || tileHeight != tileSize.y) {
        std::cerr << "Warning: Tile size mismatch! TMX tile size: " << tileWidth << "x" << tileHeight 
                  << ", Code tile size: " << tileSize.x << "x" << tileSize.y << std::endl;
    }

    // Xóa dữ liệu cũ
    backgroundBackGrid.clear();
    backgroundFrontGrid.clear();
    mapGrid.clear();
    backgroundBackTiles.clear();
    backgroundFrontTiles.clear();
    mapTiles.clear();
    solids.clear();

    // Tải các tileset
    tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    while (tilesetElement) {
        if (!loadTileset(tilesetElement, filename)) {
            return false;
        }
        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    // Tải các layer
    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
    while (layerElement) {
        std::string layerName = layerElement->Attribute("name");
        if (layerName == "background_back") {
            loadLayer(layerElement, backgroundBackGrid);
        } else if (layerName == "background_front") {
            loadLayer(layerElement, backgroundFrontGrid);
        } else if (layerName == "map") {
            loadLayer(layerElement, mapGrid);
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }

    
    // Tạo sprite cho các layer
    auto createSprites = [&](const std::vector<std::vector<int>>& grid, std::vector<sf::Sprite>& tiles, bool isSolid) {
        for (size_t row = 0; row < grid.size(); ++row) {
            for (size_t col = 0; col < grid[row].size(); ++col) {
                int tileId = grid[row][col];
                if (tileId != 0 && tileTextures.find(tileId) != tileTextures.end()) {
                    sf::Sprite tileSprite(tileTextures[tileId]);
                    tileSprite.setPosition(col * tileSize.x, row * tileSize.y);
                    tiles.push_back(tileSprite);
                    if (isSolid) {
                        solids.push_back(tileSprite.getGlobalBounds());
                    }
                }
            }
        }
        std::cout << "Created " << tiles.size() << " sprites for " << (isSolid ? "solid" : "background") << " layer" << std::endl;
    };
    
    createSprites(backgroundBackGrid, backgroundBackTiles, false);
    createSprites(backgroundFrontGrid, backgroundFrontTiles, false);
    createSprites(mapGrid, mapTiles, true);
    
    // Tải object layer
    tinyxml2::XMLElement* objectGroupElement = mapElement->FirstChildElement("objectgroup");
    while (objectGroupElement) {
        if (std::string(objectGroupElement->Attribute("name")) == "object") {
            loadObjectLayer(objectGroupElement);
            break;
        }
        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }

    std::cout << "Found player start position: (" << playerStartPos.x << "," << playerStartPos.y << ")" << std::endl;

    return true;
}

void Map::draw(sf::RenderWindow& window) {
    for (const auto& tile : backgroundBackTiles) {
        window.draw(tile);
    }
    for (const auto& tile : mapTiles) {
        window.draw(tile);
    }
    for (const auto& tile : backgroundFrontTiles) {
        window.draw(tile);
    }
}

sf::Vector2f Map::getPlayerStartPos() const {
    return playerStartPos;
}

sf::Vector2f Map::getMapSize() const {
    if (mapGrid.empty()) return sf::Vector2f(0, 0);
    return sf::Vector2f(
        mapGrid[0].size() * tileSize.x, 
        mapGrid.size() * tileSize.y
    );
}

std::vector<sf::FloatRect> Map::getSolidTiles() const {
    return solids;
}

std::vector<sf::FloatRect> Map::getNearbyTiles(const sf::FloatRect& area) const {
    std::vector<sf::FloatRect> nearbyTiles;
    
    int startX = std::max(0, static_cast<int>(area.left / tileSize.x) - 1);
    int endX = std::min(static_cast<int>(mapGrid[0].size()), 
               static_cast<int>((area.left + area.width) / tileSize.x) + 1);
    
    int startY = std::max(0, static_cast<int>(area.top / tileSize.y) - 1);
    int endY = std::min(static_cast<int>(mapGrid.size()), 
               static_cast<int>((area.top + area.height) / tileSize.y) + 1);

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            if (y >= 0 && y < static_cast<int>(mapGrid.size()) && x >= 0 && x < static_cast<int>(mapGrid[0].size()) && mapGrid[y][x] != 0) {
                nearbyTiles.emplace_back(
                    x * tileSize.x, y * tileSize.y,
                    tileSize.x, tileSize.y
                );
            }
        }
    }
    
    return nearbyTiles;
}