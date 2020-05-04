// Matrix.h Class for doing operations on matrices and vectors
// Copyright (c) 2016
// Written by Edwin P. Berlin, Jr., Secret Software
// 11/16/05
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>

#ifndef _USRDLL
//#define DLLEXPORT		__declspec(dllimport)
//#define DLLEXPORT
#endif

#ifndef DLLEXPORT
#define DLLEXPORT		__declspec(dllexport)
#endif

//This code can compile as floats or doubles, depending on this macro
//#define REAL	float
#define REAL	double

////////////
// Constants
#undef PI									//In case it was defined in another file
#define PI		3.1415926535897932384626
#define SQRT2	1.4142135623730950488

#define RADIANS_TO_DEGREES		(REAL)(180. / PI)
#define DEGREES_TO_RADIANS		(REAL)(PI / 180.)

//An epsilon used to initialize a Quaternion from a Matrix
//If you want a different value, define it before the header
#ifndef QUAT_EPSILON
#define QUAT_EPSILON	(REAL)1e-30		//Could be as small as 1e-38f when using float
#endif

//This is a struct version of Vector
//needed to allow including a Vector within a union
typedef struct {
	union {
		struct {
			REAL x, y, z;
		};
		REAL Array[3];
	};
} sVector;

#ifndef __cplusplus

//If you want to link GyroSuit.dll with C code, this will let the
//Vector and Matrix members of the Node struct compile
typedef sVector Vector;

typedef struct {
	union {
		struct {
			REAL xx, xy, xz;		//This row is the right vector
			REAL yx, yy, yz;		//This row is the up vector
			REAL zx, zy, zz;		//This row is the forward vector
		};
		REAL Array[3][3];			//[row][col]
		Vector Row[3];				//The rows of the matrix
	};
} Matrix;

typedef struct {
	REAL s;		//The scalar component
	Vector v;		//The vector component
} Quaternion;

#else

///////////////
// Vector class

class DLLEXPORT Vector {
public:
	union {
		struct {
			REAL x, y, z;
		};
		REAL Array[3];
	};

	//////////////
	//Constructors

	///////////////////////////
	//Uninitialized constructor
	inline Vector() {}
	////////////////////////
	//Initialize from floats
	inline Vector(float ax, float ay, float az) :
				  x((REAL)ax), y((REAL)ay), z((REAL)az) {}
	/////////////////////////
	//Initialize from doubles
	inline Vector(double ax, double ay, double az) :
				  x((REAL)ax), y((REAL)ay), z((REAL)az) {}
	/////////////////////////////////
	//Initialize from array of floats
	inline Vector(float *a) :
				  x((REAL)a[0]), y((REAL)a[1]), z((REAL)a[2]) {}
	//////////////////////////////////
	//Initialize from array of doubles
	inline Vector(double *a) :
				  x((REAL)a[0]), y((REAL)a[1]), z((REAL)a[2]) {}

	///////////
	//Functions

	///////////////////////////////
	//Copy constructor from sVector
	inline Vector(sVector &V)
	{
		x = V.x;
		y = V.y;
		z = V.z;
	}

	/////////////////
	//Cast to sVector
	inline operator sVector&()
	{
		return *(sVector *)this;
	}

	///////////////////////
	//Normalizes the vector
	//Returns 0 if vector length is 0, else 1
	inline int Normalize()
	{
		double t;
		t = (REAL)(x * (double)x + y * (double)y + z * (double)z);
		if(t == 0.) return 0;
		t = 1. / sqrt(t);
		x *= (REAL)t;
		y *= (REAL)t;
		z *= (REAL)t;
		return 1;
	}

	//////////////////////////////////
	//Return the length of this vector
	inline REAL Length()
	{
		return (REAL)sqrt(x * x + y * y + z * z);
	}

	////////////////////////////////////////////////
	//Return the square of the length of this vector
	inline double LengthSquared()
	{
		return (x * (double)x + y * (double)y + z * (double)z);
	}

	/////////////////
	//Vector addition
	//Operator +=
	inline void operator+=(const Vector V)
	{
		//this += V
		x += V.x;
		y += V.y;
		z += V.z;
	}

	/////////////////
	//Vector addition
	//Operator +
	inline Vector operator+(const Vector V)
	{
		Vector R;
		//R = this + V
		R.x = x + V.x;
		R.y = y + V.y;
		R.z = z + V.z;
		return R;
	}

