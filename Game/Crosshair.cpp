#include "Crosshair.h"

Crosshair::Crosshair(const ShaderProgram&prog,const Texture2d&tex):Drawable2d(glm::vec2(240.f,240.f),glm::vec2(20,20),prog,tex)
{
    //ctor
    create_data();
}
void Crosshair::create_data()
{
    MeshData<texture_vertex_2d> data;
    texture_vertex_2d v4(glm::vec2(0.f,0.f),glm::vec2(0,0));
    texture_vertex_2d v3(glm::vec2(1.f,0.f),glm::vec2(1,0));
    texture_vertex_2d v2(glm::vec2(1.f,1.f),glm::vec2(1,1));
    texture_vertex_2d v1(glm::vec2(0.f,1.f),glm::vec2(0,1));
    data.add_triangle(v1,v2,v3);
    data.add_triangle(v3,v4,v1);
    set_mesh_data(data);

}
Crosshair::~Crosshair()
{
    //dtor
}
