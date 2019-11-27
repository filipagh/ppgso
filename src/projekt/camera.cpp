#include <glm/glm.hpp>

#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (ppgso::PI/180.0f) * fow;

  projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float time) {
//

//  viewMatrix = lookAt(position, position-back, up);
//  double angle = 90 * fmodf(time,4.0f);

    position = {5*sin(time),0,5*cos(time)};

//  viewMatrix = glm::mat4{1};
//    viewMatrix = translate(viewMatrix, {0,0,-5});
//    viewMatrix = rotate(viewMatrix,time,{0,1.0f,0});
//    glm::mat4 aa = viewMatrix;
//    position = {aa[3][0],aa[3][1],aa[3][2]};
    viewMatrix = glm::lookAt(position, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
    }

glm::vec3 Camera::cast(double u, double v) {
  // Create point in Screen coordinates
  glm::vec4 screenPosition{u,v,0.0f,1.0f};

  // Use inverse matrices to get the point in world coordinates
  auto invProjection = glm::inverse(projectionMatrix);
  auto invView = glm::inverse(viewMatrix);

  // Compute position on the camera plane
  auto planePosition = invView * invProjection * screenPosition;
  planePosition /= planePosition.w;

  // Create direction vector
  auto direction = glm::normalize(planePosition - glm::vec4{position,1.0f});
  return glm::vec3{direction};
}
