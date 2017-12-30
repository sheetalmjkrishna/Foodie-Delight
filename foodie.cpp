#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<math.h > 
#include<stdarg.h>
int foo,drin;
int ctr=0; //Keeps count of number of items selected.
//If ctr=0 then ask user to select an item.
int flag_eat=0; //To check if "E or e" has been pressed
int choice_food=0; //To keep track of which food item has been selected
int flag_drink=0; //To check if "D or d" has been pressed
int choice_drink=0; //To keep track of which drink has been selected
int ctr_f1=0, ctr_f2=0, ctr_f3=0;
int render=1; //To display start-up screen
int c1=0,c=0;// marks the type of cup
//TEXT RELATED
void drawtext(char * message, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat sx, GLfloat sy, GLfloat sz)
{
	char *t;
	glPushMatrix();

glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glScalef(sx, sy, sz); glTranslatef(tx, ty, tz);
 	for(t = message; *t; t++)
	glutStrokeCharacter(GLUT_STROKE_ROMAN, *t);
	glPopMatrix();
}
void output1(char *string, GLdouble x, GLdouble y,GLdouble z)
{      
	int i;
	glColor3f(0,1,1);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glRasterPos3d(x,y,z);
	for(i=0;i<strlen(string);i++)
	{ 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		glFlush();
		Sleep(50);
    	}
 	glPopAttrib();
}
void output(char *string, GLdouble x, GLdouble y,GLdouble z) 
{
	int i; 
	glPushAttrib(GL_ALL_ATTRIB_BITS);
 	glColor3f(1.0,1.50,0.50); 
	glRasterPos3d(x,y,z);
 	for(i=0;i<strlen(string);i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		 glFlush();
	
 Sleep(50); 
	}
 	glPopAttrib(); 
}
void circle(GLfloat x,GLfloat y,GLfloat r, int thetai,int thetal) 
{ 
	GLfloat theta,thetar; glBegin(GL_POLYGON);
	for(theta=thetai;theta<=thetal;theta=theta+1) 
	{
		thetar=(theta*3.14)/ 180;
       		glVertex2f(x+(cos(thetar)*r),y+(sin(thetar)*r));
	}
 	glEnd();
	glFlush(); 
}
void display_text(int c) 
{
	GLfloat wal[] = {3.1f,3.0f,0.4f,0.04};   //yellow 
	GLfloat txt2[] = {0.0f,1.0f,1.0f,0.0f}; 
	GLfloat msg1 [] ={3.0f,0.0f,3.0f,0.04}; 
	GLfloat msg2[] = {1.0f,2.0f,0.0f,0.0f};
	GLfloat msg3[] ={0.0f,3.0f,3.0f,0.0f}; 
	GLfloat txt[] = {1.0f,0.0f,0.0f,0.04}; 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); 
	glOrtho (-0.75,0.75,-0.40,0.75,-0.75,100); 
	glMatrixMode (GL_MODELVIEW); 
	glLoadIdentity();
	glPushMatrix();
	glMaterialfv (GL_FRONT, GL_AMBIENT, txt2); 
	if(c==0)	
	 { 

output(" PLEASE ",-0.5,0.3,0); 
		output(" SELECT ",-0.3,0.25,0);
		output(" AN ",-0.1,0.2,0); 
		output(" ITEM!",-0.0,0.15,0);
	}
	else 
	{
		glMaterialfv (GL_FRONT, GL_AMBIENT, txt);
		glColor3f(0,1,0);
		output1("B",-0.25,0.6,0);
		output1("U",-0.20,0.55,0);
 		output1("R",-0.25,0.5,0);
 		output1("P!!",-0.20,0.45,0);
 		glMaterialfv (GL_FRONT, GL_AMBIENT, msg1);
		 glColor3f(0,1,0); 
 		output(" HOPE YOU ",-0.2,0.3,0);//RASTER TEXT WORKS BUT IT IS SMALL 
		glMaterialfv (GL_FRONT, GL_AMBIENT, msg2); 
		glColor3f(1,.1,0);
		output(" ENJOYED THE MEAL !!!! ",-0.4,0.2,0);
 		glMaterialfv (GL_FRONT, GL_AMBIENT, wal); 
		glColor3f(1,0,0.1);
		output(" ***********************************",-0.4,0.1,0); 
		glMaterialfv (GL_FRONT, GL_AMBIENT, msg3); 
		output("             HAVE A NICE DAY!!!!!! :)",-0.4,0.0,0);
	}
 	glPopMatrix(); 
	glFlush(); 
}
//ROOM COMPONENTS
void wall (double thickness) 
{

glColor3f(0.0,0.8,0.8); //draw thin wall with top = xz-plane, corner at origin 
	glPushMatrix();
 	glTranslated (0.5, 0.5 * thickness, 0.5); 
	glScaled (1.0, thickness, 1.0); 
	glutSolidCube (1.0);
 	glPopMatrix(); 
} //draw one table leg 
void tableLeg (double thick, double len) 
{
	glPushMatrix();
	glTranslated (0, len/2, 0); glScaled (thick, len, thick); glutSolidCube (1.0); 	glPopMatrix(); 
}
void table (double topWid, double topThick, double legThick, double legLen) 
{
// draw the table - a top and four legs 
//draw the top first 
	glPushMatrix();
	glTranslated (0, legLen, 0); 
 	glScaled(topWid, topThick, topWid); 
	glutSolidCube (1.0); glPopMatrix(); 
	double dist = 0.95 * topWid/2.0 - legThick/2.0; 
	glPushMatrix(); glTranslated (dist, 0, dist); 
	tableLeg (legThick, legLen);
 	glTranslated (0.0, 0.0, -2 * dist);
 	tableLeg (legThick, legLen); 
	glTranslated (-2*dist, 0, 2 *dist);
 	tableLeg (legThick, legLen); 
	glTranslated(0, 0, -2*dist); 
	tableLeg (legThick, legLen); 
	glPopMatrix(); 
}

void table_walls_disp() 
{
	GLfloat tabl[] = {1.80f, 1.0f, .510f, 1.04};
 	GLfloat wal[] = {13.5f,3.0f,0.4f,0.04};//yellow 
	GLfloat text[] ={0.0f,2.0f,2.0f,0.04}; 
	GLfloat mat_diffuse[] = {.5f, 0.5f, .5f, 1.0f};
	GLfloat mat_specular[] = {1.3f, .50f, .50f, 1.04};
	GLfloat mat_shininess[] = {8.0f}; //set the material properties
	glMaterialfv (GL_FRONT, GL_AMBIENT, wal); 
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular); 
	glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess); 
	//set the light source properties
 	GLfloat lightIntensity[] = {0.56f, 0.7f, 0.7f, 1.0f}; 
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.04};
 	glLightfv (GL_LIGHT0, GL_POSITION, light_position); 
	glLightfv (GL_LIGHT0, GL_DIFFUSE, lightIntensity); //set the camera 	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho (-0.75,0.75,-0.40,0.75,-0.75,100); 
	glMatrixMode (GL_MODELVIEW); 
	glLoadIdentity();
 	gluLookAt (2, 0.8, 2.0, 0, 0.23, 0, 0.0, 01.0, 0.0); 
	//(cam It rt,up dn,screen lt,rt,up,dn,tilt,ulta,lt rt tilt) 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	wall(0.02);
	glPushMatrix();
	glRotated(90.0,0.0,0.0,1.0);
	wall(0.02);
	glPopMatrix();
	glPushMatrix();
	glRotated (-90.0, 1.0, 0.0, 0.0); 

