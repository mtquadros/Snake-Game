#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height, const std::size_t display_width, const std::size_t display_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height),
      display_width(display_width), display_height(display_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  // Rubric point: Memory Management - 7th requirement
  PtrDeleter ptr_deleter;
  // Rubric point: Memory Management - 6th requirement
  // Create Window
  sdl_window = std::unique_ptr<SDL_Window, PtrDeleter>(nullptr, ptr_deleter);
  sdl_window.reset(SDL_CreateWindow("Snake Game - [Press q to quit]", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  // Rubric point: Memory Management - 6th requirement
  // Create renderer
  sdl_renderer = std::unique_ptr<SDL_Renderer, PtrDeleter>(nullptr, ptr_deleter);
  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_surf_food = std::unique_ptr<SDL_Surface,PtrDeleter>(nullptr,ptr_deleter);
  sdl_surf_head = std::unique_ptr<SDL_Surface,PtrDeleter>(nullptr,ptr_deleter);
  sdl_surf_body = std::unique_ptr<SDL_Surface,PtrDeleter>(nullptr,ptr_deleter);
  sdl_surf_tail = std::unique_ptr<SDL_Surface,PtrDeleter>(nullptr,ptr_deleter);
  sdl_surf_food.reset(SDL_LoadBMP(img_food));
  sdl_surf_head.reset(SDL_LoadBMP(img_head));
  sdl_surf_body.reset(SDL_LoadBMP(img_body));
  sdl_surf_tail.reset(SDL_LoadBMP(img_tail));

  if (!sdl_surf_food || !sdl_surf_head || !sdl_surf_body || !sdl_surf_tail)
    {
      std::cout << "Error loading image: " << SDL_GetError() << std::endl;
      exit(1);
    }
  
  sdl_text_food = std::unique_ptr<SDL_Texture, PtrDeleter>(nullptr,ptr_deleter);
  sdl_text_head = std::unique_ptr<SDL_Texture, PtrDeleter>(nullptr,ptr_deleter);
  sdl_text_body = std::unique_ptr<SDL_Texture, PtrDeleter>(nullptr,ptr_deleter);
  sdl_text_tail = std::unique_ptr<SDL_Texture, PtrDeleter>(nullptr,ptr_deleter);

  sdl_text_food.reset(SDL_CreateTextureFromSurface(sdl_renderer.get(),sdl_surf_food.get()));
  sdl_text_head.reset(SDL_CreateTextureFromSurface(sdl_renderer.get(),sdl_surf_head.get()));
  sdl_text_body.reset(SDL_CreateTextureFromSurface(sdl_renderer.get(),sdl_surf_body.get()));
  sdl_text_tail.reset(SDL_CreateTextureFromSurface(sdl_renderer.get(),sdl_surf_tail.get()));
}

Renderer::~Renderer() {
 SDL_Quit();
}

// Rubric point: Memory management - 1st requirement
void Renderer::Render(Snake &snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderCopyEx(sdl_renderer.get(), sdl_text_food.get(), nullptr, &block, 0, nullptr, SDL_FLIP_NONE);

  // Render snake's body
  if (!snake.GetBody().empty())
    { 
      for (auto body = snake.GetBody().begin() + 1; body != snake.GetBody().end(); body++){
        block.x = body->x * block.w;
        block.y = body->y * block.h;
        // render the body but the tail
        SDL_RenderCopyEx(sdl_renderer.get(), sdl_text_body.get(), nullptr, &block, body->angle, nullptr, SDL_FLIP_NONE);
      }
      // render the tail
      auto body = snake.GetBody().front();
      block.x = body.x * block.w;
      block.y = body.y * block.h;
      SDL_RenderCopyEx(sdl_renderer.get(), sdl_text_tail.get(), nullptr, &block, body.angle, nullptr, SDL_FLIP_NONE);
    }
      // Render snake's head
      block.x = static_cast<int>(snake.GetHeadPosX()) * block.w;
      block.y = static_cast<int>(snake.GetHeadPosY()) * block.h;
      if (snake.IsAlive()) {
        //SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
      } else {
        //SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
      }
  SDL_RenderCopyEx(sdl_renderer.get(), sdl_text_head.get(), nullptr, &block, snake.GetHead().angle, nullptr, SDL_FLIP_NONE);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

 // Rubric point: Memory management - 1st requirement
void Renderer::UpdateWindowTitle(int const &score, int const &fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
