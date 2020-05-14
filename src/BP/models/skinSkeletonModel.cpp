#include <glm/gtc/random.hpp>


#include "src/BP/mainScene.h"
#include "skinSkeletonModel.h"


//#include "projectile.h"
//#include "explosion.h"




#include <cmake-build-debug-mingw/shaders/skeleton_texture_frag_glsl.h>
#include <cmake-build-debug-mingw/shaders/skeleton_texture_vert_glsl.h>
#include <util.h>
#include <glm/gtx/string_cast.hpp>
#include <src/BP/fileLoaders/fileLoader.h>


// Static resources
std::unique_ptr<ppgso::MeshSkeleton> SkinSkeletonModel::mesh;
std::unique_ptr<ppgso::Texture> SkinSkeletonModel::texture;
std::unique_ptr<ppgso::Shader> SkinSkeletonModel::shader;

bool SkinSkeletonModel::update(Scene &scene, float dt) {
    skeleton->updateSkeleton(Skeletonv2::generateSkeletonBaseMatrix({0,0,0}));
    return true;
}

void SkinSkeletonModel::render(Scene &scene) {
    // TODO: Render the object

//    std::cout << "out" << std::endl;
//    std::cout << to_string(bone->vector) << std::endl;
    shader->use();
    shader->setUniform("OverallColor", color);

    shader->setUniform("SkeletonModelMatrix", skeleton->getSkeletonProjectionMatrix());
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    mesh->render();
}

void SkinSkeletonModel::onClick(Scene &scene) {
}

SkinSkeletonModel::SkinSkeletonModel(const std::string &obj_file, const std::string &br_file,
                                     const std::string &bmp_file,
                                     const std::string &sk_file) {
    color = glm::vec3{0,2,0};
    if (!shader) shader = std::make_unique<ppgso::Shader>(skeleton_texture_vert_glsl, skeleton_texture_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::MeshSkeleton>(obj_file, br_file);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(bmp_file));
    skeleton = FileLoader::loadSkeletonFromFile(sk_file);
}

