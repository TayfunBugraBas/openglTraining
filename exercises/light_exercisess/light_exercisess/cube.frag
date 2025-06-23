#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


out vec4 FragColor;

void main(){
	vec4 img = texture(texture1, TexCoord);

	float ambStrngth = 0.1;
	float specularStrg = 0.5;
	vec3 normalized = normalize(Normal);

	vec3 ambient =  ambStrngth * lightColor;
	vec3 lightDir = normalize(lightPos - FragPos);
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalized);

	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	vec3 specular = specularStrg * spec * lightColor;

	float diff = max(dot(Normal, lightDir),0.0);
	vec3 diffuse = diff * lightColor;
	
	vec4 result = vec4((ambient + diffuse + specular) * img.rgb, img.a);

	FragColor = result;

}