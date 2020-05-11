
#include "map"
//#include <glm/ext/quaternion_float.hpp>
#include <sstream>
#include "replayAnimator.h"
#include "boneMapper.h"

ReplayAnimator::ReplayAnimator(const std::string &bvh_file, float startTime) {
    this->startTime = startTime;

    std::ifstream head(bvh_file);
    std::string ignor;
    do {
        head >> ignor;
    } while (ignor != "MOTION");
    head >> ignor >> ignor >> ignor >> ignor;
    head >> this->timePerKeyFrame;
    std::string line;
    std::getline(head, line);  // end line

    while (!head.eof()) {
        std::getline(head, line);
        if (line == "") {
            break;
        }
        this->keyFrames.push_back(getKeyFrameFromLine(line));
    }
}


std::vector<glm::vec3> ReplayAnimator::getKeyFrameFromLine(const std::string &string) {
    float x,y,z;
    std::stringstream head(string);
    head >> z >> x >> y; // ignor offset;

    std::vector<glm::vec3> data;
    while (!head.eof()) {
//        head >> z >> y >> x;
//todo add axis recognison
        head >> z >> x >> y;
        data.emplace_back(x,y,z);
    }
    return data;
}

std::map<int, glm::quat> ReplayAnimator::getKeyFrameData(float time) {
    float deltaTime = fmodf(time,(this->timePerKeyFrame * ((float)this->keyFrames.size() - 1)));
    auto data = this->getKeyFrame(deltaTime);

    return data;
}

std::map<int, glm::quat> ReplayAnimator::getKeyFrame(float d) {
    float timeDivPerFrame = d / this->timePerKeyFrame;
    float timeModPerFrame = fmodf(d, this->timePerKeyFrame);

    auto modelKeyFrame = BoneMapper::applyMapping(this->keyFrames[(int)timeDivPerFrame]);
    if (timeModPerFrame != 0) {
        modelKeyFrame = interpolateKeyFrames(modelKeyFrame,
                                             BoneMapper::applyMapping(this->keyFrames[(int) timeDivPerFrame + 1]),
                                             timeModPerFrame);
    }


    return modelKeyFrame;
}
//
//glm::quat ReplayAnimator::getQuatFromEuler(float x, float y, float z) {
//    return glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
//}

//
std::map<int, glm::quat> ReplayAnimator::interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d) {
    std::map<int, glm::quat> data;
    for (auto &boneRot : map) {
        int index = boneRot.first;
        data[index] = glm::mix(boneRot.second,map1[index],d);
    }
    return data;
}

