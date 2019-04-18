#include "Mesh.h"

Mesh::Mesh(const ShaderProgram&prog,const Texture&tex):shader_program(prog),texture(tex)
{
    //ctor
    vao_index=0;
    vertices_size=0;
    triangles_size=0;
}
void Mesh::bind_mesh(bool bind_texture_and_shader) const
{
    if(bind_texture_and_shader)
    {
        shader_program.use_program();
        texture.bind_texture();
    }
    bind_vertex_array();

}
const float*Mesh::Get_bounds_pointer() const
{
    return bounds;
}
void Mesh::create_vao(const Buffer&data)
{
    delete_vertex_array();
    get_bounds(data);
    int v1=data.get_vertices_size();
    int v2=data.get_triangles_size();
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &vao_index);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(vao_index);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v1*data.get_vertex_element_size(),data.get_vertex_data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, v2*sizeof(unsigned),data.get_triangles_data(), GL_STATIC_DRAW);
    data.create_attributes();
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    triangles_size=v2;
    vertices_size=v1;
}
const ShaderProgram&Mesh::Get_shader() const
{
    return shader_program;
}
const Texture&Mesh::Get_texture() const
{
    return texture;
}
void Mesh::get_bounds(const Buffer&data)
{
    for(int i=0; i<6; i++)
    {
        bounds[i]=data.get_bounds(i);
    }
}
unsigned Mesh::Get_triangles_size()const
{
    return triangles_size;

}
unsigned Mesh::Get_vertices_size()const
{
    return vertices_size;
}
void Mesh::bind_vertex_array()const
{
    glBindVertexArray(vao_index);
}
void Mesh::delete_vertex_array()
{
    glDeleteVertexArrays(1,&vao_index);
}
Mesh::~Mesh()
{
    //dtor
    delete_vertex_array();
}
