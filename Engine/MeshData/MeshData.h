#ifndef MESHDATA_H
#define MESHDATA_H
#include<iostream>
#include<vector>
#include"Buffer.h"
#include"../Vertex/Vertex.h"
using namespace std;
template<class Vertex_type>
class MeshData:public Buffer
{
public:
    MeshData();
    virtual ~MeshData();
    const void* get_vertex_data() const override;
    const void* get_triangles_data()const override;
    void clear_data();
    int get_vertices_size() const override ;
    int get_triangles_size()const override;
    void add_vertex(Vertex_type to_add);
    int get_vertex_element_size() const override;
    void add_triangle(Vertex_type v1,Vertex_type v2,Vertex_type v3);
    void create_attributes() const override;
    void add_index(unsigned to_add);

protected:

private:
    vector<Vertex_type> verticeslist;
    vector<unsigned>triangleslist;
};
template<class Vertex_type>
MeshData<Vertex_type>::MeshData()
{
    //ctor
}
template<class Vertex_type>
void MeshData<Vertex_type>::clear_data()
{
    verticeslist.clear();
    triangleslist.clear();
}
template<class Vertex_type>
int MeshData<Vertex_type>::get_vertex_element_size() const
{
    return sizeof(Vertex_type);
}
template<class Vertex_type>
void MeshData<Vertex_type>::add_triangle(Vertex_type v1,Vertex_type v2,Vertex_type v3)
{
    int v=get_triangles_size();
    add_vertex(v1);
    add_vertex(v2);
    add_vertex(v3);
    add_index(v);
    add_index(v+1);
    add_index(v+2);

}
template<class Vertex_type>
const void* MeshData<Vertex_type>::get_vertex_data()const
{
    return &verticeslist[0];

}
template<class Vertex_type>
const void* MeshData<Vertex_type>::get_triangles_data()const
{
    return &triangleslist[0];

}
template<class Vertex_type>
void MeshData<Vertex_type>::create_attributes() const
{
    Vertex_type::enable_attributes();

}
template<class Vertex_type>
int MeshData<Vertex_type>::get_vertices_size() const
{
    return verticeslist.size();
}
template<class Vertex_type>
void MeshData<Vertex_type>::add_vertex(Vertex_type vertex_to_add)
{
    verticeslist.push_back(vertex_to_add);
    Set_bounds(vertex_to_add.get_position());


}

template<class Vertex_type>
void MeshData<Vertex_type>::add_index(unsigned to_add)
{
    triangleslist.push_back(to_add);
}
template<class Vertex_type>
int MeshData<Vertex_type>::get_triangles_size() const
{
    return triangleslist.size();
}
template<class Vertex_type>
MeshData<Vertex_type>::~MeshData()
{
    //dtor
}
#endif // MESHDATA_H
