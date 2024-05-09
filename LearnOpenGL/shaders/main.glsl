#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform float t;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}

#type fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float f;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    vec2 newTexCoord = TexCoord;
    newTexCoord.x = 1.0 - TexCoord.x;
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, newTexCoord * 2.0), f);
    //FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z)) / far, 1.0);
}