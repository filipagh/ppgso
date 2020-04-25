#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "src/projekt/object.h"


using namespace glm;

class Utils {

public:

    static quat RotationBetweenVectors(vec3 start, vec3 dest);

};

