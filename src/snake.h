#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeIsAtCell(int x, int y);

  // DONE : OOP Features * Access to private member variables by Member functions.
  Direction GetDirection() const;
  void SetDirection(Direction direction);
  float GetSpeed() const;
  int GetSize() const;
  void SetHeadXPosition(float x);
  void SetHeadYPosition(float y);
  float GetHeadPosX() const;
  float GetHeadPosY() const;
  bool IsAlive() const;
  void IncrementSpeedBy(float inc); // Increment speed
  const std::vector<SDL_Point> GetBody() const;
  

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  std::vector<SDL_Point> body;
  float head_x;
  float head_y;
  float speed{0.1f};
  bool alive{true};

  Direction direction = Direction::kUp;
  int size{1};
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif