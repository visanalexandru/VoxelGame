#include "Ray.h"

Ray::Ray(glm::vec3 pos,glm::vec3 forward_vector):Transformable(pos)
{
    //ctor
    fw_vector=forward_vector;
}
glm::vec3 Ray::step_forward(float scalar)
{
    return get_position()+scalar*fw_vector;
}
Ray::~Ray()
{
    //dtor
}
