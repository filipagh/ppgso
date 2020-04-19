#version 330
// The inputs will be fed by the vertex buffer objects
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 3) in ivec3 BoneIds;
layout(location = 4) in vec3 BoneWeights;

// Matrices as program attributes
uniform mat4 ViewMatrix;
uniform mat4 SkeletonModelMatrix[20];
uniform mat4 ProjectionMatrix;

// This will be passed to the fragment shader
out vec2 texCoord;


void main() {


//    if (BoneIds[0] == 2) {
//        gl_Position = ProjectionMatrix * ViewMatrix * SkeletonModelMatrix[3] * vec4(Position, 1.0) ;
//    }else {
//        gl_Position = ProjectionMatrix * ViewMatrix  * vec4(Position, 1.0);
//    }
//
//    if (BoneIds[0] == 4) {
//        gl_Position = ProjectionMatrix * ViewMatrix  * vec4(Position, 1.0);
//    }else if (BoneIds[0] == 3) {
//        gl_Position = ProjectionMatrix * ViewMatrix  * vec4(Position, 1.0);
//    }else if (BoneIds[0] == 2) {
//        gl_Position = ProjectionMatrix * ViewMatrix  * vec4(Position, 1.0);
//    }

//    if (BoneIds[0] == 4) {
//        gl_Position = ProjectionMatrix * ViewMatrix * SkeletonModelMatrix[3] * vec4(Position, 1.0);
//    }else if (BoneIds[0] == 3) {
//        gl_Position = ProjectionMatrix * ViewMatrix * SkeletonModelMatrix[2] * vec4(Position, 1.0);
//    }else if (BoneIds[0] == 2) {
//        gl_Position = ProjectionMatrix * ViewMatrix * SkeletonModelMatrix[1] * vec4(Position, 1.0);
//    }else {
////        gl_Position = ProjectionMatrix * ViewMatrix  * vec4(Position, 1.0);
//    }


//        gl_Position = ProjectionMatrix * ViewMatrix *  SkeletonModelMatrix[BoneIds[0]-1] * vec4(Position, 1.0);
        gl_Position = ProjectionMatrix * ViewMatrix * SkeletonModelMatrix[0] * vec4(Position, 1.0);


//
//    vec4 totalPos = vec4(0.0);
//
//    int boneI = BoneIds[0];
//    int counter = 0;
//    while (boneI != 0) {
//        boneI--;
//        vec4 posePosition = SkeletonModelMatrix[boneI] * vec4(Position, 1.0);
//        totalPos += posePosition * BoneWeights[counter];
//        boneI++;
//        counter++;
//        if (counter == 3) {
//            break;
//        }
//        boneI = BoneIds[counter];
//    }

    // Copy the input to the fragment shader
    texCoord = TexCoord;

    // Calculate the final position on screen
//    gl_Position = ProjectionMatrix * ViewMatrix * totalPos;

}
