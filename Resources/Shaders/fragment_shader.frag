#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
    vec4 texcolor = texture(ourTexture,TexCoord)*1.1;
    if(texcolor.a <0.4)
        discard;
    FragColor=texcolor;
}
