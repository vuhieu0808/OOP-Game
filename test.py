import pygame
import pytmx
import os

pygame.init()

def load_and_display_map(map_path, screen_width=200, screen_height=600):
    try:
        # 1. Tạo cửa sổ trước khi làm bất cứ điều gì khác
        screen = pygame.display.set_mode((screen_width, screen_height))
        pygame.display.set_caption(f"Map Viewer: {os.path.basename(map_path)}")
        
        # 2. Load map
        tmx_data = pytmx.load_pygame(map_path)
        
        # 3. Tính toán zoom
        map_pixel_width = tmx_data.width * tmx_data.tilewidth
        map_pixel_height = tmx_data.height * tmx_data.tileheight
        zoom = min(screen_width/map_pixel_width, screen_height/map_pixel_height) * 0.9
        
        # 4. Vòng lặp game
        clock = pygame.time.Clock()
        running = True
        camera_x, camera_y = 0, 0
        
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        running = False
            
            # Điều khiển camera
            keys = pygame.key.get_pressed()
            camera_x -= 5 if keys[pygame.K_LEFT] else 0
            camera_x += 5 if keys[pygame.K_RIGHT] else 0
            camera_y -= 5 if keys[pygame.K_UP] else 0
            camera_y += 5 if keys[pygame.K_DOWN] else 0
            
            # Giới hạn camera
            camera_x = max(0, min(camera_x, map_pixel_width - screen_width/zoom))
            camera_y = max(0, min(camera_y, map_pixel_height - screen_height/zoom))
            
            # Vẽ map
            screen.fill((0, 0, 0))
            for layer in tmx_data.visible_layers:
                if isinstance(layer, pytmx.TiledTileLayer):
                    for x, y, gid in layer:
                        tile = tmx_data.get_tile_image_by_gid(gid)
                        if tile:
                            pos_x = (x * tmx_data.tilewidth - camera_x) * zoom
                            pos_y = (y * tmx_data.tileheight - camera_y) * zoom
                            scaled_tile = pygame.transform.scale(
                                tile, 
                                (int(tmx_data.tilewidth * zoom), int(tmx_data.tileheight * zoom))
                            )
                            screen.blit(scaled_tile, (pos_x, pos_y))
            
            pygame.display.flip()
            clock.tick(60)
        
        pygame.quit()
        return True
    
    except Exception as e:
        print(f"ERROR: {str(e)}")
        return False

# Sử dụng
if __name__ == "__main__":
    map_file = "media/map/map1.tmx"  # Thay đổi đường dẫn
    if os.path.exists(map_file):
        load_and_display_map(map_file)
    else:
        print(f"ERROR: Map file not found at {map_file}")