
#include <sstream>
#include "src/BP/fileLoaders/fileLoader.h"


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

void FileLoader::loadBoneRigFromFile(std::string file, std::vector<int> &boneIds, std::vector<float> &boneWeights) {
    std::ifstream input(file);

    std::string lineType;
    while (input >> lineType)
    {
        if (lineType == "vb") {
            FileLoader::loadBoneVertexFromLine(&input, &boneIds);
        } else if (lineType == "vbv") {
            FileLoader::loadVertexBoneWeightFromLine(&input, &boneWeights);
        }
    }

}

void FileLoader::loadBoneVertexFromLine(std::ifstream *pIfstream, std::vector<int> *pVector) {
    int b1,b2,b3;
    *pIfstream >> b1 >> b2 >> b3;
    pVector->push_back(b1);
    pVector->push_back(b2);
    pVector->push_back(b3);
}

void FileLoader::loadVertexBoneWeightFromLine(std::ifstream *pIfstream, std::vector<float> *pVector) {
    float b1,b2,b3;
    *pIfstream >> b1 >> b2 >> b3;
    pVector->push_back(b1);
    pVector->push_back(b2);
    pVector->push_back(b3);
}
