varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()                                            
{                                                                                         
    vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	float ratio=texColor.r;
	ratio = max(ratio,texColor.g);
	ratio = max(ratio,texColor.b);
                                                  
	texColor.r = texColor.r;                  
	texColor.g = texColor.g;                    
	texColor.b = texColor.b;                    
	texColor.a = texColor.a * ratio;
	                                                                                                                                           
	gl_FragColor = v_fragmentColor * texColor;            
}

