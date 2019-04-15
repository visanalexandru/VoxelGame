#include "ChunkManager.h"

ChunkManager::ChunkManager(const ShaderProgram&chunk_sh,const Texture2d&chunk_t,Camera&player_cam,int v_range):chunk_shader(chunk_sh),
    chunk_texture(chunk_t),
    scene(chunk_t,chunk_sh),
    player_camera(player_cam),
    tick_time_ms(20)
{
    //ctor
    view_range=v_range;
    is_alive=false;
    start_thread();
}
glm::vec3 ChunkManager::offsets[4]
{
    glm::vec3(-ChunkConstants::chunk_width,0,0),
    glm::vec3(ChunkConstants::chunk_width,0,0),
    glm::vec3(0,0,-ChunkConstants::chunk_width),
    glm::vec3(0,0,ChunkConstants::chunk_width)
};
void ChunkManager::tick()
{
    double time,diff,aux;
    while(is_alive)
    {
        time=glfwGetTime();
        spawn_closest_chunk();
        Update_chunks();
        aux=max(((double)glfwGetTime() - time),0.0);//it might be negative if the opengl context has been destroyed
        diff =tick_time_ms-aux*1000;
        if(diff>0)
            std::this_thread::sleep_for(std::chrono::milliseconds((int)diff));
    }
}
void ChunkManager::start_thread()
{
    is_alive=true;
    worker=new std::thread([this] { this->tick(); });
}
void ChunkManager::stop_thread()
{
    is_alive=false;
    worker->join();
    delete worker;

}
void ChunkManager::Update_chunk(Chunk*chunk)
{
    chunk->create_mesh_data();

}
string ChunkManager::get_string(glm::vec3 pos)
{
    int x=pos.x,z=pos.z;
    string a=to_string(x)+" "+to_string(z);
    return a;
}
bool ChunkManager::is_position_too_far(glm::vec3 position)
{
    glm::vec3 here=get_chunk_relative_position(player_camera.get_position());
    if(abs(position.x-here.x)>view_range*ChunkConstants::chunk_width||abs(position.z-here.z)>view_range*ChunkConstants::chunk_width)
    {
        return true;
    }
    return false;
}
void ChunkManager::Update_chunks()
{
    for(unsigned i=0; i<chunks.size(); i++)
    {
        lock();
        Chunk*here=chunks[i];
        if(here->does_need_to_upate_chunk())
        {
            Update_chunk(here);
        }
        unlock();
    }
}
Chunk*ChunkManager::get_chunk_at(glm::vec3 pos)
{
    if(does_chunk_exists_at(pos))
    {
        return chunk_map[get_string(pos)];

    }
    return NULL;

}
void ChunkManager::delete_all_chunks()
{
    for(unsigned i=0; i<chunks.size(); i++)
    {
        delete chunks[i];
    }
}
void ChunkManager::destroy_chunks_out_of_range()
{
    string hashed;
    lock();
    for(unsigned i=0; i<chunks.size(); i++)
    {
        if(is_position_too_far(chunks[i]->get_position()))
        {
            hashed=get_string(chunks[i]->get_position());
            delete chunks[i];
            chunks.erase(chunks.begin()+i);
            chunk_map.erase(hashed);
            i--;
        }
    }
    unlock();

}
const Scene&ChunkManager::get_scene()
{
    scene.clear_scene();
    for (unsigned i=0; i<chunks.size(); i++)
    {
        scene.add_drawable(*chunks[i]);
    }
    return scene;

}
void ChunkManager::spawn_closest_chunk()
{
    int smallest_distance=99999,dist;
    glm::vec3 to_spawn_at,aux;
    glm::vec3 here=get_chunk_relative_position(player_camera.get_position());
    bool found=false;
    for(int i=-view_range; i<=view_range; i++)
    {
        for(int k=-view_range; k<=view_range; k++)
        {
            aux=glm::vec3(here.x+i*ChunkConstants::chunk_width,0,here.z+k*ChunkConstants::chunk_width);
            AABB box(aux,glm::vec3(ChunkConstants::chunk_width,ChunkConstants::chunk_heigth,ChunkConstants::chunk_width));
            if(!does_chunk_exists_at(aux) && player_camera.can_see(box))
            {
                dist=glm::distance(here,aux);
                if(dist<smallest_distance)
                {
                    to_spawn_at=aux;
                    smallest_distance=dist;
                    found=true;
                }
            }
        }
    }
    if(found)
        spawn_chunk(to_spawn_at);

}
void ChunkManager::create_meshes()
{
    lock();
    for(unsigned i=0; i<chunks.size(); i++)
    {
        if(chunks[i]->does_need_to_assign_mesh())
        {
            chunks[i]->assign_mesh_data();
        }
    }
    unlock();
}
void ChunkManager::lock()
{
    mutex_lock.lock();

}
void ChunkManager::unlock()
{
    mutex_lock.unlock();
}
bool ChunkManager::does_chunk_exists_at(glm::vec3 position)
{
    lock();
    string hashed=get_string(position);
    auto got = chunk_map.find (hashed);
    unlock();
    return got!=chunk_map.end();
}
void ChunkManager::spawn_chunk(glm::vec3 position)
{
    Chunk*n[4];
    for(int i=0; i<4; i++)
        n[i]=get_chunk_at(position+offsets[i]);
    Chunk* to_add=new Chunk(position,chunk_shader,chunk_texture,n);
    lock();
    chunk_map[get_string(position)]=to_add;
    to_add->update_neighbours();
    chunks.push_back(to_add);
    unlock();
}
glm::vec3 ChunkManager::get_chunk_relative_position(glm::vec3 position)
{
    float x=floor(position.x/ChunkConstants::chunk_width);
    float y=floor(position.z/ChunkConstants::chunk_width);
    return glm::vec3(x*ChunkConstants::chunk_width,0,y*ChunkConstants::chunk_width);
}
ChunkManager::~ChunkManager()
{
    //dtor
    stop_thread();
    delete_all_chunks();
}
