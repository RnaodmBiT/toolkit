#version 330

layout(location = 0) in vec4 vertPosition;
layout(location = 1) in vec4 vertColor;
layout(location = 2) in vec2 vertUv;

uniform mat4 transform;


out vec4 fragColor;
out vec2 fragUv;


void main() {
    gl_Position = transform * vertPosition;
    fragColor = vertColor;
    fragUv = vertUv;
}