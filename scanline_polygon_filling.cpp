#define BLACK 0
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

float x[100],y[100];
int n;
void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
float mx,x,temp;
int i;
	if((y2-y1)<0)
	{
		temp=y1;y1=y2;y2=temp;
		temp=x1;x1=x2;x2=temp;
	}
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
		mx=x2-x1;
	x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
			le[i]=(int)x;
		if(x>(float)re[i])
			re[i]=(int)x;
		x+=mx;
	}
}
void draw_pixel(int x,int y,int value)
{
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void scanfill(float x[],float y[])
{
	int le[500],re[500];
	int i,j;
	for(i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}

	for(i=0;i<n-1;i++){
		edgedetect(x[i],y[i],x[i+1],y[i+1],le,re);
	}
	edgedetect(x[n-1],y[n-1],x[0],y[0],le,re);
	for(j=0;j<500;j++)
	{
		if(le[j]<=re[j])
			for(i=(int)le[j];i<(int)re[j];i++)
				draw_pixel(i,j,BLACK);			
	}

}
void display()
{

	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(0.0, 0.0, 1.0);
	for(int i=0;i<n;i++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x[i],y[i]);
		glEnd();
	}	
	scanfill(x,y);
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc, char** argv)
{	
	cout<<"Enter the no of vertices\n";
	cin>>n;
	cout<<"Enter the coordinates in x,y format\n";
	for(int i=0;i<n;i++){
		cin>>x[i]>>y[i];
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Polygon Filling using Scanline algorithm");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}
