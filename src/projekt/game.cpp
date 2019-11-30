#include "camera.h"
#include "scene.h"
#include "player.h"
#include "garage.h"

#include <iostream>
#include <vector>
#include <map>
#include <list>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
const unsigned int SIZE = 1028;

class ParticleWindow : public ppgso::Window {
private:
    // Scene of objects

    Scene* activScene;
    std::unique_ptr<Camera> camera;
    // Store keyboard state
//    std::map<int, int> keys;

//    void initSceneGame() {
//        camera = std::make_unique<Camera>(120.0f, 1.0f, 0.1f, 1000.0f);
//        camera->position = glm::vec3{0.0f, 0.0f, 10.0f};
//        camera->back = camera->position;
//        camera->up = glm::vec3{0.0f, 1.0f, 0.0f};
//        sceneGame.camera = move(camera);
//
//        std::unique_ptr<Player> objPlayer;
//        objPlayer = std::make_unique<Player>();
//        objPlayer->scale = {10.0f,10.0f,10};
//        objPlayer->position = {0,-4,0};
//        objPlayer->rotation = {90*ppgso::PI/180,0,0};
//        sceneGame.objects.push_back(move(objPlayer));
//    }

public:


     void changeScene(Scene *scene,bool init) {
        activScene = scene;
        activScene->init();
    }

    ParticleWindow() : Window{"task7_particles", SIZE, SIZE} {
        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

    }
    void onKey(int key, int scanCode, int action, int mods) override {
        // Collect key state in a map
        activScene->keyEvent(key, scanCode, action, mods);

//        keys[key] = action;
//        if (keys[GLFW_KEY_SPACE]) {
//            // TODO: Add renderable object to the scene
//            int i = 5;
////            addParticle();
//    }
    }
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();
        // Compute time delta
        float dTime = (float)glfwGetTime() - time;
        time = (float) glfwGetTime();
        // Set gray background
        glClearColor(.1f,.1f,.1f,1.0f);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Update all objects in scene
        // Because we need to delete while iterating this is implemented using c++ iterators
        // In most languages mutating the container during iteration is undefined behaviour

//        time/=10;
        activScene->lightDirection =    {3*sin(time),0,3*cos(time)};
        activScene->update(time,dTime);
        activScene->render();

    }
};
int main() {
    // Create new window
    auto window = ParticleWindow{};

    Garage sceneGarage = {};
//    ParticleWindow::changeScene(&sceneGarage, true);
    window.changeScene(&sceneGarage, true);


    // Main execution loop
    while (window.pollEvents()) {}
    return EXIT_SUCCESS;
}