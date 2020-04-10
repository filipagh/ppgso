
#include "src/BP/scene.h"
#include "skeleton.h"



Skeleton* Skeleton::mockSkeleton() {
    Bone *b1 = new Bone(glm::vec3{1,0,0});
    Bone *b2 = new Bone(glm::vec3{1,2,0});
    Bone *b3 = new Bone(glm::vec3{0,1,0});
//
    b2->addChild(*b3);
    b1->addChild(*b2);
//

//
//    Bone *b1 = new Bone(glm::vec3{0.12110000 ,-0.05285040 ,-0.99121994});
//    Bone *b2 = new Bone(glm::vec3{-0.81329894 ,1.65925026 ,-0.76504004});
//    Bone *b3 = new Bone(glm::vec3{0.45799902 ,2.45542002 ,-2.45170021});
//    Bone *b4 = new Bone(glm::vec3{ -0.06579901 ,1.99352992 ,-3.69609928});
//    Bone *b5 = new Bone(glm::vec3{ -0.02790098 ,1.07680035 ,-1.68540108});
////
//    b4->addChild(*b5);
//    b3->addChild(*b4);
//    b2->addChild(*b3);
//    b1->addChild(*b2);

    return new Skeleton(*b1);
}

Skeleton::Skeleton(Bone &rootBone) {
    this->rootBone = &rootBone;
}

void Skeleton::updateSkeleton() {
    rootBone->updateRootBone();
}


