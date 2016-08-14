#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<string.h>


GLfloat x=0.0,y=0.0,c=0.0,r=0,g=0,b=0,a=0,r1=0,b1=0,g1=0,t1=0,t2=0,t3=0,tt1=0,tt2=0,tt3=0,tc1=0,tc2=0,tc3=0,st=0,s1,s2,s3,m1,m2,m3;
int flag=0;
int ch,k,i,ad;
int id;
float sol=0.1;

//for shadow growth
GLfloat x_grows=0,y_grows=0;

//for side shadow
GLfloat x_shad=0,y_shad=0,x_front=0;
GLfloat x_up=810,x_down=710;
GLfloat y_down=35,y_up=85,y_close=0;

//for front shadow shrink
GLfloat x_frontr=100,x_frontl=210,y_front=35;
GLfloat x_shrink=0,y_shrink=0;

//for flower movement
GLfloat move_x=-10,move_y=0;

//for fish movement
GLfloat fish_x=0,fish_y=0;

void shadow_move()
{
	//for side shadow
	if(x<500)
	{
		glLoadIdentity();
		glColor3f(0.3,0.3,0.3);
		glBegin(GL_POLYGON);
			glVertex3f(310.0,65.0,50.0);
			glVertex3f(410.0,115.0,50.0);
			glVertex3f(x_up-x_shad,y_up-y_shad,50.0);
			glVertex3f(x_down-x_shad,y_down-y_shad,50.0);
		glEnd();
		glFlush();

		glLoadIdentity();
		glColor3f(0.3,0.3,0.3);
		glBegin(GL_POLYGON);
			glVertex3f(310.0,65.0,50.0);
			glVertex3f(200.0,65.0,50.0);
			glVertex3f(300-x_shad,y_front-y_shad,50.0);
			glVertex3f(x_down-x_shad,y_down-y_shad,50.0);
		glEnd();
		glFlush();
	}
}


