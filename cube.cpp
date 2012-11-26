#include "shader.h"
#include "cube.h"

using namespace std;

static Cube cube;
static Cube cube1;
static Cube cube2;
static Cube cube3;
static Cube lzero;
static Cube lone;
static Cube ltwo;
Camera * camera;
char sphere_obj[] = "objfiles/sphere.obj";
char teddy_obj[] = "objfiles/teddy.obj";
char teapot_obj[] = "objfiles/teapot.obj";
char cow_obj[] = "objfiles/cow.obj";
char bunny_obj[] = "objfiles/bunny.obj";
char dragon_obj[] = "objfiles/dragon_smooth.obj";
int nVerts;
int nIndices;
float * vertices;
float * normals;
float * texcoords;
int * indices;
float xMin, xMax, yMin, yMax, zMin, zMax, axisMax;
bool isRotate, isScale, leftDown, rightDown = false;
bool isForward, isBackward, isLeft, isRight, isShift, isTranslate = false;
bool light0, light1, light2, light12_s = false;
bool isTexture = false;
float new_y, old_y;
Matrix4 scaleMatrix(10,0,0,0,
                    0,10,0,0,
                    0,0,10,0,
                    0,0,0,1);

Shader * shader;

int window::width  = 512;   // set window width in pixels here
int window::height = 512;   // set window height in pixels here

Vector3 p0;
Vector3 p1;

MatrixTransform * world = new MatrixTransform("world");
MatrixTransform * robot = new MatrixTransform("robot");
MatrixTransform * cameraMT = new MatrixTransform("cameraMT");
MatrixTransform * headMT = new MatrixTransform("heatMT");

MatrixTransform * leftUpLegMT = new MatrixTransform("leftUpLegMT");
MatrixTransform * rightUpLegMT = new MatrixTransform("rightUpLegMT");
MatrixTransform * leftUpArmMT = new MatrixTransform("leftUpArmMT");
MatrixTransform * rightUpArmMT = new MatrixTransform("rightUpArmMT");

MatrixTransform * leftLowLegMT = new MatrixTransform("leftLowLegMT");
MatrixTransform * rightLowLegMT = new MatrixTransform("rightLowLegMT");
MatrixTransform * leftLowArmMT = new MatrixTransform("leftLowArmMT");
MatrixTransform * rightLowArmMT = new MatrixTransform("rightLowArmMT");

MatrixTransform * leftElbowMT = new MatrixTransform("leftElbowMT");
MatrixTransform * rightElbowMT = new MatrixTransform("rightElbowMT");
MatrixTransform * leftKneeMT = new MatrixTransform("leftKneeMT");
MatrixTransform * rightKneeMT = new MatrixTransform("rightKneeMT");

Rectangle * torso = new Rectangle("torso", 2, 3, 2);
Torus * head = new Torus("head", 0.25, 0.75);

Cone * leftUpArm = new Cone("leftUpArm", 0.25, 2);
Cone * rightUpArm = new Cone("rightUpArm", 0.25, 2);
Cone * leftUpLeg = new Cone("leftUpLeg", 0.25, 2);
Cone * rightUpLeg = new Cone("rightUpLeg", 0.25, 2);
Sphere * leftElbow = new Sphere("leftElbow", 0.25);
Sphere * rightElbow = new Sphere("rightElbow", 0.25);

Cone * leftLowArm = new Cone("leftLowArm", 0.25, 2);
Cone * rightLowArm = new Cone("rightLowArm", 0.25, 2);
Cone * leftLowLeg = new Cone("leftLowLeg", 0.25, 2);
Cone * rightLowLeg = new Cone("rightLowLeg", 0.25, 2);
Sphere * leftKnee = new Sphere("leftKnee", 0.25);
Sphere * rightKnee = new Sphere("rightKnee", 0.25);

int frameCount = 0;
int currentTime, prevTime;
float fAngle, legAngle;
bool flipAngle = false;

double fov = 45.0, ratio = 0.0, zNear = 1.0, zFar = 1000.0;
float planes[6][4];
bool isCulling = false;

