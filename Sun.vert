//
//  Sun.vert
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

attribute vec4 position;
attribute vec2 TextureCoord;

uniform mat4 mv;
uniform mat4 proj;

uniform float transx;
const float s = 100.0;

varying vec2 TexCoord;

void main()
{
	TexCoord = TextureCoord;
	mat4 ctm = mat4(s,0,0,0,
					0,s,0,0,
					0,0,s,0,
			   transx,0,0,1);
	gl_Position = proj * mv * ctm * position;
}
