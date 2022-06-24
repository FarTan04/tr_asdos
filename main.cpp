#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<math.h>

#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 4
//  Josem Nainggolan (672018078)
//  Farrell Giovanno Tanujaya (672018115)
//  Gerald Edgard Laukon (672018121)
//  Yandri Yehezkiel Manuputty (672019112)
//  Abednego Collen Hariono (672020043)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camY = 100.0, camZ = 510.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion{
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init(){
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void tanah(){
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-900, 200, 200);
    glVertex3f(900, 200, 200);
    glVertex3f(900, 0, 200);
    glVertex3f(-900, 0, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-900, 200, 200);
    glVertex3f(-900, 200, -900);
    glVertex3f(-900, 0, -900);
    glVertex3f(-900, 0, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(900, 200, 200);
    glVertex3f(900, 200, -900);
    glVertex3f(900, 0, -900);
    glVertex3f(900, 0, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-900, 200, -900);
    glVertex3f(900, 200, -900);
    glVertex3f(900, 0, -900);
    glVertex3f(-900, 0, -900);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-900, 200, -900);
    glVertex3f(900, 200, -900);
    glVertex3f(900, 200, 200);
    glVertex3f(-900,200, 200);
    glEnd();
}

void lantai1(){
    //Tangga
    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-100, 200, 200);
    glVertex3f(-100, 0, 200);
    glVertex3f(-100, 0, 500);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(100, 200, 200);
    glVertex3f(100, 0, 200);
    glVertex3f(100, 0, 500);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 180, 200);
    glVertex3f(100, 180, 200);
    glVertex3f(100, 180, 230);
    glVertex3f(-100, 180, 230);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 160, 230);
    glVertex3f(100, 160, 230);
    glVertex3f(100, 160, 260);
    glVertex3f(-100, 160, 260);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 140, 260);
    glVertex3f(100, 140, 260);
    glVertex3f(100, 140, 290);
    glVertex3f(-100, 140, 290);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 120, 290);
    glVertex3f(100, 120, 290);
    glVertex3f(100, 120, 320);
    glVertex3f(-100, 120, 320);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 100, 320);
    glVertex3f(100, 100, 320);
    glVertex3f(100, 100, 350);
    glVertex3f(-100, 100, 350);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 80, 350);
    glVertex3f(100, 80, 350);
    glVertex3f(100, 80, 380);
    glVertex3f(-100, 80, 380);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 60, 380);
    glVertex3f(100, 60, 380);
    glVertex3f(100, 60, 410);
    glVertex3f(-100, 60, 410);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 40, 410);
    glVertex3f(100, 40, 410);
    glVertex3f(100, 40, 440);
    glVertex3f(-100, 40, 440);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 20, 440);
    glVertex3f(100, 20, 440);
    glVertex3f(100, 20, 470);
    glVertex3f(-100, 20, 470);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100, 5, 470);
    glVertex3f(100, 5, 470);
    glVertex3f(100, 5, 500);
    glVertex3f(-100, 5, 500);
    glEnd();

    //Bangunan 1
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-250, 400, -100);
    glVertex3f(250, 400,-100);
    glVertex3f(250, 200, -100);
    glVertex3f(-250, 200, -100);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-250, 400, -100);
    glVertex3f(-250, 400,-600);
    glVertex3f(-250, 200, -600);
    glVertex3f(-250, 200, -100);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(250, 400, -100);
    glVertex3f(250, 400,-600);
    glVertex3f(250, 200, -600);
    glVertex3f(250, 200, -100);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-250, 400, -600);
    glVertex3f(250, 400,-600);
    glVertex3f(250, 200, -600);
    glVertex3f(-250, 200, -600);
    glEnd();

    //atap/lantai2 dasar
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0.5, 0);
    glVertex3f(-350, 400, -700);
    glVertex3f(350, 400, -700);
    glVertex3f(350, 400, 0);
    glVertex3f(-350, 400, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-350, 400, -700);
    glVertex3f(350, 400, -700);
    glVertex3f(350, 400, 0);
    glVertex3f(-350, 400, 0);
    glEnd();

    //Pagar depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 400, 0);
    glVertex3f(-340, 400, 0);
    glVertex3f(-340, 455, 0);
    glVertex3f(-350, 455, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(350, 400, 0);
    glVertex3f(340, 400, 0);
    glVertex3f(340, 455, 0);
    glVertex3f(350, 455, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 440, 0);
    glVertex3f(350, 440, 0);
    glVertex3f(350, 450, 0);
    glVertex3f(-350, 450, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 400, -700);
    glVertex3f(-340, 400, -700);
    glVertex3f(-340, 455, -700);
    glVertex3f(-350, 455, -700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(350, 400, -700);
    glVertex3f(340, 400, -700);
    glVertex3f(340, 455, -700);
    glVertex3f(350, 455, -700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 440, -700);
    glVertex3f(350, 440, -700);
    glVertex3f(350, 450, -700);
    glVertex3f(-350, 450, -700);
    glEnd();

    //Pagar kanan kiri
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 400, 0);
    glVertex3f(-350, 400, -10);
    glVertex3f(-350, 455, -10);
    glVertex3f(-350, 455, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 400, -700);
    glVertex3f(-350, 400, -690);
    glVertex3f(-350, 455, -690);
    glVertex3f(-350, 455, -700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-350, 440, 0);
    glVertex3f(-350, 440, -700);
    glVertex3f(-350, 450, -700);
    glVertex3f(-350, 450, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(350, 400, 0);
    glVertex3f(350, 400, -10);
    glVertex3f(350, 455, -10);
    glVertex3f(350, 455, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(350, 400, -700);
    glVertex3f(350, 400, -690);
    glVertex3f(350, 455, -690);
    glVertex3f(350, 455, -700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(350, 440, 0);
    glVertex3f(350, 440, -700);
    glVertex3f(350, 450, -700);
    glVertex3f(350, 450, 0);
    glEnd();

    //Pintu depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 300, -99);
    glVertex3f(50, 300,-99);
    glVertex3f(50, 200, -99);
    glVertex3f(-50, 200, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 300, -601);
    glVertex3f(50, 300,-601);
    glVertex3f(50, 200, -601);
    glVertex3f(-50, 200, -601);
    glEnd();

    //Pintu kanan kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(252, 300, -300);
    glVertex3f(252, 300,-400);
    glVertex3f(252, 200, -400);
    glVertex3f(252, 200, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-252, 300, -300);
    glVertex3f(-252, 300,-400);
    glVertex3f(-252, 200, -400);
    glVertex3f(-252, 200, -300);
    glEnd();

    //Jendela depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(150, 400, -99);
    glVertex3f(230, 400,-99);
    glVertex3f(230, 200, -99);
    glVertex3f(150, 200, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(155, 340, -98);
    glVertex3f(225, 340,-98);
    glVertex3f(225, 260, -98);
    glVertex3f(155, 260, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 400, -99);
    glVertex3f(140, 400,-99);
    glVertex3f(140, 200, -99);
    glVertex3f(60, 200, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 340, -98);
    glVertex3f(135, 340,-98);
    glVertex3f(135, 260, -98);
    glVertex3f(65, 260, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-150, 400, -99);
    glVertex3f(-230, 400,-99);
    glVertex3f(-230, 200, -99);
    glVertex3f(-150, 200, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-155, 340, -98);
    glVertex3f(-225, 340,-98);
    glVertex3f(-225, 260, -98);
    glVertex3f(-155, 260, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 400, -99);
    glVertex3f(-140, 400,-99);
    glVertex3f(-140, 200, -99);
    glVertex3f(-60, 200, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 340, -98);
    glVertex3f(-135, 340,-98);
    glVertex3f(-135, 260, -98);
    glVertex3f(-65, 260, -98);
    glEnd();

    //Jendela belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(150, 400, -601);
    glVertex3f(230, 400,-601);
    glVertex3f(230, 200, -601);
    glVertex3f(150, 200, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(155, 340, -602);
    glVertex3f(225, 340,-602);
    glVertex3f(225, 260, -602);
    glVertex3f(155, 260, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 400, -601);
    glVertex3f(140, 400,-601);
    glVertex3f(140, 200, -601);
    glVertex3f(60, 200, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 340, -602);
    glVertex3f(135, 340,-602);
    glVertex3f(135, 260, -602);
    glVertex3f(65, 260, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-150, 400, -601);
    glVertex3f(-230, 400,-601);
    glVertex3f(-230, 200, -601);
    glVertex3f(-150, 200, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-155, 340, -602);
    glVertex3f(-225, 340,-602);
    glVertex3f(-225, 260, -602);
    glVertex3f(-155, 260, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 400, -601);
    glVertex3f(-140, 400,-601);
    glVertex3f(-140, 200, -601);
    glVertex3f(-60, 200, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 340, -602);
    glVertex3f(-135, 340,-602);
    glVertex3f(-135, 260, -602);
    glVertex3f(-65, 260, -602);
    glEnd();

    //Jendela kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(251, 400, -120);
    glVertex3f(251, 400,-200);
    glVertex3f(251, 200, -200);
    glVertex3f(251, 200, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(252, 340, -125);
    glVertex3f(252, 340,-195);
    glVertex3f(252, 260, -195);
    glVertex3f(252, 260, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(251, 400, -210);
    glVertex3f(251, 400,-290);
    glVertex3f(251, 200, -290);
    glVertex3f(251, 200, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(252, 340, -215);
    glVertex3f(252, 340,-285);
    glVertex3f(252, 260, -285);
    glVertex3f(252, 260, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(251, 400, -580);
    glVertex3f(251, 400,-500);
    glVertex3f(251, 200, -500);
    glVertex3f(251, 200, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(252, 340, -575);
    glVertex3f(252, 340,-505);
    glVertex3f(252, 260, -505);
    glVertex3f(252, 260, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(251, 400, -490);
    glVertex3f(251, 400,-410);
    glVertex3f(251, 200, -410);
    glVertex3f(251, 200, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(252, 340, -485);
    glVertex3f(252, 340,-415);
    glVertex3f(252, 260, -415);
    glVertex3f(252, 260, -485);
    glEnd();

    //Jendela kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-251, 400, -120);
    glVertex3f(-251, 400,-200);
    glVertex3f(-251, 200, -200);
    glVertex3f(-251, 200, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-252, 340, -125);
    glVertex3f(-252, 340,-195);
    glVertex3f(-252, 260, -195);
    glVertex3f(-252, 260, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-251, 400, -210);
    glVertex3f(-251, 400,-290);
    glVertex3f(-251, 200, -290);
    glVertex3f(-251, 200, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-252, 340, -215);
    glVertex3f(-252, 340,-285);
    glVertex3f(-252, 260, -285);
    glVertex3f(-252, 260, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-251, 400, -580);
    glVertex3f(-251, 400,-500);
    glVertex3f(-251, 200, -500);
    glVertex3f(-251, 200, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-252, 340, -575);
    glVertex3f(-252, 340,-505);
    glVertex3f(-252, 260, -505);
    glVertex3f(-252, 260, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-251, 400, -490);
    glVertex3f(-251, 400,-410);
    glVertex3f(-251, 200, -410);
    glVertex3f(-251, 200, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-252, 340, -485);
    glVertex3f(-252, 340,-415);
    glVertex3f(-252, 260, -415);
    glVertex3f(-252, 260, -485);
    glEnd();
}

void lantai2(){
    //Bangunan 2
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-180, 620, -100);
    glVertex3f(180, 620,-100);
    glVertex3f(180, 400, -100);
    glVertex3f(-180, 400, -100);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-180, 620, -100);
    glVertex3f(-180, 620,-600);
    glVertex3f(-180, 400, -600);
    glVertex3f(-180, 400, -100);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(180, 620, -100);
    glVertex3f(180, 620,-600);
    glVertex3f(180, 400, -600);
    glVertex3f(180, 400, -100);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-180, 620, -600);
    glVertex3f(180, 620,-600);
    glVertex3f(180, 400, -600);
    glVertex3f(-180, 400, -600);
    glEnd();

    //Pintu depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 500, -99);
    glVertex3f(50, 500,-99);
    glVertex3f(50, 400, -99);
    glVertex3f(-50, 400, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 500, -601);
    glVertex3f(50, 500,-601);
    glVertex3f(50, 400, -601);
    glVertex3f(-50, 400, -601);
    glEnd();

    //Pintu kanan kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(181, 500, -300);
    glVertex3f(181, 500,-400);
    glVertex3f(181, 400, -400);
    glVertex3f(181, 400, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-181, 500, -300);
    glVertex3f(-181, 500,-400);
    glVertex3f(-181, 400, -400);
    glVertex3f(-181, 400, -300);
    glEnd();

    //Jendela depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 600, -99);
    glVertex3f(140, 600,-99);
    glVertex3f(140, 400, -99);
    glVertex3f(60, 400, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 540, -98);
    glVertex3f(135, 540,-98);
    glVertex3f(135, 460, -98);
    glVertex3f(65, 460, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 600, -99);
    glVertex3f(-140, 600,-99);
    glVertex3f(-140, 400, -99);
    glVertex3f(-60, 400, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 540, -98);
    glVertex3f(-135, 540,-98);
    glVertex3f(-135, 460, -98);
    glVertex3f(-65, 460, -98);
    glEnd();

    //Jendela belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 600, -601);
    glVertex3f(140, 600,-601);
    glVertex3f(140, 400, -601);
    glVertex3f(60, 400, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 540, -602);
    glVertex3f(135, 540,-602);
    glVertex3f(135, 460, -602);
    glVertex3f(65, 460, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 600, -601);
    glVertex3f(-140, 600,-601);
    glVertex3f(-140, 400, -601);
    glVertex3f(-60, 400, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 540, -602);
    glVertex3f(-135, 540,-602);
    glVertex3f(-135, 460, -602);
    glVertex3f(-65, 460, -602);
    glEnd();

    //Jendela kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(181, 600, -120);
    glVertex3f(181, 600,-200);
    glVertex3f(181, 400, -200);
    glVertex3f(181, 400, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(182, 540, -125);
    glVertex3f(182, 540,-195);
    glVertex3f(182, 460, -195);
    glVertex3f(182, 460, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(181, 600, -210);
    glVertex3f(181, 600,-290);
    glVertex3f(181, 400, -290);
    glVertex3f(181, 400, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(182, 540, -215);
    glVertex3f(182, 540,-285);
    glVertex3f(182, 460, -285);
    glVertex3f(182, 460, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(181, 600, -580);
    glVertex3f(181, 600,-500);
    glVertex3f(181, 400, -500);
    glVertex3f(181, 400, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(182, 540, -575);
    glVertex3f(182, 540,-505);
    glVertex3f(182, 460, -505);
    glVertex3f(182, 460, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(181, 600, -490);
    glVertex3f(181, 600,-410);
    glVertex3f(181, 400, -410);
    glVertex3f(181, 400, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(182, 540, -485);
    glVertex3f(182, 540,-415);
    glVertex3f(182, 460, -415);
    glVertex3f(182, 460, -485);
    glEnd();

    //Jendela kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-181, 600, -120);
    glVertex3f(-181, 600,-200);
    glVertex3f(-181, 400, -200);
    glVertex3f(-181, 400, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-182, 540, -125);
    glVertex3f(-182, 540,-195);
    glVertex3f(-182, 460, -195);
    glVertex3f(-182, 460, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-181, 600, -210);
    glVertex3f(-181, 600,-290);
    glVertex3f(-181, 400, -290);
    glVertex3f(-181, 400, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-182, 540, -215);
    glVertex3f(-182, 540,-285);
    glVertex3f(-182, 460, -285);
    glVertex3f(-182, 460, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-181, 600, -580);
    glVertex3f(-181, 600,-500);
    glVertex3f(-181, 400, -500);
    glVertex3f(-181, 400, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-182, 540, -575);
    glVertex3f(-182, 540,-505);
    glVertex3f(-182, 460, -505);
    glVertex3f(-182, 460, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-181, 600, -490);
    glVertex3f(-181, 600,-410);
    glVertex3f(-181, 400, -410);
    glVertex3f(-181, 400, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-182, 540, -485);
    glVertex3f(-182, 540,-415);
    glVertex3f(-182, 460, -415);
    glVertex3f(-182, 460, -485);
    glEnd();

    //Atap depan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-180, 600, -100);
    glVertex3f(180, 600,-100);
    glVertex3f(300, 520, 0);
    glVertex3f(-300, 520, 0);
    glEnd();

    //Atap belakang
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(180, 600, -600);
    glVertex3f(-180, 600,-600);
    glVertex3f(-300, 520, -700);
    glVertex3f(300, 520, -700);
    glEnd();

    //Atap kanan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(180, 600, -100);
    glVertex3f(180, 600,-600);
    glVertex3f(300, 520, -700);
    glVertex3f(300, 520, 0);
    glEnd();

    //Atap kiri
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-180, 600, -100);
    glVertex3f(-180, 600,-600);
    glVertex3f(-300, 520, -700);
    glVertex3f(-300, 520, 0);
    glEnd();

    //Atap dalam
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0.5, 0);
    glVertex3f(-250,620,-50);
    glVertex3f(250,620,-50);
    glVertex3f(250,620,-650);
    glVertex3f(-250,620,-650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-250,620,-50);
    glVertex3f(250,620,-50);
    glVertex3f(250,620,-650);
    glVertex3f(-250,620,-650);
    glEnd();
}

void lantai3(){
    //Bangunan 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 820, -100);
    glVertex3f(150, 820,-100);
    glVertex3f(150, 620, -100);
    glVertex3f(-150, 620, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 820, -100);
    glVertex3f(-150, 820,-600);
    glVertex3f(-150, 620, -600);
    glVertex3f(-150, 620, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(150, 820, -100);
    glVertex3f(150, 820,-600);
    glVertex3f(150, 620, -600);
    glVertex3f(150, 620, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 820, -600);
    glVertex3f(150, 820,-600);
    glVertex3f(150, 620, -600);
    glVertex3f(-150, 620, -600);
    glEnd();

    //Pagar depan
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 620, -50);
    glVertex3f(-240, 620, -50);
    glVertex3f(-240, 675, -50);
    glVertex3f(-250, 675, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 620, -50);
    glVertex3f(240, 620, -50);
    glVertex3f(240, 675, -50);
    glVertex3f(250, 675, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 660, -50);
    glVertex3f(250, 660, -50);
    glVertex3f(250, 670, -50);
    glVertex3f(-250, 670, -50);
    glEnd();

    //pagar belakang
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 620, -650);
    glVertex3f(-240, 620, -650);
    glVertex3f(-240, 675, -650);
    glVertex3f(-250, 675, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 620, -650);
    glVertex3f(240, 620, -650);
    glVertex3f(240, 675, -650);
    glVertex3f(250, 675, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 660, -650);
    glVertex3f(250, 660, -650);
    glVertex3f(250, 670, -650);
    glVertex3f(-250, 670, -650);
    glEnd();

    //Pagar kiri
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 620, -50);
    glVertex3f(-250, 620, -60);
    glVertex3f(-250, 675, -60);
    glVertex3f(-250, 675, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 620, -650);
    glVertex3f(-250, 620, -640);
    glVertex3f(-250, 675, -640);
    glVertex3f(-250, 675, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 660, -50);
    glVertex3f(-250, 660, -650);
    glVertex3f(-250, 670, -650);
    glVertex3f(-250, 670, -50);
    glEnd();

    //pagar kanan
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 620, -50);
    glVertex3f(250, 620, -60);
    glVertex3f(250, 675, -60);
    glVertex3f(250, 675, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 620, -650);
    glVertex3f(250, 620, -640);
    glVertex3f(250, 675, -640);
    glVertex3f(250, 675, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 660, -50);
    glVertex3f(250, 660, -650);
    glVertex3f(250, 670, -650);
    glVertex3f(250, 670, -50);
    glEnd();

    //Pintu depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 720, -99);
    glVertex3f(50, 720,-99);
    glVertex3f(50, 620, -99);
    glVertex3f(-50, 620, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 720, -601);
    glVertex3f(50, 720,-601);
    glVertex3f(50, 620, -601);
    glVertex3f(-50, 620, -601);
    glEnd();

    //Pintu kanan kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(151, 720, -295);
    glVertex3f(151, 720,-395);
    glVertex3f(151, 620, -395);
    glVertex3f(151, 620, -295);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-151, 720, -295);
    glVertex3f(-151, 720,-395);
    glVertex3f(-151, 620, -395);
    glVertex3f(-151, 620, -295);
    glEnd();

    //Jendela depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 820, -99);
    glVertex3f(140, 820,-99);
    glVertex3f(140, 600, -99);
    glVertex3f(60, 600, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 740, -98);
    glVertex3f(135, 740,-98);
    glVertex3f(135, 660, -98);
    glVertex3f(65, 660, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 820, -99);
    glVertex3f(-140, 820,-99);
    glVertex3f(-140, 600, -99);
    glVertex3f(-60, 600, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 740, -98);
    glVertex3f(-135, 740,-98);
    glVertex3f(-135, 660, -98);
    glVertex3f(-65, 660, -98);
    glEnd();

    //jendela belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 820, -601);
    glVertex3f(140, 820,-601);
    glVertex3f(140, 600, -601);
    glVertex3f(60, 600, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 740, -602);
    glVertex3f(135, 740,-602);
    glVertex3f(135, 660, -602);
    glVertex3f(65, 660, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 820, -601);
    glVertex3f(-140, 820,-601);
    glVertex3f(-140, 600, -601);
    glVertex3f(-60, 600, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 740, -602);
    glVertex3f(-135, 740,-602);
    glVertex3f(-135, 660, -602);
    glVertex3f(-65, 660, -602);
    glEnd();

    //Jendela kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 820, -120);
    glVertex3f(151, 820,-200);
    glVertex3f(151, 600, -200);
    glVertex3f(151, 600, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 740, -125);
    glVertex3f(152, 740,-195);
    glVertex3f(152, 660, -195);
    glVertex3f(152, 660, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 820, -210);
    glVertex3f(151, 820,-290);
    glVertex3f(151, 600, -290);
    glVertex3f(151, 600, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 740, -215);
    glVertex3f(152, 740,-285);
    glVertex3f(152, 660, -285);
    glVertex3f(152, 660, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 820, -580);
    glVertex3f(151, 820,-500);
    glVertex3f(151, 600, -500);
    glVertex3f(151, 600, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 740, -575);
    glVertex3f(152, 740,-505);
    glVertex3f(152, 660, -505);
    glVertex3f(152, 660, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 820, -490);
    glVertex3f(151, 820,-410);
    glVertex3f(151, 600, -410);
    glVertex3f(151, 600, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 740, -485);
    glVertex3f(152, 740,-415);
    glVertex3f(152, 660, -415);
    glVertex3f(152, 660, -485);
    glEnd();

    //Jendela kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 820, -120);
    glVertex3f(-151, 820,-200);
    glVertex3f(-151, 600, -200);
    glVertex3f(-151, 600, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 740, -125);
    glVertex3f(-152, 740,-195);
    glVertex3f(-152, 660, -195);
    glVertex3f(-152, 660, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 820, -210);
    glVertex3f(-151, 820,-290);
    glVertex3f(-151, 600, -290);
    glVertex3f(-151, 600, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 740, -215);
    glVertex3f(-152, 740,-285);
    glVertex3f(-152, 660, -285);
    glVertex3f(-152, 660, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 820, -580);
    glVertex3f(-151, 820,-500);
    glVertex3f(-151, 600, -500);
    glVertex3f(-151, 600, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 740, -575);
    glVertex3f(-152, 740,-505);
    glVertex3f(-152, 660, -505);
    glVertex3f(-152, 660, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 820, -490);
    glVertex3f(-151, 820,-410);
    glVertex3f(-151, 600, -410);
    glVertex3f(-151, 600, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 740, -485);
    glVertex3f(-152, 740,-415);
    glVertex3f(-152, 660, -415);
    glVertex3f(-152, 660, -485);
    glEnd();

    //Atap depan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-150, 805, -100);
    glVertex3f(150, 805,-100);
    glVertex3f(280, 765, -20);
    glVertex3f(-280, 765, -20);
    glEnd();

    //atap belakang
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(150, 805, -600);
    glVertex3f(-150, 805,-600);
    glVertex3f(-280, 765, -680);
    glVertex3f(280, 765, -680);
    glEnd();

    //Atap kanan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(150, 805, -100);
    glVertex3f(150, 805,-600);
    glVertex3f(280, 765, -680);
    glVertex3f(280, 765, -20);
    glEnd();

    //atap kiri
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-150, 805, -100);
    glVertex3f(-150, 805,-600);
    glVertex3f(-280, 765, -680);
    glVertex3f(-280, 765, -20);
    glEnd();

    //Atap dalam
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0.5, 0);
    glVertex3f(-260,820,-40);
    glVertex3f(260,820,-40);
    glVertex3f(260,820,-660);
    glVertex3f(-260,820,-660);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-260,820,-40);
    glVertex3f(260,820,-40);
    glVertex3f(260,820,-660);
    glVertex3f(-260,820,-660);
    glEnd();

}

void lantai4(){
    //Bangunan 4
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 1020, -100);
    glVertex3f(150, 1020,-100);
    glVertex3f(150, 820, -100);
    glVertex3f(-150, 820, -100);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 1020, -100);
    glVertex3f(-150, 1020,-600);
    glVertex3f(-150, 820, -600);
    glVertex3f(-150, 820, -100);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(150, 1020, -100);
    glVertex3f(150, 1020,-600);
    glVertex3f(150, 820, -600);
    glVertex3f(150, 820, -100);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 0.5, 0);
    glVertex3f(-150, 1020, -600);
    glVertex3f(150, 1020,-600);
    glVertex3f(150, 820, -600);
    glVertex3f(-150, 820, -600);
    glEnd();

    //Pagar depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 820, -50);
    glVertex3f(-240, 820, -50);
    glVertex3f(-240, 875, -50);
    glVertex3f(-250, 875, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 820, -50);
    glVertex3f(240, 820, -50);
    glVertex3f(240, 875, -50);
    glVertex3f(250, 875, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 860, -50);
    glVertex3f(250, 860, -50);
    glVertex3f(250, 870, -50);
    glVertex3f(-250, 870, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 820, -650);
    glVertex3f(-240, 820, -650);
    glVertex3f(-240, 875, -650);
    glVertex3f(-250, 875, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 820, -650);
    glVertex3f(240, 820, -650);
    glVertex3f(240, 875, -650);
    glVertex3f(250, 875, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 860, -650);
    glVertex3f(250, 860, -650);
    glVertex3f(250, 870, -650);
    glVertex3f(-250, 870, -650);
    glEnd();

    //Pagar kiri kanan
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 820, -50);
    glVertex3f(-250, 820, -60);
    glVertex3f(-250, 875, -60);
    glVertex3f(-250, 875, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 820, -650);
    glVertex3f(-250, 820, -640);
    glVertex3f(-250, 875, -640);
    glVertex3f(-250, 875, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-250, 860, -50);
    glVertex3f(-250, 860, -650);
    glVertex3f(-250, 870, -650);
    glVertex3f(-250, 870, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 820, -50);
    glVertex3f(250, 820, -60);
    glVertex3f(250, 875, -60);
    glVertex3f(250, 875, -50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 820, -650);
    glVertex3f(250, 820, -640);
    glVertex3f(250, 875, -640);
    glVertex3f(250, 875, -650);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(250, 860, -50);
    glVertex3f(250, 860, -650);
    glVertex3f(250, 870, -650);
    glVertex3f(250, 870, -50);
    glEnd();

    //Pintu depan belakang
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 920, -99);
    glVertex3f(50, 920,-99);
    glVertex3f(50, 820, -99);
    glVertex3f(-50, 820, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-50, 920, -601);
    glVertex3f(50, 920,-601);
    glVertex3f(50, 820, -601);
    glVertex3f(-50, 820, -601);
    glEnd();

    //Pintu kanan kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(151, 920, -295);
    glVertex3f(151, 920,-395);
    glVertex3f(151, 820, -395);
    glVertex3f(151, 820, -295);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-151, 920, -295);
    glVertex3f(-151, 920,-395);
    glVertex3f(-151, 820, -395);
    glVertex3f(-151, 820, -295);
    glEnd();

    //Jendela depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 1000, -99);
    glVertex3f(140, 1000,-99);
    glVertex3f(140, 800, -99);
    glVertex3f(60, 800, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 940, -98);
    glVertex3f(135, 940,-98);
    glVertex3f(135, 860, -98);
    glVertex3f(65, 860, -98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 1000, -99);
    glVertex3f(-140, 1000,-99);
    glVertex3f(-140, 800, -99);
    glVertex3f(-60, 800, -99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 940, -98);
    glVertex3f(-135, 940,-98);
    glVertex3f(-135, 860, -98);
    glVertex3f(-65, 860, -98);
    glEnd();

    //jendela belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(60, 1000, -601);
    glVertex3f(140, 1000,-601);
    glVertex3f(140, 800, -601);
    glVertex3f(60, 800, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(65, 940, -602);
    glVertex3f(135, 940,-602);
    glVertex3f(135, 860, -602);
    glVertex3f(65, 860, -602);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-60, 1000, -601);
    glVertex3f(-140, 1000,-601);
    glVertex3f(-140, 800, -601);
    glVertex3f(-60, 800, -601);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-65, 940, -602);
    glVertex3f(-135, 940,-602);
    glVertex3f(-135, 860, -602);
    glVertex3f(-65, 860, -602);
    glEnd();

    //Jendela kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 1000, -120);
    glVertex3f(151, 1000,-200);
    glVertex3f(151, 800, -200);
    glVertex3f(151, 800, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 940, -125);
    glVertex3f(152, 940,-195);
    glVertex3f(152, 860, -195);
    glVertex3f(152, 860, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 1000, -210);
    glVertex3f(151, 1000,-290);
    glVertex3f(151, 800, -290);
    glVertex3f(151, 800, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 940, -215);
    glVertex3f(152, 940,-285);
    glVertex3f(152, 860, -285);
    glVertex3f(152, 860, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 1000, -580);
    glVertex3f(151, 1000,-500);
    glVertex3f(151, 800, -500);
    glVertex3f(151, 800, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 940, -575);
    glVertex3f(152, 940,-505);
    glVertex3f(152, 860, -505);
    glVertex3f(152, 860, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(151, 1000, -490);
    glVertex3f(151, 1000,-410);
    glVertex3f(151, 800, -410);
    glVertex3f(151, 800, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(152, 940, -485);
    glVertex3f(152, 940,-415);
    glVertex3f(152, 860, -415);
    glVertex3f(152, 860, -485);
    glEnd();

    //Jendela kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 1000, -120);
    glVertex3f(-151, 1000,-200);
    glVertex3f(-151, 800, -200);
    glVertex3f(-151, 800, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 940, -125);
    glVertex3f(-152, 940,-195);
    glVertex3f(-152, 860, -195);
    glVertex3f(-152, 860, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 1000, -210);
    glVertex3f(-151, 1000,-290);
    glVertex3f(-151, 800, -290);
    glVertex3f(-151, 800, -210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 940, -215);
    glVertex3f(-152, 940,-285);
    glVertex3f(-152, 860, -285);
    glVertex3f(-152, 860, -215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 1000, -580);
    glVertex3f(-151, 1000,-500);
    glVertex3f(-151, 800, -500);
    glVertex3f(-151, 800, -580);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 940, -575);
    glVertex3f(-152, 940,-505);
    glVertex3f(-152, 860, -505);
    glVertex3f(-152, 860, -575);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-151, 1000, -490);
    glVertex3f(-151, 1000,-410);
    glVertex3f(-151, 800, -410);
    glVertex3f(-151, 800, -490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-152, 940, -485);
    glVertex3f(-152, 940,-415);
    glVertex3f(-152, 860, -415);
    glVertex3f(-152, 860, -485);
    glEnd();

    //Atap depan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-50, 1080, -200);
    glVertex3f(50, 1080,-200);
    glVertex3f(300, 960, 0);
    glVertex3f(-300, 960, 0);
    glEnd();

    //atap belakang
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(50, 1080, -500);
    glVertex3f(-50, 1080,-500);
    glVertex3f(-300, 960, -700);
    glVertex3f(300, 960, -700);
    glEnd();

    //Atap kanan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(50, 1080, -200);
    glVertex3f(50, 1080,-500);
    glVertex3f(300, 960, -700);
    glVertex3f(300, 960, 0);
    glEnd();

    //atap kiri
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-50, 1080, -200);
    glVertex3f(-50, 1080,-500);
    glVertex3f(-300, 960, -700);
    glVertex3f(-300, 960, 0);
    glEnd();

    //Atap dalam
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1, 1);
    glVertex3f(-50, 1080, -200);
    glVertex3f(50, 1080, -200);
    glVertex3f(50, 1080, -500);
    glVertex3f(-50, 1080, -500);
    glEnd();

    //kotak emas
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-50, 1080, -200);
    glVertex3f(50, 1080, -200);
    glVertex3f(50, 1100, -200);
    glVertex3f(-50, 1100, -200);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-50, 1080, -500);
    glVertex3f(50, 1080, -500);
    glVertex3f(50, 1100, -500);
    glVertex3f(-50, 1100, -500);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(50, 1080, -200);
    glVertex3f(50, 1080, -500);
    glVertex3f(50, 1100, -500);
    glVertex3f(50, 1100, -200);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-50, 1080, -200);
    glVertex3f(-50, 1080, -500);
    glVertex3f(-50, 1100, -500);
    glVertex3f(-50, 1100, -200);
    glEnd();

    //dalam
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-50, 1100, -200);
    glVertex3f(-50, 1100, -500);
    glVertex3f(50, 1100, -500);
    glVertex3f(50, 1100, -200);
    glEnd();

    //tiang
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.41, 0.41, 0.41);
    glVertex3f(-10, 1100, -340);
    glVertex3f(10, 1100, -340);
    glVertex3f(10, 1400, -340);
    glVertex3f(-10, 1400, -340);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.41, 0.41, 0.41);
    glVertex3f(-10, 1100, -360);
    glVertex3f(10, 1100, -360);
    glVertex3f(10, 1400, -360);
    glVertex3f(-10, 1400, -360);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.41, 0.41, 0.41);
    glVertex3f(10, 1100, -340);
    glVertex3f(10, 1100, -360);
    glVertex3f(10, 1400, -360);
    glVertex3f(10, 1400, -340);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.41, 0.41, 0.41);
    glVertex3f(-10, 1100, -340);
    glVertex3f(-10, 1100, -360);
    glVertex3f(-10, 1400, -360);
    glVertex3f(-10, 1400, -340);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.41, 0.41, 0.41);
    glVertex3f(-20, 1400, -330);
    glVertex3f(20, 1400, -330);
    glVertex3f(20, 1400, -370);
    glVertex3f(-20, 1400, -370);
    glEnd();

    //segitiga
    //depan
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.843, 0);
    glVertex3f(-20, 1400, -330);
    glVertex3f(20, 1400, -330);
    glVertex3f(0, 1500, -350);
    glEnd();

    //kanan
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.843, 0);
    glVertex3f(20, 1400, -330);
    glVertex3f(20, 1400, -370);
    glVertex3f(0, 1500, -350);
    glEnd();

    //kiri
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.843, 0);
    glVertex3f(-20, 1400, -330);
    glVertex3f(-20, 1400, -370);
    glVertex3f(0, 1500, -350);
    glEnd();

    //belakang
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.843, 0);
    glVertex3f(-20, 1400, -370);
    glVertex3f(20, 1400, -370);
    glVertex3f(0, 1500, -350);
    glEnd();

    //kotak tiang bwh ke atas
    //1
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-50, 1150, -290);
    glVertex3f(50, 1150, -290);
    glVertex3f(50, 1150, -410);
    glVertex3f(-50, 1150, -410);
    glEnd();

     //2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-45, 1200, -295);
    glVertex3f(45, 1200, -295);
    glVertex3f(45, 1200, -405);
    glVertex3f(-45, 1200, -405);
    glEnd();

    //3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-40, 1250, -300);
    glVertex3f(40, 1250, -300);
    glVertex3f(40, 1250, -400);
    glVertex3f(-40, 1250, -400);
    glEnd();

    //4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-35, 1300, -305);
    glVertex3f(35, 1300, -305);
    glVertex3f(35, 1300, -395);
    glVertex3f(-35, 1300, -395);
    glEnd();

    //5
    glBegin(GL_POLYGON);
    glColor3f(1, 0.843, 0);
    glVertex3f(-30, 1350, -310);
    glVertex3f(30, 1350, -310);
    glVertex3f(30, 1350, -390);
    glVertex3f(-30, 1350, -390);
    glEnd();




}

void draw() {
    // Mulai tuliskan isi pikiranmu disini
    tanah();
    lantai1();
    lantai2();
    lantai3();
    lantai4();

    ground();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y){
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera(){
    if (motion.Forward){
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward){
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left){
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right){
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik){
        terbang -= 2.0;
    }
    if (motion.Turun){
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(0, -camY, 0);
    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 0.5;
        break;
    case '4':
        x_geser -= 0.5;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
        z_geser += 0.5;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 4");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;

}
