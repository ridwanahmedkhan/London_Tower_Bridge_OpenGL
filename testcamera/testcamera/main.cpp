#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Vector.h"
#include "Camera.h"

using namespace std;

#define PI 3.1416
#define BLACK 0.0,0.0,0.0






Vector origin(0, 0, 0);
Vector II(1, 0, 0);
Vector JJ(0, 1, 0);
Vector KK(0, 0, 1);
camera cam(II,JJ,KK);

GLuint texid0,texid1,texid2,texid3,texid4,texid5,texid6,texid7,texid8,texid9,texide1,texide2,texide3,texide4,texide5,texide6;

int num_texture=-1;

double polytexcord[8];
double boxcord[24];

double roadang=0.0f;




// Vectors for colours and properties of materials.
const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat yellow[] = { 0.0, 1.0f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };

int countlight=0;
int counthour=0;
int isday=1;
	
// Position the light at the origin.
//const GLfloat light_pos[] = { 0.0, 0.0, 100.0, 1.0 };
const GLfloat light_pos[] = { 0.0, 0.0, 100.0, 1.0 };

const GLfloat light_pos1[] = { 0.0, 0.0, -90.0, 1.0 };
//const GLfloat light_pos1[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat light_pos2[] = { 600.0, 0.0, 150.0, 1.0 };
//const GLfloat light_pos2[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat light_pos3[] = { -600.0, 0.0, 150.0, 1.0 };
//const GLfloat light_pos3[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat light_pos4[] = { 0.0, -600.0, 150.0, 1.0 };
//const GLfloat light_pos4[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat light_pos5[] = { 0.0, 600.0, 150.0, 1.0 };
//const GLfloat light_pos5[] = { 0.0, 0.0, 0.0, 1.0 };


// Attenuation factors for light.
GLfloat const_att = 1.0;
GLfloat const_att1 = 1.0;
GLfloat const_att2 = 1.0;
GLfloat const_att3 = 1.0;
GLfloat const_att4 = 1.0;
GLfloat const_att5 = 1.0;



GLUquadric*	 obj1;


void drawGrid()
{
	
	glBegin(GL_LINES);{

		//X axis
		glColor3f(1, 0, 0);	//100% Red
	    glVertex3f(-200, 0, 0);
		glVertex3f( 200, 0, 0);

		//Y axis
		glColor3f(0, 1, 0);	//100% Green
		glVertex3f(0, -200, 0);	// intentionally extended to -200 to 200, no big deal
		glVertex3f(0,  200, 0);

        // Z axis
	    glColor3f(0, 0, 1);	//100% blue
		glVertex3f(0, 0, -200);
		glVertex3f( 0, 0, 200);
	}glEnd();
	


}

int LoadBitmap(char *filename)
{
	int i,j=0;
	FILE *I_file;
	unsigned char *I_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;


	if((I_file=fopen(filename,"rb"))==NULL)return (-1);
	fread(&fileheader,sizeof(fileheader),1,I_file);
	fseek(I_file,sizeof(fileheader),SEEK_SET);
	fread(&infoheader,sizeof(infoheader),1,I_file);

	I_texture = (byte*)malloc(infoheader.biWidth*infoheader.biHeight*4);
//	printf("loadhere");
	memset(I_texture,0,infoheader.biWidth*infoheader.biHeight*4);

	for(i=0;i<infoheader.biWidth*infoheader.biHeight;i++)
	{
		fread(&rgb,sizeof(rgb),1,I_file);

		I_texture[j+0] = rgb.rgbtRed;
		I_texture[j+1] = rgb.rgbtGreen;
		I_texture[j+2] = rgb.rgbtBlue;
		I_texture[j+3] = 255;
		j+=4;
	}
	fclose(I_file);

	glBindTexture(GL_TEXTURE_2D,num_texture);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,  GL_LINEAR_MIPMAP_NEAREST);

	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D,0,4,infoheader.biWidth,infoheader.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,I_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,infoheader.biWidth,infoheader.biHeight,GL_RGBA,GL_UNSIGNED_BYTE,I_texture);

	free(I_texture);
	return (num_texture);
	return 0;
}



void func()
{
	texid1 = LoadBitmap("images/railing.bmp");
	texid8 = LoadBitmap("images/domewindow.bmp");
	texid9 = LoadBitmap("images/linkbridge.bmp");
	
	texide1 = LoadBitmap("images/environwater.bmp");
	texide2 = LoadBitmap("images/environsky.bmp");
	texide3 = LoadBitmap("images/environside1.bmp");
	texide4 = LoadBitmap("images/environside2.bmp");
	texide5 = LoadBitmap("images/environside3.bmp");
	texide6 = LoadBitmap("images/environside4.bmp");


	texid0 = LoadBitmap("images/street.bmp");
	
	texid2 = LoadBitmap("images/towerwaterface.bmp");
	texid3 = LoadBitmap("images/towerroadface.bmp");
	texid4 = LoadBitmap("images/roadtowercol.bmp");
	texid5 = LoadBitmap("images/towercolpoly.bmp");
	texid6 = LoadBitmap("images/towerbasepoly.bmp");

	

	texid7 = LoadBitmap("images/towercolpil.bmp");
	

	
//	printf("%d",texid);
}





