#include <glm/gtc/random.hpp>
#include "asteroid.h"
#include "player.h"
#include "garage.h"
#include "game.h"
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
    this->speed = {ppgso::Util::randomFloat(0.01f),ppgso::Util::randomFloat(0.001f),0};
    this->position = { ppgso::Util::randomInt(350,20),ppgso::Util::randomInt(350,20),0.0f};
//    this->moveVector = {(float)  (-10 + rand() % 20 +1) / 1000000,(float)  (-10 + rand() % 20 +1) / 1000000,(float)  -( rand() % 20 +1) / 100};


  scale *= glm::linearRand(1.0f, 10.0f);
//  speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-5.0f, -10.0f), 0.0f};
//  rotation = glm::ballRand(ppgso::PI);
//  rotMomentum = glm::ballRand(ppgso::PI);

  // Initialize static resources if needed
//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("asteroid.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Asteroid::update(Scene &scene, float dt) {


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
            Garage *sceneGarage = new Garage();
            ParticleWindow::changeScene(sceneGarage, true);
            return false;
        }

      // The projectile will be destroyed
      if (asteroid) {
          asteroid->speed += speed;
          asteroid->acceleration += acceleration;
          return false;
      }
    }
  }


    this->position+=speed;

    if (borderDie()) {
        return false;
    }
    generateModelMatrix();
    return true;
}

bool Asteroid::borderDie() {
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

void Asteroid::render(Scene &scene) {
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

void Asteroid::onClick(Scene &scene) {
//  std::cout << "Asteroid clicked!" << std::endl;
//  explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
//  age = 10000;
}

