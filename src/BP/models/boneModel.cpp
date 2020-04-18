#include <glm/gtc/random.hpp>
#include "boneModel.h"

#include "src/BP/mainScene.h"


//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>
#include <glm/gtx/string_cast.hpp>


// Static resources
std::unique_ptr<ppgso::Mesh> BoneModel::mesh;
std::unique_ptr<ppgso::Texture> BoneModel::texture;
std::unique_ptr<ppgso::Shader> BoneModel::shader;

bool BoneModel::update(Scene &scene, float dt) {
    return true;
}

bool BoneModel::borderDie() {
    return (abs(static_cast<int>(position.x)) > 400 || abs(static_cast<int>(position.y)) > 400);
}

void BoneModel::render(Scene &scene) {
    // TODO: Render the object

//    std::cout << "out" << std::endl;
//    std::cout << to_string(bone->vector) << std::endl;
    shader->use();
    shader->setUniform("OverallColor", color);
    shader->setUniform("ModelMatrix", bone->vector);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();
}

void BoneModel::onClick(Scene &scene) {
}

BoneModel::BoneModel(Bone &bone) {
    color = glm::vec3{0,2,0};
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("bone.obj");
    this->bone = &bone;
}

