#include <glm/gtc/random.hpp>
#include "asteroid.h"
#include "player.h"
#include "mainScene.h"
#include "game.h"
#include "missile.h"
//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>
#include <glm/gtx/euler_angles.hpp>


// Static resources
std::unique_ptr<ppgso::Mesh> Missile::mesh;
std::unique_ptr<ppgso::Texture> Missile::texture;
std::unique_ptr<ppgso::Shader> Missile::shader;

Missile::Missile(const Player& player) {

    this->speed = player.speed;
    this->acceleration = glm::orientate3(player.rotation) * glm::vec3{0,20,0};
    // todo pravit rychlost
    this->position = player.position + glm::orientate3(player.rotation) * glm::vec3{0,10,0};


//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("asteroid.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Missile::update(Scene &scene, float dt) {

    if (shouldBeDestroyed) {
        return false;
    }

    if (borderDie()) {
        return false;
    }

  // Collide with scene
  for (auto &obj : scene.objects) {
    // Ignore self in scene
    if (obj.get() == this) continue;

    // We only need to collide with asteroids and projectiles, ignore other objects
    auto asteroid = dynamic_cast<Asteroid*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
//    auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
    auto player = dynamic_cast<Player*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
    if (!asteroid && !player) continue;

    // Compare distance to approximate size of the asteroid estimated from scale.
    if (distance(position, obj->position) < (obj->scale.y + scale.y) * 0.7f) {

        if (player) {
            MainScene *sceneGarage = new MainScene();
            ParticleWindow::changeScene(sceneGarage, true);
            return false;
        }

      // The projectile will be destroyed
      if (asteroid) {
          asteroid->shouldBeDestroyed = true;
          return false;
      }
    }
  }

    generateModelMatrix(dt);
    return true;
}

bool Missile::borderDie() {
    return (abs(static_cast<int>(position.x)) > 400 || abs(static_cast<int>(position.y)) > 400);
}

//
//void Asteroid::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale, int pieces) {
//  // Generate explosion
//  auto explosion = std::make_unique<Explosion>();
//  explosion->position = explosionPosition;
//  explosion->scale = explosionScale;
//  explosion->speed = speed / 2.0f;
//  scene.objects.push_back(move(explosion));
//
//  // Generate smaller asteroids
//  for (int i = 0; i < pieces; i++) {
//    auto asteroid = std::make_unique<Asteroid>();
//    asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
//    asteroid->position = position;
//    asteroid->rotMomentum = rotMomentum;
//    float factor = (float) pieces / 2.0f;
//    asteroid->scale = scale / factor;
//    scene.objects.push_back(move(asteroid));
//  }
//}

void Missile::render(Scene &scene) {
    // TODO: Render the object
    shader->use();
    shader->setUniform("OverallColor", {255,0,0});
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();


//  shader->use();
//
//  // Set up light
//  shader->setUniform("LightDirection", scene.lightDirection);
//
//  // use camera
//  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
//  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
//
//  // render mesh
//  shader->setUniform("ModelMatrix", modelMatrix);
//  shader->setUniform("Texture", *texture);
//  mesh->render();
}

void Missile::onClick(Scene &scene) {
//  std::cout << "Asteroid clicked!" << std::endl;
//  explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
//  age = 10000;
}

