#pragma once
#include <list>
#include <ppgso/ppgso.h>



class ReplayAnimator {

public:

    std::vector<std::map<int, glm::quat>> keyFrames;
    float startTime;
    float timePerKeyFrame{};

    ReplayAnimator(const std::string &bvh_file, float startTime);
//    static std::map<int, glm::quat> data ;

     std::map<int, glm::quat> getKeyFrameData(float time);

     glm::quat getQuatFromEuler(float x, float y, float z);

     std::map<int, glm::quat> initDataForBasePositionOfSkeleton(int numberOfBones);

     std::map<int, glm::quat> getData(int count);

     std::map<int, glm::quat> getKeyFrameFromLine(const std::string& string);

    std::map<int, glm::quat> getKeyFrame(float d);

    std::map<int, glm::quat> interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d);
};
