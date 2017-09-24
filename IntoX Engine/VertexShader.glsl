#version 400 core

in layout(location=0) vec3 local_position;
in layout(location=1) vec2 local_textureCoords;

uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

out vec3 color;
out vec2 textureCoords;

void main(void) {

	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(local_position, 1.0);	
	textureCoords = local_textureCoords;

}