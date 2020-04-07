
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
//
//// shared resources
//std::unique_ptr<ppgso::Mesh> Wall::mesh;
//std::unique_ptr<ppgso::Texture> Wall::texture;
//std::unique_ptr<ppgso::Shader> Wall::shader;
//
//Wall::Wall() {
//  // Scale the default model
////  scale *= 3.0f;
//
//  // Initialize static resources if needed
//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_light_glsl);
//  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("textura.bmp"));
//  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("untitled.obj");
//}
//
//bool Wall::update(Scene &scene, float dt) {
//  // Fire delay increment
//  fireDelay += dt;
//
//
//
//  generateModelMatrix(dt);
//  return true;
//}
//
//void Wall::render(Scene &scene) {
//  shader->use();
//
//  // Set up light
//  shader->setUniform("LightDirection", scene.lightDirection);
//  shader->setUniform("ViewPosition", scene.camera->position);
//
//  // use camera
//  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
//  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
//
//  // render mesh
//  shader->setUniform("ModelMatrix", modelMatrix);
//
//  shader->setUniform("Texture", *texture);
//  mesh->render();
//}
//
//void Player::onClick(Scene &scene) {
//  std::cout << "Player has been clicked!" << std::endl;
//}

Bone::Bone(glm::vec3 boneLength) {
    this->boneLength = boneLength;
}

void Bone::addChild(Bone &bone) {
    this->childrenBones.push_back(&bone);
    bone.parrent = this;
}

void Bone::updateBone() {
    this->generateModelMatrix(parrent->position);
    for (Bone *bone : this->childrenBones) {
        bone->updateBone();
    }

}

void Bone::updateRootBone() {
    this->generateModelMatrix({0, 0, 0});
    for (Bone *bone : this->childrenBones) {
        bone->updateBone();
    }
}

void Bone::generateModelMatrix(glm::vec3 position) {
    glm::quat quat = Utils::RotationBetweenVectors({0,1,0},{boneLength});
    glm::mat4 rotMat = glm::toMat4(quat);
    this->vector =
             glm::translate(glm::mat4{1}, position)
             * rotMat;

//                   * glm::scale(glm::mat4(1.0f), glm::vec3{1,glm::length(boneLength),1});
    if (parrent != NULL) {
//        this->vector = parrent->vector * this->vector;
    }
    this->position = position + boneLength;
}



//void Orb::generateModelMatrix(float deltaTime) {
//    Object::generateModelMatrix(deltaTime);
//    modelMatrix = parent->modelMatrix * modelMatrix;
//}