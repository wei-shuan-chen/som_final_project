#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
	vec3 Normal;
    vec3 Color;
	vec2 TexCoords;
} fs_in;

uniform bool tex;
uniform int texType;
uniform sampler2D texturemap0;
uniform sampler2D texturemap1;
uniform sampler2D texturemap2;

void main()
{

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