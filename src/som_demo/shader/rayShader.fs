#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
	vec3 Normal;
    vec3 Color;
	vec2 TexCoords;
    vec3 RayPos;
} fs_in;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 modelSize;
uniform samplerCube shadowMap;
uniform sampler3D intensityMap;
uniform sampler1D colorMap;
uniform bool ray;

uniform float far_plane;
uniform float bias;


vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);
float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;

    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(shadowMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);

    return shadow;
}
vec3 phong_shade(vec3 color){
    // ka,kd,ks   ia,id,is
    float ka = 0.4, kd = 0.8, ks = 0.4;
    vec3 Ia = vec3(0.6, 0.6, 0.6);
    vec3 Id = vec3(0.8, 0.8, 0.8);
    vec3 Is = vec3(0.4, 0.4, 0.4);

    // ambient
    vec3 ambient = ka * Ia;
    // diffuse
    vec3 L = normalize(lightPos - fs_in.FragPos);
    vec3 N = normalize(fs_in.Normal);
    vec3 diffuse = kd * Id * max(dot(L, N), 0.0);
    // specular
    vec3 V = normalize(viewPos - fs_in.FragPos);
    vec3 R = reflect(-1*L, N);
    vec3 specular = ks * Is * pow(max(dot(V, R), 0.0), 256.0);

    float shadow = ShadowCalculation(fs_in.FragPos);

    return vec3(ambient + (1.0 - shadow) * (diffuse + specular))*color;
}
// function prototypes
void main()
{
    if(ray){
        vec3 Raypos = fs_in.RayPos;
        vec3 Raytex = Raypos/modelSize;

        vec3 d = (Raypos-viewPos)/length(Raypos-viewPos);
        float T = 0.0, deltat = 1.0;
        vec3 color;

        for(;;){
            vec4 myColorMap = texture(colorMap, texture(intensityMap, Raytex).r);
            vec3 myColor = phong_shade(myColorMap.rgb)*myColorMap.a;
            color = color + (1-T)*myColor;
            T = T + (1-T)*myColorMap.a;
            Raypos = Raypos + deltat*d;
            Raytex = Raypos/modelSize;
            if(Raytex.x >= 1.0 || Raytex.x < 0.0 || Raytex.y >= 1.0 || Raytex.y < 0.0 || Raytex.z >= 1.0 || Raytex.z < 0.0) break;
            if(T > 1.0) break;
        }
        FragColor = vec4(color, 1.0);
    }else{
        vec3 I = phong_shade(fs_in.Color.rgb);
        FragColor = vec4(I, 1.0);
    }
}
