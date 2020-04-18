#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"
#include "tiny_obj_loader.h"

namespace ppgso {

  class MeshSkeleton {
    struct gl_buffer {
    public:
      GLuint vao, vbo, tbo, nbo, ibo, boneIds, boneWeight = 0;
      GLsizei size = 0;
    };
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<gl_buffer> buffers;

  public:

    /*!
     * Load 3D geometry from a na Wavefront .obj file.
     *
     * The shader program passed to the object will be bound to the geometry as follows:
     * vec3 Position - Vertex position, position 0
     * vec2 TexCoord - Texture coordinate, position 1
     * vec3 Normal - Normal vector, position 2
     *
     * @param obj - File path to the obj file to load.
     */
    MeshSkeleton(const std::string &obj);

    ~MeshSkeleton();

    /*!
     * Render the geometry associated with the mesh using glDrawElements.
     */
    void render();
  };
}

