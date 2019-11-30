#pragma once

#include <ppgso/ppgso.h>
#include "src/projekt/scene.h"


/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Space final : public Scene {
private:

public:
    /*!
     * Create a new player
     */
    Space();

    void init() override;

    void keyEvent(int key, int scanCode, int action, int mods) override;

//  /*!
//   * Player click event
//   * @param scene
//   */
//  void onClick(Scene &scene) override ;
};

