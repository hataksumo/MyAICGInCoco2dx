varying vec2 v_texCoord;
void main()
{
	gl_FragColor = texture2D(CC_Texture0,v_texCoord);
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}