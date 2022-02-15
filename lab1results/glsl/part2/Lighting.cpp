//
//  Lighting
//
//  Simple module for setting up the parameters for lighting and shading
//  for the Shading Assignment.
//
//  Created by Warren R. Carithers 2019/11/18.
//  Updated: 2021/11/07 by wrc
//  Copyright 2021 Rochester Institute of Technology.  All rights reserved.
//

#include "Lighting.h"

#include "Application.h"
#include "Models.h"
#include "Utils.h"

using namespace std;

// lighting data
GLfloat lightcolor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightpos[4]   = { 4.0f, 1.0f, 2.0f, 1.0f };
GLfloat amblight[4]   = { 0.5f, 0.5f, 0.5f, 1.0f };

// cube properties
// GLfloat amb_cube[4]   = { 0.0f, 1.0f, 0.7f, 1.0f };
// GLfloat diff_cube[4]  = { 0.0f, 1.0f, 0.7f, 1.0f };
// GLfloat spec_cube[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };
// GLfloat exp_cube      = 50.0f;
// GLfloat k_cube[3]     = { 0.5f, 0.7f, 1.0f };

GLfloat color_cube[4]   = { 0.0f, 1.0f, 0.7f, 1.0f};
GLfloat smoothness_cube = 0.3f;
GLfloat metalness_cube  =  0.5f;
GLfloat transparency_cube   = 0.0f;
GLfloat refraction_cube = 0.0f;

// cylinder properties
// GLfloat amb_cyl[4]    = { 1.0f, 0.3f, 0.0f, 1.0f };
// GLfloat diff_cyl[4]   = { 1.0f, 0.3f, 0.0f, 1.0f };
// GLfloat spec_cyl[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
// GLfloat exp_cyl       = 30.0f;
// GLfloat k_cyl[3]      = { 0.5f, 0.7f, 1.0f };

GLfloat color_cyl[4]    = {1.0f, 0.3f, 0.0f, 1.0f};
GLfloat smoothness_cyl  = 0.7f;
GLfloat metalness_cyl   = 0.2f;
GLfloat transparency_cyl = 0.0f;
GLfloat refraction_cyl = 0.0f;

// sphere properties
// GLfloat amb_sph[4]    = { 1.0f, 0.3f, 0.7f, 1.0f };
// GLfloat diff_sph[4]   = { 1.0f, 0.3f, 0.7f, 1.0f };
// GLfloat spec_sph[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
// GLfloat exp_sph       = 70.0f;
// GLfloat k_sph[3]      = { 0.5f, 0.7f, 1.0f };

GLfloat color_sph[4]    = {1.0f, 0.3f, 0.7f, 1.0f};
GLfloat smoothness_sph  = 0.5f;
GLfloat metalness_sph   = 0.5f;
GLfloat transparency_sph = 0.0f;
GLfloat refraction_sph  = 0.0f;

///
/// This function sets up the lighting, material, and shading parameters
/// for the shaders.
///
/// @param program  The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param object   Which object is currently being drawn
///
void setLighting( GLuint program, Shape object )
{
    GLint loc;

    // Lighting parameters
    loc = getUniformLoc( program, "lightPosition" );
    if( loc >= 0 ) {
        glUniform4fv( loc, 1, lightpos );
    }

    loc = getUniformLoc( program, "lightColor" );
    if( loc >= 0 ) {
        glUniform4fv( loc, 1, lightcolor );
    }

    // loc = getUniformLoc( program, "ambientLight" );
    // if( loc >= 0 ) {
    //     glUniform4fv( loc, 1, amblight );
    // }



    // Object properties
    GLint objectColor 	= getUniformLoc( program, "objectColor" );
    GLint smoothness 	= getUniformLoc( program, "smoothness" );
    GLint metalness  	= getUniformLoc( program, "metalness" );
    GLint transparency 	= getUniformLoc( program, "transparency" );
    //GLint refraction  = getUniformLoc( program, "refraction" );

    switch( object ) {
    case Cube:
        glUniform4fv( objectColor, 1, color_cube );
        glUniform1f	( smoothness, smoothness_cube );
        glUniform1f	( metalness,  metalness_cube );
        glUniform1f	( transparency, transparency_cube );
        //glUniform1f(  refraction, refraction_cube );
        break;

    case Cylinder:
        glUniform4fv( objectColor, 1, color_cyl );
        glUniform1f( smoothness, smoothness_cyl );
        glUniform1f( metalness,  metalness_cyl );
        glUniform1f( transparency, transparency_cyl );
        //glUniform1f(  refraction, refraction_cyl );
        break;

    case Sphere:
        glUniform4fv( objectColor, 1, color_sph );
        glUniform1f( smoothness, smoothness_sph );
        glUniform1f( metalness,  metalness_sph );
        glUniform1f( transparency, transparency_sph );
        //glUniform1f(  refraction, refraction_sph );
        break;

    default:
        cerr << "ERROR unknown object " << object << " - ignoring" << endl;
    }
}
