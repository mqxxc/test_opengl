#version 330 core
struct Material{
	sampler2D diffuseMap;
	sampler2D specularMap;
	float shininess;
};

$定向光
struct DirLight{
	$视线方向
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

$点光源
struct PointLight{
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

$手电筒(聚光)
struct SpotLight{
	vec3 position;
	vec3  direction;
    float cutOff; 
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

#define NR_POINT_LIGHTS 4
out vec4 FragColor;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient  = light.ambient  * vec3(texture(material.diffuseMap, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	$衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
               light.quadratic * (distance * distance));

	vec3 ambient  = light.ambient  * vec3(texture(material.diffuseMap, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords));
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords));
    return (ambient + diffuse + specular) * intensity;
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result;
	$计算定向光的贡献
	result += CalcDirLight(dirLight, norm, viewDir);

	$计算点光源的贡献
	for(int i = 0 ; i < NR_POINT_LIGHTS; ++i)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	$计算手电筒的贡献
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}
