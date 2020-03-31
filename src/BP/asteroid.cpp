#include <glm/gtc/random.hpp>
#include "asteroid.h"
#include "player.h"
#include "mainScene.h"
#include "game.h"
#include "missile.h"
#include "space.h"
//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Asteroid::mesh;
std::unique_ptr<ppgso::Texture> Asteroid::texture;
std::unique_ptr<ppgso::Shader> Asteroid::shader;

Asteroid::Asteroid() {

    color = glm::vec3{0,2,0};
  if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);

//  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("asteroid.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("bone.obj");
//  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool Asteroid::update(Scene &scene, float dt) {
    generateModelMatrix(dt);
    return true;
}

bool Asteroid::borderDie() {
    return (abs(static_cast<int>(position.x)) > 400 || abs(static_cast<int>(position.y)) > 400);
}

void Asteroid::render(Scene &scene) {
    // TODO: Render the object
    shader->use();
    shader->setUniform("OverallColor", color);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();

}

void Asteroid::onClick(Scene &scene) {
//  std::cout << "Asteroid clicked!" << std::endl;
//  explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
//  age = 10000;
}

