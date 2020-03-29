#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "object.h"

void Object::generateModelMatrix(float deltaTime) {
    if (acceleration != glm::vec3{0,0,0}) {
        speed += acceleration;
        acceleration = {0,0,0};
    }
    position += speed * deltaTime;
    modelMatrix =
            glm::translate(glm::mat4(1.0f), position)
            * glm::orientate4(rotation)
            * glm::scale(glm::mat4(1.0f), scale);
}
