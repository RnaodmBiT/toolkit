#version 330

out vec4 color;

uniform sampler2D image;
uniform vec4 tint = vec4(1, 1, 1, 1);
uniform vec2 offset = vec2(0, 0);
uniform vec2 scale = vec2(1, 1);

in vec4 fragColor;
in vec2 fragUv;

void main() {
    color = texture2D(image, (fragUv + offset) * scale) * fragColor * tint;
}

