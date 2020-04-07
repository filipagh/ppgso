#pragma once
#include <memory>

#include <ppgso/ppgso.h>
#include <src/BP/skeleton/skeleton.h>

#include "scene.h"
#include "src/projekt/object.h"
#include "boneModel.h"

using namespace glm;

class Utils {

public:

    static quat RotationBetweenVectors(vec3 start, vec3 dest);

};

