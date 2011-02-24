//
//  Sun.frag
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

uniform sampler2D SunTexture;

varying mediump vec2 TexCoord;

void main()
{
	gl_FragColor = vec4(texture2D(SunTexture, TexCoord).rgb, 1.0);
}