Matrix4 patch00 = Matrix4(-15.0, -10.0, -5.0, 0.0,
                          -7.5, -2.5, -12.5, -7.5,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch01 = Matrix4(-15.0, -10.0, -5.0, 0.0,
                          -2.5, 2.5, -7.5, -2.5,
                          7.5, 7.5, 7.5, 7.5,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch02 = Matrix4(-15.0, -10.0, -5.0, 0.0,
                          2.5, 7.5, -2.5, 2.5,
                          -7.5, -7.5, -7.5, -7.5,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch03 = Matrix4(-15.0, -10.0, -5.0, 0.0,
                          7.5, 12.5, 2.5, 7.5,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);

Matrix4 patch10 = Matrix4(0.0, 5.0, 10.0, 15.0,
                          -7.5, -2.5, -12.5, -7.5,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch11 = Matrix4(0.0, 5.0, 10.0, 15.0,
                          -2.5, 2.5, -7.5, -2.5,
                          7.5, 7.5, 7.5, 7.5,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch12 = Matrix4(0.0, 5.0, 10.0, 15.0,
                          2.5, 7.5, -2.5, 2.5,
                          -7.5, -7.5, -7.5, -7.5,
                          0.0, 0.0, 0.0, 1.0);
Matrix4 patch13 = Matrix4(0.0, 5.0, 10.0, 15.0,
                          7.5, 12.5, 2.5, 7.5,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);

Matrix4 CONSTANTB = Matrix4(-1.0, 3.0, -3.0, 1.0,
                            3.0, -6.0, 3.0, 0.0,
                            -3.0, 3.0, 0.0, 0.0,
                            1.0, 0.0, 0.0, 0.0);
Matrix4 CONSTANTB_PRIME = Matrix4(-3.0, 9.0, -9.0, 3.0,
                                  6.0, -12.0, 6.0, 0.0,
                                  -3.0, 3.0, 0.0, 0.0,
                                  0.0, 0.0, 0.0, 0.0);
Matrix4 G0x = Matrix4(patch00.get(0,0), patch00.get(0,1), patch00.get(0,2), patch00.get(0,3),
                      patch01.get(0,0), patch01.get(0,1), patch01.get(0,2), patch01.get(0,3),
                      patch02.get(0,0), patch02.get(0,1), patch02.get(0,2), patch02.get(0,3),
                      patch03.get(0,0), patch03.get(0,1), patch03.get(0,2), patch03.get(0,3));
Matrix4 G0y = Matrix4(patch00.get(1,0), patch00.get(1,1), patch00.get(1,2), patch00.get(1,3),
                      patch01.get(1,0), patch01.get(1,1), patch01.get(1,2), patch01.get(1,3),
                      patch02.get(1,0), patch02.get(1,1), patch02.get(1,2), patch02.get(1,3),
                      patch03.get(1,0), patch03.get(1,1), patch03.get(1,2), patch03.get(1,3));
Matrix4 G0z = Matrix4(patch00.get(2,0), patch00.get(2,1), patch00.get(2,2), patch00.get(2,3),
                      patch01.get(2,0), patch01.get(2,1), patch01.get(2,2), patch01.get(2,3),
                      patch02.get(2,0), patch02.get(2,1), patch02.get(2,2), patch02.get(2,3),
                      patch03.get(2,0), patch03.get(2,1), patch03.get(2,2), patch03.get(2,3));

Matrix4 G1x = Matrix4(patch10.get(0,0), patch10.get(0,1), patch10.get(0,2), patch10.get(0,3),
                      patch11.get(0,0), patch11.get(0,1), patch11.get(0,2), patch11.get(0,3),
                      patch12.get(0,0), patch12.get(0,1), patch12.get(0,2), patch12.get(0,3),
                      patch13.get(0,0), patch13.get(0,1), patch13.get(0,2), patch13.get(0,3));
Matrix4 G1y = Matrix4(patch10.get(1,0), patch10.get(1,1), patch10.get(1,2), patch10.get(1,3),
                      patch11.get(1,0), patch11.get(1,1), patch11.get(1,2), patch11.get(1,3),
                      patch12.get(1,0), patch12.get(1,1), patch12.get(1,2), patch12.get(1,3),
                      patch13.get(1,0), patch13.get(1,1), patch13.get(1,2), patch13.get(1,3));
Matrix4 G1z = Matrix4(patch10.get(2,0), patch10.get(2,1), patch10.get(2,2), patch10.get(2,3),
                      patch11.get(2,0), patch11.get(2,1), patch11.get(2,2), patch11.get(2,3),
                      patch12.get(2,0), patch12.get(2,1), patch12.get(2,2), patch12.get(2,3),
                      patch13.get(2,0), patch13.get(2,1), patch13.get(2,2), patch13.get(2,3));
float INTERVAL = 0.02;
float flagAngle = 0.0, flagInterval = 0.1;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void window::idleCallback(void)
{
  displayCallback();    // call display routine to redraw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(fov, ratio, zNear, zFar);
  //glTranslated(0.0,0.0,-100);
  //glFrustum(fleft, fright, fbottom, ftop, fzNear, fzFar); // set perspective projection viewing frustum
  glFrustum(-10, 10, -10, 10, 10, 1000); // set perspective projection viewing frustum
  glTranslatef(0, 0, -10);
  //glMatrixMode(GL_MODELVIEW);
}

void drawObj()
{
    glBegin(GL_TRIANGLES);
    srand(time(0));
    for (int i = 0; i < nIndices; i++)
    {
        double r = (rand() % 100) / 100.0;
        double g = (rand() % 100) / 100.0;
        double b = (rand() % 100) / 100.0;
        if (i % 3 == 0) glColor3d(r, g, b);
        if (normals != 0)
            glNormal3f(normals[indices[i] * 3], normals[indices[i] * 3 + 1],
                       normals[indices[i] * 3 + 2]);
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], 
                   vertices[indices[i] * 3 + 2]);
    }
    glEnd();
}

void findMinMax()
{
    if (nVerts != 0)
    {
        xMin = xMax = vertices[0];
        yMin = yMax = vertices[1];
        zMin = zMax = vertices[2];
        Vector3 n(xMin, yMin, zMin);
        for (int i = 3; i < nVerts * 3; i += 3)
        {
            float x = vertices[i];
            float y = vertices[i+1];
            float z = vertices[i+2];
            if (x < xMin) xMin = x;
            else if (x > xMax) xMax = x;
            if (y < yMin) yMin = y;
            else if (y > yMax) yMax = y;
            if (z < zMin) zMin = z;
            else if (z > zMax) zMax = z;
        }
        axisMax = max(max(max(max(max(fabs(xMin), fabs(xMax)), 
                  fabs(yMin)), fabs(yMax)), fabs(zMin)), fabs(zMax));
    }
}

void navigateCamera()
{
    Vector3 eye = camera->getEye();
    Vector3 up = camera->getUp();
    Vector3 lookat = camera->getLookat();
    Vector3 forward = lookat.subtract(eye);
    Vector3 right = forward.cross(up);
    forward.normalize();
    right.normalize();
    if (isShift) 
    {
        forward.scale(.01);
        right.scale(.01);
    }
    else 
    {
        forward.scale(.003);
        right.scale(.003);
    }

    Matrix4 forwardM(1,0,0,forward.get(0),
                     0,1,0,forward.get(1),
                     0,0,1,forward.get(2),
                     0,0,0,1);
    Matrix4 backwardM(1,0,0,-forward.get(0),
                     0,1,0,-forward.get(1),
                     0,0,1,-forward.get(2),
                     0,0,0,1);
    Matrix4 rightM(1,0,0,right.get(0),
                     0,1,0,right.get(1),
                     0,0,1,right.get(2),
                     0,0,0,1);
    Matrix4 leftM(1,0,0,-right.get(0),
                     0,1,0,-right.get(1),
                     0,0,1,-right.get(2),
                     0,0,0,1);
    if (isForward)
        camera->getCameraMatrix().set(camera->getCameraMatrix().multiply(forwardM));
    else if (isBackward) 
        camera->getCameraMatrix().set(camera->getCameraMatrix().multiply(backwardM));
    if (isRight) 
        camera->getCameraMatrix().set(camera->getCameraMatrix().multiply(rightM));
    else if (isLeft)
        camera->getCameraMatrix().set(camera->getCameraMatrix().multiply(leftM));
}

void drawCube(float size)
{
    // Draw sides of cube in object coordinate system:
    glBegin(GL_QUADS);

    float coord = size / 2;

    glColor3f(0.0, 1.0, 0.0);

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-coord,  coord,  coord);
    glVertex3f( coord,  coord,  coord);
    glVertex3f( coord, -coord,  coord);
    glVertex3f(-coord, -coord,  coord);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-coord,  coord,  coord);
    glVertex3f(-coord,  coord, -coord);
    glVertex3f(-coord, -coord, -coord);
    glVertex3f(-coord, -coord,  coord);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( coord,  coord,  coord);
    glVertex3f( coord,  coord, -coord);
    glVertex3f( coord, -coord, -coord);
    glVertex3f( coord, -coord,  coord);
  
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-coord,  coord, -coord);
    glVertex3f( coord,  coord, -coord);
    glVertex3f( coord, -coord, -coord);
    glVertex3f(-coord, -coord, -coord);
  
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-coord,  coord,  coord);
    glVertex3f( coord,  coord,  coord);
    glVertex3f( coord,  coord, -coord);
    glVertex3f(-coord,  coord, -coord);
  
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-coord, -coord, -coord);
    glVertex3f( coord, -coord, -coord);
    glVertex3f( coord, -coord,  coord);
    glVertex3f(-coord, -coord,  coord);
    glEnd();
}

