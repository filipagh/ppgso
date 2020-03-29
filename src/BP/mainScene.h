#pragma once
#include <ppgso/ppgso.h>
#include "scene.h"


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class MainScene final : public Scene {
private:
//  // Static resources (Shared between instances)
//  static std::unique_ptr<ppgso::Mesh> mesh;
//  static std::unique_ptr<ppgso::Shader> shader;
//  static std::unique_ptr<ppgso::Texture> texture;

  // Delay fire and fire rate
//  float fireDelay{0.0f};
//  float fireRate{0.1f};
//  glm::vec3 fireOffset{0.7f,0.0f,0.0f};
    void addParticle();

public:
  MainScene();

  void init() override;

  void keyEvent(int key, int scanCode, int action, int mods) override;

//  /*!
//   * Player click event
//   * @param scene
//   */
//  void onClick(Scene &scene) override ;
    void update(float time, float dTime);

    void addObject(std::unique_ptr<Object> obj);
};

