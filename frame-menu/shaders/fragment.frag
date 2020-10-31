#version 330 core


in vec2 textCoord;
out vec4 color;

uniform int stage;
uniform sampler2D text2d;
uniform vec3 textColor;

vec4 jet(float t) {
  return vec4(clamp(vec3(1.5) - abs(4.0 * vec3(t) + vec3(-3, -2, -1)), vec3(0), vec3(1)), 1.0);
}

void main(void)
{
    if (stage == 0) { /* Plots the plot */
        float r = texture(text2d, textCoord).r;

        color = vec4(r, r, r, 1.0f);
    } else if (stage == 1) { /* Plots the lateral triangles */
        float val = 240.0 / 255.0;
        color = vec4(val, val, val, 1.0f);
    } else if (stage == 2) { /* Plots the box and the ticks */
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}