void drawTransCube(float size)
{
    // Draw sides of cube in object coordinate system:
    glBegin(GL_QUADS);

    float coord = size / 2;
    // x = sqrt (diam ^ 2 / 3) 
    
    //glColor4f(0.0, 0.0, 1.0, 0.5);
    
    Vector4 midpoints[6];
    Vector4 a(0,0,coord, 1); // front
    Vector4 b(-coord, 0, 0, 1); // left
    Vector4 c(coord, 0, 0, 1); // right
    Vector4 d(0,0,-coord, 1); // back
    Vector4 e(0, coord, 0, 1); // top
    Vector4 f(0, -coord, 0, 1); // bottom

    midpoints[0] = a;
    midpoints[1] = b;
    midpoints[2] = c;
    midpoints[3] = d;
    midpoints[4] = e;
    midpoints[5] = f;
    
    Vector4 realmidpoints[6];
    Vector4 sortedmidpoints[6];

    for (int i = 0; i < 6; ++i)
    {
        sortedmidpoints[i] = realmidpoints[i] = 
                cube2.getMatrix().multiply(cube1.getMatrix()).multiply(midpoints[i]);
    }
    
    // bubble sort
    bool swap = true;
    while (swap)
    {
        swap = false;
        for (int i = 0; i < 5; ++i)
        {
            if(sortedmidpoints[i].get(2) > sortedmidpoints[i+1].get(2))
            {
                Vector4 temp = sortedmidpoints[i];
                sortedmidpoints[i] = sortedmidpoints[i+1];
                sortedmidpoints[i+1] = temp;
                swap = true;
            }
        }
    }

    for (int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            if (sortedmidpoints[i].equals(realmidpoints[j]))
            {
                switch (j)
                {
                    case 0:
                        glNormal3f(0.0, 0.0, 1.0);   
                        glVertex3f(-coord,  coord,  coord);
                        glVertex3f( coord,  coord,  coord);
                        glVertex3f( coord, -coord,  coord);
                        glVertex3f(-coord, -coord,  coord);
                        break;
                    case 1:
                        glNormal3f(-1.0, 0.0, 0.0);
                        glVertex3f(-coord,  coord,  coord);
                        glVertex3f(-coord,  coord, -coord);
                        glVertex3f(-coord, -coord, -coord);
                        glVertex3f(-coord, -coord,  coord);
                        break;
                    case 2:
                        glNormal3f(1.0, 0.0, 0.0);
                        glVertex3f( coord,  coord,  coord);
                        glVertex3f( coord,  coord, -coord);
                        glVertex3f( coord, -coord, -coord);
                        glVertex3f( coord, -coord,  coord);
                        break;
                    case 3:
                        glNormal3f(0.0, 0.0, -1.0);
                        glVertex3f(-coord,  coord, -coord);
                        glVertex3f( coord,  coord, -coord);
                        glVertex3f( coord, -coord, -coord);
                        glVertex3f(-coord, -coord, -coord);
                        break;
                    case 4:
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(-coord,  coord,  coord);
                        glVertex3f( coord,  coord,  coord);
                        glVertex3f( coord,  coord, -coord);
                        glVertex3f(-coord,  coord, -coord);
                        break;
                    case 5:
                        glNormal3f(0.0, -1.0, 0.0);
                        glVertex3f(-coord, -coord, -coord);
                        glVertex3f( coord, -coord, -coord);
                        glVertex3f( coord, -coord,  coord);
                        glVertex3f(-coord, -coord,  coord);
                        break;
                }
            }
        }
    }    
    
    glEnd();
}

