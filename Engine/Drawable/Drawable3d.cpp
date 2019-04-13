#include "Drawable3d.h"

Drawable3d::Drawable3d(glm::vec3 position,const ShaderProgram&prog,const Texture2d&tex):AABB(position,glm::vec3(0,0,0)),Transformable(position),mesh(prog,tex)
{
    //ctor
}
void Drawable3d::UpdateAABB()
{
    const float*b_pointer=mesh.Get_bounds_pointer();
    glm::vec3 off(b_pointer[0],b_pointer[2],b_pointer[4]);
    AABB_position=get_position()+off;
    dimensions.x=b_pointer[1]-b_pointer[0];
    dimensions.y=b_pointer[3]-b_pointer[2];
    dimensions.z=b_pointer[5]-b_pointer[4];
}
void Drawable3d::set_mesh_data(const Buffer&data)
{
    mesh.create_vao(data);
    UpdateAABB();

}
void Drawable3d::set_position(glm::vec3 newpos)
{
    glm::vec3 diff=newpos-position;
    AABB_position+=diff;
    position=newpos;

}
const Mesh& Drawable3d::Get_mesh() const
{
    return mesh;
}
Drawable3d::~Drawable3d()
{
    //dtor
}