void fish()
{
	//fish body
	glColor3f(1.0,1.0,0.0);	
	glTranslatef(94.0-fish_x,125.0+fish_y,50.0);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(8*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),20.0);
	glEnd();
	glFlush();
	
	//tail fin
	glLoadIdentity();
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f(107.0-fish_x,130.0+fish_y,40.0);
		glVertex3f(102.0-fish_x,125.0+fish_y,40.0);
		glVertex3f(107.0-fish_x,120.0+fish_y,40.0);
	glEnd();
	glFlush();

	//side fin up
	glLoadIdentity();
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f(99.0-fish_x,133.0+fish_y,40.0);
		glVertex3f(93.0-fish_x,129.0+fish_y,40.0);
		glVertex3f(99.0-fish_x,126.0+fish_y,40.0);
	glEnd();
	glFlush();

	//side down fin
	glLoadIdentity();
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f(99.0-fish_x,117.0+fish_y,40.0);
		glVertex3f(93.0-fish_x,121.0+fish_y,40.0);
		glVertex3f(99.0-fish_x,124.0+fish_y,40.0);
	glEnd();
	glFlush();

	//eye
	glColor3f(0.0,0.0,0.0);	
	glLoadIdentity();
	glPointSize(4.0);
	glBegin(GL_POINTS);
		glVertex3f(90.0-fish_x,126.0+fish_y,45.0);
	glEnd();
	glFlush();
}
void myidle()
{

	//for fish movement
	if(fish_x<25)
	{		fish_x+=0.4;
		fish_y+=0.4;
	}
	else if(fish_x==26)
	{		fish_x=0;
		fish_y=0;
	}
	else if(fish_x>26&&fish_x<50)
	{

		fish_x+=0.4;
		fish_y-=0.4;
	}

	//to move flower during sunrise
	if(move_x<10&&x<700)
		move_x+=0.006+(sol/100);
	else if(move_y<20&&x<300)
		move_y+=0.005;
	else if(x>300&&x<700)
		move_y-=0.005;
	
	//to move the flower back to the initial position
	else if(x>700&&x<1200)
		move_x-=0.006+(sol/100);
	
	//summer solstice
	if(flag==1&&x<600)
	{ 
		sol=0.08;	
	}
	//winter solstice
	else if(flag==2&&x<600)
	{		     
		sol=0.2;
	}
	//equinox
	else if(flag==3)
	{
		sol=0.1;
	}
	else
		sol=0.4;
	
	//move Sun
	x+=sol;
	c+=sol;
	y-=sol;
	if(x<200)
	{
		//change color of sky
		r=x*(153.0/256.0)/200.0;
		g=x*(217/256.0)/200.0;
		b=x*(234/256.0)/200.0;
	}
	if(x>400)
	{
		r=x*(153.0/256.0)/200.0;
		g=x*(217/256.0)/200.0;
		b=x*(234/256.0)/200.0;
	}
	//for sunrise
	if(x>300)
		c-=(2*sol);
	if(x>600)
	{
		r1=(x-500)/500;
		g1=(x-500)/500;
		b1=(x-500)/500;
	}
	//moon to stand at the place
	if(x>=1200)
	{
		c=0;
		x-=1200;
		y+=1200;
	}
	//for shadow growth
	if(x<80)
	{
		x_grows+=(0.045*sol*10);
		y_grows+=(0.03*sol*10);
	}
	else if(x>80&&x<200)
	{
		x_grows+=(0.052*sol*10);
		y_grows+=(0.005*sol*10);
	}
	else
	{
		x_grows=0;y_grows=0;
	}
	
	//for moving the shadow
	if(x<200)
	{
		x_shad=0.0;
		y_shad=0.0;
		x_up=510;
		x_down=410;
		y_down=35;
		y_up=85;
	}
	else if(x_up!=410&&x_down!=310)
	{
		x_shad+=(0.066*sol*10);
		y_shad+=(0.0042*sol*10);
	}

	if(x>400)
	{
		y_shad-=(0.014*sol*10);
	}

	//for front shadow shrinking
	if(x>500&&x<595)
	{
		x_shrink+=(0.118*sol*10);
		y_shrink+=(0.034*sol*10);
	}
	else
	{
		x_shrink=0;
		y_shrink=0;
	}
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,640.0,0.0,480.0,-500.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void mountains()
{
 	//Mountain1
	glBegin(GL_POLYGON);
	if(x<300)
	{
		glColor3f(.95+(x/5000),0.75+(x/5000),0.65-(x/8000));
		//glColor3f(0.0,1.0,0.0);
		tc1=(.95+(x/5000));
		tc2=0.75+(x/5000);
		tc3=0.6-(x/8000);
	}
	else if(x>300 && x<900)
	{
		glColor3f(tc1-(x/10000),tc2-(x/10000),tc3+(x/16000));
	}
	else
	{
		glColor3f(.95,0.75,0.65);
	}
		glVertex3f(0.0,0.0,0.0);
	for(i=0;i<=250;i++)
	{
		glVertex3f(i*2.56,240.0+50.0*sin(i/360.0*2*3.1459),0.0);
   	}
	glColor3f(1.0,1.0,1.0);
		glVertex3f(640.0,0.0,0.0);
	glEnd();
	
	//Mountain2
	glColor3f((.85)+(x/5000),(.66)+(x/5000),(.53)-(x/8000));	
	glBegin(GL_POLYGON);	
	for(i=0;i<=180;i++)
	{
		glVertex3f(370+i*1.856,145.0+100.0*sin((i%360)/360.0*2*3.1459),-1.0);
	}	
	glEnd();
	glFlush();
	glPushMatrix(); 
}

void sky()
{
  	glTranslatef(x*0.75,c*0.75,0.0);
	glTranslatef(60.0,220.0,-100.0);
	if(x<400)
	{
		glColor3f(1.0,0.5+(x/900),0.0);
		st=(.5+(x/900));
	}
	else	
	{
		glColor3f(1.0,st-(x/1800),0.0);
	}
	glutSolidSphere(35.0,100,100);
	glPopMatrix();

	//sky
	if(x<400)
	{
		glColor3f(.03+(r/1.3),.03+(g/1.3),.06+(b/1.3));
		t1=(r/1.3);
		t2=(g/1.3);
		t3=(b/1.3);
	}
	else if(x>350 && x<600)
	{
		glColor3f((t1)-((r/x)),(t2)-((g/x)),(t3)-((b/x)));
	}
	else if(x>600 && x<1000)
	{
		glColor3f(t1-(r/13),t2-(g/13),t3-(b/13));
	}
	else
	{
		glColor3f(t1-(r/11),t2-(g/11),t3-(b/12));
	}
	glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,-200);
		glVertex3f(0.0,480.0,-200);
		glVertex3f(640.0,480.0,-200);
		glVertex3f(640.0,0.0,-200);
	glEnd();
	glFlush();

	if(x>650)
	{
	//moon
		if(x>1000)
		{
			glColor3f(1-(r1/4),1-(g1/4),1-(b1/4));
			m1=(1-(r1/4));
			m2=(1-(g1/4));
			m3=(1-(b1/4));
		}
		else if(x<1000)
		{
			glColor3f(0+r1,0+g1,0+b1);
		}
		else
		{
			glColor3f(s1,s2,s3);
		}
		glTranslatef(900-400,100+300,-100);
		glRotatef(135,0,0,1);

		//moon
		glBegin(GL_POLYGON);
		for(k=0;k<180;k++)
		{
			glVertex3f(25*cos(k*3.14159/180.0),25*sin(k*3.14159/180.0),0);
		}
		glEnd();
		glFlush();
		glLoadIdentity();
	
		//stars
		if(x>900&&x<1300)
		{	
			glColor3f(1-(r1/2),1-(g1/2),1-(b1/2));
			s1=(1-(r1/2));
			s2=(1-(g1/2));
			s3=(1-(b1/2));
		}
		else if(x<900)
		{
			glColor3f(0+r1,0+g1,0+b1);
		}
		else 
		{
			glColor3f(s1,s2,s3);
		}
		
		glPointSize(3.0);
		glBegin(GL_POINTS);
			glVertex3f(50,400,-75);
			glVertex3f(65,420,-75);
			glVertex3f(75,440,-75);
			glVertex3f(85,380,-75);
			glVertex3f(320,400,-75);
			glVertex3f(335,340,-75);
			glVertex3f(40,475,-75);
			glVertex3f(350,460,-75);
			glVertex3f(375,380,-75);
			glVertex3f(150,450,-75);
			glVertex3f(125,350,-75);
			glVertex3f(250,375,-75);
			glVertex3f(350,450,-75);
			glVertex3f(600,325,-75);
			glVertex3f(500,400,-75);
			glVertex3f(425,300,-75);
			glVertex3f(450,315,-75);
			glVertex3f(170,370,-75);
			glVertex3f(225,400,-75);
			glVertex3f(75,300,-75);
			glVertex3f(275,270,-75);
			glVertex3f(375,370,-75);
			glVertex3f(400,370,-75);
			glVertex3f(550,420,-75);
			glVertex3f(575,430,-75);
			glVertex3f(520,450,-75);
		glEnd();
		glFlush();
	}
}