	////////////////////
	//Vector subtraction
	//Operator -=
	inline void operator-=(const Vector V)
	{
		//this -= V
		x -= V.x;
		y -= V.y;
		z -= V.z;
	}

	////////////////////
	//Vector subtraction
	//Operator -
	inline Vector operator-(const Vector V)
	{
		Vector R;
		//R = this - V
		R.x = x - V.x;
		R.y = y - V.y;
		R.z = z - V.z;
		return R;
	}

	/////////////////
	//Vector negation
	//Operator unary -
	inline Vector operator-()
	{
		Vector R;
		//R = -this
		R.x = -x;
		R.y = -y;
		R.z = -z;
		return R;
	}

	/////////////
	//Dot product
	//Operator * (Vector)
	inline REAL operator*(const Vector V)
	{
		//Result = this dot V
		return x * V.x + y * V.y + z * V.z;
	}

	/////////////////////////////
	//Multiply vector by a scalar
	//Operator *= (Scalar)
	inline void operator*=(const REAL s)
	{
		//this *= s
		x *= s;
		y *= s;
		z *= s;
	}

	/////////////////////////////
	//Multiply vector by a scalar
	//Operator * (Scalar)
	inline Vector operator*(const REAL s)
	{
		Vector R(x * s, y * s, z * s);
		return R;
	}

	///////////////////////////
	//Divide vector by a scalar
	//Operator /= (Scalar)
	inline void operator/=(const REAL s)
	{
		//this /= s
		REAL d = 1.f / s;
		x *= d;
		y *= d;
		z *= d;
	}

	///////////////////////////
	//Divide vector by a scalar
	//Operator / (Scalar)
	inline Vector operator/(const REAL s)
	{
		REAL d = 1.f / s;
		Vector R(x * d, y * d, z * d);
		return R;
	}

	//////////////////////
	//Vector cross product
	//Operator ^ (Cross product)
	inline Vector operator^(const Vector V)
	{
		Vector R;

		R.x = y * V.z - V.y * z;
		R.y = z * V.x - V.z * x;
		R.z = x * V.y - V.x * y;

		return R;
	}
};

///////////////
// Matrix class

class DLLEXPORT Matrix {
public:
	//Rotation matrix
	//The columns are the X, Y, and Z axes
	union {
		struct {
			REAL xx, xy, xz;		//This row is the right vector
			REAL yx, yy, yz;		//This row is the up vector
			REAL zx, zy, zz;		//This row is the forward vector
		};
		REAL Array[3][3];			//[row][col]
		sVector Row[3];				//The rows of the matrix
									//Not a Vector because unions can't contain
									//classes with non-default constructors
									//Handled with cast and copy constructors in Vector
	};

	//////////////
	//Constructors

	///////////////////////////
	//Uninitialized constructor
	inline Matrix() {}
	////////////////////////
	//Initialize from floats
	inline Matrix(float axx, float axy, float axz,
				  float ayx, float ayy, float ayz,
				  float azx, float azy, float azz) :
			xx((REAL)axx), xy((REAL)axy), xz((REAL)axz),
			yx((REAL)ayx), yy((REAL)ayy), yz((REAL)ayz),
			zx((REAL)azx), zy((REAL)azy), zz((REAL)azz) {}
	/////////////////////////
	//Initialize from doubles
	inline Matrix(double axx, double axy, double axz,
				  double ayx, double ayy, double ayz,
				  double azx, double azy, double azz) :
			xx((REAL)axx), xy((REAL)axy), xz((REAL)axz),
			yx((REAL)ayx), yy((REAL)ayy), yz((REAL)ayz),
			zx((REAL)azx), zy((REAL)azy), zz((REAL)azz) {}
	/////////////////////////////
	//Initialize from row vectors
	inline Matrix(Vector RowX, Vector RowY, Vector RowZ) :
			xx(RowX.x), xy(RowX.y), xz(RowX.z),
			yx(RowY.x), yy(RowY.y), yz(RowY.z),
			zx(RowZ.x), zy(RowZ.y), zz(RowZ.z) {}

	//////////////
	//Initializers

