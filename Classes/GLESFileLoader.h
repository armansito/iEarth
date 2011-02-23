//
//  GLESFileLoader.h
//  Earth
//
//  Created by Arman Uguray on 2/23/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface GLESFileLoader : NSObject {}

+ (GLuint)loadTextureNamed:(NSString *)name;
+ (GLuint)loadShaderNamed:(NSString *)name;

@end
