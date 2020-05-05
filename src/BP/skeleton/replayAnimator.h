#pragma once
#include <list>
#include <ppgso/ppgso.h>



class ReplayAnimator {

public:

    std::vector<std::vector<glm::vec3>> keyFrames;
    float startTime;
    float timePerKeyFrame{};

    ReplayAnimator(const std::string &bvh_file, float startTime);
//    static std::map<int, glm::quat> data ;

    std::array<std::vector<glm::vec3>,2> getKeyFrameData(float time);

     glm::quat getQuatFromEuler(float x, float y, float z);

     std::map<int, glm::quat> initDataForBasePositionOfSkeleton(int numberOfBones);

     std::map<int, glm::quat> getData(int count);

     std::vector<glm::vec3> getKeyFrameFromLine(const std::string &string);

    std::array<std::vector<glm::vec3>,2> getKeyFrames(float d);

    std::map<int, glm::quat> interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d);
};
