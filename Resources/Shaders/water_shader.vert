#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float face_index;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time_off;
out vec2 TexCoord;
out float face;
void main()
{
    vec3 copy=aPos;
    int a,b;
    a=int(aPos.x)%16;
    b=int(aPos.z)%16;
    copy.y+=sin(a*b+time_off)/10;
    gl_Position =projection*view*model*vec4(copy, 1.0);
    face=face_index;
    TexCoord = vec2(aTexCoord.x/16,aTexCoord.y/16);

}
