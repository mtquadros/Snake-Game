#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"
#include "snake.h"

// Rubric point: Memory Management - 6th requirement
// Deleter used to properly destroy Renderer::SDL_Window and Renderer::SDL_Redender members
class PtrDeleter{
    public:
      PtrDeleter(){}
      // Rubric point: Object Oriented Programming - 7th requirement
      // The operator () is oveloaded to allow the same deleter destroy SDL_Window and SDL_Renderer
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
};


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const &snake, SDL_Point const &food);

  // Rubric point: Memory management - 1st requirement
  void UpdateWindowTitle(int const &score, int const &fps);

 private:
  // Rubric point: Memory Management - 6th requirement
  std::unique_ptr<SDL_Window, PtrDeleter> sdl_window;
  std::unique_ptr<SDL_Renderer, PtrDeleter> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

};

#endif