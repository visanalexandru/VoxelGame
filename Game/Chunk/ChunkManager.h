#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include<unordered_map>
#include<vector>
#include"Chunk.h"
#include"../../Engine/Scene/Scene.h"
#include<string>
#include<cmath>
#include<thread>
#include<mutex>
#include"../Game/Network/Connection.h"
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
namespace std
{

template <>
struct hash<glm::vec3>
{
    std::size_t operator()(const glm::vec3& k) const
    {
        std::size_t seed=0;
        hash_combine(seed,(int)k.x);
        hash_combine(seed,(int)k.y);
        hash_combine(seed,(int)k.z);
        return seed;
    }
};



}
class ChunkManager
{
public:

    ChunkManager(const ShaderProgram&chunk_sh,const ShaderProgram&water_sh,const Texture2d&chunk_t,Camera&player_cam,int v_range,Connection&connection);
    virtual ~ChunkManager();
    void create_meshes();
    const Scene&get_chunk_scene();
    const Scene&get_water_scene();
    void lock();
    void unlock();
    void destroy_chunks_out_of_range();
    bool does_chunk_exists_at(glm::vec3 position);
    Chunk* get_chunk_at(glm::vec3 pos);
    glm::vec3 get_chunk_relative_position(glm::vec3 position);
    void delete_marked_chunks();


protected:

private:
    void spawn_closest_chunk();
    void Update_chunks();
    std::mutex mutex_lock;
    atomic<bool>is_alive;
    void tick();
    void Update_chunk(Chunk*chunk);
    void delete_all_chunks();
    bool is_position_too_far(glm::vec3 position);
    void spawn_chunk(glm::vec3 position);
    int view_range;
    const ShaderProgram&chunk_shader;
    const ShaderProgram&w_shader;
    const Texture2d&chunk_texture;
    unordered_map<glm::vec3,Chunk*>chunk_map;
    vector<Chunk*>chunks;
    vector<Chunk*>chunks_to_delete;
    string get_string(glm::vec3 pos);
    Scene chunk_scene;
    Scene water_scene;
    Camera&player_camera;
    static glm::vec3 offsets[4];
    std::thread* worker;
    std::thread* server_receiver;
    void start_thread();
    void stop_thread();
    void parse_response(std::string&to_parse);
    const int tick_time_ms;
    Connection&server_connnection;
    void get_changes_from_server();

};

#endif // CHUNKMANAGER_H