wall (0.02); 
	glPopMatrix(); 
	glPushMatrix();
	glMaterialfv (GL_FRONT, GL_AMBIENT, tabl); 
	glTranslated (0.4, 0, 0.4);
 	table (0.8, 0.03, 0.03, 0.35); 
	glPopMatrix(); 
	glPushMatrix();
 	glMaterialfv (GL_FRONT, GL_AMBIENT, text);
 	glTranslated (0.4, 0, 0.4); 
	drawtext("PRESS E to EAT!",-300,900,-300,0.00085,0.00085,0.00085); 
	drawtext(" D to DRINK!",-350,750,-300,0.00085,0.00085,0.00085); 	glRotatef(90.0,0.0,1.0,0.0); 
	drawtext("RIGHT CLICK",-1500,1200,500,0.00085,0.00085,0.00085);
 	drawtext(" for Menu!!",-1500,1080,500,0.00085,0.00085,0.00085); 
	glPopMatrix();
 	glFlush(); 
}
//INDIVIDUAL FOOD CALLS 
void donut(int d_choice) //referrred by case 1 of food()
{
	table_walls_disp();
	donut_code();
	if(d_choice!=0)
	{
		switch(d_choice)
		{
			case 1: cup1_code();
			break;
			case 2: cup2_code();
			break;
			case 3: cup3_code();

 			break;
		}
}
glFlush();
}
void cake1(int d_choice) // referred by case 2 of food()
{
	table_walls_disp();
	cake1_code();
	if(d_choice!=0)
	{
		switch(d_choice)
		{
			case 1: cup1_code();
		 break;
		case 2: cup2_code();
		break;
		case 3: cup3_code();
		break;
	}
}
glFlush();
}
void cake2(int d_choice) // referred by case 3 of food()
{
		table_walls_disp();
		cake2_code();
		if(d_choice!=0)
		{
 			switch(d_choice)
			{
				case 1: cup1_code();

				break;
				case 2: cup2_code();
				break;
				case 3: cup3_code();
				break;

			}
	}
	glFlush();
}
//FOOD CODES
void donut_code()
{
	if(flag_eat==0) // Display only if has not been pressed
{
	//plates
	GLfloat donut[] = {1.5f, .701f, .7f, 1.01};
	GLfloat vessel1[] = {4.f,4.f,4.f,1.01};
	GLfloat vessel2[] = {1.5f, 0.4f, 0.5f, 0.8501};
	glPushMatrix();
	glMaterialfv (GL_FRONT, GL_AMBIENT, vessel2);
	glTranslated (0.5, 0.39, 0.45);
	glRotated (90, 1, 0, 0);
	glColor3f(0,0.45,1);
	glutSolidCone (0.15, 0.04, 50, 50); //base,height,slices,stacks
	glPopMatrix();
	glPushMatrix();
	glMaterialfv (GL_FRONT, GL_AMBIENT, vessel1);
	glTranslated (0.5, 0.39, 0.45);
	glRotated (90, 1,0, 0);
	glutSolidCone (0.13, 0.03, 50, 50); //base,height,slices,stacks
	glPopMatrix();

	//donut itself
	glPushMatrix();
	glMaterialfv (GL_FRONT, GL_AMBIENT, donut);
	glTranslated (0.45, 0.385, 0.40);
	glRotated (90, 1, 0, 0);
	glutSolidTorus (0.02, 0.05, 10, 20); 
	//Inner radius,outer radius,sides,rings
 	glPopMatrix();
}
}

	void cake1_code()
	{
 		if(flag_eat==0) // display only if this item has not been eaten already
		{
	
			GLfloat cherry[] = {1.8f, 0.01f, .101, 1.01};
			GLfloat cak[] = {2.8f, 0.5f, 1.1f, 1.01};
			GLfloat cak1[] = {3.8f, 3.5f, 3.1f, 1.01};
			GLfloat vessel1[]= {4.f,4.f,4.f,1.01};
			GLfloat vessel2[] = {1.5f, 0.41f, 0.5f, 0.8501};
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, vessel2);
			glTranslated (0.5, 0.39, 0.45);
			glRotated (90, 1, 0, 0);
		glColor3f(0,0.45,1);
		glutSolidCone (0.15, 0.04, 50, 50); //base,height,slices,stacks
		glPopMatrix();
		glPushMatrix();
		glMaterialfv (GL_FRONT, GL_AMBIENT, vessel1);
		glTranslated (0.5, 0.39, 0.45);
		glRotated (90, 1,0, 0);

		glutSolidCone (0.13, 0.03, 50, 50); //base,height,slices,stacks
		glPopMatrix();
 		glPushMatrix();
		glMaterialfv (GL_FRONT, GL_AMBIENT, cak1);
		glScaled (1.5, 0.4, 1.5);
		glTranslated (.32, 1.0, 0.29);
		glutSolidCube(0.1);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, cak);
		glScaled (1, 0.5, 1);
		glTranslated (.47, 0.86, .43);
		glutSolidCube(0.1);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv (GL_FRONT, GL_AMBIENT, cherry);
		glTranslated (.47, 0.47, .43);
		glutSolidSphere(0.012, 20, 20);
		glPopMatrix();
	}
}
void cake2_code()
{
	if(flag_eat==0)
		{
			GLfloat cherry[] = {1.8f, 0.f, .1f, 1.01};
			GLfloat cak[] = {3.8f, 3.5001f, 3.1f, 1.01};
			GLfloat vessel1[] = {4.f,4.f,4.f,1.f};
			GLfloat vessel2[] = {1.5f, 0.4f, 0.5f, 0.8501};
			glPushMatrix();
			glTranslated (0.5, 0.39, 0.45);
			glRotated (90, 1, 0, 0);

			glColor3f(0,0.45,1);
			glutSolidCone (0.15, 0.04, 50, 50); //base,height,slices,stacks
			glPopMatrix();
			glPushMatrix();
			glMaterialfv (GL_FRONT, GL_AMBIENT, vessel1);
			glTranslated (0.5, 0.39, 0.45);
			glRotated (90, 1,0, 0);
			glutSolidCone (0.13, 0.03, 50, 50); //base,height,slices,stacks
			glPopMatrix();
			//base,height,slices,stacks
			glPushMatrix();
			glMaterialfv (GL_FRONT, GL_AMBIENT, cak);
			glScaled (1.5, 0.4, 1.5);
			glTranslated (.32, 1., .29);
			glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
			glMaterialfv (GL_FRONT, GL_AMBIENT, cak);
			glScaled (1, 0.5, 1);
			glTranslated (.47, 0.86, .43);
			glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, cherry);
			glTranslated (.47, 0.47, .43);
			glutSolidSphere(0.012, 20, 20);
			glPopMatrix();
	}
}
//INDIVIDUAL DRINK CALLS
void cup1(int f_choice) //CHOCO FLOAT. Referred by case 1 of drink()
{

	table_walls_disp();
	cup1_code();
	if(f_choice!=0)
	{
		switch(f_choice)
		{
			case 1: donut_code();
			break;
			case 2: cake1_code();
			break;
			case 3: cake2_code();
			break;
	}
}
glFlush();
}
void cup2(int f_choice) // CHERRY DELIGHT. Referred by case 2 of drink()
{
 	table_walls_disp();
	cup2_code();
	if(f_choice!=0)
	{
		switch(f_choice)
		{
			case 1: donut_code();
 			break;
			case 2: cake1_code();
 			break;
			case 3: cake2_code();
			 break;
		}
}

glFlush();
}
 void cup3(int f_choice) // GRAPE SQUASH. Referred by case 3 of drink()
{
	table_walls_disp();
	cup3_code();
	 if(f_choice!=0)
	{
 	switch(f_choice)
	{
 		case 1: donut_code();
		break;
 		case 2: cake1_code();
 		break;
 		case 3: cake2_code();
 		break;
		//cup3_code();
	}
}
glFlush();
}
 //DRINK CODES
 void cup1_code()
{	
	GLfloat vessel1[] = {4.f,4.0f,4.0f,1.0f};
	GLfloat vessel2[] = {1.51, 0.41, 0.51, 0.8501};
	if(flag_drink==0)
	{	
 		c=1;
		c1=0;
		GLfloat choc[] = {1.2f, .501f,.1f, 1.0f};
		GLfloat cup[]= {0.f, 1.f, 01.f, 1.0f};

		glMaterialfv (GL_FRONT, GL_AMBIENT, choc);
		glPushMatrix();
		glTranslated (-.01, 0.48, 0.32);
		glRotated (90, 1, 0, 0);
		glutSolidTorus (0.022, 0.03, 10, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslated (-.01, 0.504, 0.32);
		glRotated (90, 1, 0, 0);
		glutSolidTorus (0.015, 0.025, 10, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslated (-.01, 0.522, 0.32);
		glRotated (90, 1, 0, 0);
		glutSolidTorus (0.01, 0.015, 10, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslated (-.01, 0.53, 0.32);
		glutSolidSphere (0.015, 10,20);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, cup);
		//glTranslated (0.25, 0.48, 0.32);
		glTranslated (-.01, 0.48, 0.32);
		glRotated (90, 1, 0, 0);
		glutSolidCone (0.05, 0.2, 20, 20);
		glPopMatrix();
		glPushMatrix();
		//glTranslated (0.25,0.29, 0.32);
		glTranslated (-.01,0.29, 0.32);
		glRotated (-90, 1, 0, 0);
		glutSolidCone (0.03, 0.1, 20, 20);

		glPopMatrix();
	}
}

void cup2_code()
{
	GLfloat vessel1[] = {4.f,4.f,4.f,1.0f};
	GLfloat vessel2[] = {1.5f, 0.4f, 0.5f, 0.850f};
	if(flag_drink==0) // display the juice only if it has not already been drunk
	{
		c1=1; 
		c=0;
		GLfloat cup[] = {0.1, 1.1, 01., 1.0f};
		GLfloat juice1[] = {2.f, 0.f, 0., 1.0f};
		GLfloat straw[]= {3.13,3.1, 3.,1.0f};
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, juice1);
		glTranslated(-.01, 0.46, 0.32);
		glRotated(90, 1, 0, 0);
		glutSolidCone(0.0425, 0.2, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslated (-.01,0.27, 0.32);
		glRotated (-90, 1, 0, 0);
		glutSolidCone (0.02, 0.1, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, juice1);
		glTranslated (-.01, 0.49, 0.36);
		glutSolidSphere(0.012, 20, 20);
		glPopMatrix();
	}

}
 void cup3_code()
{
	GLfloat vessel1[] = {4.f,4.f,4.f, 1.0f};
	GLfloat vessel2[] = {1.5f, 0.4f, 0.5f, 0.850f};
	if(flag_drink==0)
	{	c1=1;
		c=0;
		GLfloat cup[] = {0.0f, 1.0f, 1.0f, 1.0f};
		GLfloat juice2[] = {4.2f, 2.5f, 0.0f, 4.01};
		GLfloat cherry[] = {2.0f, 0.0f, 0.0f, 1.0f};
		GLfloat straw[] = {3.0f, 3.0f, 3.0f, 1.0f};
		glPushMatrix();
		glMaterialfv (GL_FRONT, GL_AMBIENT, juice2);
		glTranslated (-.01, 0.46, 0.32);
		glRotated (90, 1, 0, 0);
		glutSolidCone (0.0425, 0.2, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslated (-.01,0.27, 0.32);
		glRotated (-90, 1, 0, 0);
		glutSolidCone (0.02, 0.1, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, juice2);
		glTranslated(-.01, 0.49, 0.36);
		glutSolidSphere(0.012, 20, 20);
 		glPopMatrix();
	}
}
//MENUS DEFINITIONS
 void food(int option)

{
 	switch(option)
		{
			case 1: ctr++;
			choice_food= 1;
			donut(choice_drink);
			break;
 			case 2: ctr++;
			choice_food=2;
 			cake1(choice_drink);
			break;
			case 3: ctr++;
 			choice_food=3;
			cake2 (choice_drink);
			break;
	}
}
void drink(int option)
{
switch(option)
{
	case 1: ctr++;
	choice_drink= 1;
	cup1(choice_food);
	break;
	case 2: ctr++;
	choice_drink=2;
	cup2(choice_food);
	break;
	case 3: ctr++;
	choice_drink=3;
	cup3(choice_food);

	break;
	}
}
void choose(int option)
{
	GLfloat w[] = {5.1f,5.0f,5.4f,0.0f};
	switch(option)
	{
		 case 1:
		if (ctr==0)
		{
			 display_text(0);
			Sleep(1000);
		}
	else
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv (GL_FRONT, GL_AMBIENT, w);
	circle(-0.6,0.7,0.15,0,360);
	circle(-0.65,0.65,0.1,0,360);
	circle(-0.7,0.75,0.1,0,360);
	circle(-0.5,0.7,0.15,0,360);
	display_text(ctr);
	Sleep(2000);
	exit(0);
	}
break;
	}
}
//WINDOW MANIPULATION
void myReshape(int w, int h)

{
	glViewport( 0,0 ,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	glOrtho(-0.75,0.75,-40*(GLfloat)h/(GLfloat)w,0.75*(GLfloat)h/(GLfloat)w,-0.75,100);
else
	glOrtho(-0.75 * (GLfloat)w/(GLfloat)h,0.75 * (GLfloat)w/ (GLfloat)h,-0.40,0.75,-0.75,100);
	glMatrixMode(GL_MODELVIEW);
}
//OPENING SLIDE
void display(void)
{
	if(render== 1)
	{
 		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,200,0,200,-10,10);
		glMatrixMode(GL_MODELVIEW);
		//glCIearColor(O.3,0.0,0.0,1.0);
		glClearColor(0.80,0.90,0.0,0.0);
		glColor3f(0.0, 10,00);//green
		glClear(GL_COLOR_BUFFER_BIT);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);//combine n blend frag. col. o/p and col from col buf bit
		glEnable(GL_LINE_SMOOTH);//draw lines with correct filtering instead of aliased filtering 
		glLineWidth(3.0);
		glPushAttrib(GL_ALL_ATTRIB_BITS);//push and pop mask value into the server attribute stack
		glColor3f(.1,10.0,0);
		drawtext("Welcome to",300,630,0,0.15,0.20,0);//first 2 para for position

		glColor3f(0,0.5,0);
		drawtext("Welcome to",295,630,0,0.15,0.20,0);//first 2 para for position
		glPopAttrib();
		glColor3f(1,.7,0);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		drawtext("F  DiE's",505,345,0,0.15,0.20,0);//first 2 para for position
		glColor3f(1,0,0.0);
		drawtext("F  DiE's",500,345,0,0.15,0.20,0);//first 2 para for position
		glPopAttrib();
		 glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,0.70,4.70);
		drawtext("Hang UT! !",895,250,0,0.12,0.17,0);

		glColor3f(0,0,4.70);
		drawtext("Hang UT! !",890,250,0,0.12,0.17,0);
		glPushAttrib (GL_ALL_ATTRIB_BITS);
		glPopAttrib();
		output("PRESS ENTER to step inside", 104, 10,0);//moving char
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1.0, 1.0,1.0);//the 1/4 circles on top
		circle(7, 195,58, 180,390);
		circle(189,195,58,150,360);
		glPopAttrib();
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(2.5,2.7,0.4);
		circle(7,195,40,180,390);
		circle(189,195,40,150,360);
		glPopAttrib();
		glPopMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,0,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f( 105,40);
		glVertex2f(5, 115);
		glVertex2f(105,115);
		glEnd();
		glPopAttrib();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,0,1);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(95,40);
		glVertex2f(5, 115);
		glVertex2f(95, 115);
		glEnd();
		glPopAttrib();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,1,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(85,40);
		glVertex2f(5, 115);
		glVertex2f(85, 115);
		glEnd();
 		glPopAttrib();
 		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,1,1);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(75,40);
		glVertex2f(5, 115);
		glVertex2f(75, 115);
		glEnd();
		glPopAttrib();
 		glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(65,40);
		glVertex2f(5, 115);
		glVertex2f(65, 115);
		glEnd();
 		glPopAttrib();
 		glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(1,0,1);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(55,40);
		glVertex2f(5, 115);
		glVertex2f(55, 115);
		glEnd();
 		glPopAttrib();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(45,40);
		glVertex2f(5, 115);
		glVertex2f(45, 115);
		glEnd();
 		glPopAttrib();
		 glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(35,40);
		glVertex2f(5, 115);
		glVertex2f(35, 115);
		glEnd();
 		glPopAttrib();
 		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,0,1);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(25,40);
		glVertex2f(5, 115);
		glVertex2f(25, 115);
		glEnd();
 		glPopAttrib();
 		glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(0,0,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(15,40);
		glVertex2f(5, 115);
		glVertex2f(15, 115);
		glEnd();
 		glPopAttrib();
		 glPushAttrib(GL_ALL_ATTRIB_BITS);
 		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
		glVertex2f(5,40);
		glVertex2f(5,40);
		glVertex2f(5, 115);
		glVertex2f(5, 115);
		glEnd();
 		glPopAttrib();
  		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0,0,0);
		glTranslatef(176,92,0);
		glRotatef(180,0,0,1);
		glutSolidTeapot( 6);
		glPopMatrix();
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(10,0,0);
		glTranslatef(176,101,0);
		glRotatef(180,0,1,0);
		glutSolidTeapot( 7);
		glPopMatrix();
		glColor3f(1.6,1.5,1.5);
	glBegin(GL_LINES);
	glVertex2f(166,108);
	glVertex2f(170,113);
	glVertex2f(170,113);
	glVertex2f(166,118);
	glVertex2f(166,118);
	glVertex2f(170,123);
	glVertex2f(168,108);
	glVertex2f(172,113);
	glVertex2f(172,113);
	glVertex2f(168,118);
	glVertex2f(168,118);
	glVertex2f(172,123);
	glEnd();
	glColor3f(1.0,1,0.0);
	glPushMatrix();
	glTranslated ( 108,80,0);
	glRotatef( 180,0,1,0);
	glScalef(1.0,1.6,1.0);
	glutSolidTorus (2, 5, 10, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated (93 , 80,0);
 	glRotatef(180,0,1,0);
	glScalef(1.0,1.6,1.0);
	glutSolidTorus (2, 5, 10, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0,0,0.0);
	glTranslated (149,50,0);
	glRotatef(180,0, 1 ,0);
	glScalef(1.0,1.6,1.0);
	glutSolidTorus (2, 5, 10, 20);
	glPopMatrix();
	glColor3f(0,0,0.0);
	drawtext("O",885,480,0,0.10,0.15,0);
	drawtext("O", 1035,480,0,0.10,0.15,0);
	glColor3f(1.0,1.0,0.0);
	drawtext("O", 1195,240,0,0.12,0.17,0);
	glPopAttrib();
	glFlush();
}
else
{
 	 glEnable (GL_LIGHTING);
	 glEnable (GL_LIGHT0);
        glShadeModel (GL_SMOOTH);

	 glEnable (GL_DEPTH_TEST);
	 glEnable (GL_NORMALIZE);
       	 glClearColor (1,1, 0.0, 1.0);
       	table_walls_disp();
	glFlush();
	}
}
//KEYBOARD CONTROLS
 void myKey(unsigned char key, int X, int y)
{
  switch(key)
{
 case 'e':
 case 'E': if(choice_food!=0)//person has chosen some food
{
	flag_eat=1;//eaten
	 switch(choice_food)
{
 	case 1: ctr_f1=1;
	donut (choice_drink);
	flag_eat=0; // reset it so that they can choose another item
	break;
 	case 2: ctr_f2:1;
	cake1(choice_drink);
	flag_eat=0;
	break;
	case 3: ctr_f3=1;
	cake2 (choice_drink);
	flag_eat=0;
	break;
	}
}

choice_food=0;
break;
case 'd':
case 'D': if(choice_drink!=0)
{
 	flag_drink=1;//drunk
	switch(choice_drink)
	{
 		case 1: cup1(choice_food);
		flag_drink=0; // reset it so that they can choose another drink
		break;
		case 2: cup2(choice_food);
 		flag_drink=0;
		break;
		case 3: cup3(choice_food);
 		flag_drink=0;
		break;
	}
}
choice_drink=0;
break;
case 13: render=2;
glutPostRedisplay();
 break;
}
}
//MAIN
int main (int argc, char ** argv)
{
 	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE| GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (900, 700);
SIMULATION OF VIRTUAL FOODIE’S HANGOUT                                                                                                                                

 	glutInitWindowPosition (0, 0);
 	glutCreateWindow ("Take your pick!");
	glViewport (0, 0, 640, 480);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	foo = glutCreateMenu(food);
	glutAddMenuEntry("Donut", 1);
	glutAddMenuEntry( "Strawberry Cheesecake",2);
	glutAddMenuEntry("Cheesecake",3);
	drin=glutCreateMenu(drink);
	glutAddMenuEntry("Choco Float",1);
	glutAddMenuEntry("Cherry delight",2);
	glutAddMenuEntry("Mango Shake",3);
	glutCreateMenu(choose);
	glutAddMenuEntry("I'm done! ", 1);
	glutAddSubMenu("Food",foo);
	glutAddSubMenu("Drink",drin);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(myKey);
	glutMainLoop();
	return 0;
}
