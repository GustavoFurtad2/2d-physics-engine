#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 offset;
uniform float scale;

void main() {
    gl_Position = vec4((aPos.xy * scale) + offset, aPos.z, 1.0);
}
