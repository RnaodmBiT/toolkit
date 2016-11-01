#version 330

out vec4 output;

uniform sampler2D image;
uniform vec4 color = vec4(1, 1, 1, 1);

in vec2 uv;

void main() {
    output = vec4(color.x, color.y, color.z, color.w * texture2D(image, uv).x);
}

