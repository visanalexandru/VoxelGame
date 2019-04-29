#include "Meshdata_simple.h"
glm::vec3 Meshdata_simple::cube_offsets[6][4]
{
    {glm::vec3(0,0,0),glm::vec3(1,0,0),glm::vec3(1,1,0),glm::vec3(0,1,0)},
    {glm::vec3(1,0,0),glm::vec3(1,0,1),glm::vec3(1,1,1),glm::vec3(1,1,0)},
    {glm::vec3(0,0,1),glm::vec3(0,0,0),glm::vec3(0,1,0),glm::vec3(0,1,1)},
    {glm::vec3(1,0,1),glm::vec3(0,0,1),glm::vec3(0,1,1),glm::vec3(1,1,1)},
    {glm::vec3(0,1,0),glm::vec3(1,1,0),glm::vec3(1,1,1),glm::vec3(0,1,1)},
    {glm::vec3(0,0,1),glm::vec3(1,0,1),glm::vec3(1,0,0),glm::vec3(0,0,0)},
};
Meshdata_simple::Meshdata_simple()
{
    //ctor
}
void Meshdata_simple::add_face(glm::vec3 face_position,int face_index,glm::vec2 origin)
{
    byte_vertex v1(cube_offsets[face_index][3]+face_position,origin+glm::vec2(0,1),face_index),
                v2(cube_offsets[face_index][2]+face_position,origin+glm::vec2(1,1),face_index),
                v3(cube_offsets[face_index][1]+face_position,origin+glm::vec2(1,0),face_index),
                v4(cube_offsets[face_index][0]+face_position,origin,face_index);
    add_triangle(v1,v2,v3);
    add_triangle(v3,v4,v1);

}
void Meshdata_simple::add_cube(glm::vec3 position)
{
    for(int i=0; i<6; i++)
    {
        add_face(position,i,glm::vec2(0,0));
    }


}
Meshdata_simple::~Meshdata_simple()
{
    //dtor
}
