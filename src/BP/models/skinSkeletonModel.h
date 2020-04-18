#pragma once
#include <memory>

#include <ppgso/ppgso.h>
#include <src/BP/skeleton/skeleton.h>
#include <meshSkeleton.h>

#include "src/BP/scene.h"
#include "src/projekt/object.h"

/*!
 * Simple asteroid object
 * This sphere object represents an instance of mesh geometry
 * It initializes and loads all resources only once
 * It will move down along the Y axis and self delete when reaching below -10
 */
class SkinSkeletonModel final : public Object {
private:


  static std::unique_ptr<ppgso::MeshSkeleton> mesh;
  static std::unique_ptr<ppgso::Shader> shader;
  static std::unique_ptr<ppgso::Texture> texture;
  glm::vec3 color{0,20,0};


public:
    SkinSkeletonModel();

  /*!
   * Update asteroid
   * @param scene Scene to interact with
   * @param dt Time delta for animation purposes
   * @return
   */
  bool update(Scene &scene, float dt) override;

  /*!
   * Render asteroid
   * @param scene Scene to render in
   */
  void render(Scene &scene) override;

  /*!
   * Custom click event for asteroid
   */
  void onClick(Scene &scene) override;

private:
    bool borderDie();
};