void ExtractFrustum()
{
   float proj[16];
   float modl[16];
   float clip[16];
   float t;

 /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

 /* Get the current MODELVIEW matrix from OpenGL */
   //glGetFloatv( GL_MODELVIEW_MATRIX, modl );
    Matrix4 m = Matrix4();
    for (int i = 0; i < 16; ++i)
        modl[i] = *(m.getPointer() + i);

 /* Combine the two matrices (multiply projection by modelview)    */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] +    modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] +    modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] +    modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] +    modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4]    + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] +    modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] +    modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] +    modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4]    + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] +    modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] +    modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] +    modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4]    + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] +    modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] +    modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] +    modl[15] * proj[15];

 /* Extract the numbers for the RIGHT plane */
   planes[0][0] = clip[ 3] - clip[ 0];
   planes[0][1] = clip[ 7] - clip[ 4];
   planes[0][2] = clip[11] - clip[ 8];
   planes[0][3] = clip[15] - clip[12];

 /* Normalize the result */
   t = sqrt( planes[0][0] * planes[0][0] + planes[0][1] * planes[0][1] + planes[0][2]    * planes[0][2] );
   planes[0][0] /= t;
   planes[0][1] /= t;
   planes[0][2] /= t;
   planes[0][3] /= t;

 /* Extract the numbers for the LEFT plane */
   planes[1][0] = clip[ 3] + clip[ 0];
   planes[1][1] = clip[ 7] + clip[ 4];
   planes[1][2] = clip[11] + clip[ 8];
   planes[1][3] = clip[15] + clip[12];

 /* Normalize the result */
   t = sqrt( planes[1][0] * planes[1][0] + planes[1][1] * planes[1][1] + planes[1][2]    * planes[1][2] );
   planes[1][0] /= t;
   planes[1][1] /= t;
   planes[1][2] /= t;
   planes[1][3] /= t;

 /* Extract the BOTTOM plane */
   planes[2][0] = clip[ 3] + clip[ 1];
   planes[2][1] = clip[ 7] + clip[ 5];
   planes[2][2] = clip[11] + clip[ 9];
   planes[2][3] = clip[15] + clip[13];

 /* Normalize the result */
   t = sqrt( planes[2][0] * planes[2][0] + planes[2][1] * planes[2][1] + planes[2][2]    * planes[2][2] );
   planes[2][0] /= t;
   planes[2][1] /= t;
   planes[2][2] /= t;
   planes[2][3] /= t;

 /* Extract the TOP plane */
   planes[3][0] = clip[ 3] - clip[ 1];
   planes[3][1] = clip[ 7] - clip[ 5];
   planes[3][2] = clip[11] - clip[ 9];
   planes[3][3] = clip[15] - clip[13];

 /* Normalize the result */
   t = sqrt( planes[3][0] * planes[3][0] + planes[3][1] * planes[3][1] + planes[3][2]    * planes[3][2] );
   planes[3][0] /= t;
   planes[3][1] /= t;
   planes[3][2] /= t;
   planes[3][3] /= t;

 /* Extract the FAR plane */
   planes[4][0] = clip[ 3] - clip[ 2];
   planes[4][1] = clip[ 7] - clip[ 6];
   planes[4][2] = clip[11] - clip[10];
   planes[4][3] = clip[15] - clip[14];

 /* Normalize the result */
   t = sqrt( planes[4][0] * planes[4][0] + planes[4][1] * planes[4][1] + planes[4][2]    * planes[4][2] );
   planes[4][0] /= t;
   planes[4][1] /= t;
   planes[4][2] /= t;
   planes[4][3] /= t;

 /* Extract the NEAR plane */
   planes[5][0] = clip[ 3] + clip[ 2];
   planes[5][1] = clip[ 7] + clip[ 6];
   planes[5][2] = clip[11] + clip[10];
   planes[5][3] = clip[15] + clip[14];

 /* Normalize the result */
   t = sqrt( planes[5][0] * planes[5][0] + planes[5][1] * planes[5][1] + planes[5][2]    * planes[5][2] );
   planes[5][0] /= t;
   planes[5][1] /= t;
   planes[5][2] /= t;
   planes[5][3] /= t;
}

void drawRunningRobot()
{
    ++frameCount;

    currentTime = glutGet(GLUT_ELAPSED_TIME);

    int timeInterval = currentTime - prevTime;
    if (timeInterval > 1000)
    {
        cout << frameCount / (timeInterval / 1000.0f) << endl;
        prevTime = currentTime;
        frameCount = 0;
        flipAngle = !flipAngle;
    }  
    if (flipAngle)
    {
        legAngle = -0.0015;
        fAngle = -0.0008;
    }
    else
    {
        fAngle = 0.0008;
        legAngle = 0.0015;
    }
    
    //cameraMT->curMatrix.print();

    headMT->curMatrix.rotateX(fAngle/2);
    robot->curMatrix.rotateY(legAngle/3);

    leftUpArmMT->curMatrix.translate(-0.5,0.5,0.0);
    leftUpArmMT->curMatrix.rotateY(fAngle);
    leftUpArmMT->curMatrix.translate(0.5,-0.5, 0.0);

    leftElbowMT->curMatrix.rotateY(-fAngle);

    rightUpArmMT->curMatrix.translate(0.5,0.5,0.0);
    rightUpArmMT->curMatrix.rotateY(fAngle);
    rightUpArmMT->curMatrix.translate(-0.5,-0.5, 0.0);

    rightElbowMT->curMatrix.rotateY(-fAngle);

    leftUpLegMT->curMatrix.rotateX(legAngle/2);

    leftKneeMT->curMatrix.rotateX(-legAngle);

    rightUpLegMT->curMatrix.rotateX(-legAngle/2);

    rightKneeMT->curMatrix.rotateX(legAngle);

    cube.getMatrix().set(cube.getMatrix().multiply(cube2.getMatrix()));
    cube.getMatrix().set(cube.getMatrix().multiply(cube1.getMatrix()));
    //cube.getMatrix().invert();

    cameraMT->draw(cube.getMatrix());
}

Vector3 getBezierPoint(float u, float v, Matrix4 Gx, Matrix4 Gy, Matrix4 Gz)
{
    Matrix4 Cx = CONSTANTB.multiply(Gx).multiply(CONSTANTB);
    Matrix4 Cy = CONSTANTB.multiply(Gy).multiply(CONSTANTB);
    Matrix4 Cz = CONSTANTB.multiply(Gz).multiply(CONSTANTB);
    Vector4 U = Vector4(u * u * u, u * u, u, 1.0);
    Vector4 V = Vector4(v * v * v, v * v, v, 1.0);
    return Vector3(Cx.multiply(V).multiply(U),
                   Cy.multiply(V).multiply(U),
                   Cz.multiply(V).multiply(U));
}

