#include "Vector3D.h"

double Vector3D::Length() const //calculates magnitude
{
	return sqrt(x * x + y * y + z*z);
}

double Vector3D::LengthSq() const //omits sqrt
{
	return x * x + y * y + z * z;
}

void Vector3D::Normalize() //sets the vector as magnitude 1
{
	double vector_length = this->Length();
	if (!this->isZero())
	{
		this->x /= vector_length;
		this->y /= vector_length;
		this->z /= vector_length;
	}
	else {
		this->Zero();
	}
	
}

Vector3D Vector3D::Normalized() const //returns the vector as magnitude 1
{
	double vector_length = this->Length();
	Vector3D returnVector = Vector3D();

	if (!this->isZero())
	{
		returnVector.x /= vector_length;
		returnVector.y /= vector_length;
		returnVector.z /= vector_length;
	}
	else {
		returnVector.Zero();
	}
	return returnVector;
}

double Vector3D::Dot(const Vector3D& v2) const //dot product
{
	return (x * v2.x) + (y * v2.y) + (z * v2.z);
}

void Vector3D::Truncate(double max) //removes excess length
{
	if (this->Length() > max)
	{
		this->Normalize();

		*this *= max;
	}
}

double Vector3D::Distance(const Vector3D& v2) const //distance between 2 vectors
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	double zSeparation = v2.z - z;
	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation + zSeparation*zSeparation);
}

double Vector3D::DistanceSq(const Vector3D& v2) const //omits sqrt
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	double zSeparation = v2.z - z;
	return ySeparation * ySeparation + xSeparation * xSeparation + zSeparation * zSeparation;
}

Vector3D Vector3D::GetReverse() const
{
	return Vector3D(-this->x, -this->y, -this->z);
}

Vector3D Vector3D::Reflect(const Vector3D& normal)
{
	Vector3D reflection = Vector3D();
	
	double dot = 2.0 * this->Dot(normal.Normalized());
	reflection = dot*(normal-*this);
	return reflection;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D();
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	// TODO: insert return statement here
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D();
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	// TODO: insert return statement here
}

Vector3D& Vector3D::operator*(const Vector3D& rhs) const
{
	// TODO: insert return statement here
}

Vector3D& Vector3D::operator*=(const Vector3D& rhs)
{
	// TODO: insert return statement here
}

Vector3D& Vector3D::operator=(const Vector3D& v2)
{
	// TODO: insert return statement here
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	return false;
}

bool Vector3D::operator!=(const Vector3D& rhs) const
{
	return false;
}

Vector3D& Vector3D::operator/=(const double& scalar)
{
	// TODO: insert return statement here
}

Vector3D& Vector3D::operator*=(const double& scalar)
{
	// TODO: insert return statement here
}

Vector3D operator/(const double& lhs, const Vector3D& rhs)
{
	return Vector3D();
}

Vector3D operator/(const Vector3D& lhs, const double& rhs)
{
	return Vector3D();
}

Vector3D operator*(const double& lhs, const Vector3D& rhs)
{
	return Vector3D();
}

Vector3D operator*(const Vector3D& lhs, const double& rhs)
{
	return Vector3D();
}
