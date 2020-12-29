#version 300 es

precision mediump float;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec4 fColor;

void main() {
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;

    vec3 normal = normalize(vNormal_vs);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, vTexCoords).rgb;
    
    vec3 viewDir = normalize(viewPos - vPosition_vs);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, vTexCoords).rgb);

    vec3 resulat = ambient + diffuse + specular;
    fColor = vec4(resulat, 1.0);
}