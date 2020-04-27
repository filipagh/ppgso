
#include "bonev2.h"
#include <shaders/diffuse_vert_glsl.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Bonev2::Bonev2(int id, int parentId, std::string name, glm::vec3 offset, glm::vec3 boneLength) {
    this->id = id;
    this->name = name;
    this->parentId = parentId;
    this->offset = offset;
    this->boneLength = boneLength;
}

void Bonev2::addChild(Bonev2 *bone) {
    this->childrenBones.push_back(bone);
    bone->parrent = this;
}

void Bonev2::generateBoneMatrix(glm::mat4 parentMat, const std::map<int, glm::quat> &boneRotMat) {
    glm::mat4 rotMat = glm::toMat4(boneRotMat.at(id));
    this->vector =
            glm::translate(glm::mat4{1}, this->offset)
            * rotMat;

    this->vector = parentMat * this->vector;
}

void Bonev2::updateBones(glm::mat4 parentMat, const std::map<int, glm::quat> &boneRotMap) {

    this->generateBoneMatrix(parentMat, boneRotMap);
    for (Bonev2 *bone : this->childrenBones) {
        bone->updateBones(this->vector, boneRotMap);
    }
}




