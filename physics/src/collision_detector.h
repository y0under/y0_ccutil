#ifndef Y0_CCUTIL_PHYSICS_COLLISION_DETECTOR_H
#define Y0_CCUTIL_PHYSICS_COLLISION_DETECTOR_H

#include "shapes.h"

class collision_detector {
  public:
    bool is_collision(shapes::circle a, shapes::circle b);
};

#endif