Vector3 getNormal(float u, float v, Matrix4 Gx, Matrix4 Gy, Matrix4 Gz)
{
    Matrix4 Cx = CONSTANTB.multiply(Gx).multiply(CONSTANTB);
    Matrix4 Cy = CONSTANTB.multiply(Gy).multiply(CONSTANTB);
    Matrix4 Cz = CONSTANTB.multiply(Gz).multiply(CONSTANTB);
    Vector4 U, V;
    U = Vector4( 3 * u * u, 2 * u, 1.0, 0.0);
    V = Vector4(v * v * v, v * v, v, 1.0);
    Vector3 U_ = Vector3(Cx.multiply(V).multiply(U),
                         Cy.multiply(V).multiply(U),
                         Cz.multiply(V).multiply(U));
    U = Vector4(u * u * u, u * u, u, 1.0);
    V = Vector4(3 * v * v, 2 * v, 1.0, 0.0);
    Vector3 V_ = Vector3(Cx.multiply(V).multiply(U),
                         Cy.multiply(V).multiply(U),
                         Cz.multiply(V).multiply(U));
    return V_.cross(U_);
}

// load image file into texture object
void loadTexture()
{
    GLuint texture[1];     // storage for one texture
    int twidth, theight;   // texture width/height [pixels]
    unsigned char* tdata;  // texture pixel data

    // Load image file
    tdata = Util::loadPPM("ppm_files/Ucsd-logo.ppm", twidth, theight);
    if (tdata==NULL) return;

    // Create ID for texture
    glGenTextures(1, &texture[0]);   

    // Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

    // Set bi-linear filtering for both minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Select GL_MODULATE to mix texture with color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Use bilinear filtering for higher visual quality:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the wrap mode (but it doesn't make a difference in this project):
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void animateFlag()
{
    srand(time(0));
    flagAngle += flagInterval;
    float angletoadd = sin(flagAngle);
    if (angletoadd >= 0) angletoadd += flagInterval;
    else angletoadd -= flagInterval;
    float zRand = (rand() % 200) / 200.0;
    float yRand = (rand() % 200) / 200.0;

    // y axis
    G0y.m[0][1] = patch00.get(1,1) - angletoadd * 2;
    G0y.m[0][2] = patch00.get(1,2) + angletoadd * 2;
    G1y.m[0][1] = patch10.get(1,1) - angletoadd * 2;
    G1y.m[0][2] = patch10.get(1,2) + angletoadd * 2;

    G0y.m[1][1] = patch01.get(1,1) - angletoadd * 2;
    G0y.m[1][2] = patch01.get(1,2) + angletoadd * 2;
    G1y.m[1][1] = patch11.get(1,1) - angletoadd * 2;
    G1y.m[1][2] = patch11.get(1,2) + angletoadd * 2;

    G0y.m[2][1] = patch02.get(1,1) - angletoadd * 2;
    G0y.m[2][2] = patch02.get(1,2) + angletoadd * 2;
    G1y.m[2][1] = patch12.get(1,1) - angletoadd * 2;
    G1y.m[2][2] = patch12.get(1,2) + angletoadd * 2;

    G0y.m[3][1] = patch03.get(1,1) - angletoadd * 2;
    G0y.m[3][2] = patch03.get(1,2) + angletoadd * 2;
    G1y.m[3][1] = patch13.get(1,1) - angletoadd * 2;
    G1y.m[3][2] = patch13.get(1,2) + angletoadd * 2;

    // z axis
    G0z.m[0][1] = patch00.get(2,1) - angletoadd * 2 ;
    G0z.m[0][2] = patch00.get(2,2) + angletoadd * 2;
    //G0z.m[0][3] = patch00.get(2,3) + angletoadd;
    //G1z.m[0][0] = patch10.get(2,0) + angletoadd;
    G1z.m[0][1] = patch10.get(2,1) - angletoadd * 2;
    G1z.m[0][2] = patch10.get(2,2) + angletoadd * 2;
    G1z.m[0][3] = patch10.get(2,3) - angletoadd * 2;

    G0z.m[1][1] = patch01.get(2,1) - angletoadd * 2;
    G0z.m[1][2] = patch01.get(2,2) + angletoadd * 2;
    //G0z.m[1][3] = patch01.get(2,3) + angletoadd;
    //G1z.m[1][0] = patch11.get(2,0) + angletoadd;
    G1z.m[1][1] = patch11.get(2,1) - angletoadd * 2;
    G1z.m[1][2] = patch11.get(2,2) + angletoadd * 2;
    G1z.m[1][3] = patch11.get(2,3) - angletoadd * 2;

    G0z.m[2][1] = patch02.get(2,1) - angletoadd * 2;
    G0z.m[2][2] = patch02.get(2,2) + angletoadd * 2;
    //G0z.m[2][3] = patch02.get(2,3) + angletoadd;
    //G1z.m[2][0] = patch12.get(2,0) + angletoadd;
    G1z.m[2][1] = patch12.get(2,1) - angletoadd * 2;
    G1z.m[2][2] = patch12.get(2,2) + angletoadd * 2;
    G1z.m[2][3] = patch12.get(2,3) - angletoadd * 2;

    G0z.m[3][1] = patch03.get(2,1) - angletoadd * 2;
    G0z.m[3][2] = patch03.get(2,2) + angletoadd * 2;
    //G0z.m[3][3] = patch03.get(2,3) + angletoadd;
    //G1z.m[3][0] = patch13.get(2,0) + angletoadd;
    G1z.m[3][1] = patch13.get(2,1) - angletoadd * 2;
    G1z.m[3][2] = patch13.get(2,2) + angletoadd * 2;
    G1z.m[3][3] = patch13.get(2,3) - angletoadd * 2;

}

void drawFlag()
{
    animateFlag(); // ec
    glColor3f(1.0,1.0,1.0);
    for (float u = 0.0, u_ = INTERVAL; u_ < 1.001; u = u_, u_ += INTERVAL)
    {
        // left side
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0.0; v < 1.001; v += INTERVAL)
        {
            Vector3 uPoint = getBezierPoint(u, v, G0x, G0y, G0z);
            Vector3 u_Point = getBezierPoint(u_, v, G0x, G0y, G0z);
            Vector3 uNormal = getNormal(u, v, G0x, G0y, G0z);
            Vector3 u_Normal = getNormal(u_, v, G0x, G0y, G0z);
            
            glNormal3f(uNormal[0], uNormal[1], uNormal[2]);
            glTexCoord2f(v / 2, 1 - u);
            glVertex3f(uPoint[0], uPoint[1], uPoint[2]);
            
            glNormal3f(u_Normal[0], u_Normal[1], u_Normal[2]);
            glTexCoord2f(v / 2, 1 - u_);
            glVertex3f(u_Point[0], u_Point[1], u_Point[2]);
        }
        glEnd();
        // right side
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0.0; v < 1.001; v += INTERVAL)
        {
            Vector3 uPoint = getBezierPoint(u, v, G1x, G1y, G1z);
            Vector3 u_Point = getBezierPoint(u_, v, G1x, G1y, G1z);
            Vector3 uNormal = getNormal(u, v, G1x, G1y, G1z);
            Vector3 u_Normal = getNormal(u_, v, G1x, G1y, G1z);

            glNormal3f(uNormal[0], uNormal[1], uNormal[2]);
            glTexCoord2f(v / 2 + 0.5, 1 - u);
            glVertex3f(uPoint[0], uPoint[1], uPoint[2]);

            glNormal3f(u_Normal[0], u_Normal[1], u_Normal[2]);
            glTexCoord2f(v / 2 + 0.5, 1 - u_);
            glVertex3f(u_Point[0], u_Point[1], u_Point[2]);
        }
        glEnd();
    }
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void window::displayCallback(void)
{

  GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat specular[]  = {0.5, 0.5, 0.5, 1.0};
  GLfloat shininess[] = {25.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  cube.getMatrix().identity();

  cube.getMatrix().set(camera->C);
  cube.getMatrix().set(cube.getMatrix().multiply(cube2.getMatrix()));
  cube.getMatrix().set(cube.getMatrix().multiply(cube1.getMatrix()));
  glLoadMatrixd(cube.getMatrix().getGLPointer());
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  
  drawFlag();
  
  //display frame rate
  ++frameCount;

  currentTime = glutGet(GLUT_ELAPSED_TIME);

  int timeInterval = currentTime - prevTime;
  if (timeInterval > 1000)
  {
      cout << frameCount / (timeInterval / 1000.0f) << endl;
      prevTime = currentTime;
      frameCount = 0;
  }

  //glFlush();  
  glutSwapBuffers();
}

void drawobj(int nVerts, Vector3 * verticies, int nIndices, int * indices, Color * colors)
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < nIndices - 2; i += 3)
    {   
        if (colors != 0)
            glColor3d(colors[indices[i]].r, colors[indices[i]].g, colors[indices[i]].b);

        glVertex3f(verticies[indices[i]].get(0), 
                   verticies[indices[i]].get(1), 
                   verticies[indices[i]].get(2));
        
        glVertex3f(verticies[indices[i + 1]].get(0), 
                   verticies[indices[i + 1]].get(1),
                   verticies[indices[i + 1]].get(2));
        
        glVertex3f(verticies[indices[i + 2]].get(0),
                   verticies[indices[i + 2]].get(1),
                   verticies[indices[i + 2]].get(2));
    }
    glEnd();
}

