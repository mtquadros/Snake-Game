#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  SetHeadXPosition(fmod(GetHeadPosX() + grid_width, grid_width));
  SetHeadYPosition(fmod(GetHeadPosY() + grid_height, grid_height));
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeIsAtCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
// DONE : OOP Features * Access to private member variables by member functions.
Snake::Direction Snake::GetDirection() const
{
  return direction;
}

int Snake::GetSize() const
{
  return size;
}

float Snake::GetSpeed() const
{
  return speed;
}

void Snake::SetHeadXPosition(float x)
{
  head_x = x;
}

void Snake::SetHeadYPosition(float y)
{
  head_y = y;
}

void Snake::SetDirection(Direction direction)
{
  Snake::direction = direction;
}

float Snake::GetHeadPosX() const
{
  return head_x;
}

float Snake::GetHeadPosY() const
{
  return head_y;
}

bool Snake::IsAlive() const
{
  return alive;
}

void Snake::IncrementSpeedBy(float inc)
{
  speed += abs(inc);
}

const std::vector<SDL_Point> Snake::GetBody() const
{
  return body;
}