	///////////////////////////////////////////////////////
	//These functions return rotation matrices about 1 axis
	//Rotations are all CCW looking down the axis of rotation
	//(in the minus direction)
	static Matrix RotX(REAL theta);	//Rotation matrix about X axis
	static Matrix RotY(REAL theta);	//Rotation matrix about Y axis
	static Matrix RotZ(REAL theta);	//Rotation matrix about Z axis

	/////////////////////////////////////////////////////////
	//These functions return rotation matrices about 3 axes
	//Matrices are composed as: RotY * RotX * RotZ
	//Since these are applied right first, this is a rotation
	//about Z, then X, then Y
	//Pay attention to the order of the arguments
	static Matrix RotYXZ(REAL thetay, REAL thetax, REAL thetaz);
	//Matrices are composed as: RotZ * RotX * RotY
	//Since these are applied right first, this is a rotation
	//about Y, then X, then Z
	//Pay attention to the order of the arguments
	static Matrix RotZXY(REAL thetaz, REAL thetax, REAL thetay);
	//Matrices are composed as: RotZ * RotY * RotX
	//Since these are applied right first, this is a rotation
	//about X, then Y, then Z
	//Pay attention to the order of the arguments
	static Matrix RotZYX(REAL thetaz, REAL thetay, REAL thetax);

	///////////
	//Functions

	////////////////////////////////////////////////////////////////////
	//Converts a pure rotation matrix into Euler angles in the order YXZ
	//reading right to left.
	//Assumes the matrix is a pure rotation with no scale or shear.
	//There is an ambiguity of the sign of cos(thetax) which we resolve
	//by simply forcing cos(thetaz) >= 0
	//There is an additional ambiguity when cos(thetax) = 0.  This is the
	//gymbal lock condition in which thetay and thetaz are not independent.
	//We resolve this special case by assuming thetay = 0 when cos(thetax) = 0.
	//These are fundamental issues caused by the fact that Euler angles are
	//inherently ill-defined.
	//Pay attention to the order of the arguments
	void MatrixToEulerYXZ(REAL *ty, REAL *tx, REAL *tz);

	////////////////////////////////////////////////////////////////////
	//Converts a pure rotation matrix into Euler angles in the order ZYX
	//reading right to left.
	//Assumes the matrix is a pure rotation with no scale or shear.
	//There is an ambiguity of the sign of cos(thetay) which we resolve
	//by simply forcing cos(thetay) >= 0
	//There is an additional ambiguity when cos(thetay) = 0.  This is the
	//gymbal lock condition in which thetax and thetaz are not independent.
	//We resolve this special case by assuming thetax = 0 when cos(thetay) = 0.
	//These are fundamental issues caused by the fact that Euler angles are
	//inherently ill-defined.
	//Pay attention to the order of the arguments
	void MatrixToEulerZYX(REAL *tz, REAL *ty, REAL *tx);

	////////////////////////////////////////////////////////////////////
	//Converts a pure rotation matrix into Euler angles in the order ZXY
	//reading right to left.
	//Angles range over +/- PI
	//Assumes the matrix is a pure rotation with no scale or shear.
	//There is an ambiguity of the sign of cos(thetax) which we resolve
	//by simply forcing cos(thetaz) >= 0
	//There is an additional ambiguity when cos(thetax) = 0.  This is the
	//gymbal lock condition in which thetay and thetaz are not independent.
	//We resolve this special case by assuming thetay = 0 when cos(thetax) = 0.
	//These are fundamental issues caused by the fact that Euler angles are
	//inherently ill-defined.
	//Pay attention to the order of the arguments
	void MatrixToEulerZXY(REAL *tz, REAL *tx, REAL *ty);

	////////////////////////////////////////////////////////////
	//Assumes Matrix is a pure rotation about some axis by theta
	//This scales theta by scale to give a new matrix rotating
	//about the same axis
	void ScaleRotation(REAL scale);

	///////////////
	//M = A inverse
	//Returns 0 if matrix not invertible
	//Gaussian-Jordan elimination with full pivoting
	//From numerical recipes in C
	//Special case of B = I
	int Inverse(Matrix A);

	////////////////////////////////////
	//Return the transpose of the matrix
	inline Matrix Transpose()
	{
		Matrix R(xx, yx, zx,
				 xy, yy, zy,
				 xz, yz, zz);
		return R;
	}

	//////////////////////////////////
	//Return row vectors of the matrix
	//Can also use Row[]
	inline Vector RowX() {	return Row[0]; }
	inline Vector RowY() {	return Row[1]; }
	inline Vector RowZ() {	return Row[2]; }

