#version  330 core 
out  vec4 FragColor; 
in vec3 FragShader;

void main(){

FragColor = vec4(FragShader,1.0);
}