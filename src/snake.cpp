#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  Body prev_cell{
      static_cast<int>(head.x),
      static_cast<int>(head.y),head.angle};  // We first capture the head's cell before updating.
  UpdateHead();
  Body current_cell{
      static_cast<int>(head.x),
      static_cast<int>(head.y),head.angle};  // Capture the head's cell after updating.

  // Update all of the GetBody() vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  head.angle = static_cast<double>(direction);
  switch (direction) {
    case Direction::kUp:
      head.y -= speed;
      break;

    case Direction::kDown:
      head.y += speed;
      break;

    case Direction::kLeft:
      head.x -= speed;
      break;

    case Direction::kRight:
      head.x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head.x = fmod(head.x + grid_width, grid_width);
  head.y = fmod(head.y + grid_height, grid_height);
}

void Snake::UpdateBody(Snake::Body &current_head_cell, Snake::Body &prev_head_cell) {
  // Add previous head location to vector
  GetBody().push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    GetBody().erase(GetBody().begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : GetBody()) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeIsAtCell(int x, int y) {
  if (x == static_cast<int>(head.x) && y == static_cast<int>(head.y)) {
    return true;
  }
  for (auto const &item : GetBody()) {
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
  head.x = x;
}

void Snake::SetHeadYPosition(float y)
{
  head.y = y;
}

void Snake::SetDirection(Direction direction)
{
  Snake::direction = direction;
}

float Snake::GetHeadPosX() const
{
  return head.x;
}

float Snake::GetHeadPosY() const
{
  return head.y;
}

bool Snake::IsAlive() const
{
  return alive;
}

void Snake::IncrementSpeedBy(float inc)
{
  speed += abs(inc);
}

std::vector<Snake::Body>& Snake::GetBody()
{
  return body;
}

Snake::Head& Snake::GetHead()
{
  return head;
}

void Snake::SetHeadAngle(double angle)
{
  head.angle = angle;
}

double Snake::GetHeadAngle() const
{
  return head.angle;
}