void shadow_shrink()
{
	//for front shadow
	glLoadIdentity();
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
		glVertex3f(310.0,65.0,50.0);
		glVertex3f(200.0,65.0,50.0);
		glVertex3f(x_frontr-x_shrink,y_front-y_shrink,50.0);
		glVertex3f(x_frontl-x_shrink,y_front-y_shrink,50.0);
	glEnd();
	glFlush();
}

void shadow_growth()
{
	//the part of the shadow that moves due to the change in the position of the sun
	glLoadIdentity();
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
		glVertex3f(410.0,115.0,50.0);
		glVertex3f(310.0,65.0,50.0);
		glVertex3f(510-x_grows,5+y_grows,50.0);
		glVertex3f(610-x_grows,55+y_grows,50.0);
	glEnd();
	glFlush();

	//front growth
	glLoadIdentity();
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
		glVertex3f(310.0,65.0,50.0);
		glVertex3f(200.0,65.0,50.0);
		glVertex3f(400-x_grows,5+y_grows,50.0);
		glVertex3f(510-x_grows,5+y_grows,50.0);
	glEnd();
	glFlush();
}

void home()
{
	//front
	glLoadIdentity();
	glColor3f(.255,.224,.133);
	glBegin(GL_POLYGON);
		glVertex3f(200.0,180.0,50.0);
		glVertex3f((310.0),180.0,50.0);
		glVertex3f(310.0,65.0,50.0);
		glVertex3f(200.0,65.0,50.0);
	glEnd();
	glFlush();

	//back
	glLoadIdentity();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3f(300.0,230.0,40.0);
		glVertex3f((410.0),230.0,40.0);
		glVertex3f(410.0,115.0,40.0);
		glVertex3f(300.0,115.0,40.0);
	glEnd();
	glFlush();

	//left side
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3f((300.0),230.0,50.0);
		glVertex3f((200.0),180.0,50.0);
		glVertex3f(200.0,65.0,50.0);
		glVertex3f((300.0),115.0,50.0);
	glEnd();
	glFlush();

	//right side
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex3f((410.0),230.0,50.0);
		glVertex3f((310.0),180.0,50.0);
		glVertex3f(310.0,65.0,50.0);
		glVertex3f((410.0),115.0,50.0);
	glEnd();
	glFlush();

	//roof FRONT TRIWNGLE
	glLoadIdentity();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);	
		glVertex3f(200.0,180.0,100.0);
		glVertex3f((310.0),180.0,100.0);
		glVertex3f(255.0,235.0,100.0);
	glEnd();
	glFlush();

	//TRIANGLE
	glLoadIdentity();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f(300.0,230.0,40.0);
		glVertex3f((410.0),230.0,40.0);
		glVertex3f(355.0,285.0,40.0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3f((410.0),230.0,40.0);
		glVertex3f(355.0,285.0,40.0);
		glVertex3f(255.0,235.0,100.0);
		glVertex3f((310.0),180.0,100.0);
	glEnd();
	glFlush();
	if(x>30&&x<200)
	{
		shadow_growth();
	}
	else if(x>200&&x<500)
	{
		shadow_move();
	}
	else if(x>500&&x<595)
	{
		shadow_shrink();
	}
}

