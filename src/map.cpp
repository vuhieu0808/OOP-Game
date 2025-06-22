#include "map.h"
#include <fstream>
#include <iostream>

Map::Map() : tileSize(12.f, 12.f) {
    // Thiết lập màu mặc định cho các tile
    tileColors['0'] = sf::Color::Red;
    tileColors['1'] = sf::Color::Blue;
    tileColors['2'] = sf::Color::Green;
    tileColors['3'] = sf::Color::Yellow;
    tileColors['4'] = sf::Color::Magenta;
    tileColors['5'] = sf::Color::Cyan;
    tileColors['6'] = sf::Color(150, 75, 0);  // Brown
    tileColors['7'] = sf::Color::White;
    tileColors['8'] = sf::Color(128, 128, 128);  // Gray
    tileColors['9'] = sf::Color::Black;
}

void Map::setTileColor(char tileChar, sf::Color color) {
    tileColors[tileChar] = color;
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to load map file: " << filename << std::endl;
        return false;
    }

    grid.clear();
    std::string line;
    int y = 0;
    
    while (std::getline(file, line)) {
        // Bỏ qua các dòng metadata (bắt đầu bằng w:, h:, s:)
        if (line.find("w:") == 0 || line.find("h:") == 0 || line.find("s:") == 0) {
            if (line.find("s:") == 0) {
                std::string texturePath = line.substr(2);
                if (!tilesetTexture.loadFromFile(texturePath)) {
                    std::cerr << "Failed to load tileset texture: " << texturePath << std::endl;
                }
            }
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

    // Tạo các shape từ grid
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            char tileChar = grid[row][col];
            if (tileChar != ' ') {
                sf::RectangleShape tileShape(tileSize);
                tileShape.setPosition(col * tileSize.x, row * tileSize.y);
                
                // Đặt màu từ map màu hoặc màu mặc định
                if (tileColors.find(tileChar) != tileColors.end()) {
                    tileShape.setFillColor(tileColors[tileChar]);
                } else {
                    tileShape.setFillColor(sf::Color(100, 100, 100)); // Màu mặc định
                }
                
                tiles.push_back(tileShape);
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
        if (tile.getFillColor() != sf::Color::Transparent) { // Chỉ xét tile không trong suốt
            solids.push_back(tile.getGlobalBounds());
        }
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
