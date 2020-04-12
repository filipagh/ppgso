#pragma once
#include <ppgso/ppgso.h>
#include "fileLoader.h"


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Skeleton {
private:
public:

    Skeleton();

    static Skeleton* mockSkeleton();

    void updateSkeleton();

    void addBone(Bone *bone);

    std::map<int, Bone*> boneMap;

    Bone* rootBone;
    std::string name = "";

};

