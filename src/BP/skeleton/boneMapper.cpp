
#include "src/BP/skeleton/boneMapper.h"
#include "replayAnimator.h"
#include <map>
#include <algorithm>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <src/BP/mapper/mapperItem.h>
//#include <glm/ext/quaternion_float.hpp>

ReplayAnimator *BoneMapper::replayAnimator = nullptr;

std::map<int, glm::quat> BoneMapper::initDataForBasePositionOfSkeleton(int numberOfBones) {
    std::map<int, glm::quat> data;
    for (int i = 1; i <= numberOfBones; i++) {
        data[i] = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f)));
    }
    return data;
}

std::map<int, glm::quat> BoneMapper::getData(int count, Skeletonv2 *skeleton) {

    std::map<int, glm::quat> a;
    return  a;

    BoneMapper::replayAnimator->getKeyFrameData((float) glfwGetTime());
    return BoneMapper::applyMapping();

}

std::map<int, glm::quat> BoneMapper::applyMapping(std::map<int, glm::quat> inputMap) {
    std::map<int, glm::quat> exportMap = {};
//    std::map<int, int> mappingMap = {
//            {11, 9,},
//            {12, 10},
//            {13, 11}, // leftleg
//            {14, 14},
//            {15, 15},
//            {16, 16}, // rightleg
//            {5,  9},
//            {6,  10},
//            {7,  11},  // arm
//            {8,  9},
//            {9,  10},
//            {10, 11}     // arm
//    };

    std::map<int, int> mappingMap = {
            {11, 19,},
            {12, 20},
            {13, 21} // leftleg
//            {14, 14},
//            {15, 15},
//            {16, 16}, // rightleg
//            {5,  9},
//            {6,  10},
//            {7,  11},  // arm
//            {8,  9},
//            {9,  10},
//            {10, 11}     // arm
    };

    for (auto &mapIndex : mappingMap) {
        exportMap[mapIndex.first] = inputMap[mapIndex.second];
    }
    return exportMap;
};

void BoneMapper::loadMappingFile(const std::string &bvh_file) {
    std::vector<MapperItem> data;

    std::ifstream head(bvh_file);

    std::string line;
    while (!head.eof()) {
        std::getline(head, line);
        data.push_back(MapperItem(line));
    }

    BoneMapper::mappingData = data;
}




