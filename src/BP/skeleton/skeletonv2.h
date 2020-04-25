#pragma once
#include <ppgso/ppgso.h>
#include "fileLoader.h"
#include "bonev2.h"


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Skeletonv2 {
private:
public:

    Skeletonv2();

    static Skeletonv2* mockSkeleton();

    void updateSkeleton();


    std::map<int, Bonev2*> boneMap;
    std::map<int, glm::mat4> inverseBaseBoneMap;

    Bonev2* rootBone;
    std::string name = "";

    std::vector<glm::mat4> getSkeletonProjectionMatrix();

    int boneCount = 0;

    void addBone(Bonev2 *bone);
};

