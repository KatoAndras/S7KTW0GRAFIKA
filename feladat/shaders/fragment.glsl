#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D texture1;
uniform float lightIntensity;
void main()
{
    vec4 tex = texture(texture1, TexCoord);
    FragColor = tex * lightIntensity;
}