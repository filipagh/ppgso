#include <glm/gtc/random.hpp>
#include "boneModel.h"

#include "src/BP/mainScene.h"
#include "cubeModel.h"


//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>
#include <glm/gtx/string_cast.hpp>
#include <src/BP/skeleton/bonev2.h>


// Static resources
std::unique_ptr<ppgso::Mesh> CubeModel::mesh;
std::unique_ptr<ppgso::Texture> CubeModel::texture;
std::unique_ptr<ppgso::Shader> CubeModel::shader;

bool CubeModel::update(Scene &scene, float dt) {
    return true;
}

bool CubeModel::borderDie() {
    return (abs(static_cast<int>(position.x)) > 400 || abs(static_cast<int>(position.y)) > 400);
}

void CubeModel::render(Scene &scene) {
    // TODO: Render the object

//    std::cout << "out" << std::endl;
//    std::cout << to_string(bone->vector) << std::endl;
    shader->use();
    shader->setUniform("OverallColor", color);
    shader->setUniform("ModelMatrix", glm::scale(bone->vector, glm::vec3(0.3f)));
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();
}

void CubeModel::onClick(Scene &scene) {
}

CubeModel::CubeModel(Bonev2 &bone) {
    color = glm::vec3{0,2,0};
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
    this->bone = &bone;
}

