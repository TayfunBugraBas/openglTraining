#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D texture2;
out vec4 fragment;


void main(){

	fragment = mix(texture(ourTexture, TexCoord), texture(texture2,TexCoord),0.2); //burada sonda yazdýðýmýz 0.2 karýþým miktarýný belirtir
}