
#include "map"
#include <glm/ext/quaternion_float.hpp>
#include <sstream>
#include "replayAnimator.h"

std::map<int, glm::quat> ReplayAnimator::getKeyFrameData(float time) {
    float deltaTime = fmodf(time,(this->timePerKeyFrame * (float)this->keyFrames.size()));
    auto data = this->getKeyFrame(deltaTime);
if (data.empty()) {
    int a = 4;
}
    return data;
}

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

    int c = 0;
    while (!head.eof()) {
        if (c == 713) {
            int cc = 4;
        }
        c++;
        std::getline(head, line);
        if (line == "") {
            break;
        }
        this->keyFrames.push_back(getKeyFrameFromLine(line));
    }
}

std::map<int, glm::quat> ReplayAnimator::getKeyFrameFromLine(const std::string& string) {
    float x,y,z;
    std::stringstream head(string);
    head >> x >> y >> z; // ignor offset;

    int counter = 1;
    std::map<int, glm::quat> data;
    while (!head.eof()) {
        head >> z >> y >> x;
        data[counter] = ReplayAnimator::getQuatFromEuler(x, y, z);;
        counter++;
    }
    return data;
}

glm::quat ReplayAnimator::getQuatFromEuler(float x, float y, float z) {
    return glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
}

std::map<int, glm::quat> ReplayAnimator::getKeyFrame(float d) {
    float timeDivPerFrame = d / this->timePerKeyFrame;
    float timeModPerFrame = fmodf(d, this->timePerKeyFrame);
    if (timeModPerFrame == 0) {
        return this->keyFrames[(int)timeDivPerFrame];
    }
    auto lastFrame = this->keyFrames[(int)timeDivPerFrame];
    auto nextFrame = this->keyFrames[(int)timeDivPerFrame + 1];

    return this->interpolateKeyFrames(lastFrame,nextFrame,timeModPerFrame);
}

std::map<int, glm::quat>
ReplayAnimator::interpolateKeyFrames(std::map<int, glm::quat> map, std::map<int, glm::quat> map1, float d) {
    std::map<int, glm::quat> data;
    for (auto &boneRot : map) {
        int index = boneRot.first;
        data[index] = glm::mix(boneRot.second,map1[index],d);
    }
    return data;
}

