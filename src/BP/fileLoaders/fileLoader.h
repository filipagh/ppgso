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
};

