
#include <src/BP/scene.h>
#include <src/BP/mainScene.h>
#include <src/BP/skeleton/boneMapper.h>






#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>
#include <src/BP/fileLoaders/fileLoader.h>
#include <src/BP/models/skinSkeletonModel.h>
#include <src/BP/models/skeletonModelv2.h>



MainScene::MainScene() {

}

void MainScene::init() {
    camera = std::make_unique<Camera>(120.0f, 1.0f, 0.1f, 100000.0f);
    camera->position = camera->positionBase;
    camera->back = camera->position;
    camera->up = glm::vec3{0.0f, 1.0f, 0.0f};
    camera = move(camera);

//    std::unique_ptr<SkeletonModelv2> objj;
//    objj = std::make_unique<SkeletonModelv2>(FileLoader::loadSkeletonFromFile("postavicka.sk"));
//    objects.push_back(move(objj));


    BoneMapper::replayAnimator = new ReplayAnimator("/home/filipagh/Desktop/fagh/p8.bvh", 0);
    std::unique_ptr<SkinSkeletonModel> obj;
    obj = std::make_unique<SkinSkeletonModel>("postavicka.obj", "postavicka.br", "postavicka.bmp", "postavicka.sk");
//    obj = std::make_unique<SkinSkeletonModel>("test.obj", "test.br", "postavicka.bmp", "test.sk");
    objects.push_back(move(obj));

}

void MainScene::keyEvent(int key, int scanCode, int action, int mods) {

    if (key == GLFW_KEY_SPACE) {
        // TODO: Add renderable object to the scene
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
    int m_radius = 10;
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

