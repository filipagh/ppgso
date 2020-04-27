#pragma once
#include <list>
#include <ppgso/ppgso.h>
#include "replayAnimator.h"


class BoneMapper {

public:
    static ReplayAnimator *replayAnimator;

    static std::map<int, glm::quat> initDataForBasePositionOfSkeleton(int numberOfBones);

    static std::map<int, glm::quat> getData(int count);
};


