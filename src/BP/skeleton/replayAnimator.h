#pragma once

#include <list>
#include <ppgso/ppgso.h>


class ReplayAnimator {

public:

    std::vector<std::vector<glm::vec3>> keyFrames;
    float startTime;
    float timePerKeyFrame{};

    ReplayAnimator(const std::string &bvh_file, float startTime);

    std::map<int, glm::quat> getKeyFrameData(float time);

    static std::vector<glm::vec3> getKeyFrameFromLine(const std::string &string);

    std::map<int, glm::quat> getKeyFrame(float d);

    std::map<int, glm::quat> interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d);
};
