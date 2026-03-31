#include <GL/glut.h>
#include <cstring>
#include <cmath>

// Basic circle (for sun, wheels, foliage, clouds)
void drawCircle(float cx, float cy, float r, int segments = 50)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(segments);
        float x = r * static_cast<float>(std::cos(theta));
        float y = r * static_cast<float>(std::sin(theta));
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Sun
void drawSun()
{
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(-0.8f, 0.8f, 0.12f, 40);
}

void drawBackground()
{
    // Sky
    glBegin(GL_QUADS);
    glColor3f(0.53f, 0.81f, 0.98f);        // light blue
    glVertex2f(-1.0f,  1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f( 1.0f,  0.1f);
    glVertex2f(-1.0f,  0.1f);
    glEnd();

    // Far ground (behind road)
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.8f, 0.4f);           // green
    glVertex2f(-1.0f,  0.1f);
    glVertex2f( 1.0f,  0.1f);
    glVertex2f( 1.0f, -0.1f);
    glVertex2f(-1.0f, -0.1f);
    glEnd();

        // Road
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);           // dark gray
    glVertex2f(-1.0f, -0.1f);
    glVertex2f( 1.0f, -0.1f);
    glVertex2f( 1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();

    // Road lines
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f( 1.0f, -0.3f);
    glEnd();


    glLineWidth(1.0f);
}

// Realistic house: body + roof + door + step + windows
// wallColor (rw,gw,bw), roofColor (rr,gr,br)
void drawHouse(float x, float y, float scale,
               float rw, float gw, float bw,
               float rr, float gr, float br)
{
    float w = 0.25f * scale;   // house width
    float h = 0.22f * scale;   // house height

    // Walls
    glColor3f(rw, gw, bw);
    glBegin(GL_QUADS);
    glVertex2f(x,       y);
    glVertex2f(x + w,   y);
    glVertex2f(x + w,   y + h);
    glVertex2f(x,       y + h);
    glEnd();

    // Roof (triangle)
    glColor3f(rr, gr, br);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.03f*scale,     y + h);
    glVertex2f(x + w + 0.03f*scale, y + h);
    glVertex2f(x + w * 0.5f,        y + h + 0.12f*scale);
    glEnd();

    // Door (centered)
    float doorW = w * 0.22f;
    float doorH = h * 0.60f;
    float doorX = x + w * 0.5f - doorW * 0.5f;
    float doorY = y;

    glColor3f(0.45f, 0.25f, 0.1f); // brown door
    glBegin(GL_QUADS);
    glVertex2f(doorX,         doorY);
    glVertex2f(doorX+doorW,   doorY);
    glVertex2f(doorX+doorW,   doorY+doorH);
    glVertex2f(doorX,         doorY+doorH);
    glEnd();

    // Door knob
    glColor3f(0.9f, 0.8f, 0.2f);
    drawCircle(doorX + doorW*0.8f, doorY + doorH*0.5f, 0.006f*scale, 15);

    // Step in front of door
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(doorX - 0.01f*scale,      doorY - 0.02f*scale);
    glVertex2f(doorX + doorW + 0.01f*scale, doorY - 0.02f*scale);
    glVertex2f(doorX + doorW + 0.01f*scale, doorY);
    glVertex2f(doorX - 0.01f*scale,      doorY);
    glEnd();

    // Windows: left and right
    float winW = w * 0.2f;
    float winH = h * 0.28f;
    float winY = y + h * 0.55f;

    // Left window frame
    glColor3f(1.0f, 1.0f, 1.0f); // white frame
    glBegin(GL_QUADS);
    glVertex2f(x + w*0.12f,           winY);
    glVertex2f(x + w*0.12f + winW,    winY);
    glVertex2f(x + w*0.12f + winW,    winY + winH);
    glVertex2f(x + w*0.12f,           winY + winH);
    glEnd();

    // Left window glass
    glColor3f(0.65f, 0.85f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + w*0.12f + 0.005f*scale,        winY + 0.005f*scale);
    glVertex2f(x + w*0.12f + winW - 0.005f*scale, winY + 0.005f*scale);
    glVertex2f(x + w*0.12f + winW - 0.005f*scale, winY + winH - 0.005f*scale);
    glVertex2f(x + w*0.12f + 0.005f*scale,        winY + winH - 0.005f*scale);
    glEnd();

    // Right window frame
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + w - w*0.12f - winW,        winY);
    glVertex2f(x + w - w*0.12f,               winY);
    glVertex2f(x + w - w*0.12f,               winY + winH);
    glVertex2f(x + w - w*0.12f - winW,        winY + winH);
    glEnd();

    // Right window glass
    glColor3f(0.65f, 0.85f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + w - w*0.12f - winW + 0.005f*scale,        winY + 0.005f*scale);
    glVertex2f(x + w - w*0.12f - 0.005f*scale,               winY + 0.005f*scale);
    glVertex2f(x + w - w*0.12f - 0.005f*scale,               winY + winH - 0.005f*scale);
    glVertex2f(x + w - w*0.12f - winW + 0.005f*scale,        winY + winH - 0.005f*scale);
    glEnd();
}

// Tree
void drawTree(float x, float y, float scale)
{
    // Trunk
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.01f*scale, y);
    glVertex2f(x + 0.01f*scale, y);
    glVertex2f(x + 0.01f*scale, y + 0.09f*scale);
    glVertex2f(x - 0.01f*scale, y + 0.09f*scale);
    glEnd();

    // Foliage
    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(x, y + 0.12f*scale, 0.06f*scale, 30);
}

// Cloud (simple circles)
void drawCloud(float x, float y, float scale)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x,y, 0.06f*scale, 20);
    drawCircle(x + 0.06f*scale, y, 0.05f*scale, 20);
    drawCircle(x - 0.06f*scale, y, 0.05f*scale, 20);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawSun();
    drawCloud(-0.5f,0.75f, 1.0f);
    drawCloud(1-0.6f, 0.65f, 0.8f);
    drawCloud(-0.7f, 0.70f, 0.9f);

    // Houses (placed behind trees, with different colors)
    // 1) Light orange walls, dark red roof
    drawHouse(-0.85f, 0.02f, 1.0f,
              1.0f, 0.78f, 0.56f,   // walls (light orange)
              0.6f, 0.1f, 0.1f);    // roof (dark red)

    // 2) Beige walls, brown roof
    drawHouse(-0.35f, 0.03f, 0.95f,
              0.96f, 0.90f, 0.75f,  // walls (beige)
              0.4f, 0.2f, 0.05f);   // roof (brown)

    // 3) Light yellow walls, dark brown roof
    drawHouse(0.10f, 0.02f, 1.05f,
              1.0f, 0.95f, 0.70f,   // walls (light yellow)
              0.45f, 0.15f, 0.05f); // roof (dark brown)

    // Trees (drawn after houses so they appear in front)
    drawTree(-0.9f, -0.05f, 1.3f);
    drawTree(-0.5f, -0.04f, 1.0f);
    drawTree( 0.0f, -0.03f, 1.2f);
    drawTree( 0.4f, -0.04f, 1.0f);
    drawTree( 0.8f, -0.05f, 1.3f);


    glutSwapBuffers();
}


void init()
{
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics Project");

    init();

    glutDisplayFunc(display);


    glutMainLoop();
    return 0;
}
