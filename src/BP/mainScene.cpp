
#include "scene.h"
#include "mainScene.h"



#include "skeletonModel.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <src/BP/skeleton/fileLoader.h>
#include <src/BP/skeleton/skeleton.h>
#include <src/BP/fileLoaders/fileLoader.h>


//// shared resources
//std::unique_ptr<ppgso::Mesh> Player::mesh;
//std::unique_ptr<ppgso::Texture> Player::texture;
//std::unique_ptr<ppgso::Shader> Player::shader;

MainScene::MainScene() {

}

void MainScene::init() {
    camera = std::make_unique<Camera>(120.0f, 1.0f, 0.1f, 100000.0f);
    camera->position = camera->positionBase;
    camera->back = camera->position;
    camera->up = glm::vec3{0.0f, 1.0f, 0.0f};
    camera = move(camera);



    std::unique_ptr<SkeletonModel> obj;
    obj = std::make_unique<SkeletonModel>(FileLoader::loadSkeletonFromFile("humanSkel"));
    objects.push_back(move(obj));


//    std::unique_ptr<Wall> obj;
//    obj = std::make_unique<Wall>();
////    obj->scale = {10.0f,10.0f,.01f};
////    obj->position = {0,0,-5.0f};
////    obj->rotation = {90*ppgso::PI/180,0,0};
//    objects.push_back(move(obj));
//
//
//
//
//    std::unique_ptr<Asteroid> bone;
//    bone = std::make_unique<Asteroid>();
////    obj->scale = {10.0f,10.0f,.01f};
////    obj->position = {0,0,-5.0f};
////    obj->rotation = {90*ppgso::PI/180,0,0};
//    objects.push_back(move(bone));



//    std::unique_ptr<Player> objPlayer;
//    objPlayer = std::make_unique<Player>();
//    objPlayer->scale = {10.0f,10.0f,10};
//    objPlayer->position = {0,-4,0};
//    objPlayer->rotation = {90*ppgso::PI/180,0,0};
//    objects.push_back(move(objPlayer));

}

void MainScene::keyEvent(int key, int scanCode, int action, int mods) {

    if (key == GLFW_KEY_SPACE) {
        // TODO: Add renderable object to the scene
        int i = 5;
//        addParticle();
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        // TODO: Add renderable object to the scene

//        Player::animator = new Animator((float) glfwGetTime());
//        Player::isAnimatorSet = true;
//        Space* sceneSpace = new Space(10);
//        ParticleWindow::changeScene(sceneSpace, true);

    }
    if (key == GLFW_KEY_RIGHT ) {
        camera->angleX-=10;
        handleCameraAnglesX();

    }
    if (key == GLFW_KEY_LEFT ) {
        camera->angleX+=10;
        handleCameraAnglesX();
    }
    if (key == GLFW_KEY_UP ) {
        camera->angleY-=10;
        handleCameraAnglesX();
    }
    if (key == GLFW_KEY_DOWN ) {
        camera->angleY+=10;
        handleCameraAnglesX();
    }


}

void MainScene::handleCameraAnglesX() {
    int m_radius = 500;
    float x = m_radius * glm::sin(glm::radians((float) camera->angleY)) * glm::sin(glm::radians((float) camera->angleX));
    float y = m_radius * glm::cos(glm::radians((float) camera->angleY));
    float z = m_radius * glm::sin(glm::radians((float) camera->angleY)) * cosf(glm::radians((float) camera->angleX));

    camera->position = {x,y,z};

    camera->back = camera->position;
}

void MainScene::update(float time, float dTime) {
    lightDirection = {-2,0,0};
    Scene::update(time, dTime);
}
void MainScene::addObject(std::unique_ptr<Object> obj) {
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
