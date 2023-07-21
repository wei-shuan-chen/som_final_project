#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
	vec3 Normal;
    vec3 Color;
	vec2 TexCoords;
} fs_in;


uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool tex;
uniform bool shader;
uniform int texType;
uniform sampler2D texturemap0;
uniform sampler2D texturemap1;
uniform sampler2D texturemap2;
uniform samplerCube shadowMap;
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
// function prototypes
void main()
{
    if(!shader){
        if(tex){
            if(texType == 0)
                FragColor = texture(texturemap0, fs_in.TexCoords);
            if(texType == 1)
                FragColor = texture(texturemap1, fs_in.TexCoords);
            if(texType == 2)
                FragColor = texture(texturemap2, fs_in.TexCoords);
            if(fs_in.TexCoords.x < 0.0 || fs_in.TexCoords.x > 1.0 || fs_in.TexCoords.y < 0.0 || fs_in.TexCoords.y > 1.0){
                FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        }else{
            FragColor = vec4(fs_in.Color, 1.0);
        }
    }
    else{

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



        if(tex){
            vec3 texcolor = vec3(1.0, 1.0, 1.0);
            if(texType == 0)
                texcolor = texture(texturemap0, fs_in.TexCoords).rgb;
            if(texType == 1)
                texcolor = texture(texturemap1, fs_in.TexCoords).rgb;
            if(texType == 2)
                texcolor = texture(texturemap2, fs_in.TexCoords).rgb;

            vec3 I = vec3(ambient + (1.0 - shadow) * (diffuse + specular))*texcolor;
            FragColor = vec4(I, 1.0);
        }else{
            vec3 I = vec3(ambient + (1.0 - shadow) * (diffuse + specular))*fs_in.Color.rgb;
            FragColor = vec4(I, 1.0);
        }
    }

}
