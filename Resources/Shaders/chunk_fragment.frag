#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
in float face;
void main()
{
    float shade;
    if(face==4)
        shade=1.5;
    else if(face==5)
        shade=1;
    else
        shade=1.1;
    vec4 texcolor = texture(ourTexture,TexCoord);
    texcolor.a*=1.1;
    texcolor.x*=shade;
    texcolor.y*=shade;
    texcolor.z*=shade;
    if(texcolor.a <0.4)
        discard;
    FragColor=texcolor;
}
