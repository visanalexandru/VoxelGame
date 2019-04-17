#include "Drawable2d.h"

Drawable2d::Drawable2d(glm::vec2 position,glm::vec2 size,const ShaderProgram&prog,const Texture2d&tex):Transformable2d(position,size),
    mesh(prog,tex)
{
    //ctor
}
void Drawable2d::set_mesh_data(const Buffer&data)
{
    mesh.create_vao(data);
}
const Mesh&Drawable2d::Get_mesh() const
{
    return mesh;
}
Drawable2d::~Drawable2d()
{
    //dtor
}
