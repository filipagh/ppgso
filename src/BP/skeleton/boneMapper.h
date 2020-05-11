#pragma once
#include <list>
#include <ppgso/ppgso.h>
#include <src/BP/mapper/mapperItem.h>
#include "replayAnimator.h"
#include "skeletonv2.h"


class BoneMapper {

public:
    static ReplayAnimator *replayAnimator;

    static std::map<int, glm::quat> initDataForBasePositionOfSkeleton(int numberOfBones);

    static std::map<int, glm::quat> getData(int count, Skeletonv2 *skeleton);

    static void loadMappingFile(const std::string &bm_file);

    static std::vector<MapperItem> mappingData;

    static std::map<int, glm::quat> applyMapping(std::vector<glm::vec3> inputRotation);

    static glm::quat calculateRotation(MapperItem &mapperItem, glm::vec3 mocapRotationXYZ);

    static float getRotationValueForAxis(char mapping, glm::vec3 vec);

    std::map<int, glm::quat> interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d);
};


