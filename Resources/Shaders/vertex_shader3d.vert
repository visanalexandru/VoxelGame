#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float face_index;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
out float face;
void main()
{
    face=face_index;
    gl_Position =projection*view*model*vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x/16,aTexCoord.y/16);

}
