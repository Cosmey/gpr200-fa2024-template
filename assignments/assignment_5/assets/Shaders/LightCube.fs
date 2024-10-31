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

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    //vec4 result = (vec4(ambient,1.0f) + vec4(diffuse,1.0f)) * texture(texture1,TexCoord);
	FragColor = vec4(objectColor,1.0f);

}