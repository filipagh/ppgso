#pragma once
#include <list>
#include <ppgso/ppgso.h>


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Bonev2 {
private:
    void updateBone(glm::quat parrentRotQuat);

public:

    Bonev2(int id, int parentId, std::string name, glm::vec3 offset, glm::vec3 boneLength);

    std::list<Bonev2*> childrenBones;
    int parentId;
    Bonev2 *parrent = nullptr;
    int id{};
    std::string name = "";
    glm::mat4 vector{1};

    glm::mat4 baseModelMatrix{1};
    glm::mat4 updatedModelMatrix{1};
    glm::vec3 boneVector;

    glm::vec3 position;
    glm::quat rotation;

    glm::vec3 boneLength;


    glm::vec3 offset;

    void addChild(Bonev2 *bone);

    void generateRootModelMatrix(glm::vec3 globalOffset, glm::quat globalRotation);

    void generateModelMatrix(glm::vec3 parentPos, glm::quat parentRotationQuat);

    void updateRootBone();
};

