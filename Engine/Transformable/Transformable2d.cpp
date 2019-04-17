#include "Transformable2d.h"

Transformable2d::Transformable2d(glm::vec2 pos,glm::vec2 size)
{
    //ctor
    set_position(pos);
    set_scale(size);
}
void Transformable2d::set_position(glm::vec2 pos)
{
    position=pos;
}
void Transformable2d::set_scale(glm::vec2 size)
{
    scale=size;

}
glm::vec2 Transformable2d::get_scale() const
{
    return scale;
}
glm::vec2 Transformable2d::get_position()const
{
    return position;
}
glm::mat4 Transformable2d::Get_position_matrix()const
{
    glm::mat4 model(1);
    glm::vec2 pos=get_position();
    model = glm::translate(model,glm::vec3(pos,0.0f));
    model=glm::scale(model,glm::vec3(scale,0));
    return model;
}
Transformable2d::~Transformable2d()
{
    //dtor
}