void grass()
{
	int grass=0;
	for(int grass_x=-12;grass_x<24;grass_x+=12)
	{
			//1st set
			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(142.0+grass_x,175.0+grass,10.0);
				glVertex3f(142.0+grass_x,185.0+grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(142.0+grass_x,175.0+grass,10.0);
				glVertex3f(138.0+grass_x,183.0+grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(142.0+grass_x,175.0+grass,10.0);
				glVertex3f(146.0+grass_x,183.0+grass,10.0);
			glEnd();
			glFlush();

			//2nd set
			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,175.0-grass,10.0);
				glVertex3f(74.0+grass_x,185.0-grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,175.0-grass,10.0);
				glVertex3f(70.0+grass_x,183.0-grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,175.0-grass,10.0);
				glVertex3f(78.0+grass_x,183.0-grass,10.0);
			glEnd();
			glFlush();
		
			//3rd set
			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,72.0+grass,10.0);
				glVertex3f(74.0+grass_x,82.0+grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,72.0+grass,10.0);
				glVertex3f(70.0+grass_x,80.0+grass,10.0);
			glEnd();
			glFlush();

			glLoadIdentity();
			glColor3f(0.8,1.0,0.2);	
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glVertex3f(74.0+grass_x,72.0+grass,10.0);
				glVertex3f(78.0+grass_x,80.0+grass,10.0);
			glEnd();
			glFlush();
		grass=grass-4;
	}
}

