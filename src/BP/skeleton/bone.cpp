
#include "src/BP/scene.h"
#include "src/BP/skeleton/bone.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <glm/gtx/euler_angles.inl>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <src/BP/utils.h>

Bone::Bone(glm::vec3 boneLength) {
    this->boneLength = boneLength;
}

void Bone::addChild(Bone &bone) {
    this->childrenBones.push_back(&bone);
    bone.parrent = this;
}

void Bone::updateBone(quat parrentRotQuat) {

    this->generateModelMatrix(parrent->position, parrent->rotation);

    for (Bone *bone : this->childrenBones) {
        bone->updateBone(rotation);
    }

}

void Bone::updateRootBone() {
    glm::quat rotQuat = glm::quat(glm::vec3(glm::radians(0.0f),glm::radians(0.0f),glm::radians(0.0f)));


    this->generateModelMatrix({0, 0, 0}, rotQuat);
    for (Bone *bone : this->childrenBones) {
        bone->updateBone(this->rotation);
    }
}

void Bone::generateModelMatrix(glm::vec3 parentPos, quat parentRotationQuat) {
    glm::quat quat = Utils::RotationBetweenVectors({0,1,0},{boneLength});

    glm::quat finalQuat = quat * parentRotationQuat;
    glm::mat4 rotMat = glm::toMat4(finalQuat);
    this->vector =
             glm::translate(glm::mat4{1}, parentPos)
             * rotMat
             * glm::scale(glm::mat4(1.0f), glm::vec3{1,glm::length(boneLength),1});

    this->position = parentPos + (parentRotationQuat * boneLength);
    this->rotation = finalQuat;
}



//void Orb::generateModelMatrix(float deltaTime) {
//    Object::generateModelMatrix(deltaTime);
//    modelMatrix = parent->modelMatrix * modelMatrix;
//}