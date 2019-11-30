#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "garage.h"
#include "wall.h"
#include "game.h"
#include "space.h"
//#include "projectile.h"
//#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>

//// shared resources
//std::unique_ptr<ppgso::Mesh> Player::mesh;
//std::unique_ptr<ppgso::Texture> Player::texture;
//std::unique_ptr<ppgso::Shader> Player::shader;

Garage::Garage() {

  // Scale the default model
//  scale *= 3.0f;
//
//  // Initialize static resources if needed
//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_light_glsl);
//  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("corsair.bmp"));
//  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("corsair.obj");
}

void Garage::init() {
    camera = std::make_unique<Camera>(120.0f, 1.0f, 0.1f, 1000.0f);
    camera->position = glm::vec3{0.0f, 0.0f, 4.0f};
    camera->back = camera->position;
    camera->up = glm::vec3{0.0f, 1.0f, 0.0f};
    camera = move(camera);



    std::unique_ptr<Wall> obj;
    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {0,0,-5.0f};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {5,0,0};
    obj->rotation = {0,0,-90*ppgso::PI/180};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {-5,0,0};
    obj->rotation = {0,0,-90*ppgso::PI/180};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {0,0,5};
    obj->rotation = {0,0,0};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {0,-5,0};
    obj->rotation = {90*ppgso::PI/180,0,0};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {10.0f,10.0f,.01f};
    obj->position = {0,5,0};
    obj->rotation = {90*ppgso::PI/180,0,0};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {2.0f,2.0f,2.00f};
    obj->position = {0,0,0};
    obj->rotation = {0,0,-45*ppgso::PI/180};
    objects.push_back(move(obj));


    std::unique_ptr<Player> objPlayer;
    objPlayer = std::make_unique<Player>();
    objPlayer->scale = {10.0f,10.0f,10};
    objPlayer->position = {0,-4,0};
    objPlayer->rotation = {90*ppgso::PI/180,0,0};
    objects.push_back(move(objPlayer));

}

void Garage::keyEvent(int key, int scanCode, int action, int mods) {

    if (key == GLFW_KEY_SPACE) {
        // TODO: Add renderable object to the scene
        int i = 5;
        addParticle();
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        // TODO: Add renderable object to the scene
        Space* sceneSpace = new Space();
        ParticleWindow::changeScene(sceneSpace, true);

    }


}

void Garage::addParticle() {
    auto obj = std::make_unique<Asteroid>();
    obj->scale = {10,1,1};
    objects.push_back(move(obj));
}



//bool Player::update(Scene &scene, float dt) {
////  // Fire delay increment
////  fireDelay += dt;
////
////  // Hit detection
////  for ( auto& obj : scene.objects ) {
////    // Ignore self in scene
////    if (obj.get() == this)
////      continue;
////
////    // We only need to collide with asteroids, ignore other objects
////    auto asteroid = dynamic_cast<Asteroid*>(obj.get());
////    if (!asteroid) continue;
////
////    if (distance(position, asteroid->position) < asteroid->scale.y) {
////      // Explode
////      auto explosion = std::make_unique<Explosion>();
////      explosion->position = position;
////      explosion->scale = scale * 3.0f;
////      scene.objects.push_back(move(explosion));
////
////      // Die
////      return false;
////    }
////  }
////
////  // Keyboard controls
////  if(scene.keyboard[GLFW_KEY_LEFT]) {
////    position.x += 10 * dt;
////    rotation.z = -ppgso::PI/4.0f;
////  } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
////    position.x -= 10 * dt;
////    rotation.z = ppgso::PI/4.0f;
////  } else {
////    rotation.z = 0;
////  }
////
////  // Firing projectiles
////  if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
////    // Reset fire delay
////    fireDelay = 0;
////    // Invert file offset
////    fireOffset = -fireOffset;
////
////    auto projectile = std::make_unique<Projectile>();
////    projectile->position = position + glm::vec3(0.0f, 0.0f, 0.3f) + fireOffset;
////    scene.objects.push_back(move(projectile));
////  }
//
//  generateModelMatrix();
//  return true;
//}
//
//void Player::render(Scene &scene) {
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
//
//  // render mesh
//
//  shader->setUniform("ModelMatrix", modelMatrix);
//  shader->setUniform("Texture", *texture);
//  mesh->render();
//}
//
//void Player::onClick(Scene &scene) {
//  std::cout << "Player has been clicked!" << std::endl;
//}
