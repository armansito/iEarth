//
//  Moon.frag
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

uniform sampler2D MoonTexture;

varying mediump float Diffuse;
varying mediump vec3 Specular;
varying mediump vec2 TexCoord;

void main()
{
	mediump vec3 lightside = texture2D(MoonTexture, TexCoord).rgb + vec3(0.2,0.2,0.2);
	mediump vec3 color = lightside + Specular;
	if (Diffuse <= 0.1)
        color = mix(vec3(0,0,0), lightside, (Diffuse + 0.1) * 1.5);
	gl_FragColor = vec4(color.rgb, 1.0);
}