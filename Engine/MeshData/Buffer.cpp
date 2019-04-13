#include "Buffer.h"
#include<iostream>
Buffer::Buffer():bounds {0}
{
    //ctor
    has_not_set_bounds=true;
}
void Buffer::Set_bounds(glm::vec3 to_add)
{
    float params[] {to_add.x,to_add.y,to_add.z};
    for(int i=0; i<6; i+=2)
    {
        float current_bound=params[i/2];
        if(has_not_set_bounds)
        {
            bounds[i]=current_bound;
            bounds[i+1]=current_bound;
        }
        else
        {
            bounds[i]=std::min(bounds[i],current_bound);
            bounds[i+1]=std::max(bounds[i+1],current_bound);

        }

    }
    has_not_set_bounds=false;
}
float Buffer::get_bounds(int index) const
{
    return bounds[index];
}
Buffer::~Buffer()
{
    //dtor
}
