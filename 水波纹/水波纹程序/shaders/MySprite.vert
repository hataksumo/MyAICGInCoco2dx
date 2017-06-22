attribute vec2 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec4 v_color;
varying vec2 v_texCoord;

void main()
{
	gl_Position = CC_MVPMatrix * vec4(a_position,0.0,1.0);
	v_texCoord = a_texCoord;
	v_color = a_color;
}