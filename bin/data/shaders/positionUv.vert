#version 330

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 vertexUv;

uniform mat4 transform;

out vec2 uv;

void main() {
    gl_Position = transform * vertexPosition;
    uv = vertexUv;
}

