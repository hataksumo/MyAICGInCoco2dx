attribute vec3 in_position;
attribute vec2 in_Tex;
varying vec2 tex_coord;
uniform mat4 modelViewMatrix;
uniform mat4 projectMatrix;

void main(void)
{
   gl_Position = projectMatrix * (modelViewMatrix * vec4(in_position,1.0));
   tex_coord = in_Tex;
}