#version 330 core
out vec4 FragColor;

// 环境光颜色在几乎所有情况下都等于漫反射颜色
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDirection = normalize(light.position - FragPos);

    float theta = dot(lightDirection, normalize(-light.direction));

    // 环境光反射
    vec3 diffuseMap = vec3(texture(material.diffuse, TexCoords));
    vec3 ambient = light.ambient * diffuseMap;
    // 执行光照计算
    vec3 normal = normalize(Normal);
    //    vec3 lightDirection = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseMap;


    //specular(Blinn-Phong Shading)
    //----------------------------------------------
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 halfDirection = normalize(lightDirection + viewDirection);
    float speccular = pow(max(dot(normal, halfDirection), 0.0), material.shininess);
    vec3 specular = light.specular * speccular * vec3(texture(material.specular, TexCoords));

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // 将不对环境光做出影响，让它总是能有一点光
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}