	/////////////////////////////////////
	//Return column vectors of the matrix
	inline Vector ColX() {	return Vector(xx, yx, zx); }
	inline Vector ColY() {	return Vector(xy, yy, zy); }
	inline Vector ColZ() {	return Vector(xz, yz, zz); }

	/////////////////////////
	//Set a row of the matrix
	//Cal also use Row[] =
	inline void SetRowX(Vector RowX) {	Row[0] = RowX; }
	inline void SetRowY(Vector RowY) {	Row[1] = RowY; }
	inline void SetRowZ(Vector RowZ) {	Row[2] = RowZ; }

	////////////////////////////
	//Set a column of the matrix
	inline void SetColX(Vector ColX) {	xx = ColX.x; yx = ColX.y; zx = ColX.z; }
	inline void SetColY(Vector ColY) {	xy = ColY.x; yy = ColY.y; zy = ColY.z; }
	inline void SetColZ(Vector ColZ) {	xz = ColZ.x; yz = ColZ.y; zz = ColZ.z; }

	///////////
	//Operators

	/////////////////
	//Matrix multiply
	//Operator *=
	inline void operator*=(const Matrix B)
	{
		Matrix A(*this);
		//Result = A B

		//Each column of Result = A times each column of B
		xx = A.xx * B.xx + A.xy * B.yx + A.xz * B.zx;
		yx = A.yx * B.xx + A.yy * B.yx + A.yz * B.zx;
		zx = A.zx * B.xx + A.zy * B.yx + A.zz * B.zx;

		xy = A.xx * B.xy + A.xy * B.yy + A.xz * B.zy;
		yy = A.yx * B.xy + A.yy * B.yy + A.yz * B.zy;
		zy = A.zx * B.xy + A.zy * B.yy + A.zz * B.zy;

		xz = A.xx * B.xz + A.xy * B.yz + A.xz * B.zz;
		yz = A.yx * B.xz + A.yy * B.yz + A.yz * B.zz;
		zz = A.zx * B.xz + A.zy * B.yz + A.zz * B.zz;
	}

	/////////////////
	//Matrix multiply
	//Operator * (Matrix)
	inline Matrix operator*(const Matrix B)
	{
		Matrix R;
		//Result = this B

		//Each column of Result = A times each column of B
		R.xx = xx * B.xx + xy * B.yx + xz * B.zx;
		R.yx = yx * B.xx + yy * B.yx + yz * B.zx;
		R.zx = zx * B.xx + zy * B.yx + zz * B.zx;

		R.xy = xx * B.xy + xy * B.yy + xz * B.zy;
		R.yy = yx * B.xy + yy * B.yy + yz * B.zy;
		R.zy = zx * B.xy + zy * B.yy + zz * B.zy;

		R.xz = xx * B.xz + xy * B.yz + xz * B.zz;
		R.yz = yx * B.xz + yy * B.yz + yz * B.zz;
		R.zz = zx * B.xz + zy * B.yz + zz * B.zz;

		return R;
	}

	/////////////////////////////
	//Matrix times a right vector
	//Operator * (Vector)
	inline Vector operator*(const Vector V)
	{
		Vector R;
		//Result = this V

		//A nice way to think of multiplying a matrix
		//by a vector is one dot product per row
		R.x = (Vector)Row[0] * V;
		R.y = (Vector)Row[1] * V;
		R.z = (Vector)Row[2] * V;

		return R;
	}

	//////////
	//Addition
	//Operator +=
	inline void operator+=(const Matrix B)
	{
		//this += M
		xx += B.xx;
		yx += B.yx;
		zx += B.zx;

		xy += B.xy;
		yy += B.yy;
		zy += B.zy;

		xz += B.xz;
		yz += B.yz;
		zz += B.zz;
	}

	//////////
	//Addition
	//Operator +
	inline Matrix operator+(const Matrix B)
	{
		Matrix R;
		//R = this + M
		R.xx = xx + B.xx;
		R.yx = yx + B.yx;
		R.zx = zx + B.zx;

		R.xy = xy + B.xy;
		R.yy = yy + B.yy;
		R.zy = zy + B.zy;

		R.xz = xz + B.xz;
		R.yz = yz + B.yz;
		R.zz = zz + B.zz;
		return R;
	}

