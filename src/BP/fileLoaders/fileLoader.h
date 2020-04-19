#pragma once
#include <list>
#include <ppgso/ppgso.h>
#include <src/BP/skeleton/skeleton.h>


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class FileLoader {
private:
    static Bone* loadBoneFromLine(std::basic_ifstream<char>* ifstream);

public:
    static Skeleton* loadSkeletonFromFile(std::string file);

    static void loadBoneRigFromFile(std::string file,  std::vector<int> &boneIds, std::vector<float > &boneWeights);

    static void loadBoneVertexFromLine(std::ifstream *pIfstream, std::vector<int> *pVector);

    static void loadVertexBoneWeightFromLine(std::ifstream *pIfstream, std::vector<float> *pVector);
};

