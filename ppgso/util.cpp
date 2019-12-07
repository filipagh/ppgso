#include <cstdlib>
#include <glm/gtc/random.hpp>
#include "util.h"


int ppgso::Util::randomUInt(int to, int from) {
        return (rand() % (to - from)) + from;
    }

int ppgso::Util::random_plus_minus() {
    if (randomBool())
        return 1;
    else
        return -1;
    }

bool ppgso::Util::randomBool() {
        return (bool) (rand() % 2);
}

int ppgso::Util::randomInt(int distance, int from) {
    return randomUInt(distance,from) * random_plus_minus();
}

float ppgso::Util::randomFloat(float distance, float from) {
    float tmp = glm::linearRand(from,distance);
    if (randomBool()) {
        return -tmp;
    }
    return tmp;

}





