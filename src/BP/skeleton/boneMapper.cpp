
#include "src/BP/skeleton/boneMapper.h"
#include "replayAnimator.h"
#include <map>
#include <glm/ext/quaternion_float.hpp>

ReplayAnimator* BoneMapper::replayAnimator = nullptr;

std::map<int, glm::quat> BoneMapper::initDataForBasePositionOfSkeleton(int numberOfBones) {
    std::map<int, glm::quat> data;
    for (int i = 1; i <= numberOfBones; i++) {
         data[i] = glm::quat(glm::vec3(glm::radians(0.0f),glm::radians(0.0f),glm::radians(0.0f)));
    }
    return data;
}

std::map<int, glm::quat> BoneMapper::getData(int count) {
    return BoneMapper::replayAnimator->getKeyFrameData( (float) glfwGetTime());

}



