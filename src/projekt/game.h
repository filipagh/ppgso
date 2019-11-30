//
// Created by fagh on 23. 11. 2019.
//

#ifndef PPGSO_GAME_H
#define PPGSO_GAME_H



class ParticleWindow : public ppgso::Window  {
private:
    static Scene* activScene;
public:

    ParticleWindow(std::string title, int width, int height);
    static void changeScene(Scene *scene, bool init);
    void onKey(int key, int scanCode, int action, int mods) override;
    void onIdle() override;
};
#endif //PPGSO_GAME_H