void Cube::drawHouse()
{
  int nVerts = 42; 
  int nInd = 60;
  
  // These are the x,y,z coordinates of the vertices of the triangles
  Vector3 vertices[] = {  
            Vector3(-4,-4,4), Vector3(4,-4,4), Vector3(4,4,4), Vector3(-4,4,4),     // front face
            Vector3(-4,-4,-4), Vector3(-4,-4,4), Vector3(-4,4,4), Vector3(-4,4,-4), // left face
            Vector3(4,-4,-4),Vector3(-4,-4,-4), Vector3(-4,4,-4), Vector3(4,4,-4),  // back face
            Vector3(4,-4,4), Vector3(4,-4,-4), Vector3(4,4,-4), Vector3(4,4,4),     // right face
            Vector3(4,4,4), Vector3(4,4,-4), Vector3(-4,4,-4), Vector3(-4,4,4),     // top face
            Vector3(-4,-4,4), Vector3(-4,-4,-4), Vector3(4,-4,-4), Vector3(4,-4,4), // bottom face

            Vector3(-20,-4,20), Vector3(20,-4,20), Vector3(20,-4,-20), Vector3(-20,-4,-20), // grass
            Vector3(-4,4,4), Vector3(4,4,4), Vector3(0,8,4),                       // front attic wall
            Vector3(4,4,4), Vector3(4,4,-4), Vector3(0,8,-4), Vector3(0,8,4),               // left slope
            Vector3(-4,4,4), Vector3(0,8,4), Vector3(0,8,-4), Vector3(-4,4,-4),             // right slope
            Vector3(4,4,-4), Vector3(-4,4,-4), Vector3(0,8,-4)};                   // rear attic wall

  // These are the RGB colors corresponding to the vertices, in the same order
  Color colors[] = { 
            Color(1,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0),  // front is red
            Color(0,1,0), Color(0,1,0), Color(0,1,0), Color(0,1,0),  // left is green
            Color(1,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0),  // back is red
            Color(0,1,0), Color(0,1,0), Color(0,1,0), Color(0,1,0),  // right is green
            Color(0,0,1), Color(0,0,1), Color(0,0,1), Color(0,0,1),  // top is blue
            Color(0,0,1), Color(0,0,1), Color(0,0,1), Color(0,0,1),  // bottom is blue
  
            Color(0,0.5,0), Color(0,0.5,0), Color(0,0.5,0), Color(0,0.5,0), // grass is dark green
            Color(0,0,1), Color(0,0,1), Color(0,0,1),                // front attic wall is blue
            Color(1,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0),         // left slope is green
            Color(0,1,0), Color(0,1,0), Color(0,1,0), Color(0,1,0),         // right slope is red
            Color(0,0,1), Color(0,0,1), Color(0,0,1)};              // rear attic wall is red

  // The index data stores the connectivity of the triangles; 
  // index 0 refers to the first triangle defined above
  int indices[] = {
            0,2,3,    0,1,2,      // front face
            4,6,7,    4,5,6,      // left face
            8,10,11,  8,9,10,     // back face
            12,14,15, 12,13,14,   // right face
            16,18,19, 16,17,18,   // top face
            20,22,23, 20,21,22,   // bottom face
                   
            24,26,27, 24,25,26,   // grass
            28,29,30,             // front attic wall
            31,33,34, 31,32,33,   // left slope
            35,37,38, 35,36,37,   // right slope
            39,40,41};            // rear attic wall

  drawobj(nVerts, &vertices[0], nInd, &indices[0], &colors[0]);
}

