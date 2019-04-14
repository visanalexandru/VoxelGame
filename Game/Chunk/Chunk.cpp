#include "Chunk.h"
glm::vec3 Chunk::offsets[6]
{
    glm::vec3(0,0,-1),
    glm::vec3(1,0,0),
    glm::vec3(-1,0,0),
    glm::vec3(0,0,1),
    glm::vec3(0,1,0),
    glm::vec3(0,-1,0),
};
Chunk::Chunk(glm::vec3 pos,const ShaderProgram&pr,const Texture2d&te):Drawable3d(pos,pr,te),generator(pos,0,p)
{
    //ctor
    needs_to_update=true;
    needs_to_assign_mesh=false;
    generator.generate_3d_heigthmap(data);
}
bool Chunk::is_inside(int x,int y,int z)
{
    return x>=0 && x<ChunkConstants::chunk_width && z>=0 && z<ChunkConstants::chunk_width && y>=0 && y<ChunkConstants::chunk_heigth;

}
bool Chunk::does_need_to_assign_mesh()
{
    return needs_to_assign_mesh;
}
bool Chunk::does_need_to_upate_chunk()
{
    return needs_to_update;
}
BlockId Chunk::get_block_at(int x,int y,int z)
{
    return data.get_value_at(x,y,z);

}
void Chunk::add_faces_at(int x,int y,int z)
{
    int xp,yp,zp;
    glm::vec2 uv_origin;
    if(data.get_value_at(x,y,z)!=BlockId::Air_block)
        for(int i=0; i<6; i++)
        {
            xp=x+offsets[i].x;
            yp=y+offsets[i].y;
            zp=z+offsets[i].z;
            uv_origin=TextureAtlas::get_origin_coords(data.get_value_at(x,y,z),i);
            if(is_inside(xp,yp,zp))
            {
                if(data.get_value_at(xp,yp,zp)==BlockId::Air_block)
                {
                    meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
            }
            else
            {
                if(xp<0)
                {
                    if(neighbours[0]->get_block_at(ChunkConstants::chunk_width-1,yp,zp)==BlockId::Air_block)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(xp>ChunkConstants::chunk_width-1)
                {
                    if(neighbours[1]->get_block_at(0,yp,zp)==BlockId::Air_block)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(zp<0)
                {
                    if(neighbours[2]->get_block_at(xp,yp,ChunkConstants::chunk_width-1)==BlockId::Air_block)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(zp>ChunkConstants::chunk_width-1)
                {
                    if(neighbours[3]->get_block_at(xp,yp,0)==BlockId::Air_block)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
            }
        }
}
void Chunk::set_block_at(int x,int y,int z,BlockId to_set)
{
    data.set_value_at(x,y,z,to_set);
    needs_to_update=true;

}
void Chunk::create_mesh_data(Chunk*c1,Chunk*c2,Chunk*c3,Chunk*c4)
{
    neighbours[0]=c1;
    neighbours[1]=c2;
    neighbours[2]=c3;
    neighbours[3]=c4;
    meshdata.clear_data();
    for(int i=0; i<ChunkConstants::chunk_heigth; i++)
    {
        for(int k=0; k<ChunkConstants::chunk_width; k++)
        {
            for(int p=0; p<ChunkConstants::chunk_width; p++)
            {
                add_faces_at(p,i,k);
            }
        }

    }
    needs_to_update=false;
    needs_to_assign_mesh=true;
}
void Chunk::assign_mesh_data()
{
    set_mesh_data(meshdata);
    needs_to_assign_mesh=false;
}
Chunk::~Chunk()
{
    //dtor
}
