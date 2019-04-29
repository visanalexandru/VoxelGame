#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"../Graphics/GraphicsUtil.h"
typedef std::uint8_t byte;
struct simple_vertex
{
    glm::vec3 position;
    simple_vertex(glm::vec3 pos)
    {
        position=pos;
    }
    simple_vertex()
    {
        position=glm::vec3(0,0,0);
    }
    static void enable_attributes()
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(simple_vertex), (const GLvoid*)offsetof(simple_vertex, position));
        glEnableVertexAttribArray(0);
    }
    glm::vec3 get_position()
    {
        return position;
    }
};
struct texture_vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    texture_vertex(glm::vec3 pos,glm::vec2 newuv)
    {
        position=pos;
        uv=newuv;
    }
    texture_vertex()
    {
        position=glm::vec3(0,0,0);
        uv=glm::vec2(0,0);
    }
    static void enable_attributes()
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(texture_vertex), (const GLvoid*)offsetof(texture_vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(texture_vertex), (const GLvoid*)offsetof(texture_vertex, uv));
        glEnableVertexAttribArray(1);
    }
    glm::vec3 get_position()
    {
        return position;
    }
};
struct texture_vertex_2d
{
    glm::vec2 position;
    glm::vec2 uv;
    texture_vertex_2d(glm::vec2 pos,glm::vec2 newuv)
    {
        position=pos;
        uv=newuv;
    }
    texture_vertex_2d()
    {
        position=glm::vec2(0,0);
        uv=glm::vec2(0,0);
    }
    static void enable_attributes()
    {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(texture_vertex_2d), (const GLvoid*)offsetof(texture_vertex_2d, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(texture_vertex_2d), (const GLvoid*)offsetof(texture_vertex_2d, uv));
        glEnableVertexAttribArray(1);
    }
    glm::vec3 get_position()
    {
        return glm::vec3(position,0);
    }
};
struct byte_vertex
{
    byte position[3];
    byte uv[2];
    byte face_index;
    byte_vertex(glm::vec3 pos,glm::vec2 newuv,int face)
    {
        position[0]=pos.x;
        position[1]=pos.y;
        position[2]=pos.z;
        uv[0]=newuv.x;
        uv[1]=newuv.y;
        face_index=face;
    }
    byte_vertex():position{0},uv{0}
    {

    }
    static void enable_attributes()
    {
        glVertexAttribPointer(0, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(byte_vertex), (const GLvoid*)offsetof(byte_vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(byte_vertex), (const GLvoid*)offsetof(byte_vertex, uv));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(byte_vertex), (const GLvoid*)offsetof(byte_vertex, face_index));
        glEnableVertexAttribArray(2);
    }
    glm::vec3 get_position()
    {
        return glm::vec3(position[0],position[1],position[2]);
    }
};
#endif
