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
    bool cameraMapMod = false;
public:
    static int asteroidCount;
    static int playerScore;

    /*!
     * Create a new player
     */
    Space(int asteroidCount = 100);
    void init() override;

    void keyEvent(int key, int scanCode, int action, int mods) override;


    void render() override ;

    void update(float time, float dTime) override ;

    Player * getPlayer();


    void addObject(std::unique_ptr<Object> obj);
};