	/////////////
	//Subtraction
	//Operator -=
	inline void operator-=(const Matrix B)
	{
		//this -= M
		xx -= B.xx;
		yx -= B.yx;
		zx -= B.zx;

		xy -= B.xy;
		yy -= B.yy;
		zy -= B.zy;

		xz -= B.xz;
		yz -= B.yz;
		zz -= B.zz;
	}

	/////////////
	//Subtraction
	//Operator -
	inline Matrix operator-(const Matrix B)
	{
		Matrix R;
		//R = this - M
		R.xx = xx - B.xx;
		R.yx = yx - B.yx;
		R.zx = zx - B.zx;

		R.xy = xy - B.xy;
		R.yy = yy - B.yy;
		R.zy = zy - B.zy;

		R.xz = xz - B.xz;
		R.yz = yz - B.yz;
		R.zz = zz - B.zz;
		return R;
	}

	//////////
	//Negation
	//Operator unary -
	inline Matrix operator-()
	{
		Matrix R;
		//R = -this
		R.xx = -xx;
		R.yx = -yx;
		R.zx = -zx;

		R.xy = -xy;
		R.yy = -yy;
		R.zy = -zy;

		R.xz = -xz;
		R.yz = -yz;
		R.zz = -zz;
		return R;
	}

	/////////////////////////////
	//Multiply matrix by a scalar
	//Operator *= (Scalar)
	inline void operator*=(const REAL s)
	{
		//this *= s
		xx *= s;
		yx *= s;
		zx *= s;

		xy *= s;
		yy *= s;
		zy *= s;

		xz *= s;
		yz *= s;
		zz *= s;
	}

	/////////////////////////////
	//Multiply matrix by a scalar
	//Operator * (Scalar)
	inline Matrix operator*(const REAL s)
	{
		Matrix R;
		//R = this * s
		R.xx = xx * s;
		R.yx = yx * s;
		R.zx = zx * s;

		R.xy = xy * s;
		R.yy = yy * s;
		R.zy = zy * s;

		R.xz = xz * s;
		R.yz = yz * s;
		R.zz = zz * s;
		return R;
	}
};

///////////////////
// Quaternion class

class DLLEXPORT Quaternion {
public:
	REAL s;		//The scalar component
	Vector v;		//The vector component

	//////////////
	//Constructors

	///////////////////////////
	//Uninitialized constructor
	inline Quaternion() {}
	////////////////////////
	//Initialize from floats
	inline Quaternion(float S, float vx, float vy, float vz) :
				  s((REAL)S), v(Vector(vx, vy, vz)) {}
	//Initialize from doubles
	inline Quaternion(double S, double vx, double vy, double vz) :
				  s((REAL)S), v(Vector(vx, vy, vz)) {}
	//////////////////////////////////
	//Initialize from REAL and Vector
	inline Quaternion(REAL S, Vector V) :
				  s(S), v(V) {}
	/////////////////////////////////
	//Initialize from array of floats
	inline Quaternion(float *a) :
				  s((REAL)a[0]), v(Vector(a[1], a[2], a[3])) {}
	//////////////////////////////////
	//Initialize from array of doubles
	inline Quaternion(double *a) :
				  s((REAL)a[0]), v(Vector(a[1], a[2], a[3])) {}
	////////////////////////
	//Initialize from Matrix
	//Assumes matrix is a pure rotation
	Quaternion(Matrix M)
	{
		REAL inv;

		s = .25f * (M.xx + M.yy + M.zz + 1.f);
		if(s > QUAT_EPSILON) {
			s = (REAL)sqrt(s);
			inv = .25f / s;
			v.x = (M.zy - M.yz) * inv;
			v.y = (M.xz - M.zx) * inv;
			v.z = (M.yx - M.xy) * inv;
		} else {
			s = 0.f;
			v.x = -.5f * (M.yy + M.zz);
			if(v.x > QUAT_EPSILON) {
				v.x = (REAL)sqrt(v.x);
				inv = .5f / v.x;
				v.y = M.yx * inv;
				v.z = M.zx * inv;
			} else {
				v.x = 0.f;
				v.y = .5f * (1.f - M.zz);
				if(v.y > QUAT_EPSILON) {
					v.y = (REAL)sqrt(v.y);
					v.z = M.zy * .5f / v.y;
				} else {
					v.y = 0.f;
					v.z = 1.f;
				}
			}
		}
		Normalize();
	}

