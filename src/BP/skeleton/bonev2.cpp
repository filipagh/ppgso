
#include "src/BP/scene.h"
#include "bonev2.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <glm/gtx/euler_angles.inl>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <src/BP/utils.h>

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

void Bonev2::updateBone(quat parrentRotQuat) {

    this->generateModelMatrix(parrent->position, parrent->rotation);

    for (Bonev2 *bone : this->childrenBones) {
        bone->updateBone(rotation);
    }

}

void Bonev2::updateRootBone() {
    this->temp++;
    auto presun = glm::vec3(0,0,0);
    glm::quat rotQuat = glm::quat(glm::vec3(glm::radians(0.0f),glm::radians(0.0f),glm::radians(0.0f)));

    this->generateRootModelMatrix(presun, rotQuat);
    for (Bonev2 *bone : this->childrenBones) {
        bone->updateBone(this->rotation);
    }
}

void Bonev2::generateModelMatrix(glm::vec3 parentPos, quat parentRotationQuat) {
//    glm::quat quat = Utils::RotationBetweenVectors({0,1,0},{boneLength});

//    glm::quat finalQuat = quat * parentRotationQuat;
//    glm::quat finalQuat = parentRotationQuat;
    glm::quat myRot;

  if (this->id == 2 && this->parrent->temp > 5) {
      myRot = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(50.0f), glm::radians(0.0f)));
  } else {
      myRot = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f)));
  }


    glm::mat4 rotMat = glm::toMat4(myRot);
    this->vector =
             glm::translate(glm::mat4{1}, this->offset)
             * rotMat;

    this->vector = parrent->vector * this->vector;
//
//    this->position = parentPos + (parentRotationQuat * boneLength);
//    this->rotation = parentRotationQuat;
}

void Bonev2::generateRootModelMatrix(glm::vec3 globalOffset, quat globalRotation) {
//    glm::quat quat = Utils::RotationBetweenVectors({0,1,0},{boneLength});

//    glm::quat finalQuat = quat * parentRotationQuat;
//    glm::quat finalQuat = parentRotationQuat;

    glm::quat myRot = glm::quat(glm::vec3(glm::radians(0.0f),glm::radians(0.0f),glm::radians(0.0f)));
    glm::mat4 rotMat = glm::toMat4(myRot * globalRotation);
    this->vector =
             glm::translate(glm::mat4{1}, this->offset + globalOffset)
             * rotMat;


//    this->vector = parrent->vector * this->vector;
//
//    this->position = parentPos + (parentRotationQuat * boneLength);
//    this->rotation = parentRotationQuat;
}



//void Orb::generateModelMatrix(float deltaTime) {
//    Object::generateModelMatrix(deltaTime);
//    modelMatrix = parent->modelMatrix * modelMatrix;
//}