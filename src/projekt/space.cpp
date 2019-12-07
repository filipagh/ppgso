#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "garage.h"
#include "wall.h"
#include "space.h"
#include "game.h"
//#include "projectile.h"
//#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>

//// shared resources
//std::unique_ptr<ppgso::Mesh> Player::mesh;
//std::unique_ptr<ppgso::Texture> Player::texture;
//std::unique_ptr<ppgso::Shader> Player::shader;

Space::Space() {

    // Scale the default model
//  scale *= 3.0f;
//
//  // Initialize static resources if needed
//  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_light_glsl);
//  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("corsair.bmp"));
//  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("corsair.obj");
}

std::unique_ptr<Player> objPlayer;

void Space::init() {
    camera = std::make_unique<Camera>(120.0f, 1.0f, 0.1f, 1000.0f);
    camera->position = glm::vec3{0.0f, 0.0f, 1000.0f};
    camera->back = camera->position;
    camera->up = glm::vec3{0.0f, 1.0f, 0.0f};
    camera = move(camera);

    objPlayer = std::make_unique<Player>();
    objPlayer->scale = {10,10,10};
    objPlayer->position = {0, 0, 0};
    objects.push_back(move(objPlayer));

    std::unique_ptr<Wall> obj;
    obj = std::make_unique<Wall>();
    obj->scale = {1.0f,800.0f,.01f};
    obj->position = {400,0,-5.0f};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {1.0f,800.0f,.01f};
    obj->position = {-400,0,-5.0f};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {800.0f,1.0f,.01f};
    obj->position = {0,-400,-5.0f};
    objects.push_back(move(obj));

    obj = std::make_unique<Wall>();
    obj->scale = {800.0f,1.0f,.01f};
    obj->position = {0,400,-5.0f};
    objects.push_back(move(obj));

    int i = 0;
    std::unique_ptr<Asteroid> asteroid;
    for (i=0;i <=100;i++) {
        asteroid = std::make_unique<Asteroid>();
        objects.push_back(move(asteroid));
    }


}

void Space::keyEvent(int key, int scanCode, int action, int mods) {

//    if (key == GLFW_KEY_SPACE) {
//        // TODO: Add renderable object to the scene
//        int i = 5;
//        addParticle();//
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        Garage *garageSpace = new Garage();
        ParticleWindow::changeScene(garageSpace, true);
    } else if (key == GLFW_KEY_W) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{0,1,0};
    } else if (key == GLFW_KEY_A) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{-1,0,0};
    } else if (key == GLFW_KEY_S) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{0,-1,0};
    } else if (key == GLFW_KEY_D) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{1,0,0};
    }

}

void Space::render() {
    Scene::render();
}

void Space::update(float time, float dTime) {
    lightDirection = {1, 1, 1};
    Scene::update(time, dTime);
    camera->position = getPlayer()->position + glm::vec3{0,0,100};
    camera->back = glm::vec3{0,0,100};
    camera->update(time);
}

Object * Space::getPlayer() {
    auto p = std::begin(objects)->get();
    return p;
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
