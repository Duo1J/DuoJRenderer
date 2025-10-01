#version 460 core

struct Material {
    sampler2D tex_diffuse1;
    sampler2D tex_diffuse2;
    // ...
    sampler2D tex_specular1;
    sampler2D tex_specular2;
    // ...
    // 增加法线贴图
    sampler2D tex_normal1;
    sampler2D tex_normal2;
    // ...
    float shininess;
};

struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;

    float constant;
    float linear;
    float quadratic;
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat3 TBN;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Debug;
} fs_in;

out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;

uniform DirLight dirLight;
#define POINT_LIGHT_NUM 4
uniform PointLight pointLight[POINT_LIGHT_NUM];

vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 ambient = light.ambient * vec3(texture(material.tex_diffuse1, fs_in.TexCoords));
    float diff = max(dot(normal, lightDir), 0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.tex_diffuse1, fs_in.TexCoords));
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.tex_specular1, fs_in.TexCoords));

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(normalize(fs_in.TBN * light.position) - fragPos);

    float d = length(normalize(fs_in.TBN * light.position) - fragPos);
    float attenuation = 1 / (light.constant + light.linear * d + light.quadratic * d * d);

    vec3 ambient = light.ambient * vec3(texture(material.tex_diffuse1, fs_in.TexCoords)) * attenuation;
    float diff = max(dot(normal, lightDir), 0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.tex_diffuse1, fs_in.TexCoords)) * attenuation;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.tex_specular1, fs_in.TexCoords)) * attenuation;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 normal = texture(material.tex_normal1, fs_in.TexCoords).rgb;
    normal = normalize(normal * 2 - 1);
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

    vec3 result = CalcDirectionalLight(dirLight, normal, viewDir);
    for (int i = 0; i < POINT_LIGHT_NUM; i++)
    {
        result += CalcPointLight(pointLight[i], normal, viewDir, fs_in.TangentFragPos);
    }

    FragColor = vec4(result, 1.0);
}