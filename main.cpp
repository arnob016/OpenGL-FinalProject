#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <cmath>

float cloudX = 0.0f;
float cloudY = 260.0f;
float cloudSpeedY = 0.001f;
float sunX = 150.0f;
float sunY = 300.0f;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 350.0, 0.0, 350.0);
}

void CircleFunc(float cX, float cY, float rd, float r, float g, float b)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(cX, cY);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0 * 3.1415926 * i / 100;
        float x = rd * cos(angle);
        float y = rd * sin(angle);
        glVertex2f(x + cX, y + cY);
    }
    glEnd();
}

void cloud()
{
    glPushMatrix();
    glTranslatef(cloudX, cloudY, 0.0f);
    CircleFunc(9.0f, 0.0f, 15.0f, 0.7, 0.7, 0.7);
    CircleFunc(-9.0f, 0.0f, 15.0f, 0.7, 0.7, 0.7);
    CircleFunc(-18.0f, 5.0f, 15.0f, 0.7, 0.7, 0.7);
    CircleFunc(18.0f, 5.0f, 15.0f, 0.7, 0.7, 0.7);
    CircleFunc(0.0f, 5.0f, 15.0f, 0.7, 0.7, 0.7);

    CircleFunc(112.0f, 0.0f, 15.0f, 0.6, 0.6, 0.6);
    CircleFunc(88.0f, 0.0f, 15.0f, 0.6, 0.6, 0.6);
    CircleFunc(88.0f, 5.0f, 15.0f, 0.6, 0.6, 0.6);
    CircleFunc(121.0f, 5.0f, 15.0f, 0.6, 0.6, 0.6);
    CircleFunc(103.0f, 5.0f, 15.0f, 0.6, 0.6, 0.6);
    glPopMatrix();

    cloudY += cloudSpeedY;

    if (cloudY > 280.0f || cloudY < 250.0f)
    {
        cloudSpeedY = -cloudSpeedY;
    }

    if (cloudX > 350.0f)
    {
        cloudX = -150.0f;
    }
}

void Sun()
{
    glPushMatrix();
    CircleFunc(sunX, sunY, 15.0f, 1, 0.5, 0);
    glPopMatrix();
}

void updateSun()
{
    if (sunX > 350.0f)
    {
        sunX = -50.0f;
    }
    if (sunX < -50.0f)
    {
        sunX = 350.0f;
    }
}

void update(int value)
{
    cloudX += 0.5f;
    updateSun();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        sunX -= 5.0f;
        sunY = sunY + 1.0f * (sunX - 150.0f) / 50.0f;
        break;
    case GLUT_KEY_RIGHT:
        sunX += 5.0f;
        sunY = sunY - 1.0f * (sunX - 150.0f) / 50.0f;
        break;
    }
    glutPostRedisplay();
}

void mountain(){
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0, 0);
    glVertex2f(100.0, 20.0);
    glVertex2f(300.0, 20.0);
    glVertex2f(200.0, 250.0);
    glEnd();

}

void road(){

    //lower pitch
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0.0, 0.0);
    glVertex2f(350.0, 0.0);
    glVertex2f(350.0, 50.0);
    glVertex2f(0.0, 50.0);
    glEnd();

    //middle z axis
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(0.0, 50.0);
    glVertex2f(350.0, 50.0);
    glVertex2f(350.0, 53.0);
    glVertex2f(0, 53.0);
    glEnd();

    //up walking raod
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(0.0, 53.0);
    glVertex2f(350.0, 53.0);
    glVertex2f(350.0, 70.0);
    glVertex2f(0.0, 70.0);
    glEnd();
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float r, g, b;

    if (sunX < 50.0f)
    {
        r = 0.0f;
        g = 0.0f;
        b = 0.1f;
    }
    else if (sunX < 100.0f)
    {
        r = 0.8f;
        g = 0.8f;
        b = 0.6f;
    }
    else if (sunX < 150.0f)
    {
        r = 0.53f;
        g = 0.81f;
        b = 0.98f;
    }
    else if (sunX < 220.0f)
    {
        // Afternoon - light yellow
        r = 1.0f;
        g = 1.0f;
        b = 0.8f;
    }
    else if (sunX < 300.0f)
    {
        // Sunset - orange/red
        r = 0.7f;
        g = 0.5f;
        b = 0.2f;
    }
    else
    {
        // Night - dark blue
        r = 0.0f;
        g = 0.0f;
        b = 0.1f;
    }

    glColor3f(r, g, b);

    glBegin(GL_QUADS);
    glVertex2f(0.0, 0.0);
    glVertex2f(350.0, 0.0);
    glVertex2f(350.0, 350.0);
    glVertex2f(0.0, 350.0);
    glEnd();

    mountain();
    // Draw road
    road();

    Sun();
    cloud();

    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lab Final Project");
    init();
    glutDisplayFunc(Draw);
    glutIdleFunc(Draw);

    glutSpecialFunc(specialKey);

    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
