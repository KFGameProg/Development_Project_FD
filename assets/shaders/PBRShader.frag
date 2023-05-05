#version 410 core

out vec4 FragColour;
in vec3 posWS;
in vec3 normWS;
in vec2 uv;
in mat3 TBN;
in vec3 camera;

//*******************Toggles***********************
// Light Caster
uniform bool tTexture;

// Shader Details
uniform bool tFragOut;

//************Object Attributes**************

uniform vec4 tint;
uniform vec3 lightPos;
uniform vec3 lightCol;

//************PBR Attributes****************
// Material Parameters 
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ambOccul;
// Light Parameters
vec3 norm       = normalize(normWS);
vec3 lightDir   = normalize(lightPos - posWS);
vec3 viewDir    = normalize(camera - posWS);
vec3 halfDir    = normalize(viewDir + lightDir);
const float Pi  = 3.14159265359;
vec3 surfRef0 = vec3(0.04);

//***********Texture Attributes**************
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D ambOcculMap;
uniform sampler2D normalMap;

//*************************************************Calculations for PBR*************************************************
// Attenuation
float calculateAttenuation(vec3 fragPos, vec3 lightPos){

    float dist = length(lightPos - fragPos);

    float attenuation = 1.0 / (dist * dist);

    return attenuation;
};
// Normal Distribution
float getNormalDistibutionGGX(vec3 normal, vec3 halfDir, float rough){
    
    float area   = (rough * rough);
    float area2  = (area * area);
    float NdotH  = max(dot(normal, halfDir), 0.0);
    float NdotH2 = (NdotH * NdotH);

    float num   = area2;
    float denom = (NdotH2 * (area2 - 1.0) + 1.0);
    denom       = (Pi * denom * denom);

    float NDGGX = num / denom;

    return NDGGX;
};
// Geometry
float getGeometryGGX(float NdotV, float rough){

    float r         = (rough + 1.0);
    float areaRemap = ((r * r) / 8.0);

    float num   = NdotV;
    float denom = (NdotV * (1.0 - areaRemap) + areaRemap);

    float GGGX = num / denom;

    return GGGX;
};
float getGeometrySmith(vec3 normal, vec3 viewDir, vec3 lightDir, float rough){

    float NdotV = max(dot(normal, viewDir), 0.0);
    float NdotL = max(dot(normal, lightDir), 0.0);

    float GGX2 = getGeometryGGX(NdotV, rough);
    float GGX1 = getGeometryGGX(NdotL, rough);

    float GS = GGX1 * GGX2;

    return GS;
};
// Fresnel
vec3 calculateFresnel(float cosTheta, vec3 F0) {
    
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
};

//***********************************************Physically-Based*****************************************************
vec3 getPBRDirectional(){

    surfRef0        = mix(surfRef0, albedo, metallic);
    vec3 outRef     = vec3(0.0);
    float att       = calculateAttenuation(posWS, lightPos);
    vec3 rad        = lightCol * att;
    float halfAngle = max(dot(halfDir, viewDir), 0.0);

    // Cook-Torrance BRDF
    float NDF      = getNormalDistibutionGGX(norm, halfDir, roughness);
    float geometry = getGeometrySmith(norm, viewDir, lightDir, roughness);
    vec3 fresnel   = calculateFresnel(halfAngle, surfRef0);

    // Light Contribution to reflectance equation
    vec3 specFac = fresnel;
    vec3 diffFac = vec3(1.0) - specFac;
    diffFac *= 1.0 - metallic;

    vec3 numerator    = NDF * geometry * fresnel;
    float denominator = (4.0 * max(dot(norm, viewDir), 0.0)) * max(dot(norm, lightDir), 0.0) + 0.0001; //0.0001 prevents / by 0;
    
    vec3 specular = numerator / denominator;

    // Outgoing light
    float NdotL = max(dot(norm, lightDir), 0.0);
    outRef += (diffFac * albedo / Pi + specular) * rad * NdotL;

    vec3 ambient = vec3(0.03) * albedo * ambOccul;
    vec3 result  = ambient + outRef;

    // Tone Mapping (HDR)
    result = result / (result + vec3(1.0));
    // Gamma Correction
    result = pow(result, vec3(1.0/2.2));

    return result;
};
//*************************************Textured PBR************************************
vec3 getTexturedPBR(){
    
    vec3 norm       = normalize(normalize(texture(normalMap, uv).rgb * 2.0 - 1.0));
    vec3 albedo     = pow(texture(albedoMap, uv).rgb, vec3(2.2));
    float metallic  = texture(metallicMap, uv).r;
    float roughness = texture(roughnessMap, uv).r;
    float ambOccul  = texture(ambOcculMap, uv).r;

    surfRef0        = mix(surfRef0, albedo, metallic);
    vec3 outRef     = vec3(0.0);
    float att       = calculateAttenuation(posWS, lightPos);
    vec3 rad        = lightCol * att;
    float halfAngle = max(dot(halfDir, viewDir), 0.0);

    // Cook-Torrance BRDF
    float NDF      = getNormalDistibutionGGX(norm, halfDir, roughness);
    float geometry = getGeometrySmith(norm, viewDir, lightDir, roughness);
    vec3 fresnel   = calculateFresnel(halfAngle, surfRef0);

    // Light Contribution to reflectance equation
    vec3 specFac = fresnel;
    vec3 diffFac = vec3(1.0) - specFac;
    diffFac *= 1.0 - metallic;

    vec3 numerator    = NDF * geometry * fresnel;
    float denominator = (4.0 * max(dot(norm, viewDir), 0.0)) * max(dot(norm, lightDir), 0.0) + 0.0001; //0.0001 prevents / by 0;
    
    vec3 specular = numerator / denominator;

    // Outgoing light
    float NdotL = max(dot(norm, lightDir), 0.0);
    outRef += (diffFac * albedo / Pi + specular) * rad * NdotL;

    vec3 ambient = vec3(0.03) * albedo * ambOccul;
    vec3 result  = ambient + outRef;

    // Tone Mapping (HDR)
    result = result / (result + vec3(1.0));
    // Gamma Correction
    result = pow(result, vec3(1.0/2.2));

    return result;
};



//*************Main Body****************
void main(){
vec3 result = vec3(0.f);
    
    //result = getPBRDirectional(); 
    result = getTexturedPBR(); 

    FragColour = vec4(result, 1.0);
    //FragColour = vec4(norm, 1.0);

    FragColour = vec4(result, 1.0);
}