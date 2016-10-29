#version 330

out vec4 color;

uniform sampler2D image;
in vec2 uv;

void main() {
    color = texture2D(image, uv);
}

