//  ========================================================================
//  COSC363: Computer Graphics (2017);  University of Canterbury.
//
//  FILE NAME: Humanoid.cpp
//  See Lab02.pdf for details
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
#include "loadTGA.h"
using namespace std;

//--Globals ---------------------------------------------------------------
float  eye_x = 0,  eye_y = 8,  eye_z = 32;    //Initial camera position
float look_x = 1, look_y = 10, look_z = 1;    //"Look-at" point along -z direction

//float look_x = 12, look_y = 1, look_z = 10;    //"Look-at" point along -z direction
float  h_look_angle = 0;                              //Look angles
float  v_look_angle = 0;
int cam_step = 0;								   //camera motion
GLuint txId[6];   //Texture ids

float grey[4] = {0.2, 0.2, 0.2, 1.0};
float black[4] = {0};
float white[4]  = {1.0, 1.0, 1.0, 1.0};

int walk_theta = 20;
int walk_z = 0;
int walk_x = 0;

int walk_dir_angle = 90;
int animation_time = 0;
float ring_turning_angle = 0;

// vase
const int N = 50;  // Total number of vertices on the base curve


float vx[N] = {9.5, 8.2, 7, 6.2,
    6, 6.2, 6.8, 7.6, 8.5, 8.7};
float vy[N] = {0, 1, 2, 3,
    4, 5, 6, 7, 8, 9};
float vz[N] = {0};

//--------------------------------------------------------------------------------
void loadTexture()
{
    glGenTextures(6, txId); 	// Create 6 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_bk.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_ft.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_lf.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_rt.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_up.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
    loadTGA("/Users/Pang/Desktop/COSC363/assignment1/criminal-impact_dn.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


}

//	Create the skybox
void skybox() {
  glDisable(GL_LIGHTING);
	//glEnable(GL_BLEND);
	glColor4f(1.0, 1.0, 1.0, 0.9);
	glPushMatrix();
//		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
//		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glEnable(GL_TEXTURE_2D);
		// Back
		glBindTexture(GL_TEXTURE_2D, txId[0]);
		glBegin(GL_QUADS);
      glTexCoord2f(0,  1); glVertex3f(-50, 50, -50);
      glTexCoord2f(0,  0); glVertex3f(-50, 0, -50);
      glTexCoord2f(1,  0); glVertex3f(50, 0, -50);
      glTexCoord2f(1,  1); glVertex3f(50, 50, -50);
		glEnd();
		// Right
		glBindTexture(GL_TEXTURE_2D, txId[3]);
		glBegin(GL_QUADS);
      glTexCoord2f(0,  1); glVertex3f(50, 50, -50);
      glTexCoord2f(0,  0); glVertex3f(50, 0, -50);
      glTexCoord2f(1,  0); glVertex3f(50, 0, 50);
      glTexCoord2f(1,  1); glVertex3f(50, 50, 50);
		glEnd();
		// Front
		glBindTexture(GL_TEXTURE_2D, txId[1]);
		glBegin(GL_QUADS);
        glTexCoord2f(1,  1); glVertex3f(-50, 50, 50);
        glTexCoord2f(1,  0); glVertex3f(-50, 0, 50);
        glTexCoord2f(0,  0); glVertex3f(50, 0, 50);
        glTexCoord2f(0,  1); glVertex3f(50, 50, 50);
		glEnd();
		// Left
		glBindTexture(GL_TEXTURE_2D, txId[2]);
		glBegin(GL_QUADS);
      glTexCoord2f(1,  1); glVertex3f(-50, 50, -50);
      glTexCoord2f(1,  0); glVertex3f(-50, 0, -50);
      glTexCoord2f(0,  0); glVertex3f(-50, 0, 50);
      glTexCoord2f(0,  1); glVertex3f(-50, 50, 50);
		glEnd();
		// Top
		glBindTexture(GL_TEXTURE_2D, txId[4]);
		glBegin(GL_QUADS);
      glTexCoord2f(0,  1); glVertex3f(-50, 50, -50);
      glTexCoord2f(1,  1); glVertex3f(-50, 50, 50);
      glTexCoord2f(1,  0); glVertex3f(50, 50, 50);
      glTexCoord2f(0,  0); glVertex3f(50, 50, -50);
		glEnd();
	glDisable(GL_TEXTURE_2D);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glPopMatrix();
	//glDisable(GL_BLEND);
}

void drawFloor()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
      glNormal3f(0.0, 1.0, 0.0);
      glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glColor3d(1, 1, 1);
      //glMaterialfv(GL_FRONT, GL_SPECULAR, black);
      //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
      glTexCoord2f(0,  0); glVertex3f(-50, 0, -50);
      glTexCoord2f(1,  0); glVertex3f(-50, 0, 50);
      glTexCoord2f(1,  1); glVertex3f(50, 0, 50);
      glTexCoord2f(0,  1); glVertex3f(50, 0, -50);
      //glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    	glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


//--------------------------------------------------------------------------------

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

    glNormal3f(nx, ny, nz);
}


