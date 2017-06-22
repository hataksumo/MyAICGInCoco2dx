attribute vec2 b_texCord;
attribute vec2 b_position;
varying vec2 v_texCoord;
void main()
{
	gl_Position = CC_MVPMatrix * vec4(b_position,0.0,1.0);
	v_texCoord = b_texCord;
}