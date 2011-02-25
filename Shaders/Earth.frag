//
//  Earth.frag
//  Earth
//
//  Created by Arman Uguray on 2/21/11.
//  Copyright 2011 Brown University. All rights reserved.
//

uniform sampler2D EarthDay;
uniform sampler2D EarthNight;
uniform sampler2D EarthCloudGloss;

varying mediump float Diffuse;
varying mediump vec3  Specular;
varying mediump vec2  TexCoord;

void main (void)
{
    // Monochrome cloud cover value will be in clouds.r
    // Gloss value will be in clouds.g
    // clouds.b will be unused

    mediump vec2 clouds    = texture2D(EarthCloudGloss, TexCoord).rg;
    mediump vec3 daytime   = (texture2D(EarthDay, TexCoord).rgb * Diffuse + 
                          Specular * (clouds.g + 0.2)) * (1.0 - clouds.r) +
                          clouds.r * Diffuse;
    mediump vec3 nighttime = texture2D(EarthNight, TexCoord).rgb * 
                         (1.0 - clouds.r) * 2.0;

    mediump vec3 color = daytime;

    if (Diffuse <= 0.1)
        color = mix(nighttime, daytime, (Diffuse + 0.1) * 5.0);

    gl_FragColor = vec4 (color, 1.0);
}
