#version 410 core

out vec4 FragColour;
in vec3 posWS;
in vec3 normWS;
in vec2 uv;
in mat3 TBN;

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

//******************************************************Blinn-Phong*********************************************************
vec3 getBlinnPhong(){

    N = normalize(normWS);
    
    rim = clamp(pow((brightness * (1.0 - max(dot(N, -viewDir), 0.0))), sharpness), 0.0, 1.0);

    vec3 lightDir = normalize(dirLightPos - posWS);

// Ambient
    vec3 ambient = clamp((objCol * dirLightCol * ambFac), 0.0, 1.0);          //(diffTexCol * dirLightCol * ambFac)

// Diffuse
    float diffFac = max(dot(N, -lightDir), 0.0);
    vec3 diffuse = clamp((objCol * dirLightCol * diffFac), 0.0, 1.0);  //(objCol -> diffTexCol)

// Specular
    vec3 halfDir = normalize(viewDir + normalize(lightDir - posWS));       
    vec3 reflectDir = reflect(lightDir, N);                                
    float specFac = pow(max(dot(N, halfDir), 0.0), shine);                 // halfDir (Blinn-Phong), reflectDir (Phong)
    vec3 specular = clamp((specLevel * specFac * dirLightCol), 0.0, 1.0);  // (specLevel -> specMapCol)

// Result
    vec3 result = vec3(0.0);
    
    result = ambient + diffuse + specular;

    return result;
};



//*************Main Body****************
void main(){
vec3 result = vec3(0.0);

    result = getBlinnPhong();

    FragColour = vec4(result, 1.0);
    
    //if(!gl_FrontFacing) FragColour = vec4(0.0,1.0,0.0,1.0);
}