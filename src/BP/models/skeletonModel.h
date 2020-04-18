#pragma once
#include <memory>

#include <ppgso/ppgso.h>
#include <src/BP/skeleton/skeleton.h>

#include "src/BP/scene.h"
#include "src/projekt/object.h"
#include "src/BP/models/boneModel.h"

/*!
 * Simple asteroid object
 * This sphere object represents an instance of mesh geometry
 * It initializes and loads all resources only once
 * It will move down along the Y axis and self delete when reaching below -10
 */
class SkeletonModel: public Object {
private:
  Skeleton *skeleton;
  std::list<BoneModel> boneModels;


public:

    SkeletonModel(Skeleton *skeleton);

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
    void renderSkeleton();

    void renderBone(Bone &bone);
};

