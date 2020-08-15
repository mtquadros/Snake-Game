#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"
#include "snake.h"

// Rubric point: Memory Management - Sixth requirement
class PtrDeleter{
    public:
      PtrDeleter(){}
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

<<<<<<< HEAD
  // Rubric point: Memory management - First requirement
=======
  // Memory management - First requirement
>>>>>>> 3be7ee733506fd656c13a5eb14eff8c247cf230f
  void UpdateWindowTitle(int const &score, int const &fps);

 private:
  // Rubric point: Memory Management - Sixth requirement
  std::unique_ptr<SDL_Window, PtrDeleter> sdl_window;
  std::unique_ptr<SDL_Renderer, PtrDeleter> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

};

#endif