Cube::Cube()
{
  angle = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

void loadObj(char * filename)
{
    ObjReader::readObj(filename, nVerts, &vertices, &normals, &texcoords, nIndices, &indices);

    findMinMax();

    cube.angle = 0;
    camera->resetCamera();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    GLfloat light0_color_src[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light1_color_src[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat light2_color_src[] = {0.0, 0.0, 1.0, 1.0};

    GLfloat specular[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat zero[] = {0.0, 0.0, 0.0, 0.0};
    switch(key)
    {
        case 'r':
            cube1.getMatrix().identity();
            cube2.getMatrix().identity();
            cube3.getMatrix().identity();
            cube.getMatrix().identity();
            lzero.getMatrix().identity();
            lone.getMatrix().identity();
            ltwo.getMatrix().identity();
            cube.angle = 0.0;
            nVerts = 0;
            break;
        case 'z':
            isTranslate = true;
            break;
        case 'g':
            light12_s = !light12_s;
            if (light12_s)
                shader->bind();
            else
                shader->unbind();
            break;
        case 't':
            isTexture = !isTexture;
            if (isTexture) glEnable(GL_TEXTURE_2D);
            else glDisable(GL_TEXTURE_2D);
            break;
        case 27:
            delete camera;
            delete shader;
            delete world;
            exit(0);
    }
}

void processUpKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'z':
            isTranslate = false;
            break;
    }   
}

void processSpecialKeys(int key, int x, int y)
{
    isShift = glutGetModifiers(); // GLUT_ACTIVE_SHIFT

    switch (key) 
    {
        case GLUT_KEY_UP:
            isForward = true;
            break;
        case GLUT_KEY_DOWN:
            isBackward = true;
            break;
        case GLUT_KEY_LEFT:
            isLeft = true;
            break;
        case GLUT_KEY_RIGHT:
            isRight = true;
            break;
    }
}

void processSpecialUpKeys(int key, int x, int y)
{
    switch (key) 
    {
        case GLUT_KEY_UP:
            isForward = false;
            break;
        case GLUT_KEY_DOWN:
            isBackward = false;
            break;
        case GLUT_KEY_LEFT:
            isLeft = false;
            break;
        case GLUT_KEY_RIGHT:
            isRight = false;
            break;
    }
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float x_ = x - window::width / 2.0;
        float y_ = -(y - window::height / 2.0);
        float z = (window::width / 2.0) * (window::width / 2.0) - x_ * x_ - y_ * y_; 
        if (z < 0) z = 0.0;
        else z = sqrt(z);
        p0.set(x_, y_, z);

        leftDown = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    {
        leftDown = false;
        if (light0)
            lzero.getMatrix().set(cube2.getMatrix().multiply(lzero.getMatrix()));
        if (light1)
            lone.getMatrix().set(cube2.getMatrix().multiply(lone.getMatrix()));
        if (light2)
            ltwo.getMatrix().set(cube2.getMatrix().multiply(ltwo.getMatrix()));
        if (!light0 && !light1 && !light2)
        {
            cube1.getMatrix().set(cube2.getMatrix().multiply(cube1.getMatrix()));
            cube3.getMatrix().set(cube2.getMatrix().multiply(cube3.getMatrix()));
        }
        cube2.getMatrix().identity();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        old_y = -(y - window::height / 2.0);
        rightDown = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        rightDown = false;
        // save prev state
        if (light0)
            lzero.getMatrix().set(cube2.getMatrix().multiply(lzero.getMatrix()));
        if (light1)
            lone.getMatrix().set(cube2.getMatrix().multiply(lone.getMatrix()));
        if (light2)
            ltwo.getMatrix().set(cube2.getMatrix().multiply(ltwo.getMatrix()));
        if (!light0 && !light1 && !light2)
        {
            cube1.getMatrix().set(cube2.getMatrix().multiply(cube1.getMatrix()));
            cube3.getMatrix().set(cube2.getMatrix().multiply(cube3.getMatrix()));
        }
        cube2.getMatrix().identity();
    }
}

void mouseMotionFunc(int x, int y)
{
    float x_ = x - window::width / 2.0;
    float y_ = -(y - window::height / 2.0);
    float z = (window::width / 2.0) * (window::width / 2.0) - x_ * x_ - y_ * y_;
    float theta;
    Vector3 axis;
    if (z < 0) z = 0.0;
    else z = sqrt(z);
    p1.set(x_, y_, z);
    cube2.getMatrix().identity();
    if (isTranslate && leftDown) // if translating 
    {
        cube2.getMatrix().translate((p1.get(0) - p0.get(0)) / 35.0, 
                                    (p1.get(1) - p0.get(1)) / 35.0,
                                    0);
    }
    else if (leftDown) // rotating 
    {
        p1.normalize();
        p0.normalize();
        axis = p0.cross(p1);
        theta = acos(p0.dot(p1));
        axis.normalize();
        Vector4 a(axis.get(0), axis.get(1), axis.get(2), 0);
        cube2.getMatrix().rotateA(a,theta);
    }
    else if (rightDown) // scaling
    {
        new_y = -(y - window::height / 2.0);
        float scale = (new_y - old_y) / window::height / 2.0 + 1;
        cube2.getMatrix().scale(scale, scale, scale);
    }
}

MatrixTransform * newrobot;

void loadRobot()
{
    world->addChild(cameraMT);
    cameraMT->addChild(robot);

    robot->addChild(torso);
    robot->addChild(leftUpArmMT);
    robot->addChild(rightUpArmMT);
    robot->addChild(leftUpLegMT);
    robot->addChild(rightUpLegMT);
    robot->addChild(headMT);

    headMT->addChild(head);

    leftUpArmMT->addChild(leftUpArm);
    leftUpArmMT->addChild(leftElbowMT);
    leftElbowMT->addChild(leftElbow);
    leftElbowMT->addChild(leftLowArmMT);
    leftLowArmMT->addChild(leftLowArm);

    rightUpArmMT->addChild(rightUpArm);
    rightUpArmMT->addChild(rightElbowMT);
    rightElbowMT->addChild(rightElbow);
    rightElbowMT->addChild(rightLowArmMT);
    rightLowArmMT->addChild(rightLowArm);

    leftUpLegMT->addChild(leftUpLeg);
    leftUpLegMT->addChild(leftKneeMT);
    leftKneeMT->addChild(leftKnee);
    leftKneeMT->addChild(leftLowLegMT);
    leftLowLegMT->addChild(leftLowLeg);

    rightUpLegMT->addChild(rightUpLeg);
    rightUpLegMT->addChild(rightKneeMT);
    rightKneeMT->addChild(rightKnee);
    rightKneeMT->addChild(rightLowLegMT);
    rightLowLegMT->addChild(rightLowLeg);

    //camera->getCameraMatrix().print();
    camera->C.invert();
    cameraMT->curMatrix = camera->C;
    //camera->getCameraMatrix().print();
    //camera->getCameraMatrix().invert();

    leftUpArm->setColor(0,1,0);
    leftLowArm->setColor(0,0,1);

    rightUpArm->setColor(0,1,0);
    rightLowArm->setColor(0,0,1);

    leftUpLeg->setColor(0,1,0);
    leftLowLeg->setColor(0,0,1);

    rightUpLeg->setColor(0,1,0);
    rightLowLeg->setColor(0,0,1);

    torso->setColor(0.8,0.2,1.0);

    robot->curMatrix.rotateY(-0.25);

    headMT->curMatrix.translate(0.0,2.65,0.0);
    headMT->curMatrix.rotateY(-0.2);

    leftUpArmMT->curMatrix.translate(-2, 0.5, 0.0);
    leftUpArmMT->curMatrix.rotateZ(1.0);
    leftUpArmMT->curMatrix.rotateY(1.0);
    
    rightUpArmMT->curMatrix.translate(2.2, 0, 0.0);
    rightUpArmMT->curMatrix.rotateZ(-1.0);
    rightUpArmMT->curMatrix.rotateY(-2.5);

    leftElbowMT->curMatrix.rotateX(2.5);

    rightElbowMT->curMatrix.rotateX(2.5);

    leftUpLegMT->curMatrix.translate(-0.75, -3, 0.0);
    leftUpLegMT->curMatrix.rotateX(-2);

    rightUpLegMT->curMatrix.translate(0.75,-3, 0.0);
    rightUpLegMT->curMatrix.rotateX(-1);
    
    leftKneeMT->curMatrix.rotateX(4);

    rightKneeMT->curMatrix.rotateX(2);
    /*for (int i = -5; i < 5; ++i)
        for (int j = -5; j < 5; ++j)
        {
            string name("robot" + i + j);
            newrobot = new MatrixTransform(name, robot);
            newrobot->curMatrix.translate(i * 5, 0, j* 5);
            cameraMT->addChild(newrobot);
        }*/
}

int main(int argc, char *argv[])
{
  float specular[]  = {0.8, 0.8, 0.8, 1.0};
  float shininess[] = {50.0};
  
  GLfloat light0_position[] = {0.0, 0.0, 10.0, 0.0};	// lightsource position
  GLfloat light1_position[] = {-1.5, 1.0, 0.0, 1.0};
  GLfloat light2_position[] = {-5.0, 5.0, 3.0, 1.0};
  
  GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
  
  GLfloat light0_color_src[] = {1.0, 0.0, 0.0, 1.0};
  GLfloat light1_color_src[] = {0.0, 1.0, 0.0, 1.0};
  GLfloat light2_color_src[] = {0.0, 0.0, 1.0, 1,0};
  
  GLfloat light1_direction[] = {0.0, 0.0, -1.0};
  GLfloat light1_cutoff[] = {3.0};
  
  GLfloat zero[] = {0.0, 0.0, 0.0, 0.0};

  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(window::width, window::height);      // set initial window size
  glutCreateWindow("CSE 167 project 6");    	      // open window and set window title
  
  //glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST); // enable depth buffering
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);
  //glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  //glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  //glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  /*glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);*/
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, zero);
  glLightfv(GL_LIGHT0, GL_SPECULAR, zero);
  glLightfv(GL_LIGHT0, GL_SHININESS, shininess);

  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, zero);
  glLightfv(GL_LIGHT2, GL_SPECULAR, zero);
  glLightfv(GL_LIGHT2, GL_SHININESS, shininess);

  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, zero);
  glLightfv(GL_LIGHT1, GL_SPECULAR, zero);
  glLightfv(GL_LIGHT1, GL_SHININESS, shininess);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
  glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_cutoff);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color_src);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);  // set the default ambient color
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  // allow glColor to set ambient and diffuse colors of geometry
 
  // Install callback functions:
  glutDisplayFunc(window::displayCallback);
  glutReshapeFunc(window::reshapeCallback);
  glutIdleFunc(window::idleCallback);

  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(&processNormalKeys);
  glutKeyboardUpFunc(&processUpKeys);
  glutSpecialFunc(&processSpecialKeys);
  glutSpecialUpFunc(&processSpecialUpKeys);

  glutMotionFunc(&mouseMotionFunc);
  glutMouseFunc(&mouseFunc);
    
  // Initialize cube matrix:
  cube.getMatrix().identity();
  
  cube1.getMatrix().identity();
  cube2.getMatrix().identity();
  cube3.getMatrix().identity();
  lzero.getMatrix().identity();
  lone.getMatrix().identity();
  ltwo.getMatrix().identity();

  //camera = new Camera(Vector3(-2,8,55),Vector3(0,0,1),Vector3(0,1,0));
  camera = new Camera(Vector3(0,0,25),Vector3(0,0,0),Vector3(0,1,0));
  //camera->resetCamera();
  
  char vert[] = "shaders/light1_2_shading.vert";
  char frag[] = "shaders/light1_2_shading.frag";
  shader = new Shader(vert, frag, true);

  loadTexture();

  //camera = new Camera(new Vector3(0,10,10), new Vector3(0,0,0), new Vector3(0,1,0));
  //camera = new Camera(new Vector3(-15,5,10), new Vector3(-5,0,0), new Vector3(0,1,0.5));

  loadRobot();
 
  glutMainLoop();
  return 0;
}
