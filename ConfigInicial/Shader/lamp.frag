#version 330 core
out vec4 outColor;
  
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    outColor = vec4(Color,1.0)*texture(ourTexture, TexCoord);
    if (outColor.a < 0.1)                                       //corresponde a la opacidad del fragmento, si es menor a 0.1 se descarta el fragmento
    discard;//descarta el fragmento, no se dibuja
}