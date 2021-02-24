#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"
#include "snake.h"

// Rubric point: Object Oriented Programming - 7th requirement
// PtrDeleter properly destroy SDL_Window, SDL_Redender and SDL_Texture unique pointers
class PtrDeleter{
    public:
      PtrDeleter(){}

      // The operator () is oveloaded so the deleter knows how to destroy SDL_Window, SDL_Redender and SDL_Texture unique pointers
      void operator()(SDL_Window* p)
      {
        if (p != nullptr)
        {
          SDL_DestroyWindow(p); 
        }
      }
      void operator()(SDL_Renderer* p)
      {
        if (p != nullptr)
        {
          SDL_DestroyRenderer(p);
        }
      }
      void operator()(SDL_Texture* p)
      {
        if (p != nullptr)
        {
          SDL_DestroyTexture(p);
        }
      }
      void operator()(SDL_Surface* p)
      {
        if (p != nullptr)
        {
          SDL_FreeSurface(p);
        }
      }

};


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, const std::size_t display_width, const std::size_t display_height);
  ~Renderer();

  void Render(Snake &snake, SDL_Point const &food);

  // Rubric point: Memory management - 1st requirement
  void UpdateWindowTitle(int const &score, int const &fps);

 private:
  // Rubric point: Memory Management - 6th requirement
  std::unique_ptr<SDL_Window, PtrDeleter> sdl_window;
  std::unique_ptr<SDL_Renderer, PtrDeleter> sdl_renderer;

  std::unique_ptr<SDL_Surface, PtrDeleter> sdl_surf_food;
  std::unique_ptr<SDL_Surface, PtrDeleter> sdl_surf_head;
  std::unique_ptr<SDL_Surface, PtrDeleter> sdl_surf_body;
  std::unique_ptr<SDL_Surface, PtrDeleter> sdl_surf_tail;

  std::unique_ptr<SDL_Texture, PtrDeleter> sdl_text_food;
  std::unique_ptr<SDL_Texture, PtrDeleter> sdl_text_head;
  std::unique_ptr<SDL_Texture, PtrDeleter> sdl_text_body;
  std::unique_ptr<SDL_Texture, PtrDeleter> sdl_text_tail;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::size_t display_width;
  const std::size_t display_height;
  const char* img_food = "../food.bmp";
  const char* img_head = "../head.bmp";
  const char* img_body = "../body.bmp";
  const char* img_tail = "../tail.bmp";
};

#endif