void stone()
{
	glColor3f(0.4,0.4,0.5);	
	glTranslatef(0.0,63.0,0.0);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(5*cos(k*3.14159/180.0),6*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glTranslatef(9.0,6.0,0.0);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(7*cos(k*3.14159/180.0),6*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();
		
	glTranslatef(2.0,-9.0,0.0);
	glBegin(GL_POLYGON);
		for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),3*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();
	
	glTranslatef(15.0,5.0,0.0);
	glRotatef(135,0,0,1);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(14*cos(k*3.14159/180.0),9*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(161.0,166.0,10.0);
	glRotatef(135,0,0,1);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(6*cos(k*3.14159/180.0),6*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();
	
	glLoadIdentity();
	glTranslatef(173.0,163.0,10.0);
	glRotatef(135,0,0,1);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(8*cos(k*3.14159/180.0),6*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(183.0,148.0,10.0);
	glRotatef(135,0,0,1);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(11*cos(k*3.14159/180.0),9*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(185.0,128.0,10.0);
	glRotatef(135,0,0,1);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(9*cos(k*3.14159/180.0),11*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();
}


void pond()
{
	glColor3f(0.3,0.5,0.9);	
	glTranslatef(94.0,125.0,0.0);
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(88*cos(k*3.14159/180.0),58*sin(k*3.14159/180.0),5.0);
	glEnd();
	glFlush();
	stone();
	grass();
	fish();
}

void sunflower()
{
	int middle=0;
	for(int flower_x=0;flower_x<165;flower_x+=55)
	{
		if(flower_x==55)
			middle=10;
		else 
			middle=0;
	for(int flower_y=0;flower_y<40;flower_y+=10)
	{
		glLoadIdentity();
		glColor3f(0.8,1.0,0.2);	
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3f(154.0-flower_x,172.0+flower_y+middle,40.0);
			glVertex3f(154.0-flower_x,182.0+flower_y+middle,40.0);
		glEnd();
		glFlush();

		glLoadIdentity();
		glColor3f(0.8,1.0,0.2);	
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3f(154.0-flower_x,172.0+flower_y+middle,40.0);
			glVertex3f(150.0-flower_x,180.0+flower_y+middle,40.0);
		glEnd();
		glFlush();

		glLoadIdentity();
		glColor3f(0.8,1.0,0.2);	
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3f(154.0-flower_x,172.0+flower_y+middle,40.0);
			glVertex3f(158.0-flower_x,180.0+flower_y+middle,40.0);
		glEnd();
		glFlush();
	}

	//brown centre
	glTranslatef(154.0-flower_x+move_x,215.0+middle+move_y,55.0);
	glColor3f(0.7,0.3,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(10*cos(k*3.14159/180.0),6.67*sin(k*3.14159/180.0),0);
	glEnd();

	//petals
	glLoadIdentity();
	glTranslatef(154.0-flower_x+move_x,205.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(154.0-flower_x+move_x,225.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(167.0-flower_x+move_x,215.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(141.0-flower_x+move_x,215.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(162.0-flower_x+move_x,222.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(146.0-flower_x+move_x,222.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(146.0-flower_x+move_x,208.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();

	glLoadIdentity();
	glTranslatef(162.0-flower_x+move_x,208.0+middle+move_y,50.0);
	glRotatef(90,0,0,1);
	glColor3f(1.0,1.0,0.4);	
	glBegin(GL_POLYGON);
	for(int k=0;k<360;k++)
		glVertex3f(4*cos(k*3.14159/180.0),4*sin(k*3.14159/180.0),0);
	glEnd();
	glFlush();
	}
}


void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	mountains();
    sky();
	home();
	pond();
	sunflower();
    glFlush();
    glutPostRedisplay();
	glutSwapBuffers(); 
/* Performs a buffer swap on the layer in use for the current window,and empties all buffers, causing all issued commands to be executed as quickly as they are accepted by the actual rendering engine*/
}

/* The menu function is to pop-up the menu when click Right Button of the mouse. On different selections,here the flag is set. According the value of the flags ,the different lights are glown in display function..*/
void main_menu(int id)
{
    switch(id)
	{
		case 1:	flag=1; 
				mydisplay();
				x=0.0;y=0.0;c=0.0;r=0;g=0;b=0;a=0;r1=0;b1=0;g1=0;t1=0;t2=0;t3=0;tt1=0;tt2=0;tt3=0;tc1=0;tc2=0;tc3=0;st=0;
			
				//for shadow growth
				x_grows=0;y_grows=0;
				
				//for side shadow
				x_shad=0;y_shad=0;x_front=0;
				x_up=810;x_down=710;
				y_down=35;y_up=85;y_close=0;
	
				//for front shadow
				x_frontr=100;x_frontl=210;y_front=35;

				//for flower movement
				 move_x=-10;move_y=0;
				 //for fish movement
				 fish_x=0;fish_y=0;

				break;

		case 2:	flag=2;
				mydisplay();
				x=0.0;y=0.0;c=0.0;r=0;g=0;b=0;a=0;r1=0;b1=0;g1=0;t1=0;t2=0;t3=0;tt1=0;tt2=0;tt3=0;tc1=0;tc2=0;tc3=0;st=0;
				
				//for shadow growth
				x_grows=0;y_grows=0;
				
				//for side shadow
				x_shad=0;y_shad=0;x_front=0;
				x_up=810;x_down=710;
				y_down=35;y_up=85;y_close=0;
	
				//for front shadow
				x_frontr=100;x_frontl=210;y_front=35;

				
				//for flower movement
				 move_x=-10;move_y=0;
				 //for fish movement
				 fish_x=0;fish_y=0;
				break;

		case 3: flag=3;
				mydisplay();
				x=0.0;y=0.0;c=0.0;r=0;g=0;b=0;a=0;r1=0;b1=0;g1=0;t1=0;t2=0;t3=0;tt1=0;tt2=0;tt3=0;tc1=0;tc2=0;tc3=0;st=0;
				
				//for shadow growth
				x_grows=0;y_grows=0;
				
				//for side shadow
				x_shad=0;y_shad=0;x_front=0;
				x_up=810;x_down=710;
				y_down=35;y_up=85;y_close=0;
	
				//for front shadow
				x_frontr=100;x_frontl=210;y_front=35;

				
				//for flower movement
				 move_x=-10;move_y=0;
				 //for fish movement
				 fish_x=0;fish_y=0;
				break;

		case 4:	exit(0);
				break;
	}
}

/* The main function is used to call other functions such as keyboard function, mouse function, display function. */

int main(int argc,char **argv)
{
	glutInit(&argc,argv);   
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Day and Night");

	//to create menu and add menu entries
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Summer Solstice",1);
    glutAddMenuEntry("Winter Solstice",2);
	glutAddMenuEntry("Equinox",3);
	glutAddMenuEntry("Quit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(mydisplay);
	glutIdleFunc(myidle);
	glEnable(GL_DEPTH_TEST);
	init();	
	glutMainLoop();
	return 0;
}