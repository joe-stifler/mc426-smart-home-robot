#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 textCoord;

uniform int stage;
uniform mat4 transform;
uniform mat4 projection;

void main(void)
{
    textCoord = vertex.zw;

    if (stage == 0) { /* Plots the plot */
        gl_Position = transform * vec4(vertex.xy, 0.1, 1.0);
    } else if (stage == 1) { /* Plots the lateral triangles */
        gl_Position = vec4(vertex.xy, 0.05, 1.0);
    } else if (stage == 2) { /* Plots the box and the ticks */
        gl_Position = vec4(vertex.xy, 0.0, 1.0);
    }
}
