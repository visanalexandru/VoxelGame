#ifndef MESH_H
#define MESH_H
#include"../ShaderProgram/ShaderProgram.h"
#include"../Texture/Texture2d.h"
#include"../Texture/Texture3d.h"
#include"../MeshData/MeshData.h"
class Mesh
{
public:
    Mesh(const ShaderProgram&prog,const Texture&tex);
    virtual ~Mesh();
    void create_vao(const Buffer&data);
    void get_bounds(const Buffer&data);
    void bind_mesh(bool bind_texture_and_shader) const;
    unsigned Get_vertices_size() const;
    unsigned Get_triangles_size() const;
    const float* Get_bounds_pointer() const;
    const  ShaderProgram&Get_shader() const;
    const Texture&Get_texture() const;
protected:
    unsigned vao_index;
    unsigned vertices_size;
    unsigned triangles_size;
    const ShaderProgram&shader_program;
    const Texture&texture;
    float bounds[6];
private:
    void bind_vertex_array()const;
    void delete_vertex_array();
};

#endif // MESH_H
