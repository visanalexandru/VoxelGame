#ifndef MESHDATA_SIMPLE_H
#define MESHDATA_SIMPLE_H

#include"MeshData.h"
class Meshdata_simple:public MeshData<byte_vertex>
{
public:
    Meshdata_simple();
    virtual ~Meshdata_simple();
    static glm::vec3 cube_offsets[6][4];
    void add_face(glm::vec3 face_position,int face_index,glm::vec2 origin);
    void add_cube(glm::vec3 position);
};


#endif // MESHDATA_SIMPLE_H
