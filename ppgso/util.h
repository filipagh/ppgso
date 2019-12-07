#pragma once

namespace ppgso {

    class Util {
    public:
        static int randomUInt(int to, int from = 0);

        static int random_plus_minus();

        static bool randomBool();

        static int randomInt(int distance, int from = 0);

        static float randomFloat(float distance, float from = 0);
    };
}

