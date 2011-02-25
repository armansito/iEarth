//
//  Earth.vert
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

attribute vec4 position;
attribute vec3 Tangent;
attribute vec2 TextureCoord;

uniform mat4 mv;
uniform mat4 proj;
uniform float rot;

varying vec2 TexCoord;

varying vec3 lightPos;
varying vec3 viewVec;

uniform vec3 LightPosition;

void main()
{					
	float c = cos(-rot);
	float s = sin(-rot);
	mat4 ctm = mat4(c,0,s,0,
					0,1,0,0,
				   -s,0,c,0,
				    0,0,0,1);
	
	TexCoord = TextureCoord;
	vec4 pos = mv * ctm * position;
	vec4 normal = normalize(mv * ctm * vec4(position.xyz, 0.0));
	
	// get tangent vectors
	vec3 n = normal.xyz;
	vec3 t = normalize((mv * ctm * vec4(normalize(-Tangent),0.0)).xyz);
	vec3 b = normalize(cross(n,t));

    vec3 light = (mv * vec4(LightPosition, 1.0)).xyz;
	vec3 v;
	v.x = dot(light, t);
	v.y = dot(light, b);
	v.z = dot(light, n);
	lightPos = normalize(v);
	
	v.x = dot(pos.xyz, t);
	v.y = dot(pos.xyz, b);
	v.z = dot(pos.xyz, n);
	viewVec = normalize(v);
	
	gl_Position = proj * pos;
}
