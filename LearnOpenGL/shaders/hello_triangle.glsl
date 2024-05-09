#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    //gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}

#type fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture0;

void main()
{
    //FragColor = vec4(0., 1., 0, 1.);
    FragColor = texture(texture0, TexCoord);
}