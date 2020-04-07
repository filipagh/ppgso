
#include "src/BP/scene.h"
#include "skeleton.h"



Skeleton* Skeleton::mockSkeleton() {
    Bone *b1 = new Bone(glm::vec3{1,0,0});
    Bone *b2 = new Bone(glm::vec3{1,1,0});
    Bone *b3 = new Bone(glm::vec3{0,1,0});
//
    b2->addChild(*b3);
    b1->addChild(*b2);

    return new Skeleton(*b1);
}

Skeleton::Skeleton(Bone &rootBone) {
    this->rootBone = &rootBone;
}

void Skeleton::updateSkeleton() {
    rootBone->updateRootBone();
}


