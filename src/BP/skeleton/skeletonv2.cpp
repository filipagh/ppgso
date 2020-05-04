
#include <glm/gtx/quaternion.hpp>
#include "src/BP/scene.h"
#include "skeletonv2.h"
#include "bonev2.h"
#include "boneMapper.h"


Skeletonv2::Skeletonv2() {
}

void Skeletonv2::updateSkeleton(glm::mat4 modelBaseMat) {
    if (inverseBaseBoneMap.empty()) {
        rootBone->updateBones(generateSkeletonBaseMatrix({0, 0, 0}),
                              BoneMapper::initDataForBasePositionOfSkeleton(this->boneCount));
        for (int i = 1; i <= boneCount; i++) {
            inverseBaseBoneMap[boneMap[i]->id] = glm::inverse(boneMap[i]->vector);
        }
    }
    rootBone->updateBones(modelBaseMat, BoneMapper::getData(this->boneCount, this));
}

void Skeletonv2::addBone(Bonev2 *bone) {
    boneCount++;
    boneMap[bone->id] = bone;
    if (bone->parentId != 0) {
        Bonev2* parent = boneMap[bone->parentId];
        parent->addChild(bone);
    } else {
        rootBone = bone;
    }
}

std::vector<glm::mat4> Skeletonv2::getSkeletonProjectionMatrix() {
    std::vector<glm::mat4> vector;
    for (int i = 1; i<= boneCount; i++) {
        vector.push_back(boneMap[i]->vector * inverseBaseBoneMap[i]);
    }
    return vector;
}

glm::mat4 Skeletonv2::generateSkeletonBaseMatrix(glm::vec3 basePosition) {

    glm::quat baseRotation;
    baseRotation = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f)));

    glm::mat4 rotMat = glm::toMat4(baseRotation);
    auto baseMat =
            glm::translate(glm::mat4{1}, basePosition)
            * rotMat;

    return baseMat;
}


