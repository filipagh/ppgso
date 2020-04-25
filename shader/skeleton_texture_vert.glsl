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


    mat4 totalPos = mat4(0);// final position vector

    int boneI = BoneIds[0];//actual processing bone
    int counter = 0;//while iterate counter
    while (boneI != 0) {
        boneI--;//negate offset


        totalPos += (SkeletonModelMatrix[boneI] * BoneWeights[counter]);
        boneI++;
        counter++;
        if (counter == 3) {
            break;
        }
        boneI = BoneIds[counter];
    }
    gl_Position = ProjectionMatrix * ViewMatrix *totalPos*  vec4(Position.xyz, 1);
//    gl_Position = ProjectionMatrix * ViewMatrix *totalPos*  vec4(Position, 1.0);



//
//    mat4 totalPos = mat4(0);// final position vector
//
//    int boneI = 1;//actual processing bone
//    int counter = 0;//while iterate counter
////    while (boneI != 0) {
//        boneI--;//negate offset
//
//
//        totalPos += (SkeletonModelMatrix[boneI] * 1.0);
//        boneI++;
//        counter++;
//        if (counter == 3) {
////            break;
//        }
//        boneI = BoneIds[counter];
////    }
//    gl_Position = ProjectionMatrix * ViewMatrix *totalPos*  vec4(Position.xyz, 1);
////    gl_Position = ProjectionMatrix * ViewMatrix *totalPos*  vec4(Position, 1.0);
//



//    **********************************************************************

    // example values
    //layout(location = 3) in ivec3 BoneIds;
    // 1 0 0
    // 1 2 3

    //layout(location = 4) in vec3 BoneWeights;
    // 1.0 0 0
    // 0.5 0.3 0.2

//    vec4 totalPos = vec4(0);   // final position vector
////    mat4 totalPos = mat4(0);   // final position vector
//
//    int boneI = BoneIds[0];  //actual processing bone
//    int counter = 0;        //while iterate counter
//    while (boneI != 0) {
//        boneI--;            //negate offset
//
//
////        totalPos += (SkeletonModelMatrix[boneI] * BoneWeights[counter]);
//
//        vec4 posePosition = SkeletonModelMatrix[boneI] * vec4(Position, 1.0);
//        totalPos += (posePosition * BoneWeights[counter]);
//        boneI++;
//        counter++;
//        if (counter == 3) {
//            break;
//        }
//        boneI = BoneIds[counter];
//    }
////    gl_Position = ProjectionMatrix * ViewMatrix * totalPos * vec4(Position, 1.0);
//
//
////        gl_Position = ProjectionMatrix * ViewMatrix * vec4(totalPos.xyz, 1);
//    //
//    //
//            gl_Position = ProjectionMatrix * ViewMatrix * totalPos;

//    //**********************************************************************


//    gl_Position = ProjectionMatrix * ViewMatrix* ((SkeletonModelMatrix[5] * vec4(Position, 1.0)));
//    gl_Position = ProjectionMatrix * ViewMatrix*  vec4(Position, 1.0);
    //**********************************************************************
    //    const float constant = 1;
    //    vec4 rawPosition = SkeletonModelMatrix[1] * vec4(Position, 1.0);
    //    vec4 newPosition = rawPosition * constant;
    //    gl_Position = ProjectionMatrix * ViewMatrix * vec4(newPosition.xyz, 1);
    //

    //**********************************************************************

    // Copy the input to the fragment shader
    texCoord = TexCoord;
}


