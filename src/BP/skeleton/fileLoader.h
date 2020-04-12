#pragma once
#include <list>
#include <ppgso/ppgso.h>


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Bone {
private:
    void updateBone(glm::quat parrentRotQuat);

public:

    std::list<Bone*> childrenBones;
    int parentId;
    Bone *parrent = nullptr;
    int id{};
    std::string name = "";
    glm::mat4 vector{1};

    glm::mat4 baseModelMatrix{1};
    glm::mat4 updatedModelMatrix{1};
    glm::vec3 boneVector;

    glm::vec3 position;
    glm::quat rotation;

    glm::vec3 boneLength;

    /**
     *
     * @param boneLength
     */
    Bone(int id, int parentId, std::string name, glm::vec3 boneLength);

    /**
     *
     * @param bone
     */
    void addChild(Bone *bone);


    void updateRootBone();

    void generateModelMatrix(glm::vec3 parentPos, glm::quat parentRotationQuat);
};

