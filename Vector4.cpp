#include "Vector4.h"

using namespace std;

Vector4::Vector4()
{
    this->x = 0; this->y = 0; this->z = 0; this->w = 0;
}
Vector4::Vector4(float x, float y, float z, float w)
{
    set(x, y, z, w);
}
Vector4::Vector4(float a[4])
{
    this->x = a[0]; this->y = a[1]; this->z = a[2]; this->w = a[3];
}
void Vector4::set(float x, float y, float z, float w)
{
    this->x = x; this->y = y; this->z = z; this->w = w;
}
void Vector4::scale(float s)
{
    x *= s; y *= s; z *= s; w *= s; 
}
float Vector4::get(int i)
{
    if (i == 0) return this->x;
    else if (i == 1) return this->y;
    else if (i == 2) return this->z;
    else if (i == 3) return this->w;
    else 
    {
        cerr << "invalid index for get()" << endl;
        return 0.0; 
    }
}
float Vector4::operator[](int a)
{
    return get(a);    
}
Vector4 Vector4::add(Vector4 & a) 
{
    return Vector4(this->x + a.x, this->y + a.y, 
                       this->z + a.z, this->w + a.w);
}
Vector4 Vector4::operator+(Vector4 & a )
{
    return add(a);
}
Vector4 Vector4::subtract(Vector4 & a) 
{
    return Vector4(this->x - a.x, this->y - a.y, 
                       this->z - a.z, this->w - a.w);     
}
Vector4 Vector4::operator-(Vector4 & a )
{
    return subtract(a); 
}
void Vector4::dehomogenize()
{
    this->x /= this->w; this->y /= this->w;
    this->z /= this->w; this->w /= this->w;
}
bool Vector4::equals(Vector4 & v)
{
    if (fabs(v.get(0) - x) < 0.00001 &&
        fabs(v.get(1) - y) < 0.00001 &&
        fabs(v.get(2) - z) < 0.00001 &&
        fabs(v.get(3) - w) < 0.00001)
        return true;
    return false;
}
float Vector4::multiply(Vector4 v)
{
    return x * v.get(0) + y * v.get(1) + z * v.get(2) + w * v.get(3);
}
Vector3 Vector4::getVector3()
{
    return Vector3(x, y, z);
}
void Vector4::print() 
{ 
    cout << this->x << ", "
         << this->y << ", "
         << this->z << ", "
         << this->w << endl;
}
