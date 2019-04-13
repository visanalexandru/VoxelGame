#include "Scene.h"

Scene::Scene(const Texture&a,const ShaderProgram&b):texture_to_bind(a),shader_to_bind(b)
{
    //ctor
}
void Scene::bind_resources() const
{
    texture_to_bind.bind_texture();
    shader_to_bind.use_program();
}
void Scene::add_drawable(const Drawable3d&to_add)
{
    to_draw.push_back(&to_add);
}
void Scene::clear_scene()
{
    to_draw.clear();
}
Scene::~Scene()
{
    //dtor
}
