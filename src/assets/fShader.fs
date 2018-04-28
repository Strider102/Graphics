#version 150

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 FragColor;

uniform bool lightOn;
uniform vec3 lightAmbient;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 lightDiffuse;
uniform float lightCutOff;
uniform float lightOutCutOff;
uniform float lightConst;
uniform float lightLin;
uniform float lightQuad;

uniform sampler2D texture_diffuse1;

void main()
{
    //ambient
    vec3 ambient = lightAmbient * texture(texture_diffuse1, fTexCoord).rgb;

    //diffuse
    vec3 norm = normalize(fNormal);
    vec3 nlightDir = normalize(lightPos - fPosition);
    vec3 diffuse = lightDiffuse * max(dot(norm, nlightDir), 0.0) * texture(texture_diffuse1, fTexCoord).rgb;

    //spotlight
    float intensity = clamp((dot(nlightDir, normalize(-lightDir)) - lightOutCutOff) / (lightCutOff - lightOutCutOff), 0.0, 1.0);
    diffuse *= intensity;

    //attenuation
    float distance = length(lightPos - fPosition);
    float attenuation = 1.0 / (lightConst + lightLin * distance + lightQuad * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;

    if (lightOn) {
        FragColor = vec4(ambient + diffuse, 1.0);
    } else {
        FragColor = vec4(ambient, 1.0);
    }
}