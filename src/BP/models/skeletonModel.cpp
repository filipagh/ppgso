#include <glm/gtc/random.hpp>
#include "src/BP/models/boneModel.h"

#include "src/BP/mainScene.h"

#include "skeletonModel.h"
//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug/shaders/color_vert_glsl.h>
#include <cmake-build-debug/shaders/color_frag_glsl.h>
#include <util.h>



bool SkeletonModel::update(Scene &scene, float dt) {
    return true;
}

void SkeletonModel::render(Scene &scene) {
    for (BoneModel bone : boneModels) {
        bone.render(scene);
    }
}

void SkeletonModel::onClick(Scene &scene) {}

SkeletonModel::SkeletonModel(Skeleton *skeleton) {
    this->skeleton = skeleton;
    this->skeleton->updateSkeleton();
    this->renderSkeleton();
}

void SkeletonModel::renderSkeleton() {
    this->renderBone(*(this->skeleton->rootBone));
}

void SkeletonModel::renderBone(Bone &bone) {
    for (Bone *childBone : bone.childrenBones) {
    renderBone(*childBone);
    }
    boneModels.push_back(*(new BoneModel(bone)));
}

