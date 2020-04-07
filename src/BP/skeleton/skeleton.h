#pragma once
#include <ppgso/ppgso.h>
#include "bone.h"


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Skeleton {
private:
public:

    Skeleton(Bone &rootBone1);

    static Skeleton* mockSkeleton();

    void updateSkeleton();


    Bone* rootBone;
    std::string name = "";

};

