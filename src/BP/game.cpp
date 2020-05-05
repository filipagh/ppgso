#include "camera.h"
#include "scene.h"

#include "mainScene.h"
#include "game.h"

//#include <src/BP/mocapHandFiles/SynLab.h>

#include <iostream>
#include <utility>
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
#include <src/BP/fileLoaders/fileLoader.h>
#include <src/BP/skeleton/replayAnimator.h>

const unsigned int SIZE = 1028;

Scene* ParticleWindow::activScene = nullptr;
Scene* ParticleWindow::rendersScene = nullptr;


int main() {
    // Create new window
//
//    auto a = SynGetVersion();
//
//    Skeleton s;
//    SynReadSkeleton(&s,R"(C:\Users\PC\Desktop\Synertial_SDK_v3_0_Extended\RightGlove7Latest.sk)");
//
//    SynHubInfo info[4];
//    uint32_t num = 4;
//
//
//        SynInit();
//        int code = SynEnumerate(info, &num,(uint32_t) 1000);
//        SynHandle h;
//        code = SynOpen(&h,&info[0].UID,NULL);
//        SynFrame f;
//
//
//            code = SynRead(h, &f);
//            TransformedSensors p;
//    code = SynApplyTransformation(&p,&f,-1);
//    code = SynRead(h, &f);
//    code = SynApplyTransformation(&p,&f,-2);
//    code = SynRead(h, &f);
//    code = SynApplyTransformation(&p,&f,0);
//    code = SynApplyPose(&s,&p);


    auto window = ParticleWindow{"BP", SIZE, SIZE};
    MainScene sceneGarage = {};
    ParticleWindow::changeScene(&sceneGarage, true);
//    window.changeScene(&sceneGarage, true);


    // Main execution loop
    while (window.pollEvents()) {}
    return EXIT_SUCCESS;
}




//public:
ParticleWindow::ParticleWindow(std::string title, int width, int height) : Window(std::move(title), width, height) {
        // Initialize OpenGL state
        // Enable Z-buffer
//        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
void ParticleWindow::onKey(int key, int scanCode, int action, int mods)  {
        // Collect key state in a map
        ParticleWindow::rendersScene->keyEvent(key, scanCode, action, mods);

//        keys[key] = action;
//        if (keys[GLFW_KEY_SPACE]) {
//            // TODO: Add renderable object to the scene
//            int i = 5;
////            addParticle();
//    }
    }

    void ParticleWindow::onIdle() {
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

        rendersScene = activScene;
        rendersScene->lightDirection = {3*sin(time),0,3*cos(time)};
        rendersScene->update(time,dTime);
        rendersScene->render();

    }

void ParticleWindow::changeScene(Scene *scene, bool init) {
        if (ParticleWindow::activScene != nullptr) {
//            free(ParticleWindow::activScene);
        }
        ParticleWindow::activScene = scene;
        if (init) {
            ParticleWindow::activScene->init();
        }
}