//--------------------------------------------------------------------------------

//--Draws a character model constructed using GLUT objects ------------------
void drawModel()
{
  	glColor3f(.85, 0.72, 0.63);		//Head
  	glPushMatrix();
  	  glTranslatef(0, 8.5, 0);
      glScalef(2.8, 1.7, 1.5);
  	  glutSolidCube(2);
  	glPopMatrix();

    glColor3f(0, 1, 0);		//Left eye
    glPushMatrix();
      glTranslatef(0.9, 8.7, 1.3);
      glutSolidSphere(0.35, 10, 10);
    glPopMatrix();

    glColor3f(0, 1, 0);		//Right eye
    glPushMatrix();
      glTranslatef(-0.9, 8.7, 1.3);
      glutSolidSphere(0.35, 10, 10);
    glPopMatrix();

    glColor3f(0, 0, 0);		//Mouth
    glPushMatrix();
      glTranslatef(0.0, 7.6, 1.51);
      glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex3f(-0.4f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(0.4f, 0.0f, 0.0f);
      glEnd(); //End triangle coordinates
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Torso
    //glColor3f(1, 1, 1);
  	glPushMatrix();
  	  glTranslatef(0, 5.2, 0);
  	  glScalef(3, 4, 1.8);
  	  glutSolidCube(1);
  	glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Torso Skirt Front
    glPushMatrix();
      glTranslatef(0, 2.8, 1.2);
      glRotatef(-35, 1, 0, 0);
      glScalef(3, 1.3, 0.1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Torso Skirt Back
    glPushMatrix();
      glTranslatef(0, 2.8, -1.2);
      glRotatef(35, 1, 0, 0);
      glScalef(3, 1.3, 0.1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Torso Skirt Right
    glPushMatrix();
      glTranslatef(1.6, 2.7, 0);
      glRotatef(15, 0, 0, 1);
      glScalef(0.1, 1.3, 1.8);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Torso Skirt Left
    glPushMatrix();
      glTranslatef(-1.6, 2.7, 0);
      glRotatef(-15, 0, 0, 1);
      glScalef(0.1, 1.3, 1.8);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Right leg circle
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glRotatef(-walk_theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(-0.8, 3, 0);
      glutSolidSphere(.5, 10, 10);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);	      //Moved right leg
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glRotatef(-walk_theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(-0.8, 1.3, 0);
      glScalef(1, 2.8, 1.4);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(.85, 0.72, 0.63);				//Left leg circle
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glRotatef(walk_theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 3, 0);
      glutSolidSphere(.5, 10, 10);
    glPopMatrix();

             //Moved left leg
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glRotatef(walk_theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 1.3, 0);
      glScalef(1, 2.8, 1.4);
      glutSolidCube(1);
    glPopMatrix();

    			//Right arm circle shoulder
    glPushMatrix();
      glTranslatef(-2, 6.5, 0);
      glutSolidSphere(0.4, 10, 10);
    glPopMatrix();

    			//Right arm block shoulder
    glPushMatrix();
      glTranslatef(-1.5, 6.6, 0);
      glScalef(0.8, 0.8, 1);
      glutSolidCube(1);
    glPopMatrix();

             //Moved right arm
    glPushMatrix();
      glTranslatef(2, 6.5, 0);
      glRotatef(walk_theta, 1, 0, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(-2, 4.4, 0);
      glScalef(.8, 3.5, 0.8);
      glutSolidCube(1);
    glPopMatrix();

    			//Left arm circle shoulder
    glPushMatrix();
      glTranslatef(2, 6.5, 0);
      glutSolidSphere(0.4, 10, 10);
    glPopMatrix();

    			//Left arm block shoulder
    glPushMatrix();
      glTranslatef(1.5, 6.6, 0);
      glScalef(0.8, 0.8, 1);
      glutSolidCube(1);
    glPopMatrix();

              //Moved left arm
    glPushMatrix();
      glTranslatef(2, 6.5, 0);
      glRotatef(-walk_theta, 1, 0, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(2, 4.4, 0);
      glScalef(.8, 3.5, 1);
      glutSolidCube(1);
    glPopMatrix();

}



void updateNormalLookXYZ() {
    float dir_x = -sin(h_look_angle), dir_y = sin(v_look_angle),  dir_z = -cos(h_look_angle);
    float d = 2.0;
    look_x = eye_x + d * dir_x;
    look_y = eye_y + d * dir_y;
    look_z = eye_z + d * dir_z;
}


//------- Ring ----------------------------------------------------
// A single circular ring of specified radius
void ring(float radius)
{
    float angle1,angle2, ca1,sa1, ca2,sa2;
    float x1,z1, x2,z2, x3,z3, x4,z4;  //four points of a quad
    float toRad = 3.14159265/180.0;  //Conversion from degrees to radians
    float height = 0.2; // was 1
    float width = 0.1; // was .5
    glBegin(GL_QUADS);
    for(int i = 0; i < 360; i += 5)    //5 deg intervals
    {
        angle1 = i * toRad;       //Computation of angles, cos, sin etc
        angle2 = (i+5) * toRad;
        ca1=cos(angle1); ca2=cos(angle2);
        sa1=sin(angle1); sa2=sin(angle2);
        x1=(radius-width)*sa1; z1=(radius-width)*ca1;
        x2=(radius+width)*sa1; z2=(radius+width)*ca1;
        x3=(radius+width)*sa2; z3=(radius+width)*ca2;
        x4=(radius-width)*sa2; z4=(radius-width)*ca2;
        
        glNormal3f(0., height, 0.);       //Quad 1 facing up
        glVertex3f(x1, height, z1);
        glVertex3f(x2, height, z2);
        glVertex3f(x3, height, z3);
        glVertex3f(x4, height, z4);
        
        glNormal3f(-sa1, 0.0, -ca1);   //Quad 2 facing inward
        glVertex3f(x1, 0.0, z1);
        glVertex3f(x1, height, z1);
        glNormal3f(-sa2 ,0.0, -ca2);
        glVertex3f(x4, height, z4);
        glVertex3f(x4, 0.0, z4);
        
        glNormal3f(sa1, 0.0, ca1);   //Quad 3 facing outward
        glVertex3f(x2, height, z2);
        glVertex3f(x2, 0.0, z2);
        glNormal3f(sa2, 0.0, ca2);
        glVertex3f(x3, 0.0, z3);
        glVertex3f(x3, height, z3);
    }
    glEnd();
}


void drawSweepModel() {
    
    // draw circle that rotates around it
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(ring_turning_angle, 0.0, 1.0, 0.0);
    glTranslated(0, 4.3, 10); // move on track
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    // draw ring with radius 2
    glPushMatrix();
    glTranslated(0, 4.3, 0);
    glColor4f(0.0, 0.0, 0.3, 1.0);
    ring(10);
    glPopMatrix();
    
    float wx[N], wy[N], wz[N];
    glColor4f (0.5, 1.0, 1.0, 1.0); // cyanish colour

    double theta = (-1 * M_PI)/180;
    glBegin(GL_TRIANGLE_STRIP);
    for(int s = 0; s < 360; s++){
        for(int i = 0; i < N; i++)
        {
            wx[i] = vx[i] * cos(theta) + vz[i] * sin(theta);
            wy[i] = vy[i];
            wz[i] = -vx[i] * sin(theta) + vz[i] * cos(theta);
        }

        for(int i = 0; i < N; i++)
        {



            if(i > 0) normal(wx[i-1], wy[i-1], wz[i-1],
                             vx[i-1], vy[i-1], vz[i-1],
                             vx[i], vy[i], vz[i] );
            //glTexCoord2d(float(s)/360.0, float(i)/N);
            glVertex3f(vx[i], vy[i], vz[i]);


            if(i > 0) normal( wx[i-1], wy[i-1], wz[i-1],
                             vx[i], vy[i], vz[i],
                             wx[i], wy[i], wz[i] );

           // glTexCoord2f(float(s+1)/360.0, float(i)/N);
            glVertex3f(wx[i], wy[i], wz[i]);



        }

        for (int j = 0; j < N; j++){
            vx[j] = wx[j];
            vy[j] = wy[j];
            vz[j] = wz[j];
        }

    }
    glEnd();
}

void myTimer(int value)
{
    // walk 13 steps on x axis
    if (animation_time < 13) {
        walk_x++;
    }
    // then turn forward
    else if (animation_time == 13) {
        walk_dir_angle = 0;
    }
    // walk few steps on z axis
    else if (animation_time > 13 && animation_time < 20) {
        walk_z++;
    }
    
    
    ring_turning_angle+=40;
    animation_time++; // increment timer of animation
    if(value == 0){
        walk_theta-=40;
        glutPostRedisplay();
        glutTimerFunc(400, myTimer, 1);
    }
    else if(value == 1){
        walk_theta+=40;
        glutPostRedisplay();
        glutTimerFunc(400, myTimer, 0);
    }

}


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float dir_x = -sin(h_look_angle), dir_y = 0,  dir_z = -cos(h_look_angle);
    // Set the camera
    updateNormalLookXYZ();
    gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z,   0, 1, 0);

    float lpos[4] = {10., 10., 10., 1.0};  //light's position

  	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //Set light position
  	glEnable(GL_LIGHTING);	       //Enable lighting when drawing the model


    
    // draw robot
    glPushMatrix();
    glTranslatef(walk_x, 0, walk_z); // walk
    glRotatef(walk_dir_angle, 0, 1, 0);
    glScalef(0.7, 0.7, 0.7);
    drawModel();
    glPopMatrix();

    // draw sweep model
    glPushMatrix();
    //glTranslated(-30, 0, 0);
    glScalef(0.4, 0.6, 0.4);
    drawSweepModel();
    glPopMatrix();
    

    
    drawFloor();
    skybox();
    glRotatef(dir_x, 0, 1, 0);
  	glRotatef(dir_z, 1, 0, 0);
    glutSwapBuffers(); //Useful for animation
}

void special(int key, int x, int y)
{
    float dir_x = -sin(h_look_angle), dir_y = 0,  dir_z = -cos(h_look_angle);
    float s = 0.1;
    if(key == GLUT_KEY_LEFT) {
        h_look_angle += 0.1;   //in radians
    }
    else if(key == GLUT_KEY_RIGHT) {
        h_look_angle -= 0.1;
    }
    else if(key == GLUT_KEY_DOWN) {
      eye_x = eye_x - s * dir_x;
      //eye_y = eye_y - s * dir_y;
      eye_z = eye_z - s * dir_z;
    }
    else if(key == GLUT_KEY_UP) {
      eye_x = eye_x + s * dir_x;
      //eye_y = eye_y + s * dir_y;
      eye_z = eye_z + s * dir_z;
    }
    updateNormalLookXYZ();
    //cameraMovement();
    glutPostRedisplay();
}


//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    loadTexture();
    glEnable(GL_TEXTURE_2D);
  	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour
  	glEnable(GL_LIGHTING);					//Enable OpenGL states
  	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
  	glEnable(GL_DEPTH_TEST);
  	glEnable(GL_NORMALIZE);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
    gluPerspective(45., 1., 1., 100.);
}



//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Assignment 1");
    initialize();
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutTimerFunc(1000, myTimer, 0);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}
