#version 330 core

layout(location = 0) in vec3 vertices_position_modelspace;
layout (location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 normals;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 project_mat;
uniform mat4 localTransformMatrix;
uniform bool isMesh;

uniform sampler2D texture0;



out vec2 TexCoord; // UV

void main()
{
	vec3 pos = vertices_position_modelspace;

	if(isMesh)
	{
		gl_Position = project_mat * view_mat * localTransformMatrix * vec4(pos,1);
	} else
	{
		float height = texture(texture0,textureCoordinates).r;
		pos.y += height;

		// --------------------------- Out --------------------------- //
		TexCoord = textureCoordinates;

		gl_Position =  project_mat * view_mat * model_mat * vec4(pos,1);
	}
}

