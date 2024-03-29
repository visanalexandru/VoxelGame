#include "Chunk.h"
#include<sstream>
glm::vec3 Chunk::offsets[6]
{
    glm::vec3(0,0,-1),
    glm::vec3(1,0,0),
    glm::vec3(-1,0,0),
    glm::vec3(0,0,1),
    glm::vec3(0,1,0),
    glm::vec3(0,-1,0),
};
Chunk::Chunk(glm::vec3 pos,const ShaderProgram&pr,const ShaderProgram&w,const Texture2d&te,Chunk*neighbours[4],Connection&connection):Drawable3d(pos,pr,te),
    generator(pos,0,p),
    Water_obj(pos,w,te),
    sv_connection(connection)
{
    //ctor
    set_neighbours(neighbours[0],neighbours[1],neighbours[2],neighbours[3]);
    needs_to_update=true;
    needs_to_assign_mesh=false;
    generator.generate_3d_heigthmap(data);
}
void Chunk::get_data_from_server()
{
    string here=" "+to_string((int)get_position().x)+" "+to_string((int)get_position().z);
    string to_request="r"+here;//we request block updates
    sv_connection.send_data(to_request);
}
void Chunk::parse(const string&to_parse)
{
    int x,y,z;
    int id;
    stringstream stream;
    stream<<to_parse;
    char delim;
    stream>>delim>>x>>y;
    while(stream>>x>>y>>z>>id)
    {
        BlockId casted= static_cast<BlockId>(id);
        set_block_at_server(x,y,z,casted);
    }
}
void Chunk::mark_for_update()
{
    needs_to_update=true;
}
bool Chunk::has_all_neighbours()
{
    return n_down&&n_up&&n_left&&n_right;
}
void Chunk::update_neighbours()
{
    if(n_down)
        n_down->set_n_up(this);
    if(n_up)
        n_up->set_n_down(this);
    if(n_left)
        n_left->set_n_right(this);
    if(n_right)
        n_right->set_n_left(this);
}
void Chunk::dereference_chunk_from_neighbours()
{
    if(n_down)
        n_down->set_n_up(nullptr);
    if(n_up)
        n_up->set_n_down(nullptr);
    if(n_left)
        n_left->set_n_right(nullptr);
    if(n_right)
        n_right->set_n_left(nullptr);
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
void Chunk::add_faces_at(int x,int y,int z,Meshdata_simple&meshdata)
{
    int xp,yp,zp;
    glm::vec2 uv_origin;
    BlockId here;
    BlockId block_here=data.get_value_at(x,y,z);
    if(data.get_value_at(x,y,z)!=BlockId::Air_block)
        for(int i=0; i<6; i++)
        {
            xp=x+offsets[i].x;
            yp=y+offsets[i].y;
            zp=z+offsets[i].z;
            uv_origin=TextureAtlas::get_origin_coords(data.get_value_at(x,y,z),i);
            if(is_inside(xp,yp,zp))
            {
                here=data.get_value_at(xp,yp,zp);
                if(ChunkConstants::is_block_transparent(here)&&here!=block_here)
                {
                    meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
            }
            else
            {
                if(xp<0)
                {
                    here=n_left->get_block_at(ChunkConstants::chunk_width-1,yp,zp);
                    if(ChunkConstants::is_block_transparent(here)&&here!=block_here)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(xp>ChunkConstants::chunk_width-1)
                {
                    here=n_right->get_block_at(0,yp,zp);
                    if(ChunkConstants::is_block_transparent(here)&&here!=block_here)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(zp<0)
                {
                    here=n_down->get_block_at(xp,yp,ChunkConstants::chunk_width-1);
                    if(ChunkConstants::is_block_transparent(here)&&here!=block_here)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
                else if(zp>ChunkConstants::chunk_width-1)
                {
                    here=n_up->get_block_at(xp,yp,0);
                    if(ChunkConstants::is_block_transparent(here)&&here!=block_here)
                        meshdata.add_face(glm::vec3(x,y,z),i,uv_origin);
                }
            }
        }
}
string Chunk::vec_to_string(int x,int y,int z)
{
    return to_string(x)+" "+to_string(y)+" "+to_string(z);
}
void Chunk::set_block_at_client(int x,int y,int z,BlockId to_set)
{
    mutex_lock.lock();
    int casted=(int)to_set;
    int x2=get_position().x,z2=get_position().z;
    string to_send="s "+vec_to_string(x+x2,y,z+z2)+" "+to_string(casted);
    sv_connection.send_data(to_send);
    data.set_value_at(x,y,z,to_set);
    update_neighbours_at(x,y,z);
    needs_to_update=true;
    mutex_lock.unlock();
}
void Chunk::update_neighbours_at(int x,int y,int z)
{

    if(x==15 && n_right)
    {
        n_right->mark_for_update();

    }
    else if(x==0 &&n_left)
    {
        n_left->mark_for_update();
    }
    if(z==15 && n_up)
    {
        n_up->mark_for_update();
    }
    else if(z==0 && n_down)
    {
        n_down->mark_for_update();
    }
}
void Chunk::set_block_at_server(int x,int y,int z,BlockId to_set)
{
    mutex_lock.lock();
    if(data.get_value_at(x,y,z)!=to_set)
    {
        data.set_value_at(x,y,z,to_set);
        update_neighbours_at(x,y,z);
        needs_to_update=true;
    }
    mutex_lock.unlock();
}
void Chunk::set_neighbours(Chunk*c1,Chunk*c2,Chunk*c3,Chunk*c4)
{
    set_n_left(c1);
    set_n_right(c2);
    set_n_down(c3);
    set_n_up(c4);
}
void Chunk::set_n_left(Chunk*c1)
{
    n_left=c1;
}
void Chunk::set_n_right(Chunk*c1)
{
    n_right=c1;
}
void Chunk::set_n_down(Chunk*c1)
{
    n_down=c1;
}
void Chunk::set_n_up(Chunk*c1)
{
    n_up=c1;
}
void Chunk::create_mesh_data()
{
    mutex_lock.lock();
    if(has_all_neighbours())
    {
        meshdata.clear_data();
        water_meshdata.clear_data();
        for(int i=0; i<ChunkConstants::chunk_heigth; i++)
        {
            for(int k=0; k<ChunkConstants::chunk_width; k++)
            {
                for(int p=0; p<ChunkConstants::chunk_width; p++)
                {
                    if(data.get_value_at(p,i,k)!=BlockId::Water_block)
                        add_faces_at(p,i,k,meshdata);
                    else
                        add_faces_at(p,i,k,water_meshdata);
                }
            }

        }
        needs_to_update=false;
        needs_to_assign_mesh=true;
    }
    mutex_lock.unlock();
}
const Drawable3d&Chunk::get_water_obj()
{
    return Water_obj;
}
void Chunk::assign_mesh_data()
{
    mutex_lock.lock();
    set_mesh_data(meshdata);
    Water_obj.set_mesh_data(water_meshdata);
    needs_to_assign_mesh=false;
    mutex_lock.unlock();
}
Chunk::~Chunk()
{
    dereference_chunk_from_neighbours();
    //dtor
}