void drawfilledcircle(double radius){

	double x,y;
	glBegin(GL_POLYGON);
     
		x = (double)radius * cos(359 * PI/180.0f);
		y = (double)radius * sin(359 * PI/180.0f);
		for(int j = 0; j < 360; j++)
		{
			glVertex2f(x,y);
			x = (double)radius * cos(j * PI/180.0f);
			y = (double)radius * sin(j * PI/180.0f);
			glVertex2f(x,y);
		}
	glEnd();
}




void drawquad(double toplx,double toply,double toplz,double toprx,double topry,double toprz,double botrx,double botry,double botrz,double botlx,double botly,double botlz)
{

	glPushMatrix();{
	glBegin(GL_QUADS);                      // Draw A Quad
		glTexCoord2f(polytexcord[0],polytexcord[1]);
        glVertex3f(toplx, toply, toplz);				// Top Left
		glTexCoord2f(polytexcord[2],polytexcord[3]);
        glVertex3f(toprx, topry, toprz);              // Top Right
		glTexCoord2f(polytexcord[4],polytexcord[5]);
        glVertex3f( botrx, botry, botrz);              // Bottom Right
		glTexCoord2f(polytexcord[6],polytexcord[7]);
        glVertex3f( botlx, botly, botlz);              // Bottom Left
    glEnd();
	}glPopMatrix();
}

void drawpoly(double toplx,double toply,double toplz,double toprx,double topry,double toprz,double botrx,double botry,double botrz,double botlx,double botly,double botlz)
{
		
	glPushMatrix();{
	glBegin(GL_QUADS);                      // Draw A Quad
		//glTexCoord2f(polytexcord[0],polytexcord[1]);
        glVertex3f(toplx, toply, toplz);				// Top Left
		//glTexCoord2f(polytexcord[2],polytexcord[3]);
        glVertex3f(toprx, topry, toprz);              // Top Right
		//glTexCoord2f(polytexcord[4],polytexcord[5]);
        glVertex3f( botrx, botry, botrz);              // Bottom Right
		//glTexCoord2f(polytexcord[6],polytexcord[7]);
        glVertex3f( botlx, botly, botlz);              // Bottom Left
    glEnd();
	}glPopMatrix();

}


void drawbox()
{
	
	drawpoly(boxcord[0],boxcord[1],boxcord[2] ,boxcord[3],boxcord[4],boxcord[5] ,boxcord[6],boxcord[7],boxcord[8] ,boxcord[9],boxcord[10],boxcord[11]);
	//drawpoly(p1, p2, p3, p4);
	
	drawpoly( boxcord[0],boxcord[1],boxcord[2] ,boxcord[3],boxcord[4],boxcord[5] ,boxcord[15],boxcord[16],boxcord[17] ,boxcord[12],boxcord[13],boxcord[14] );
	//drawpoly(p1, p2, p6, p5);
	
	
	drawpoly( boxcord[3],boxcord[4],boxcord[5] ,boxcord[15],boxcord[16],boxcord[17] ,boxcord[18],boxcord[19],boxcord[20] ,boxcord[6],boxcord[7],boxcord[8] );
	//drawpoly(p2, p6, p7, p3);

	drawpoly( boxcord[6],boxcord[7],boxcord[8] ,boxcord[18],boxcord[19],boxcord[20] ,boxcord[21],boxcord[22],boxcord[23] ,boxcord[9],boxcord[10],boxcord[11] );

	//drawpoly(p3, p7, p8, p4);


	drawpoly( boxcord[0],boxcord[1],boxcord[2] ,boxcord[12],boxcord[13],boxcord[14] ,boxcord[21],boxcord[22],boxcord[23] ,boxcord[9],boxcord[10],boxcord[11] );

	//drawpoly(p1, p5, p8, p4);

	drawpoly( boxcord[12],boxcord[13],boxcord[14] ,boxcord[15],boxcord[16],boxcord[17] ,boxcord[18],boxcord[19],boxcord[20] ,boxcord[21],boxcord[22],boxcord[23] );
	//drawpoly(p5, p6, p7, p8);

}






