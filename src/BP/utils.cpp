#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include "utils.h"

using namespace glm;

quat Utils::RotationBetweenVectors(vec3 start, vec3 dest) {
    start = normalize(start);
    dest = normalize(dest);

    float cosTheta = dot(start, dest);
    vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions :
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        // This implementation favors a rotation around the Up axis,
        // since it's often what you want to do.
        rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
        if (length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = normalize(rotationAxis);
        return angleAxis(glm::radians(180.0f), rotationAxis);
    }

    // Implementation from Stan Melax's Game Programming Gems 1 article
    rotationAxis = cross(start, dest);

    float s = sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;

    return quat(
            s * 0.5f,
            rotationAxis.x * invs,
            rotationAxis.y * invs,
            rotationAxis.z * invs
    );


    //TODO credit https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp
    //http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/


}
