#pragma once
#include <ppgso/ppgso.h>

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

    void updateSkeleton(glm::mat4 modelBaseMat);

    std::map<int, glm::quat> boneActualPose;

    std::map<int, Bonev2*> boneMap;
    std::map<int, glm::mat4> inverseBaseBoneMap;

    Bonev2* rootBone;
    std::string name = "";

    std::vector<glm::mat4> getSkeletonProjectionMatrix();

    int boneCount = 0;

    void addBone(Bonev2 *bone);


    static glm::mat4 generateSkeletonBaseMatrix(glm::vec3 basePosition);
};

