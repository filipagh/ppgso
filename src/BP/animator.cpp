#include "camera.h"
#include "scene.h"
#include "player.h"
#include "mainScene.h"
#include "game.h"
#include "space.h"


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





    Animator::Animator(float time) {
        animation.startTime = time;
        Frame f0;
        f0.time=0;
        f0.position= {0,-4,0};
        f0.rotation= {90*ppgso::PI/180,0,0};
        animation.frames.push_back(f0);
        Frame f1;
        f1.time=3;
        f1.position= {0,0,0};
        f1.rotation= {90*ppgso::PI/180,0,0};
        animation.frames.push_back(f1);
        Frame f2;
        f2.time=10;
        f2.position= {0,0,0};
        f2.rotation= {30*ppgso::PI/180,0,0};
        animation.frames.push_back(f2);
        Frame f3;
        f3.time=12;
        f3.position= {0,600,10};
        f3.rotation= {30*ppgso::PI/180,0,0};
        animation.frames.push_back(f3);
    }

void Animator::startAnimation(float time) {

}

glm::mat4 Animator::getMatrix(glm::vec3 scale, float time) {

    float animationTime = time - animation.startTime;

    if (animationTime > 12) {
        Player::isAnimatorSet= false;
        Space* sceneSpace = new Space(100);
        ParticleWindow::changeScene(sceneSpace, true);
    }

    Frame frameLeft = getFrame(animationTime);
    Frame frameRight = getNextFrame(frameLeft);

    float dTime;
        dTime = (animationTime - frameLeft.time) / (frameRight.time - frameLeft.time);

    glm::vec3 newPos =  glm::mix(frameLeft.position,frameRight.position,dTime);
    glm::vec3 newRot =  glm::mix(frameLeft.rotation,frameRight.rotation,dTime);



    glm::mat4 modelMatrix =
            glm::translate(glm::mat4(1.0f), newPos)
            * glm::orientate4(newRot)
            * glm::scale(glm::mat4(1.0f), scale);


    return modelMatrix;
}

Animator::Frame Animator::getFrame(float time) {
    if (time > 10.9){
        int a = 9;
    }

    Frame minFrame = animation.frames[0];

    for (int i=1; i < animation.frames.size(); i++) {
        Frame f = animation.frames[i];
        if (f.time< time) {
            minFrame = f;
        } else if (f.time >time) {
            break;
        }
    }
    return minFrame;
}

Animator::Frame Animator::getNextFrame(Animator::Frame frame) {
    Frame nextFrame= animation.frames[animation.frames.size()-1];

    for (int i=1; i < animation.frames.size(); i++) {
        Frame f = animation.frames[i];
        if (f.time>frame.time ) {
            nextFrame = f;
            break;
        }
    }

    return nextFrame;
}


