#ifndef CHUNK_H
#define CHUNK_H
#include"ChunkConstants.h"
#include"../../Engine/Drawable/Drawable3d.h"
#include"../../Engine/Noise/NoiseGenerator.h"
#include"../../Engine/MeshData/Meshdata_simple.h"
#include"../ChunkData/Heightmap3d.h"
#include"../TextureAtlas/TextureAtlas.h"
class Chunk:public Drawable3d
{
public:
    Chunk(glm::vec3 pos,const ShaderProgram&p,const Texture2d&t);
    virtual ~Chunk();
    void create_mesh_data(Chunk*c1,Chunk*c2,Chunk*c3,Chunk*c4);
    void assign_mesh_data();
    BlockId get_block_at(int x,int y,int z);
    void set_update(bool x);
    void set_mesh_update(bool x);
    bool does_need_to_upate_chunk();
    bool does_need_to_assign_mesh();
protected:

private:
    bool is_inside(int x,int y,int z);
    static glm::vec3 offsets[6];
    void add_faces_at(int x,int y,int z);
    Heightmap3d<BlockId> data;
    Chunk*neighbours[4];
    Meshdata_simple meshdata;
    NoiseParameters p;
    NoiseGenerator generator;
    bool needs_to_update;
    bool needs_to_assign_mesh;
};

#endif // CHUNK_H
