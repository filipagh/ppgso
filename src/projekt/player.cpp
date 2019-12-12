#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "missile.h"
#include "orb.h"
//#include "projectile.h"
//#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <glm/gtx/euler_angles.hpp>

// shared resources
std::unique_ptr<ppgso::Mesh> Player::mesh;
std::unique_ptr<ppgso::Texture> Player::texture;
std::unique_ptr<ppgso::Shader> Player::shader;
Animator* Player::animator;
bool Player::isAnimatorSet = false;

Player::Player() {
  // Scale the default model
  scale *= 3.0f;

  // Initialize static resources if needed
  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_light_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("corsair.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("corsair.obj");

  asteroid = new Orb(this, true);
}



void Player::fireMissile(Scene &scene) {
    std::unique_ptr<Missile> missle;
    missle = std::make_unique<Missile>(*this);
    scene.addObject(move(missle));
}

bool Player::update(Scene &scene, float dt) {

    if (rotationAcceleration != glm::vec3{0,0,0}){
//        rotationAcceleration *= 0.001f;
        rotationSpeed += rotationAcceleration;
        rotationAcceleration = {0,0,0};

    }
    rotation += rotationSpeed * dt;
    acceleration = glm::orientate3(rotation) * acceleration;

  generateModelMatrix(dt);

  if (isAnimatorSet){
      modelMatrix = animator->getMatrix(scale,(float) glfwGetTime());
  }

  asteroid->update(scene,dt);

  return true;
}

void Player::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection);
  shader->setUniform("ViewPosition", scene.camera->position);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


  // render mesh

  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
    if (drawOrs) {
        asteroid->render(scene);
    }
}

void Player::onClick(Scene &scene) {
  std::cout << "Player has been clicked!" << std::endl;
}
