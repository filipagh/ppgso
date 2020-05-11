
#include "src/BP/skeleton/boneMapper.h"
#include "replayAnimator.h"
#include <map>
#include <algorithm>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <src/BP/mapper/mapperItem.h>
//#include <glm/ext/quaternion_float.hpp>

ReplayAnimator* BoneMapper::replayAnimator = nullptr;
std::vector<MapperItem> BoneMapper::mappingData = {};

std::map<int, glm::quat> BoneMapper::initDataForBasePositionOfSkeleton(int numberOfBones) {
    std::map<int, glm::quat> data;
    for (int i = 1; i <= numberOfBones; i++) {
         data[i] = glm::quat(glm::vec3(glm::radians(0.0f),glm::radians(0.0f),glm::radians(0.0f)));
    }
    return data;
}

std::map<int, glm::quat> BoneMapper::getData(int count, Skeletonv2 *skeleton) {

      std::map<int, glm::quat> a;
//    return  a;
    return BoneMapper::replayAnimator->getKeyFrameData( (float) glfwGetTime());

}

std::map<int, glm::quat> BoneMapper::applyMapping(std::vector<glm::vec3> inputRotation) {
    std::map<int, glm::quat> exportMap = {};

    for (auto &mapItem : BoneMapper::mappingData) {
        glm::quat modelRot = BoneMapper::calculateRotation(mapItem, inputRotation[mapItem.mocapBoneId - 1]);
        exportMap[mapItem.modelBoneId] = modelRot;
    }

    return exportMap;

};

glm::quat BoneMapper::calculateRotation(MapperItem &mapperItem, glm::vec3 mocapRotationXYZ) {
    float modelXAngle = 0;
    float angleX = BoneMapper::getRotationValueForAxis(mapperItem.modelXAxisMapping, mocapRotationXYZ);
    float mocapRange = (mapperItem.mocapMaxXAxisRotation - mapperItem.mocapMinXAxisRotation);
    float modelRange = (mapperItem.modelMaxXAxisRotation - mapperItem.modelMinXAxisRotation);
    if (mocapRange != 0) {
        modelXAngle = (angleX * (modelRange /mocapRange)) +
                      mapperItem.modelMinXAxisRotation;
    }

    float modelYAngle = 0;
    float angleY = BoneMapper::getRotationValueForAxis(mapperItem.modelYAxisMapping, mocapRotationXYZ);
    mocapRange = (mapperItem.mocapMaxYAxisRotation - mapperItem.mocapMinYAxisRotation);
    if (mocapRange != 0) {
        modelYAngle = (angleY * ((mapperItem.modelMaxYAxisRotation - mapperItem.modelMinYAxisRotation) /
                                 mocapRange)) +
                      mapperItem.modelMinYAxisRotation;
    }

    float modelZAngle = 0;
    float angleZ = BoneMapper::getRotationValueForAxis(mapperItem.modelZAxisMapping, mocapRotationXYZ);
    mocapRange = (mapperItem.mocapMaxZAxisRotation - mapperItem.mocapMinZAxisRotation);
    modelRange = (mapperItem.modelMaxZAxisRotation - mapperItem.modelMinZAxisRotation);
    if (mocapRange != 0) {
        modelZAngle = (angleZ * (modelRange /mocapRange)) +
                      mapperItem.modelMinZAxisRotation;
    }
    
    return glm::quat(glm::vec3(glm::radians(modelXAngle), glm::radians(modelYAngle), glm::radians(modelZAngle)));
}

float BoneMapper::getRotationValueForAxis(char mapping, glm::vec3 vec) {
    switch (mapping) {
        case 'x':
            return vec.x;
        case 'y':
            return vec.y;
        case 'z':
            return vec.z;
        default:
            return 0;
    }
}

void BoneMapper::loadMappingFile(const std::string &bm_file) {
    std::vector<MapperItem> data;

    std::ifstream head(bm_file);

    std::string line;
    while (!head.eof()) {
        std::getline(head, line);
        if (line.empty()) {
            break;
        }
        data.push_back(MapperItem(line));
    }

    BoneMapper::mappingData = data;
}