	///////////
	//Functions

	//Convert a quaternion to a matrix
	//Assumes quaternion has unit magnitude
	Matrix ToMatrix()
	{
		Matrix M;
		REAL tx2, ty2, tz2, txy, txz, tyz, twx, twy, twz;

		tx2 = 2.f * v.x * v.x;
		ty2 = 2.f * v.y * v.y;
		tz2 = 2.f * v.z * v.z;
		txy = 2.f * v.x * v.y;
		txz = 2.f * v.x * v.z;
		tyz = 2.f * v.y * v.z;
		twx = 2.f * s * v.x;
		twy = 2.f * s * v.y;
		twz = 2.f * s * v.z;

		//First row
		M.xx = 1.f - ty2 - tz2;
		M.xy = txy - twz;
		M.xz = txz + twy;

		//Second row
		M.yx = txy + twz;
		M.yy = 1.f - tx2 - tz2;
		M.yz = tyz - twx;

		//Third row
		M.zx = txz - twy;
		M.zy = tyz + twx;
		M.zz = 1.f - tx2 - ty2;

		return M;
	}

	//Quaternion is a rotation around axis v by theta
	//s is cos(theta/2) and v.Length() is sin(theta/2)
	//This returns theta in range -PI to PI
	REAL GetAngle()
	{
		REAL theta, cosx, sinx;
		cosx = s;
		sinx = v.Length();
		if(sinx == 0.f) return 0.f;
		theta = 2.f * atan2(sinx, cosx);
		while(theta >= (REAL)PI) theta -= 2.f * (REAL)PI;
		while(theta < -(REAL)PI) theta += 2.f * (REAL)PI;
		return theta;
	}

	//Finds the component of the quaternion rotation around axis vec
	//This returns theta around vec in range -PI to PI
	REAL GetAngleAroundVector(Vector vec)
	{
		REAL theta, cosx, sinx;
		if(vec.Normalize() == 0) return 0.f;
		if(s < 0.f) v = -v;
		sinx = v * vec;
		cosx = (REAL)sqrt(1. - sinx * sinx);
		if(sinx == 0.f) return 0.f;
		theta = 2.f * atan2(sinx, cosx);
		while(theta >= (REAL)PI) theta -= 2.f * (REAL)PI;
		while(theta < -(REAL)PI) theta += 2.f * (REAL)PI;
		return theta;
	}

	//Make a quaternion that is a rotation by theta around vec
	static Quaternion AroundVector(REAL theta, Vector vec)
	{
		theta *= .5f;
		if(vec.Normalize() == 0)
		 return Quaternion((REAL)1., (REAL)0., (REAL)0., (REAL)0.);
		else
		 return Quaternion(cos(theta), vec * sin(theta));
	}

	//Quaternion is a rotation around axis v by theta
	//s is cos(theta/2) and v.Length() is sin(theta/2)
	//This scales theta by scale to get a new rotation
	//about the same axis
	//Angle is reduce to range -PI to PI before scaling
	void ScaleRotation(REAL scale)
	{
		REAL theta, cosx, sinx;
		cosx = s;
		sinx = v.Length();
		if(sinx != 0.f) {
			theta = atan2(sinx, cosx);

			theta *= 2.f;
			while(theta >= (REAL)PI) theta -= 2.f * (REAL)PI;
			while(theta < -(REAL)PI) theta += 2.f * (REAL)PI;
			theta *= .5f;

			theta *= scale;

			v *= sin(theta) / sinx;
			s = cos(theta);
		}
	}

	////////////////////////////////////////////////////////////////
	//These functions return a unit rotation Quaternion about 1 axis
	//Rotations are all CCW looking down the axis of rotation
	//(in the minus direction)
	//You can build an arbitrary rotation by composing with
	//quaternion multiply.  Rotations are applied right to left
	static Quaternion RotX(REAL theta)
	{
		theta *= .5f;
		Quaternion R((REAL)cos(theta), (REAL)sin(theta), (REAL)0., (REAL)0.);
		return R;
	}

	static Quaternion RotY(REAL theta)
	{
		theta *= .5f;
		Quaternion R((REAL)cos(theta), (REAL)0., (REAL)sin(theta), (REAL)0.);
		return R;
	}

