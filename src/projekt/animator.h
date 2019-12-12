//
// Created by fagh on 23. 11. 2019.
//



class Animator {
private:

public:
struct Frame {
    float time;
    glm::vec3 position{0,0,0};
    glm::vec3 rotation{0,0,0};
};
    struct Animation {
        float startTime;
        std::vector<Frame> frames;
    };
    Animator(float time);

    Animation animation;
    void startAnimation(float time);
    glm::mat4 getMatrix(glm::vec3 scale, float time);

    Frame getFrame(float time);
    Frame getNextFrame(Frame frame);


};

