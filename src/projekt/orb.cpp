#include <glm/gtc/random.hpp>
#include "asteroid.h"
#include "player.h"
#include "garage.h"
#include "game.h"
#include "missile.h"
#include "orb.h"
//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Orb::mesh;
std::unique_ptr<ppgso::Texture> Orb::texture;
std::unique_ptr<ppgso::Shader> Orb::shader;

Orb::Orb(Object* parent, bool hasChilds) {
    this->parent = parent;
    isParent = hasChilds;

    if (isParent){
        orb1 = new Orb(this, false);
        orb2 = new Orb(this, false);
        orb3 = new Orb(this, false);

    }


//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("asteroid.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Orb::update(Scene &scene, float dt) {
    float time = (float) glfwGetTime();
    if (!isParent) {
        time *= rand();
    }
    position = {sin(time),cos(time),0};

    generateModelMatrix(dt);
    if (isParent) {
        this->orb1->update(scene, dt);
        this->orb2->update(scene, dt);
        this->orb3->update(scene, dt);
    }
    return true;
}

bool Orb::borderDie() {
    return (abs(static_cast<int>(position.x)) > 400 || abs(static_cast<int>(position.y)) > 400);
}

void Orb::render(Scene &scene) {
    // TODO: Render the object
    shader->use();
    shader->setUniform("OverallColor", {255,0,0});
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();
    if  (isParent) {
        this->orb1->render(scene);
        this->orb2->render(scene);
        this->orb3->render(scene);
    }
}

void Orb::onClick(Scene &scene) {
}

void Orb::generateModelMatrix(float deltaTime) {
    Object::generateModelMatrix(deltaTime);
    modelMatrix = parent->modelMatrix * modelMatrix;
}

