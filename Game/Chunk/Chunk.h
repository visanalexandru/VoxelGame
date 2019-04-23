#ifndef CHUNK_H
#define CHUNK_H
#include"ChunkConstants.h"
#include"../../Engine/Drawable/Drawable3d.h"
#include"../../Engine/Noise/NoiseGenerator.h"
#include"../../Engine/MeshData/Meshdata_simple.h"
#include"../ChunkData/Heightmap3d.h"
#include"../TextureAtlas/TextureAtlas.h"
#include"../Game/Network/Connection.h"
class Chunk:public Drawable3d
{
public:
    Chunk(glm::vec3 pos,const ShaderProgram&p,const Texture2d&t,Chunk*neighbours[4],Connection&connection);
    virtual ~Chunk();
    void create_mesh_data();
    void assign_mesh_data();
    BlockId get_block_at(int x,int y,int z);
    void set_block_at_client(int x,int y,int z,BlockId to_set);
    void set_block_at_server(int x,int y,int z,BlockId to_set);
    bool does_need_to_upate_chunk();
    bool does_need_to_assign_mesh();
    void set_neighbours(Chunk*c1,Chunk*c2,Chunk*c3,Chunk*c4);
    void set_n_down(Chunk*c1);
    void set_n_left(Chunk*c2);
    void set_n_right(Chunk*c3);
    void set_n_up(Chunk*c4);
    void update_neighbours();
    bool has_all_neighbours();
    void mark_for_update();
    const Drawable3d&get_water_obj();
    void get_update_from_server();
protected:

private:
    void dereference_chunk_from_neighbours();
    bool is_inside(int x,int y,int z);
    static glm::vec3 offsets[6];
    void add_faces_at(int x,int y,int z,Meshdata_simple&meshdata);
    Heightmap3d<BlockId> data;
    Chunk*n_up;
    Chunk*n_down;
    Chunk*n_left;
    Chunk*n_right;
    Meshdata_simple meshdata;
    Meshdata_simple water_meshdata;
    NoiseParameters p;
    NoiseGenerator generator;
    bool needs_to_update;
    bool needs_to_assign_mesh;
    Drawable3d Water_obj;
    Connection&sv_connection;
    string vec_to_string(int x,int y,int z);
    void parse(const string&to_parse);
};

#endif // CHUNK_H
