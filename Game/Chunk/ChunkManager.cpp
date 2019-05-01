#include "ChunkManager.h"
#include<string>
#include<sstream>
ChunkManager::ChunkManager(const ShaderProgram&chunk_sh,const ShaderProgram&water_sh,const Texture2d&chunk_t,Camera&player_cam,int v_range,Connection&connection):chunk_shader(chunk_sh),
    w_shader(water_sh),
    chunk_texture(chunk_t),
    chunk_scene(chunk_t,chunk_sh),
    water_scene(chunk_t,water_sh),
    player_camera(player_cam),
    tick_time_ms(20),
    server_connnection(connection)
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
        destroy_chunks_out_of_range();
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
    server_receiver=new std::thread([this] { this->get_changes_from_server(); });
}
void ChunkManager::stop_thread()
{
    is_alive=false;
    worker->join();
    server_receiver->join();
    delete worker;
    delete server_receiver;

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
        return chunk_map[pos];

    }
    return NULL;

}
void ChunkManager::get_changes_from_server()
{
    sf::SocketSelector selector;
    selector.add(server_connnection.get_socket());
    char p;
    int x,y;
    string a;
    while(is_alive)
    {
        if(selector.wait(sf::seconds(1.f)))
        {
            if(selector.isReady(server_connnection.get_socket()))
            {
                a=server_connnection.receive_data();
                stringstream parser;
                parser<<a;
                parser>>p;
                switch(p)
                {
                case 'r':
                {
                    parser>>x>>y;
                    glm::vec3 pos(x,0,y);
                    if(does_chunk_exists_at(pos))
                    {
                        Chunk*to_update=get_chunk_at(pos);
                        lock();
                        to_update->parse(a);
                        unlock();
                    }
                    break;
                }
                case 's':
                {
                    parse_response(a);
                    break;
                }
                }
            }
        }
    }
}
void ChunkManager::parse_response(std::string&to_parse)
{
    stringstream parser;
    char delim;
    parser<<to_parse;
    glm::vec3 pos;
    parser>>delim;
    int x,y,z,block;
    Chunk*aux;
    while(parser>>x>>y>>z>>block)
    {
        pos=glm::vec3(x,y,z);
        glm::vec3 fixed=get_chunk_relative_position(pos);
        if(does_chunk_exists_at(fixed))
        {
            aux=get_chunk_at(fixed);
            int x2=(int)(x-fixed.x);
            int y2=(int)y;
            int z2=(int)(z-fixed.z);
            lock();
            aux->set_block_at_server(x2,y2,z2,(BlockId)block);
            unlock();
        }
    }
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
    lock();
    for(unsigned i=0; i<chunks.size(); i++)
    {
        if(is_position_too_far(chunks[i]->get_position()))
        {
            glm::vec3 pos=chunks[i]->get_position();
            chunks_to_delete.push_back(chunks[i]);
            chunks.erase(chunks.begin()+i);
            chunk_map.erase(pos);
            i--;
        }
    }
    unlock();

}
const Scene&ChunkManager::get_chunk_scene()
{
    chunk_scene.clear_scene();
    for (unsigned i=0; i<chunks.size(); i++)
    {
        chunk_scene.add_drawable(*chunks[i]);
    }
    return chunk_scene;

}
const Scene&ChunkManager::get_water_scene()
{
    water_scene.clear_scene();
    for (unsigned i=0; i<chunks.size(); i++)
    {
        water_scene.add_drawable(chunks[i]->get_water_obj());
    }
    return water_scene;

}
void ChunkManager::delete_marked_chunks()
{
    lock();
    for(unsigned i=0; i<chunks_to_delete.size(); i++)
        delete chunks_to_delete[i];
    chunks_to_delete.clear();
    unlock();


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
    auto got = chunk_map.find (position);
    unlock();
    return got!=chunk_map.end();
}
void ChunkManager::spawn_chunk(glm::vec3 position)
{
    Chunk*n[4];
    for(int i=0; i<4; i++)
        n[i]=get_chunk_at(position+offsets[i]);
    Chunk* to_add=new Chunk(position,chunk_shader,w_shader,chunk_texture,n,server_connnection);
    lock();
    chunk_map[position]=to_add;
    to_add->update_neighbours();
    chunks.push_back(to_add);
    unlock();
    to_add->get_data_from_server();
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
