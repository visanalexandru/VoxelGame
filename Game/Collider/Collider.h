#ifndef COLLIDER_H
#define COLLIDER_H
#include"../../Engine/AABB/AABB.h"
#include"../Chunk/ChunkManager.h"

class Collider
{
public:
    Collider(const glm::vec3 player_dimensions,ChunkManager&manager);
    virtual ~Collider();
    void fix_speed(glm::vec3&camera_position,glm::vec3&speed);
protected:
    const glm::vec3 player_dimensions;
    ChunkManager&manager;
    void collide(glm::vec3&position,glm::vec3 speed);
    void handle_collision(glm::vec3&position,glm::vec3 offset,glm::vec3 speed);
    const float error=0.001f;
private:
};

#endif // COLLIDER_H
