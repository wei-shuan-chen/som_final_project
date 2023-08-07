#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoords;
//layout (location = 4) in vec3 aRaypos;

out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec3 Color;
	vec2 TexCoords;
	//vec3 RayPos;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
	vs_out.Color = vec3(aColor.x,aColor.y,aColor.z);
	vs_out.TexCoords = aTexCoords;
	//vs_out.RayPos = vec3(model * vec4((aRaypos+vec3(0.5,0.5,0.5)), 1.0));
	gl_Position = projection * view * model * vec4(aPos, 1.0);

}