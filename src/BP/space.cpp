#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "mainScene.h"
#include "wall.h"
#include "space.h"
#include "game.h"
//#include "projectile.h"
//#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <util.h>
#include <glm/gtx/euler_angles.hpp>

//// shared resources
int Space::asteroidCount;
int Space::playerScore;
Space::Space(int asteroidCount) {
    Space::asteroidCount = asteroidCount;
    Space::playerScore = 0;
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
    objPlayer->rotation = {0,-90*ppgso::PI/180,0};
//    objPlayer->position = {0, 4000, 0};
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
    for (i=0;i <asteroidCount;i++) {
        asteroid = std::make_unique<Asteroid>();
        objects.push_back(move(asteroid));
    }


}
void Space::addObject(std::unique_ptr<Object> obj)  {
    objects.push_back(move(obj));
}
void Space::keyEvent(int key, int scanCode, int action, int mods) {

//    if (key == GLFW_KEY_SPACE) {
//        // TODO: Add renderable object to the scene
//        int i = 5;
//        addParticle();//
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        MainScene *garageSpace = new MainScene();
        ParticleWindow::changeScene(garageSpace, true);
    } else if (key == GLFW_KEY_W) {
        getPlayer()->acceleration = getPlayer()->acceleration + (glm::vec3 {0,3,0});
    } else if (key == GLFW_KEY_A) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{-3,0,0};
    } else if (key == GLFW_KEY_S) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{0,-3,0};
    } else if (key == GLFW_KEY_D) {
       getPlayer()->acceleration = getPlayer()->acceleration + glm::vec3{3,0,0};
    } else if (key == GLFW_KEY_Q) {
        getPlayer()->rotationAcceleration = getPlayer()->rotationAcceleration + glm::vec3{0,30*ppgso::PI/180,0};
    } else if (key == GLFW_KEY_E) {
        getPlayer()->rotationAcceleration = getPlayer()->rotationAcceleration + glm::vec3{0,-30*ppgso::PI/180,0};
    } else if (key == GLFW_KEY_T) {
        getPlayer()->rotationSpeed = {0,0,0};
    } else if (key == GLFW_KEY_SPACE) {
        getPlayer()->fireMissile(*this);
    } else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        cameraMapMod = !cameraMapMod;
    } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
      getPlayer()->drawOrs=!getPlayer()->drawOrs;
    }
}

void Space::render() {
    Scene::render();
}

void Space::update(float time, float dTime) {
    if (!Space::asteroidCount) {
        MainScene *garageSpace = new MainScene();
        ParticleWindow::changeScene(garageSpace, true);
        return;
    }

    lightDirection = {1, 1, 1};
    Scene::update(time, dTime);
    if (cameraMapMod) {
        camera->position = glm::vec3{0,0,300};
        camera->back = glm::vec3{0,0,300};
    } else {
        camera->position = getPlayer()->position + glm::vec3{0, 0, 100};
        camera->back = glm::vec3{0, 0, 100};
    }
    camera->update(time);
}

Player * Space::getPlayer() {

    auto p = std::begin(objects)->get();
    auto player = dynamic_cast<Player*>(p);
    return player;
}

