#include "Vector3.h"

using namespace std;

Vector3::Vector3() 
{ 
    this->x = 0; this->y = 0; this->z = 0; 
}
Vector3::Vector3(float x, float y, float z) 
{
    set(x, y, z);        
}
void Vector3::set(float x, float y, float z) 
{
    this->x = x; this->y = y; this->z = z;    
}
float Vector3::get(int i)
{
    if (i == 0) return this->x;
    else if (i == 1) return this->y;
    else if (i == 2) return this->z;
    else 
    {
        cerr << "invalid index for get()" << endl;
        return 0.0; 
    }
}
float Vector3::operator[](int a)
{
    return get(a);    
}
Vector3 Vector3::add(Vector3 a) 
{
    return Vector3(this->x + a.x, this->y + a.y, this->z + a.z);
}
Vector3 Vector3::operator+(Vector3 a )
{
    return add(a);
}
Vector3 Vector3::subtract(Vector3 a) 
{
    return Vector3(this->x - a.x, this->y - a.y, this->z - a.z);     
}
Vector3 Vector3::operator-(Vector3 a )
{
    return subtract(a); 
}
void Vector3::negate() 
{
    this->x = -this->x; this->y = -this->y; this->z = -this->z;    
}
Vector3 Vector3::operator*(double s)
{
    return Vector3(x*s, y*s, z*s);
}
Vector3 Vector3::operator*(float s)
{
    return Vector3(x*s, y*s, z*s);
}
void Vector3::negate(Vector3 & a) 
{
    this->x = -a.x; this->y = -a.y; this->z = -a.z;    
}
void Vector3::scale(float s) 
{
    this->x *= s; this->y *= s; this->z *= s;        
}
void Vector3::scale(float s, Vector3 & a) 
{
    this->x = a.x * s; this->y = a.y * s; this->z = a.z * s;  
}
float Vector3::dot(Vector3 & a) 
{
    return this->x * a.x + this->y * a.y + this->z * a.z;
}
Vector3 Vector3::cross(Vector3 & b) 
{
    return Vector3 (this->y * b.z - this->z * b.y,
                        this->z * b.x - this->x * b.z,
                        this->x * b.y - this->y * b.x);
}
float Vector3::magnitude() 
{
    return sqrt(this->x * this->x + 
                this->y * this->y + 
                this->z * this->z);    
}
void Vector3::normalize() 
{
    if (magnitude() != 0)
        scale(1.0/magnitude());    
}
void Vector3::print() 
{ 
    cout << this->x << ", "
         << this->y << ", "
         << this->z << endl;
}

