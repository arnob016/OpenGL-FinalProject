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

float carX = -150.0f;
float carY = 25.0f;

float car2X = 200.0f;
float car2Y = 10.0f;
float car2Speed = -0.5f;

float car3X = -100.0f;
float car3Y = 25.0f;
float car3Speed = 0.5f;

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
    carX += 1.0f;
    car2X += car2Speed;
    car3X += car3Speed;
    updateSun();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);

    if (carX > 350.0f)
    {
        carX = -150.0f;
    }

    if (car2X < -150.0f)
    {

        car2X = 350.0f;
        car2Speed = -0.5f;
    }
    else if (car2X > 350.0f)
    {
        car2X = -150.0f;
        car2Speed = 0.5f;
    }


    if (car3X > 350.0f)
    {
        car3X = 350.0f;
        car3Speed = -0.5f;
    }
    else if (car3X < -150.0f)
    {
        car3X = -150.0f;
        car3Speed = 0.5f;
    }
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

void mountain()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(180.0, 20.0);
    glVertex2f(280.0, 20.0);
    glVertex2f(240.0, 200.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(100.0, 20.0);
    glVertex2f(300.0, 20.0);
    glVertex2f(200.0, 250.0);
    glEnd();
}

void Hill()
{
    const int numVertices = 100;
    const float radius = 100.0;
    const float centerX = 100.0;
    const float centerY = 100.0;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.2, 0.5, 0.2);
    glVertex2f(centerX, centerY); // Center of the hill

    for (int i = 0; i <= numVertices; ++i) {
        float theta = 2.0 * M_PI * float(i) / numVertices;
        float x = centerX + radius * std::cos(theta);
        float y = centerY + 0.5 * radius * std::sin(theta); // Adjust the y-coordinate for a flatter hill
        glVertex2f(x, y);
    }

    glEnd();
}


void road()
{
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

void car(float xPos, float yPos, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(xPos, yPos, 0.0f);

    // Body
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex2f(85.0, 20.0);
    glVertex2f(95.0, 30.0);
    glVertex2f(105.0, 30.0);
    glVertex2f(110.0, 38.0);
    glVertex2f(145.0, 38.0);
    glVertex2f(150.0, 30.0);
    glVertex2f(155.0, 30.0);
    glVertex2f(165.0, 20.0);
    glEnd();

    // Roof
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(102.0, 30.0);
    glVertex2f(125.0, 30.0);
    glVertex2f(125.0, 37.0);
    glVertex2f(110.0, 37.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(148.0, 30.0);
    glVertex2f(126.0, 30.0);
    glVertex2f(126.0, 37.0);
    glVertex2f(144.0, 37.0);
    glEnd();

    // chakka
    CircleFunc(140.0f, 22.0f, 6.0f, 0, 0, 0);
    CircleFunc(110.0f, 22.0f, 6.0f, 0, 0, 0);
    CircleFunc(140.0f, 22.0f, 3.0f, 0.7, 0.7, 0.7);
    CircleFunc(110.0f, 22.0f, 3.0f, 0.7, 0.7, 0.7);

    glPopMatrix();
}

void streetLight(float x, float y)
{
    float streetLightColorR, streetLightColorG, streetLightColorB;

    if (sunX < 100.0f || sunX > 300.0f)
    {
        streetLightColorR = 1.0f;
        streetLightColorG = 1.0f;
        streetLightColorB = 0.0f;
    }
    else
    {
        streetLightColorR = 0.7f;
        streetLightColorG = 0.7f;
        streetLightColorB = 0.7f;
    }

    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(x, y + 35.0);
    glVertex2f(x, y + 85.0);
    glEnd();

    CircleFunc(x, y + 85.0, 10.0, streetLightColorR, streetLightColorG, streetLightColorB);
}

void roadLight()
{
    streetLight(-40.0, 35.0);
    streetLight(0.0, 35.0);
    streetLight(40.0, 35.0);
    streetLight(80.0, 35.0);
    streetLight(120.0, 35.0);
    streetLight(160.0, 35.0);
    streetLight(200.0, 35.0);
    streetLight(240.0, 35.0);
    streetLight(280.0, 35.0);
    streetLight(320.0, 35.0);
    streetLight(350.0, 35.0);
}

void roadstrip()
{
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(0, 0.0);
    glVertex2f(0.0, 15.0);
    glVertex2f(60.0, 15.0);
    glVertex2f(60.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(80, 0.0);
    glVertex2f(80.0, 15.0);
    glVertex2f(140.0, 15.0);
    glVertex2f(140.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(160, 0.0);
    glVertex2f(160.0, 15.0);
    glVertex2f(220.0, 15.0);
    glVertex2f(220.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(240, 0.0);
    glVertex2f(240.0, 15.0);
    glVertex2f(300.0, 15.0);
    glVertex2f(300.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(320, 0.0);
    glVertex2f(320.0, 15.0);
    glVertex2f(360.0, 15.0);
    glVertex2f(360.0, 0.0);
    glEnd();
}

void treeBush(float x, float y) {
    CircleFunc(x, y, 20.0f, 0.1, 0.7, 0.1);
    CircleFunc(x + 20.0f, y, 20.0f, 0.0, 0.8, 0.0);
    CircleFunc(x - 20.0f, y, 20.0f, 0.0, 0.8, 0.0);
    CircleFunc(x, y + 20.0f, 20.0f, 0.0, 0.8, 0.0);
    CircleFunc(x, y - 20.0f, 20.0f, 0.0, 0.8, 0.0);
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
        r = 1.0f;
        g = 1.0f;
        b = 0.8f;
    }
    else if (sunX < 300.0f)
    {
        r = 0.7f;
        g = 0.5f;
        b = 0.2f;
    }
    else
    {
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
    Hill();

    treeBush(20.0, 70.0);
    treeBush(70.0, 70.0);
    treeBush(110.0, 70.0);
    treeBush(190.0, 70.0);
    treeBush(250.0, 70.0);
    treeBush(300.0, 70.0);
    treeBush(320.0, 70.0);
    road();

    Sun();
    cloud();

    car(carX, carY, 0.5, 0.5, 0.0); // Yellow car
    car(car3X, car3Y, 0.8, 0.2, 0.2); // Red car
    car(car2X, car2Y, 0.2, 0.8, 0.2); // Green car

    roadLight();
    roadstrip();
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
