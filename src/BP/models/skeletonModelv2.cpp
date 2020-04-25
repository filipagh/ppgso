#include <glm/gtc/random.hpp>
#include "src/BP/models/boneModel.h"

#include "src/BP/mainScene.h"

#include "skeletonModel.h"
#include "skeletonModelv2.h"
//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>
#include <src/BP/skeleton/bonev2.h>


bool SkeletonModelv2::update(Scene &scene, float dt) {
    skeleton->updateSkeleton();
    return true;
}

void SkeletonModelv2::render(Scene &scene) {
    for (CubeModel bone : boneModels) {
        bone.render(scene);
    }
}

void SkeletonModelv2::onClick(Scene &scene) {}

SkeletonModelv2::SkeletonModelv2(Skeletonv2 *skeleton) {
    this->skeleton = skeleton;
    this->skeleton->updateSkeleton();
    this->renderSkeleton();
}

void SkeletonModelv2::renderSkeleton() {
    this->renderBone(*(this->skeleton->rootBone));
}

void SkeletonModelv2::renderBone(Bonev2 &bone) {
    for (Bonev2 *childBone : bone.childrenBones) {
    renderBone(*childBone);
    }
    boneModels.push_back(*(new CubeModel(bone)));
}

