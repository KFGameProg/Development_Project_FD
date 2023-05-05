#version 410 core

out vec4 FragColour;
in vec3 posWS;
in vec3 normWS;
in vec2 uv;
in mat3 TBN;

//*******************Toggles***********************
// Light Models
uniform bool tAmbient;
uniform bool tDiffuse;
uniform bool tSpecular;

// Shader Details
uniform bool tNorm = true;
uniform bool tFragOut = true;

//************Object Attributes**************

uniform vec3 objCol;
uniform vec4 tint;
uniform vec3 dirLightCol;
uniform vec3 dirLightPos;
uniform vec3 camPos;

//***********Light Values**************

// General
vec3 N = vec3(0.f);
vec3 viewDir = normalize(camPos - posWS); 
float ambFac = 0.5f;
float shine = 10.f;
float specLevel = 0.5f;

// Rim Attributes
float brightness = 100.f;
float sharpness = 20.f;
float rim;

//***********Texture Attributes**************

uniform sampler2D diffuseTexture;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform sampler2D displacementMap;

vec3 diffTexCol = texture(diffuseTexture, uv).xyz;
float specMapCol = texture(specularMap, uv).x;

//******************************************************Blinn-Phong*********************************************************
vec3 getBlinnPhong(){

    N = normalize(normalize(texture(normalMap, uv).rgb * 2.0 - 1.0));
    //N = normalize(normWS);

    rim = clamp(pow((brightness * (1.0 - max(dot(N, -viewDir), 0.0))), sharpness), 0.0, 1.0);

    vec3 lightDir = normalize(dirLightPos - posWS);

// Ambient
    vec3 ambient = clamp((diffTexCol * dirLightCol * ambFac), 0.0, 1.0);       //(objCol * dirLightCol * ambFac)  (diffTexCol * dirLightCol * ambFac)

// Diffuse
    float diffFac = max(dot(N, -lightDir), 0.0);
    vec3 diffuse = clamp((diffTexCol * dirLightCol * diffFac), 0.0, 1.0);      //(objCol -> diffTexCol)

// Specular
    vec3 halfDir = normalize(viewDir + normalize(lightDir - posWS));       
    vec3 reflectDir = reflect(lightDir, N);                                
    float specFac = pow(max(dot(N, halfDir), 0.0), shine);                 // halfDir (Blinn-Phong), reflectDir (Phong)
    vec3 specular = clamp((specMapCol * specFac * dirLightCol), 0.0, 1.0);  // (specLevel -> specMapCol)

// Result
    vec3 result = vec3(0.0);

//    if (tAmbient) {
//        result += ambient;
//    }
//    if (tDiffuse){
//        result += diffuse;
//    }
//    if (tSpecular){
//        result += specular;
//    }

    result = ambient + diffuse + specular;

    return result;
};



//*************Main Body****************
void main(){
vec3 result = vec3(0.0);

    result = getBlinnPhong();

    FragColour = vec4(result, 1.0);
    //FragColour = vec4(N, 1.0);
    
//    if(!gl_FrontFacing) FragColour = vec4(0.0,1.0,0.0,1.0);
}