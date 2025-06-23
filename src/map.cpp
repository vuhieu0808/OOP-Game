#include "map.h"
#include <fstream>
#include <iostream>

Map::Map() : tileSize(12.f, 12.f) {
    // Không cần thiết lập màu mặc định nữa
}

bool Map::loadTexture(char tileChar, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }
    tileTextures[tileChar] = texture;
    return true;
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to load map file: " << filename << std::endl;
        return false;
    }

    grid.clear();
    tiles.clear();
    std::string line;
    int y = 0;
    
    while (std::getline(file, line)) {
        // Bỏ qua các dòng metadata (bắt đầu bằng w:, h:, s:)
        if (line.find("w:") == 0 || line.find("h:") == 0) {
            continue;
        }

        // Tìm vị trí player
        size_t pPos = line.find('p');
        if (pPos != std::string::npos) {
            playerStartPos.x = pPos * tileSize.x;
            playerStartPos.y = y * tileSize.y;
            line[pPos] = ' '; // Xóa 'p' khỏi grid
        }

        grid.push_back(line);
        y++;
    }

    // Tải tất cả texture cần thiết trước
    for (char c = '0'; c <= '9'; c++) {
        std::string path = "media/tile/" + std::string(1, c) + ".png";
        loadTexture(c, path);
    }
    for (char c = 'a'; c <= 'e'; c++) {
        std::string path = "media/tile/" + std::string(1, c) + ".png";
        loadTexture(c, path);
    }

    // Tạo các sprite từ grid
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            char tileChar = grid[row][col];
            if (tileChar != ' ' && tileTextures.find(tileChar) != tileTextures.end()) {
                sf::Sprite tileSprite(tileTextures[tileChar]);
                tileSprite.setPosition(col * tileSize.x, row * tileSize.y);
                
                // Scale sprite để phù hợp với kích thước tile
                sf::Vector2u texSize = tileTextures[tileChar].getSize();
                tileSprite.setScale(
                    tileSize.x / texSize.x,
                    tileSize.y / texSize.y
                );
                
                tiles.push_back(tileSprite);
            }
        }
    }

    return true;
}

void Map::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        window.draw(tile);
    }
}

sf::Vector2f Map::getPlayerStartPos() const {
    return playerStartPos;
}

sf::Vector2f Map::getMapSize() const {
    if (grid.empty()) return sf::Vector2f(0, 0);
    return sf::Vector2f(
        grid[0].size() * tileSize.x, 
        grid.size() * tileSize.y
    );
}

std::vector<sf::FloatRect> Map::getSolidTiles() const {
    std::vector<sf::FloatRect> solids;
    for (const auto& tile : tiles) {
        solids.push_back(tile.getGlobalBounds());
    }
    return solids;
}

std::vector<sf::FloatRect> Map::getNearbyTiles(const sf::FloatRect& area) const {
    std::vector<sf::FloatRect> nearbyTiles;
    
    // Tính toán phạm vi tile cần kiểm tra
    int startX = std::max(0, static_cast<int>(area.left / tileSize.x) - 1);
    int endX = std::min(static_cast<int>(grid[0].size()), 
               static_cast<int>((area.left + area.width) / tileSize.x) + 1);
    
    int startY = std::max(0, static_cast<int>(area.top / tileSize.y) - 1);
    int endY = std::min(static_cast<int>(grid.size()), 
               static_cast<int>((area.top + area.height) / tileSize.y) + 1);

    // Lấy các tile trong phạm vi
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            if (grid[y][x] != ' ') {  // Chỉ tile không trống
                nearbyTiles.emplace_back(
                    x * tileSize.x, y * tileSize.y,
                    tileSize.x, tileSize.y
                );
            }
        }
    }
    
    return nearbyTiles;
}