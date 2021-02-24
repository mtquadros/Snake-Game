#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  // Each element of Direction relates to direction is moving to and angle the snake has to be rendered  
  enum class Direction { kUp = 0, kDown = 180, kLeft = 270, kRight = 90 };

  struct Body {
    int x;
    int y;
    double angle;
  };

  struct Head {
    float x;
    float y;
    double angle;
  };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head({static_cast<float>(grid_width / 2), static_cast<float>(grid_height / 2), 0}) {}


  // Rubric point : OOP Features - 5th requirement: Classes encapsulate behaviour
  void Update();
  void GrowBody();
  bool SnakeIsAtCell(int x, int y);
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
  void SetHeadAngle(double angle);
  double GetHeadAngle() const;
  std::vector<Body>& GetBody();
  Head& GetHead();
  

 private:
  void UpdateHead();
  void UpdateBody(Body &current_head_cell, Body &prev_head_cell);

  std::vector<Body> body;
  Head head;
  //float head_x;
  //float head_y;
  float speed{0.1f};
  bool alive{true};

  Direction direction = Direction::kUp;
  int size{1};
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif