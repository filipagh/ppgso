#pragma once
#include <list>
#include <ppgso/ppgso.h>
#include "replayAnimator.h"
#include "skeletonv2.h"


class BoneMapper {

public:
    static ReplayAnimator *replayAnimator;

    static std::map<int, glm::quat> initDataForBasePositionOfSkeleton(int numberOfBones);

    static std::map<int, glm::quat> getData(int count, Skeletonv2 *skeleton);

    static std::map<int, glm::quat> applyMapping(std::map<int, glm::quat> inputMap);
};


