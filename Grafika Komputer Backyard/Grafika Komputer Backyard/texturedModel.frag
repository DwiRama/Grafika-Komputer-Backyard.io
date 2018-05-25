#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    // ambient
    float Ka = 0.7;
    vec3 ambient = Ka * lightColor * vec3(texture(material.diffuse, TexCoords));
    // diffuse 
	float Kd = 0.7;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = Kd * max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * vec3(texture(material.diffuse, TexCoords));
    // specular
    float Ks = 0.9;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = Ks * spec * lightColor * vec3(texture(material.specular, TexCoords));
    vec3 result = (ambient + diffuse + specular);
    gl_FragColor = vec4(result, 1.0);
}