void drawrailing(){
		
	// railing left face

	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=10.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=10.0f;
	polytexcord[7]=0.0f;
		
	

	glPushMatrix();
	//glTranslatef(-120.0f,0.0f,10.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid1);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(60.0f,-11.5f,0.0f,  60.0f,-11.5f,3.0f,  120.0f,-11.5f,3.0f,  120.0f,-11.5f,0.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// railing right face	
	//glColor3f(1.0f,0.0f,0.0f);

	glPushMatrix();
		glTranslatef(0.0f,1.5f,0.0f);
		//glRotatef(90,1.0f,0.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid1);
		glNormal3f(0.0,1.0,0.0);

		drawquad(60.0f,-11.5f,0.0f,  60.0f,-11.5f,3.0f,  120.0f,-11.5f,3.0f,  120.0f,-11.5f,0.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	

	// railing up face
	//glColor3f(139.0f/255.0f,131.0f/255.0f,134.0f/255.0f);
	glColor3f(0.12f,0.24f,0.3f);
	//glColor3f(0.8f,0.8f,0.8f);


	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(60.0f,-11.5f,3.0f,  60.0f,-10.0f,3.0f,  120.0f,-10.0f,3.0f,  120.0f,-11.5f,3.0f);
	glPopMatrix();
	
	// railing front side face
	//glColor3f(85.0f/255.0f,26.0f/255.0f,139.0f/255.0f);

	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(120.0f,-11.5f,0.0f,  120.0f,-11.5f,3.0f,  120.0f,-10.0f,3.0f,  120.0f,-10.0f,0.0f);
	glPopMatrix();

	// railing back side face
	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(60.0f,-11.5f,0.0f,  60.0f,-11.5f,3.0f,  60.0f,-10.0f,3.0f,  60.0f,-10.0f,0.0f);
	glPopMatrix();
}



void drawroadtower()
{

	//road side face
	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		//glTranslatef(0.0f,20.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid3);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,11.3f,  60.0f,-10.0f,60.0f,  60.0f,10.0f,60.0f,  60.0f,10.0f,11.3f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




	//towercol
		
	glPushMatrix();{
		//glColor3f(1.0f,1.0f,1.0f);
		//glTranslatef(0.0f,20.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid4);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,0.0f,  60.0f,-10.0f,11.3f,  60.0f,-6.0f,11.3f,  60.0f,-6.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

		
	glPushMatrix();{
		//glColor3f(1.0f,1.0f,1.0f);
		glTranslatef(0.0f,16.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid4);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,0.0f,  60.0f,-10.0f,11.3f,  60.0f,-6.0f,11.3f,  60.0f,-6.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




}



void drawtowerpiller()
{

		
	glPushMatrix();{
		glTranslatef(60.0,-10.0f,0.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid7);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,1.25f,64.0f,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(60,-10.0f,64.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	////

		
	glPushMatrix();{
		glTranslatef(60.0,10.0f,0.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid7);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,1.25f,64.0f,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(60,10.0f,64.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	///////////


		
	glPushMatrix();{
		glTranslatef(45.0,-10.0f,0.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid7);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,1.25f,64.0f,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(45,-10.0f,64.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();



	///////


		
	glPushMatrix();{
		glTranslatef(45.0,10.0f,0.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid7);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,1.25f,64.0f,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(45,10.0f,64.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,1.25f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

}





void drawtowerdome(){

	
	boxcord[0]=59.0f;
	boxcord[1]=-9.0f;
	boxcord[2]=60.0f;

		boxcord[3]=46.0f;
		boxcord[4]=-9.0f;
		boxcord[5]=60.0f;

		boxcord[6]=46;
		boxcord[7]=9.0f;
		boxcord[8]=60.0f;

		boxcord[9]=59.0f;
		boxcord[10]=9.0f;
		boxcord[11]=60.0f;


		//chinho	
		boxcord[12]=53.5f;
		boxcord[13]=-1.0f;
		boxcord[14]=75.0f;

		boxcord[15]=51.5;
		boxcord[16]=-1.0f;
		boxcord[17]=75;

		boxcord[18]=51.5;
		boxcord[19]=1.0f;
		boxcord[20]=75;

		boxcord[21]=53.5f;
		boxcord[22]=1.0f;
		boxcord[23]=75;





		glPushMatrix();{
			glColor3f(0.2f,0.6f,1.0f);
		
			drawbox();
		
		}glPopMatrix();



		//window ploygon


			
	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=1.0f;
	polytexcord[7]=0.0f;
		
	

	glPushMatrix();
	//glTranslatef(-120.0f,0.0f,10.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid8);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(60.0f,-3.0f,60.0f,  60.0f,-3.0f,67.0f,  60.0f,3.0f,67.0f,  60.0f,3.0f,60.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();


		
	glPushMatrix();
	glTranslatef(-15.0f,0.0f,0.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid8);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(60.0f,-3.0f,60.0f,  60.0f,-3.0f,67.0f,  60.0f,3.0f,67.0f,  60.0f,3.0f,60.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	


	glPushMatrix();
	//glTranslatef(-120.0f,0.0f,10.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid8);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(49.5f,-10.0f,60.0f,  49.5f,-10.0f,67.0f,  55.5f,-10.0f,67.0f,  55.5f,-10.0f,60.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();


		
	glPushMatrix();
	glTranslatef(0.0f,20.0f,0.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid8);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(49.5f,-10.0f,60.0f,  49.5f,-10.0f,67.0f,  55.5f,-10.0f,67.0f,  55.5f,-10.0f,60.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();





	//window connector


	
	boxcord[0]=55.5f;
	boxcord[1]=-10.0f;
	boxcord[2]=60.0f;

		boxcord[3]=49.5f;
		boxcord[4]=-10.0f;
		boxcord[5]=60.0f;

		boxcord[6]=49.5;
		boxcord[7]=10.0f;
		boxcord[8]=60.0f;

		boxcord[9]=55.5f;
		boxcord[10]=10.0f;
		boxcord[11]=60.0f;


		//chinho	
	boxcord[12]=55.5f;
	boxcord[13]=-10.0f;
	boxcord[14]=67.0f;

		boxcord[15]=49.5f;
		boxcord[16]=-10.0f;
		boxcord[17]=67.0f;

		boxcord[18]=49.5;
		boxcord[19]=10.0f;
		boxcord[20]=67.0f;

		boxcord[21]=55.5f;
		boxcord[22]=10.0f;
		boxcord[23]=67.0f;





		glPushMatrix();{
			glColor3f(1.0f,1.0f,1.0f);
			glColor3f(0.2f,0.6f,1.0f);
		
			drawbox();
		
		}glPopMatrix();



		///////	

	boxcord[0]=60.0f;
	boxcord[1]=-3;
	boxcord[2]=60.0f;

		boxcord[3]=45.0f;
		boxcord[4]=-3;
		boxcord[5]=60.0f;

		boxcord[6]=45;
		boxcord[7]=3;
		boxcord[8]=60.0f;

		boxcord[9]=60.0f;
		boxcord[10]=3;
		boxcord[11]=60.0f;


		//chinho	
	boxcord[12]=60.0f;
	boxcord[13]=-3;
	boxcord[14]=67.0f;

		boxcord[15]=45.0f;
		boxcord[16]=-3;
		boxcord[17]=67.0f;

		boxcord[18]=45;
		boxcord[19]=3;
		boxcord[20]=67.0f;

		boxcord[21]=60.0f;
		boxcord[22]=3;
		boxcord[23]=67.0f;




		glPushMatrix();{
			glColor3f(1.0f,1.0f,1.0f);
			glColor3f(0.2f,0.6f,1.0f);
		
			drawbox();
		
		}glPopMatrix();










}





void drawtower(){

		
	// tower water face
	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=1.0f;
	polytexcord[7]=0.0f;

	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid2);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 45.0f,-10.0f,0.0f,  45.0f,-10.0f,60.0f,  60.0f,-10.0f,60.0f,  60.0f,-10.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	



	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glTranslatef(0.0f,20.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid2);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 45.0f,-10.0f,0.0f,  45.0f,-10.0f,60.0f,  60.0f,-10.0f,60.0f,  60.0f,-10.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	

	//down inside face of tower	
	glPushMatrix();{
		//glColor3f(1.0f,1.0f,1.0f);
		//glTranslatef(0.0f,20.0f,0.0f);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,texid3);
		//glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,11.3f,  45.0f,-10.0f,11.3f,  45.0f,10.0f,11.3f,  60.0f,10.0f,11.3f);
		//glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	//down inside face of tower 2
	glPushMatrix();{
		glColor3f(0.0f,0.0f,0.0f);
		glTranslatef(0.0f,0.0f,-11.3f);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,texid3);
		//glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,11.3f,  45.0f,-10.0f,11.3f,  45.0f,10.0f,11.3f,  60.0f,10.0f,11.3f);
		//glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		//glColor3f(0.1f,0.3f,0.4f);   ///blue --catcch it
		glColor3f(0.2f,0.3f,0.3f);
		glTranslatef(0.0f,0.0f,48.4f);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,texid3);
		//glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 60.0f,-10.0f,11.3f,  45.0f,-10.0f,11.3f,  45.0f,10.0f,11.3f,  60.0f,10.0f,11.3f);
		//glDisable(GL_TEXTURE_2D);
	}glPopMatrix();







	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		drawroadtower();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-15.0f,0.0f,0.0f);
		drawroadtower();
	}glPopMatrix();

	

	//tower piller
	glPushMatrix();{
		drawtowerpiller();	
	}glPopMatrix();


		
	glPushMatrix();{
		drawtowerdome();	
	}glPopMatrix();

	


}


void drawpillar()
{
		
	double pilx=60.0f;
	double pilz=45.0f;

	double heightpillar[4];

	heightpillar[0]=39.0f;
	heightpillar[1]=27.0f;
	heightpillar[2]=16.0f;
	heightpillar[3]=7.0f;



	int i;

	for(i=0;i<4;i++)
	{
		pilz=heightpillar[i];
		pilx+=11.0f;

		boxcord[0]=pilx+1.5f;
		boxcord[1]=-11.5f;
		boxcord[2]=0.0f;

		boxcord[3]=pilx;
		boxcord[4]=-11.5f;
		boxcord[5]=0.0f;

		boxcord[6]=pilx;
		boxcord[7]=-10.0f;
		boxcord[8]=0.0f;

		boxcord[9]=pilx+1.5f;
		boxcord[10]=-10.0f;
		boxcord[11]=0.0f;


		//chinho	
		boxcord[12]=pilx+1.5f;
		boxcord[13]=-11.5f;
		boxcord[14]=pilz;

		boxcord[15]=pilx;
		boxcord[16]=-11.5f;
		boxcord[17]=pilz;

		boxcord[18]=pilx;
		boxcord[19]=-10.0f;
		boxcord[20]=pilz;

		boxcord[21]=pilx+1.5f;
		boxcord[22]=-10.0f;
		boxcord[23]=pilz;





		glPushMatrix();{
			glColor3f(1.0f,1.0f,1.0f);
		
			drawbox();
		
		}glPopMatrix();


	}

}



void drawarc()
{

	double equ[4];
	double equ1[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = 53;//50

	equ1[0] = -1;	//0.x
	equ1[1] = 0;	//0.y
	equ1[2] = 0;//-1.z
	equ1[3] = 111;//52



	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);


	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE1);{
		glPushMatrix();{
			glEnable(GL_CLIP_PLANE0);{
				glColor3f(35.0f/255.0f,85.0f/255.0f,250.0f/255.0f);	//blue
				glRotatef(90,1.0,0.0,0.0);
				glTranslatef(115.0f,55.0f,0.0f);
				glutSolidTorus(0.75,52,4,1000);

			}glDisable(GL_CLIP_PLANE0);
	
		}glPopMatrix();

	
	}glDisable(GL_CLIP_PLANE1);


	//second


	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE1);{
	glPushMatrix();{
	glEnable(GL_CLIP_PLANE0);{
		//glColor3f(0.2,0.3,0.8);	//blue
				
		glRotatef(90,1.0,0.0,0.0);
		glTranslatef(265.0f,200.0f,0.0f);
		glutSolidTorus(0.75,250,4,1000);

	}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	}glDisable(GL_CLIP_PLANE1);
	

}



void drawbasetower()
{
	//base ploygon



	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;

	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;

	polytexcord[4]=5.0f;
	polytexcord[5]=1.0f;

	polytexcord[6]=5.0f;
	polytexcord[7]=0.0f;
		
	

	glPushMatrix();
	//glTranslatef(-120.0f,0.0f,10.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(61.0f,-10.0f,-18.0f, 61.0f,-10.0f,0.0f,   61.0f,10.0f,0.0f, 61.0f,10.0f,-18.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();


		
	glPushMatrix();
	glTranslatef(-17.0f,0.0f,0.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(61.0f,-10.0f,-18.0f, 61.0f,-10.0f,0.0f,   61.0f,10.0f,0.0f, 61.0f,10.0f,-18.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	glPushMatrix();{
		glTranslatef(52.5,-10.0f,-18.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,8.5f,8.5f,18,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	glPushMatrix();{
		glColor3f(0.05f,0.1f,0.2f);
		glTranslatef(52.5,-10.0f,-2.0f);
		drawfilledcircle(8.5);

	}glPopMatrix();

	

	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();{
		glTranslatef(52.5,10.0f,-18.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,8.5f,8.5f,18,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	glPushMatrix();{
		glColor3f(0.05f,0.1f,0.2f);
		glTranslatef(52.5,10.0f,-2.0f);
		drawfilledcircle(8.5);

	}glPopMatrix();
	glColor3f(1.0f,1.0f,1.0f);




//paser cyllinder	
	glPushMatrix();{
		glTranslatef(52.5,-17.5f,-18.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,4.8f,4.8f,5,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(52.5,-17.5f,-13.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,4.8f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	//again opasher cyllinder


		
	glPushMatrix();{
		glTranslatef(52.5,17.5f,-18.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,4.8f,4.8f,5,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		glTranslatef(52.5,17.5f,-13.0f);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid6);


		gluQuadricNormals(obj1,GLU_SMOOTH);
		gluQuadricTexture(obj1,GLU_TRUE);
		gluCylinder(obj1,4.8f,0.0f,6,40,40);

		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();



}






void drawStaticBridge()
{


	// road quad
	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=1.0f;
	polytexcord[3]=0.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=0.0f;
	polytexcord[7]=1.0f;

	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid0);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(60.0f,-10.0f,0.0f,  60.0f,10.0f,0.0f,  120.0f,10.0f,0.0f,  120.0f,-10.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	glPushMatrix();{
		drawrailing();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0.0f,21.5f,0.0f);
		drawrailing();
	}glPopMatrix();

		
	glPushMatrix();{
		drawtower();
	}glPopMatrix();

	
	
	glPushMatrix();{
	//	glTranslatef(2.2,10.25,0.0);
		drawpillar();
	}glPopMatrix();
	


		
	glPushMatrix();{
		glTranslatef(-2.2,-10.75,0.0);
		drawarc();
	}glPopMatrix();





	//again arc & pillar

	glPushMatrix();{
		glTranslatef(0.0,21.5,0.0);
		drawpillar();
	}glPopMatrix();
	


		
	glPushMatrix();{
		glTranslatef(-2.2,10.75,0.0);
		drawarc();
	}glPopMatrix();



		
	glPushMatrix();{
	//	glTranslatef(-2.2,10.75,0.0);
		drawbasetower();
	}glPopMatrix();




	
}



void drawconnectorbridge()
{
			
	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=3.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=3.0f;
	polytexcord[7]=0.0f;

	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid9);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(-25.0f,-10.0f,54.0f,  -25.0f,-10.0f,58.0f,  25.0f,-10.0f,58.0f,  25.0f,-10.0f,54.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

		
	glPushMatrix();{
		glTranslatef(0,3,0);
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid9);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(-25.0f,-10.0f,54.0f,  -25.0f,-10.0f,58.0f,  25.0f,-10.0f,58.0f,  25.0f,-10.0f,54.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


	glPushMatrix();{
		glColor3f(0.2f,0.4f,1.0f);

		drawpoly(25.0f,-10.0f,54.0f,  -25.0f,-10.0f,54.0f,  -25.0f,-7.0f,54.0f,  25.0f,-7.0f,54.0f);

	}glPopMatrix();


		
	glPushMatrix();{
		glColor3f(0.2f,0.4f,1.0f);
		glTranslatef(0,0,4);
		drawpoly(25.0f,-10.0f,54.0f,  -25.0f,-10.0f,54.0f,  -25.0f,-7.0f,54.0f,  25.0f,-7.0f,54.0f);

	}glPopMatrix();


}



void drawhalfrailing()
{
		// railing left face

	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=5.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=5.0f;
	polytexcord[7]=0.0f;
		
	

	glPushMatrix();
	//glTranslatef(-120.0f,0.0f,10.0f);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid1);
		glNormal3f(0.0,-1.0,0.0);
		
		drawquad(25.0f,-11.5f,0.0f,  25.0f-25.0*cos(roadang*PI/180),-11.5f,25.0*sin(roadang*PI/180),  25.0f-25.0*cos(roadang*PI/180),-11.5f,3.0f+25.0*sin(roadang*PI/180),  25.0f,-11.5f,3.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	
	// railing right face	
	glColor3f(1.0f,1.0f,1.0f);

	glPushMatrix();
		glTranslatef(0.0f,1.5f,0.0f);
		//glRotatef(90,1.0f,0.0f,0.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid1);
		glNormal3f(0.0,1.0,0.0);

		drawquad(25.0f,-11.5f,0.0f,  25.0f-25.0*cos(roadang*PI/180),-11.5f,25.0*sin(roadang*PI/180),  25.0f-25.0*cos(roadang*PI/180),-11.5f,3.0f+25.0*sin(roadang*PI/180),  25.0f,-11.5f,3.0f);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	

	// railing up face
	//glColor3f(139.0f/255.0f,131.0f/255.0f,134.0f/255.0f);
	//
	
	glColor3f(0.12f,0.24f,0.3f);
	//glColor3f(0.8f,0.8f,0.8f);


	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(25.0f,-11.5f,3.0f,  25.0f-25.0*cos(roadang*PI/180),-11.5f,3.0f+25.0*sin(roadang*PI/180),  25.0f-25.0*cos(roadang*PI/180),-10.0f,3.0f+25.0*sin(roadang*PI/180),  25.0f,-10.0f,3.0f);
	glPopMatrix();
	
	// railing front side face
	//glColor3f(85.0f/255.0f,26.0f/255.0f,139.0f/255.0f);

	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(25.0f,-11.5f,0.0f,  25.0f,-11.5f,3.0f,  25.0f,-10.0f,3.0f,  25.0f,-10.0f,0.0f);
	glPopMatrix();

	// railing back side face
	glPushMatrix();
	//glTranslatef(0.0f,0.0f,8.0f);
	//glTranslatef(-120.0f,0.0f,10.0f);
	//glRotatef(90,1.0f,0.0f,0.0f);
		drawquad(25.0f-25.0*cos(roadang*PI/180),-11.5f,25.0*sin(roadang*PI/180),  25.0f-25.0*cos(roadang*PI/180),-11.5f,25.0*sin(roadang*PI/180)+3.0f,   25.0f-25.0*cos(roadang*PI/180),-10.0f,25.0*sin(roadang*PI/180)+3.0f,  25.0f-25.0*cos(roadang*PI/180),-10.0f,25.0*sin(roadang*PI/180));
	glPopMatrix();



	
}




void drawhalfroad()
{
	// road quad
	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=1.0f;
	polytexcord[7]=0.0f;


	glPushMatrix();{
		//glTranslatef(-25,0,0);
		//glRotatef(45,0,1,0);



		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid0);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(25.0f,-10.0f,0.0f,  25.0f-25*cos(roadang*PI/180),-10.0f,25*sin(roadang*PI/180),  25.0f-25*cos(roadang*PI/180),10.0f,25*sin(roadang*PI/180),  25.0f,10.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();


		
	glPushMatrix();{
		//glTranslatef(-25,0,0);
		glRotatef(180,0,0,1);



		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texid0);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(25.0f,-10.0f,0.0f,  25.0f-25*cos(roadang*PI/180),-10.0f,25*sin(roadang*PI/180),  25.0f-25*cos(roadang*PI/180),10.0f,25*sin(roadang*PI/180),  25.0f,10.0f,0.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	glPushMatrix();{
		drawhalfrailing();
	}glPopMatrix();


	glPushMatrix();{
		glTranslatef(0,21.5,0);
		drawhalfrailing();
	}glPopMatrix();


	////	
	glPushMatrix();{
		glRotatef(180,0,0,1);
		drawhalfrailing();
	}glPopMatrix();


	glPushMatrix();{
		glRotatef(180,0,0,1);
		glTranslatef(0,21.5,0);
		drawhalfrailing();
	}glPopMatrix();



}




void drawdynamicbridge()
{

	drawconnectorbridge();

	glPushMatrix();{
		glTranslatef(0,17,0);
		drawconnectorbridge();
	}glPopMatrix();

	glPushMatrix();{

		drawhalfroad();

	}glPopMatrix();

}






void initscenelighting()
{
	/*
	// Enable light and set up 2 light sources (GL_LIGHT0 and GL_LIGHT1)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

	// We're setting up two light sources. One of them is located
	// on the left side of the model (x = -1.5f) and emits white light. The
	// second light source is located on the right side of the model (x = 1.5f)
	// emitting red light.

	// GL_LIGHT0: the white light emitting light source
	// Create light components for GL_LIGHT0
	float ambientLight0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuseLight0[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specularLight0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float position0[] = { -1.5f, 1.0f, -4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	// GL_LIGHT1: the red light emitting light source
	// Create light components for GL_LIGHT1
	float ambientLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	float diffuseLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	float specularLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	float position1[] = { 1.5f, 1.0f, -4.0f, 1.0f };	
	// Assign created components to GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);




	*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	if(countlight==0){
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	}
	
	else{
		glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT0, GL_SPECULAR, yellow);
	}
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	if(countlight==0){
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	}
		
	else{
		glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT1, GL_SPECULAR, yellow);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	if(countlight==0){
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white);
	}
	
	else{
		glLightfv(GL_LIGHT2, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT2, GL_SPECULAR, yellow);
	}


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT3);
	if(countlight==0){
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT3, GL_SPECULAR, white);
	}
	
	else{
		glLightfv(GL_LIGHT3, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT3, GL_SPECULAR, yellow);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT4);
	if(countlight==0){
	glLightfv(GL_LIGHT4, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT4, GL_SPECULAR, white);
	}
	
	else{
		glLightfv(GL_LIGHT4, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT4, GL_SPECULAR, yellow);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT5);
	if(countlight==0){
	glLightfv(GL_LIGHT5, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT5, GL_SPECULAR, white);
	}
	else{
		glLightfv(GL_LIGHT5, GL_DIFFUSE, yellow);
		glLightfv(GL_LIGHT5, GL_SPECULAR, yellow);
	}


}

void startlighting()
{

	initscenelighting();
		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();

		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, const_att1);
		glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();


		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, const_att2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();


		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, const_att3);
		glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();


		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, const_att4);
		glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();

		
	glPushMatrix();
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, const_att5);
		glLightfv(GL_LIGHT5, GL_POSITION, light_pos5);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		//glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();


}



void drawenviron(){


	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=1.0f;
	polytexcord[7]=0.0f;

	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide1);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(640.0f,-640.0f,-18.0f,  -640.0f,-640.0f,-18.0f,  -640.0f,640.0f,-18.0f,  640.0f,640.0f,-18.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	

	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide1);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(640.0f,-640.0f,-40.0f,  -640.0f,-640.0f,-40.0f,  -640.0f,640.0f,-40.0f,  640.0f,640.0f,-40.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




	//sky
	/*

	polytexcord[0]=0.0f;
	polytexcord[1]=0.0f;
	polytexcord[2]=0.0f;
	polytexcord[3]=1.0f;
	polytexcord[4]=1.0f;
	polytexcord[5]=1.0f;
	polytexcord[6]=1.0f;
	polytexcord[7]=0.0f;
	*/
		
	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide2);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(640.0f,-640.0f,340.0f,  -640.0f,-640.0f,340.0f,  -640.0f,640.0f,340.0f,  640.0f,640.0f,340.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide3);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(640.0f,-640.0f,-40.0f,  640.0f,-640.0f,340.0f,  -640.0f,-640.0f,340.0f,  -640.0f,-640.0f,-40.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	


	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide4);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(-640.0f,-640.0f,-40.0f,  -640.0f,-640.0f,340.0f,  -640.0f,640.0f,340.0f,  -640.0f,640.0f,-40.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();



	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide5);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad(-640.0f,640.0f,-40.0f,  -640.0f,640.0f,340.0f,  640.0f,640.0f,340.0f,  640.0f,640.0f,-40.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




	glPushMatrix();{
		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texide6);
		glNormal3f(0.0,0.0,1.0);
		//glColor3f(0.2f,0.2f,0.4f);

		drawquad( 640.0f,640.0f,-40.0f,  640.0f,640.0f,340.0f,  640.0f,-640.0f,340.0f ,  640.0f,-640.0f,-40.0f);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();




}






void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(CO(cam.position),CO(cam.LookAtPosition()),CO(cam.up));

	glMatrixMode(GL_MODELVIEW);


	startlighting();





	//your drawing code here
	/*
	glPushMatrix();
		drawGrid();
	glPopMatrix();
	*/

	glPushMatrix();
		drawenviron();
	glPopMatrix();

		
	glPushMatrix();
	glTranslatef(-20,0,0);
	//glRotatef(180,0.0,0.0,1.0);
		drawStaticBridge();
	glPopMatrix();
	
		
	glPushMatrix();
	glTranslatef(20,0,0);
	glRotatef(180,0.0,0.0,1.0);
		drawStaticBridge();
	glPopMatrix();


	glPushMatrix();{
		drawdynamicbridge();
	}glPopMatrix();



	glutSwapBuffers();
}

void animate(){

	if(isday==1){
		counthour++;
		if(counthour==250)
		{
			counthour=0;
			if(countlight==1) countlight=0;
			else countlight=1;

		}
	}

	glutPostRedisplay();
	//codes for any changes in Models, Camera
}


void init(){

	cam.front = -II;
	cam.up=KK;
	cam.right=-JJ;

	//init cam pos
	//back(40,40,40)
	cam.position=Vector(-40,-40,60);

	glEnable(GL_COLOR_MATERIAL);
	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,	1,	0.1,	10000.0);

	initscenelighting();

	func();


	obj1= gluNewQuadric();;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

			
		case '<': 
			const_att *= 0.9f;
			const_att1 *= 0.9f;
			const_att2 *= 0.9f;
			const_att3 *= 0.9f;
			const_att4 *= 0.9f;
			const_att5 *= 0.9f;
			break;
		case '>': 
			const_att /= 0.9f;
						
			const_att1 /= 0.9f;
			const_att2 /= 0.9f;
			const_att3 /= 0.9f;
			const_att4 /= 0.9f;
			const_att5 /= 0.9f;
		break;

				
		case 'u':
			if(roadang<45)
				roadang+=3.0f;
		break;
				
		case 'd':
			if(roadang>2)
				roadang-=3.0f;
			break;

		case 'n':
			if(isday==1)
				isday=0;
			else isday=1;
			break;


		case '1':
			cam.position.x-=5;
			break;
		case '2':
			cam.position.x+=5;
			break;
		case '3':
			cam.position.y-=5;
			break;
		case '4':
			cam.position.y+=5;
			break;
		case '5':
			cam.position.z-=5;
			break;
		case '6':
			cam.position.z+=5;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void specialKeyListener(int key, int x,int y)
{
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
			   cam.Move(cam.up,-10.0);
			else
               cam.Move(cam.front,-10.0);
			break;
		case GLUT_KEY_UP:		// up arrow key
            if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
               cam.Move(cam.up,10);
			else
               cam.Move(cam.front,10);
			break;

		case GLUT_KEY_RIGHT:
			if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
			   cam.Move(cam.right,10);
			else
               cam.Turn(10);
			break;
		case GLUT_KEY_LEFT:
			if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
			   cam.Move(cam.right,-10);
			else
			   cam.Turn(-10);
			break;

		case GLUT_KEY_PAGE_UP:
			cam.Pitch(-10);
			break;
		case GLUT_KEY_PAGE_DOWN:
			cam.Pitch(10);
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			cam.Roll(10);
			break;
		case GLUT_KEY_END:
			cam.Roll(-10);
			break;

		default:
			break;
	}
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

