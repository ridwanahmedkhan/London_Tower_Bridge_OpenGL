#ifndef camera_H_INCLUDED
#define camera_H_INCLUDED

#include"Vector.h"
#include"math.h"

struct camera
{
public:
    Vector front;
    Vector up;
    Vector right;
    Vector position;
    camera();
    camera(Vector F,Vector U,Vector R);
    Vector LookAtPosition();
    void Move(Vector dir,double value);
    void Pitch(double angle);
    void Turn(double angle);
    void Roll(double angle);
};
camera::camera(){

}

camera::camera(Vector F,Vector U,Vector R)
{
	this->front=F;
	this->up=U;
	this->right=R;
}

Vector camera::LookAtPosition()
{
	return Vector(this->position+this->front*30.0);
}

//move forward or backward with magnitude 'value'
void camera::Move(Vector dir,double value)
{
	this->position=this->position+dir*value;
}
//pitch up or down 'angle' degrees
void camera::Pitch(double angle)
{
	double rad=angle*2*acos(0.)/180;
	Vector up1=this->up*cos(rad)+this->front*sin(rad);
	Vector front1=this->front*cos(rad)+(-this->up)*sin(rad);
	this->up=up1;
	this->front=front1;
}

//turn left or right 'angle' degrees
void camera::Turn(double angle)
{
	double rad=angle*2*acos(0.)/180;
	Vector front1=this->front*cos(rad)+this->right*sin(rad);
	Vector right1=this->right*cos(rad)+(-this->front)*sin(rad);
	this->front=front1;
	this->right=right1;
}

//roll left or right 'angle' degrees
void camera::Roll(double angle)
{
	double rad=angle*2*acos(0.)/180;
	Vector up1=this->up*cos(rad)+this->right*sin(rad);
	Vector right1=this->right*cos(rad)+(-this->up)*sin(rad);
	this->up=up1;
	this->right=right1;
}


#endif // camera_H_INCLUDED
