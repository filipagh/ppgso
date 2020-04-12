
#include <sstream>
#include "fileLoader.h"

Skeleton* FileLoader::loadSkeletonFromFile(std::string file) {

    auto skeleton = new Skeleton();

    std::ifstream input(file);

    std::string lineType;
    while (input >> lineType)
    {
        if (lineType == "b") {
            skeleton->addBone(loadBoneFromLine(&input));
        }
    }
    return skeleton;
}

Bone* FileLoader::loadBoneFromLine(std::basic_ifstream<char>* ifstream) {
    int id;
    std::string name;
    int parentId;
    float x,y,z;
    *ifstream >> id >> name >> parentId >> x >> y >> z;

    return new Bone(id, parentId, name, glm::vec3(x, y, z));
}
