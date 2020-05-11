//
//  GLESFileLoader.m
//  Earth
//
//  Created by Arman Uguray on 2/23/11.
//  Copyright 2011 Brown University. All rights reserved.
//

#import "GLESFileLoader.h"


@implementation GLESFileLoader

+ (GLuint)loadTextureNamed:(NSString *)name
{
	UIImage *image = [UIImage imageNamed:name];
	if (image == nil) {
		NSLog(@"Could not find %@ in application bundle.", name);
		return 0;
	}
	
    GLuint width = (GLuint)CGImageGetWidth(image.CGImage);
    GLuint height = (GLuint)CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( height * width * 4 );
    CGContextRef context = CGBitmapContextCreate( imageData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
    CGContextTranslateCTM( context, 0, height - height );
    CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image.CGImage );
	
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
    CGContextRelease(context);
	
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		NSLog(@"Error while loading image %@ with error no %u",name,err);
		glDeleteTextures(1, &tex);
	}
	
    free(imageData);
	return tex;
}

+ (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return FALSE;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return FALSE;
    }
    
    return TRUE;
}

+ (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        NSLog(@"Failed to link shader program");
        return FALSE;
    }

    NSLog(@"Program linked successfully");
    return TRUE;
}

+ (GLuint)loadShaderNamed:(NSString *)name
{
	GLuint vert, frag, program;
	program = glCreateProgram();
	BOOL good = [GLESFileLoader compileShader:&vert 
										 type:GL_VERTEX_SHADER 
										 file:[[NSBundle mainBundle] pathForResource:name 
																			  ofType:@"vert"]];
	if (!good) {
		NSLog(@"Failed to compile vertex shader");
        return 0;
	}
	
	good = [GLESFileLoader compileShader:&frag
									type:GL_FRAGMENT_SHADER
									file:[[NSBundle mainBundle] pathForResource:name
																		 ofType:@"frag"]];
	if (!good) {
		NSLog(@"Failed to compile fragment shader");
        return 0;
	}
	
	// Attach vertex shader to program.
    glAttachShader(program, vert);
    
    // Attach fragment shader to program.
    glAttachShader(program, frag);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "TextureCoord");

    if ([name isEqualToString:@"Earth"]) {
        glBindAttribLocation(program, 2, "Tangent");
    }
    
    // Link program.
    if (![self linkProgram:program])
    {
        NSLog(@"Failed to link program: %d", program);
        
        if (vert)
        {
            glDeleteShader(vert);
            vert = 0;
        }
        if (frag)
        {
            glDeleteShader(frag);
            frag = 0;
        }
        if (program)
        {
            glDeleteProgram(program);
            program = 0;
        }
        
        return 0;
    }
    
    // Release vertex and fragment shaders.
    if (vert)
        glDeleteShader(vert);
    if (frag)
        glDeleteShader(frag);
	
	return program;
}

@end
