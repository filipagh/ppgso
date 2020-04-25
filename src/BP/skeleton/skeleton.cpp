
#include "src/BP/scene.h"
#include "skeleton.h"



Skeleton* Skeleton::mockSkeleton() {
//    Bone *b1 = new Bone(glm::vec3{1,0,0});
//    Bone *b2 = new Bone(glm::vec3{1,2,0});
//    Bone *b3 = new Bone(glm::vec3{0,10,0});
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

Skeleton::Skeleton() {
}

void Skeleton::updateSkeleton() {
    rootBone->updateRootBone();
}

void Skeleton::addBone(Bone *bone) {
    boneCount++;
    boneMap[bone->id] = bone;
    if (bone->parentId != 0) {
        Bone* parent = boneMap[bone->parentId];
        parent->addChild(bone);
    } else {
        rootBone = bone;
    }
}

std::vector<glm::mat4> Skeleton::getSkeletonProjectionMatrix() {
    std::vector<glm::mat4> vector;
    for (int i = 1; i<= boneCount; i++) {
//        vector.push_back(glm::mat4(1));
        vector.push_back(boneMap[i]->vector);
    }
    return vector;
}


