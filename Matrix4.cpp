#include <math.h>

#include "Matrix4.h"

using namespace std;

Matrix4::Matrix4()
{
    identity();
} 
Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

Matrix4::Matrix4(double n[4][4])
{
  m[0][0] = n[0][0];
  m[0][1] = n[0][1];
  m[0][2] = n[0][2];
  m[0][3] = n[0][3];
  m[1][0] = n[1][0];
  m[1][1] = n[1][1];
  m[1][2] = n[1][2];
  m[1][3] = n[1][3];
  m[2][0] = n[2][0];
  m[2][1] = n[2][1];
  m[2][2] = n[2][2];
  m[2][3] = n[2][3];
  m[3][0] = n[3][0];
  m[3][1] = n[3][1];
  m[3][2] = n[3][2];
  m[3][3] = n[3][3];    
}

Matrix4::Matrix4(const Matrix4 & n)
{
  m[0][0] = n.m[0][0];
  m[0][1] = n.m[0][1];
  m[0][2] = n.m[0][2];
  m[0][3] = n.m[0][3];
  m[1][0] = n.m[1][0];
  m[1][1] = n.m[1][1];
  m[1][2] = n.m[1][2];
  m[1][3] = n.m[1][3];
  m[2][0] = n.m[2][0];
  m[2][1] = n.m[2][1];
  m[2][2] = n.m[2][2];
  m[2][3] = n.m[2][3];
  m[3][0] = n.m[3][0];
  m[3][1] = n.m[3][1];
  m[3][2] = n.m[3][2];
  m[3][3] = n.m[3][3];  
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

double * Matrix4::getGLPointer()
{
    transpose();
    return getPointer();
}

double Matrix4::get(int i, int j)
{
    return m[i][j];
}

void Matrix4::identity()
{
    double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            m[i][j] = ident[i][j];
        }
    }
}

Matrix4 Matrix4::add(Matrix4 n)
{
    Matrix4 ret;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            ret.m[r][c] = m[r][c] + n.m[r][c];
    return ret;
}

Matrix4 Matrix4::multiply(Matrix4 n)
{
    double res[4][4] = {0.0};
    double * a = n.getPointer(); //a[i][c] 
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            for (int i = 0; i < 4; ++i)
            {
                res[r][c] += m[r][i] * *(a + (i * 4) + c); 
            }
        }
    }
    return Matrix4(res);
}

Vector4 Matrix4::multiply(Vector4 v)
{
    return Vector4(m[0][0] * v[0] + m[0][1] * v[1] 
                 + m[0][2] * v[2] + m[0][3] * v[3], 
                   m[1][0] * v[0] + m[1][1] * v[1] 
                 + m[1][2] * v[2] + m[1][3] * v[3],
                   m[2][0] * v[0] + m[2][1] * v[1] 
                 + m[2][2] * v[2] + m[2][3] * v[3],
                   m[3][0] * v[0] + m[3][1] * v[1] 
                 + m[3][2] * v[2] + m[3][3] * v[3]);
}

void Matrix4::rotateX(double angle)
{
    Matrix4 n(1,0,0,0,
              0,cos(angle), -sin(angle), 0, 
              0, sin(angle), cos(angle), 0,
              0,0,0,1);
    set(multiply(n));
}

// angle in radians
void Matrix4::rotateY(double angle)
{
    Matrix4 n(cos(angle), 0, sin(angle), 0, 
              0, 1, 0, 0, 
              -sin(angle), 0, cos(angle), 0, 
              0, 0, 0, 1);
    set(multiply(n));
}

void Matrix4::rotateZ(double angle)
{
    Matrix4 n(cos(angle), -sin(angle), 0, 0, 
              sin(angle), cos(angle), 0,0,
              0,0,1,0,
              0,0,0,1);
    set(multiply(n));
}

void Matrix4::rotateA(Vector4 & v, double angle)
{
    double x = v.get(0), y = v.get(1), z = v.get(2);
	Matrix4 n(1 + (1 - cos(angle)) * (x * x - 1),
	          -z * sin(angle) + (1 - cos(angle)) * x * y,
	          y * sin(angle) + (1 - cos(angle)) * x * z,
	          0,
	          z * sin(angle) + (1 - cos(angle)) * y * x,
	          1 + (1 - cos(angle)) * (y * y - 1),
	          -x * sin(angle) + (1 - cos(angle)) * y * z,
	          0,
	          -y * sin(angle) + (1 - cos(angle)) * z * x,
	          x * sin(angle) + (1 - cos(angle)) * z * y,
	          1 + (1 - cos(angle)) * (z * z - 1),
	          0,
	          0,
	          0,
	          0,
	          1);
    set(multiply(n));
}

void Matrix4::scale(double a, double b, double c)
{
    Matrix4 s(a,0,0,0,
              0,b,0,0,
              0,0,c,0,
              0,0,0,1);
    set(multiply(s));
}

void Matrix4::scale(double s)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            m[i][j] *= s;
}

void Matrix4::set(Matrix4 n)
{
    for(int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = n.get(i,j);
}

void Matrix4::translate(double a, double b, double c)
{
    Matrix4 n(1,0,0,a,
              0,1,0,b,
              0,0,1,c,
              0,0,0,1);
    set(multiply(n));
}

void Matrix4::transpose()
{
    Matrix4 temp(m);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = temp.m[j][i];
}

void Matrix4::invert()
{
    Matrix4 rotation(m[0][0], m[0][1], m[0][2], 0,
                     m[1][0], m[1][1], m[1][2], 0,
                     m[2][0], m[2][1], m[2][2], 0,
                     0, 0, 0, 1);
    Matrix4 translation(1, 0, 0, -m[0][3],
                        0, 1, 0, -m[1][3],
                        0, 0, 1, -m[2][3],
                        0, 0, 0, 1);
    rotation.transpose();
    set(translation.multiply(rotation));
}

void Matrix4::negate()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = -m[i][j];
}

void Matrix4::print()
{
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
           cout << m[i][j] << " ";  
        }
        cout << endl;
    }
}

void Matrix4::originMultiply(Matrix4 n)
{
    double a = m[0][3];
    double b = m[1][3];
    double c = m[2][3];
    translate(-a, -b, -c);
    set(multiply(n));
    translate(a, b, c);
}
