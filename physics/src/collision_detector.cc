#include "collision_detector.h"

bool collision_detector::is_collision(
      shapes::circle a, shapes::circle b) {
  auto distance_x = a.center_x - b.center_x;
  auto distance_y = a.center_y - b.center_y;

  return (a.radius + b.radius) * (a.radius + b.radius) > distance_x *distance_x + distance_y *distance_y;
}
