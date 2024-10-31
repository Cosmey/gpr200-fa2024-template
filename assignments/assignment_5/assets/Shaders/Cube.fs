#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture sampler
uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform float shininess;
uniform float ambientK;
uniform float diffuseK;
uniform float specularK;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = diff * lightColor * diffuseK;

    vec3 lightDir   = normalize(lightPos - FragPos);
    vec3 viewDir    = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = lightColor * spec * specularK;

    vec3 ambient = lightColor * ambientK;
    vec4 result = (vec4(ambient,1.0f) + vec4(diffuse,1.0f) + vec4(specular,1.0f)) * texture(texture1,TexCoord);
	FragColor = result;

}