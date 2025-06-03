#version 330 core

in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 ourFrag;

void main(){
	ourFrag = mix(texture(texture1,ourTexCoord), texture(texture2,ourTexCoord),0.2);
}