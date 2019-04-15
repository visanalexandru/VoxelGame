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
class ChunkManager
{
public:

    ChunkManager(const ShaderProgram&chunk_sh,const Texture2d&chunk_t,Camera&player_cam,int v_range);
    virtual ~ChunkManager();
    void create_meshes();
    const Scene&get_scene();
    void lock();
    void unlock();
    void destroy_chunks_out_of_range();
    bool does_chunk_exists_at(glm::vec3 position);
    Chunk* get_chunk_at(glm::vec3 pos);
    glm::vec3 get_chunk_relative_position(glm::vec3 position);

protected:

private:
    void spawn_closest_chunk();
    void Update_chunks();
    std::mutex mutex_lock;
    bool is_alive;
    void tick();
    void Update_chunk(Chunk*chunk);
    void delete_all_chunks();
    bool is_position_too_far(glm::vec3 position);
    void spawn_chunk(glm::vec3 position);
    int view_range;
    const ShaderProgram&chunk_shader;
    const Texture2d&chunk_texture;
    unordered_map<string,Chunk*>chunk_map;
    vector<Chunk*>chunks;
    string get_string(glm::vec3 pos);
    Scene scene;
    Camera&player_camera;
    static glm::vec3 offsets[4];
    std::thread* worker;
    void start_thread();
    void stop_thread();
    const int tick_time_ms;

};

#endif // CHUNKMANAGER_H
