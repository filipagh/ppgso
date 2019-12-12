#include "wall.h"
#include "scene.h"



#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_light_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Wall::mesh;
std::unique_ptr<ppgso::Texture> Wall::texture;
std::unique_ptr<ppgso::Shader> Wall::shader;

Wall::Wall() {
  // Scale the default model
//  scale *= 3.0f;

  // Initialize static resources if needed
  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_light_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sphere.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool Wall::update(Scene &scene, float dt) {
  // Fire delay increment
  fireDelay += dt;

//  // Hit detection
//  for ( auto& obj : scene.objects ) {
//    // Ignore self in scene
//    if (obj.get() == this)
//      continue;
//
//    // We only need to collide with asteroids, ignore other objects
//    auto asteroid = dynamic_cast<Asteroid*>(obj.get());
//    if (!asteroid) continue;
//
//    if (distance(position, asteroid->position) < asteroid->scale.y) {
//      // Explode
//      auto explosion = std::make_unique<Explosion>();
//      explosion->position = position;
//      explosion->scale = scale * 3.0f;
//      scene.objects.push_back(move(explosion));
//
//      // Die
//      return false;
//    }
//  }

//  // Keyboard controls
//  if(scene.keyboard[GLFW_KEY_LEFT]) {
//    position.x += 10 * dt;
//    rotation.z = -ppgso::PI/4.0f;
//  } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
//    position.x -= 10 * dt;
//    rotation.z = ppgso::PI/4.0f;
//  } else {
//    rotation.z = 0;
//  }

//  // Firing projectiles
//  if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
//    // Reset fire delay
//    fireDelay = 0;
//    // Invert file offset
//    fireOffset = -fireOffset;
//
//    auto projectile = std::make_unique<Projectile>();
//    projectile->position = position + glm::vec3(0.0f, 0.0f, 0.3f) + fireOffset;
//    scene.objects.push_back(move(projectile));
//  }

  generateModelMatrix(dt);
  return true;
}

void Wall::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection);
  shader->setUniform("ViewPosition", scene.camera->position);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);

  shader->setUniform("Texture", *texture);
  mesh->render();
}
//
//void Player::onClick(Scene &scene) {
//  std::cout << "Player has been clicked!" << std::endl;
//}
