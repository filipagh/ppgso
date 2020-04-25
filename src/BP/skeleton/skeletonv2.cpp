
#include "src/BP/scene.h"
#include "skeleton.h"
#include "skeletonv2.h"
#include "bonev2.h"


Skeletonv2* Skeletonv2::mockSkeleton() {

    auto skel = new Skeletonv2;

    Bonev2 *b1 = new Bonev2( 1, 0, "Torso", glm::vec3{0,0,0} ,glm::vec3{0,5,0});
    Bonev2 *b2 = new Bonev2(2, 1,"Torso",  glm::vec3{0,5,0} ,glm::vec3{0,5,0});
    Bonev2 *b3 = new Bonev2(3, 2,"Torso",  glm::vec3{0,5,0} ,glm::vec3{0,5,0});

    skel->addBone(b1);
    skel->addBone(b2);
    skel->addBone(b3);

    return skel;
////
//    b2->addChild(*b3);
//    b1->addChild(*b2);
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
//
//    return new Skeleton();
}

Skeletonv2::Skeletonv2() {
}

void Skeletonv2::updateSkeleton() {
    rootBone->updateRootBone();
    if (inverseBaseBoneMap.empty()) {
        for (int i = 1; i<= boneCount; i++) {
            inverseBaseBoneMap[boneMap[i]->id] = glm::inverse(boneMap[i]->vector);
        }
    }
}

void Skeletonv2::addBone(Bonev2 *bone) {
    boneCount++;
    boneMap[bone->id] = bone;
    if (bone->parentId != 0) {
        Bonev2* parent = boneMap[bone->parentId];
        parent->addChild(bone);
    } else {
        rootBone = bone;
    }
}

std::vector<glm::mat4> Skeletonv2::getSkeletonProjectionMatrix() {
    std::vector<glm::mat4> vector;
    for (int i = 1; i<= boneCount; i++) {
        vector.push_back(boneMap[i]->vector * inverseBaseBoneMap[i]);
    }
    return vector;
}


