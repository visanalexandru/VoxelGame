#include "Collider.h"
#include<cmath>
Collider::Collider(const AABB player_box,ChunkManager&c_manager):player_aabb(player_box),
    manager(c_manager)

{
    //ctor
}
void Collider::fix_speed(glm::vec3&camera_position,glm::vec3&speed)
{
    camera_position.x+=speed.x;
    collide(camera_position,glm::vec3(speed.x,0,0));
    camera_position.y+=speed.y;
    collide(camera_position,glm::vec3(0,speed.y,0));
    camera_position.z+=speed.z;
    collide(camera_position,glm::vec3(0,0,speed.z));
}
void Collider::collide(glm::vec3&position,glm::vec3 speed)
{
    glm::vec3 dimensions=player_aabb.get_dimension();
    float a=dimensions.x;
    float b=dimensions.y;
    float c=dimensions.z;
    for(float p=-a; p<=a; p+=1)
    {
        for(float q=-b; q<=b; q+=1)
        {
            for(float r=-c; r<=c; r+=1)
            {
                glm::vec3 pos=position+glm::vec3(p,q,r);
                glm::vec3 fixed=manager.get_chunk_relative_position(pos);
                if(manager.does_chunk_exists_at(fixed))
                {
                    glm::vec3 converted=pos-fixed;
                    Chunk*x=manager.get_chunk_at(fixed);
                    if(ChunkConstants::is_inside(converted.y))
                    {
                        BlockId new_block=x->get_block_at((int)(converted.x),(int)(converted.y),(int)(converted.z));
                        if(ChunkConstants::can_collide(new_block))
                        {
                            handle_collision(position,glm::vec3(p,q,r),speed);
                        }
                    }
                }
            }
        }
    }
}

void Collider::handle_collision(glm::vec3&position,glm::vec3 offset,glm::vec3 speed)
{
    glm::vec3 dimensions=player_aabb.get_dimension();
    float a=dimensions.x;
    float b=dimensions.y;
    float c=dimensions.z;
    if(speed.x>0)
    {
        position.x=floor(position.x+offset.x)-a-error;
    }
    else if(speed.x<0)
    {
        position.x=floor(position.x+offset.x)+1+a+error;
    }
    if(speed.z>0)
    {
        position.z=floor(position.z+offset.z)-c-error;
    }
    else if(speed.z<0)
    {
        position.z=floor(position.z+offset.z)+1+c+error;
    }
    if(speed.y>0)
    {
        position.y=floor(position.y+offset.y)-b-error;
    }
    else if(speed.y<0)
    {
        position.y=floor(position.y+offset.y)+1+b+error;
    }
}
Collider::~Collider()
{
    //dtor
}