	static Quaternion RotZ(REAL theta)
	{
		theta *= .5f;
		Quaternion R((REAL)cos(theta), (REAL)0., (REAL)0., (REAL)sin(theta));
		return R;
	}

	//Normalizes the quaternion
	//Returns 0 if quaternion length is 0, else 1
	inline int Normalize()
	{
		double t;

		t = s * (double)s + v.LengthSquared();
		if(t == 0.) return 0;
		t = 1. / sqrt(t);
		s *= (REAL)t;
		v *= (REAL)t;

		return 1;
	}

	/////////////////////////////////////////
	//Returns the conjugate of the quaternion
	//Same as Inverse for unit quaternions
	inline Quaternion Conjugate()
	{
		Quaternion R;
		R.s = s;
		R.v = -v;
		return R;
	}

	/////////////////////////////////////////
	//Returns the inverse rotation quaternion
	inline Quaternion Inverse()
	{
		double t;
		Quaternion R;

		t = s * (double)s + v.LengthSquared();
		if(t != 0.) t = 1. / t;	//Don't divide by zero~
		R.s = s * (REAL)t;
		R.v = -v * (REAL)t;
		return R;
	}

	///////////////////////////////////////////////////////
	//Assumes this quaternion is a unit rotation quaternion
	//Applies that rotation to P to get a rotated vector
	inline Vector Rotate(Vector P)
	{
		//Turn P into an imaginary quaternion
//		Quaternion Q;
//		Q.s = 0.f;
//		Q.v = P;
//		Q = *this * Q * this->Conjugate();
//		return Q.v;

		//Above can be simplified knowing that Q.s = 0:
		return P * (s * s - (v * v)) + v * (2.f * (v * P)) + (v ^ P) * (2.f * s);
	}

	///////////
	//Conjugate
	//Operator unary !
	inline Quaternion operator!()
	{
		return Conjugate();
	}

	/////////////////////////
	//Operator * (Vector)
	//Rotates the vector
	inline Vector operator*(const Vector P)
	{
		return Rotate(P);
	}

	/////////////////////////
	//Operator * (Quaternion)
	inline Quaternion operator*(const Quaternion Q)
	{
		Quaternion R;
		//R = this * Q
		R.s = s * Q.s - v * Q.v;
		R.v = v ^ Q.v;	//Cross product
		R.v += (Vector)Q.v * s + v * Q.s;
		return R;
	}

	//////////////////////////
	//Operator *= (Quaternion)
	inline void operator*=(const Quaternion Q)
	{
		*this = *this * Q;
	}

	/////////////////////////
	//Operator + (Quaternion)
	inline Quaternion operator+(const Quaternion Q)
	{
		Quaternion R;
		//R = this + Q
		R.s = s + Q.s;
		R.v = v + Q.v;
		return R;
	}

	//////////////////////////
	//Operator += (Quaternion)
	inline void operator+=(const Quaternion Q)
	{
		*this = *this + Q;
	}

	/////////////////////////
	//Operator - (Quaternion)
	inline Quaternion operator-(const Quaternion Q)
	{
		Quaternion R;
		//R = this - Q
		R.s = s - Q.s;
		R.v = v - Q.v;
		return R;
	}

	//////////////////////////
	//Operator -= (Quaternion)
	inline void operator-=(const Quaternion Q)
	{
		*this = *this - Q;
	}

	/////////////////
	//Vector negation
	//Operator unary -
	inline Quaternion operator-()
	{
		Quaternion R;
		//R = -this
		R.s = -s;
		R.v = -v;
		return R;
	}

	/////////////////////
	//Operator * (Scalar)
	inline Quaternion operator*(const REAL S)
	{
		Quaternion R;
		R.s = s * S;
		R.v = v * S;
		return R;
	}

	//////////////////////
	//Operator *= (Scalar)
	inline void operator*=(const REAL S)
	{
		s *= S;
		v *= S;
	}

	/////////////////////
	//Operator / (Scalar)
	inline Quaternion operator/(const REAL S)
	{
		REAL inv = 1.f / S;
		return *this * inv;
	}

	//////////////////////
	//Operator /= (Scalar)
	inline void operator/=(const REAL S)
	{
		REAL inv = 1.f / S;
		*this *= inv;
	}
};

#endif

#endif
