#version 330 core

in vec2 ourTextureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 ourFrag;

void main(){

	ourFrag = mix(texture(texture1,ourTextureCoord), texture(texture2,ourTextureCoord),0.2);

}

