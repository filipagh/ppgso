// BigMat.h
// Class for big matrices and vectors
// Copyright (c) 2006, Secret Software
// Written by Edwin P. Berlin, Jr.

//All matrices and vectors are 0-based

#ifndef __BIGMAT__
#define __BIGMAT__

//Some macros for printing a CBigMat or a CBigVec

#define PRINT_MATRIX(mat, name)													\
	{																			\
		printf("\n%s(%d x %d) =\n", name, mat.nrow, mat.ncol);					\
		for(int i = 0; i < mat.nrow; ++i) {										\
			for(int j = 0; j < mat.ncol; ++j) printf("\t% 12g", mat[i][j]);		\
			printf("\n");														\
		}																		\
	}

#define PRINT_VECTOR(vec, name)												\
	{																		\
		printf("\n%s(%d) =\n", name, vec.nrow);								\
		for(int i = 0; i < vec.nrow; ++i) printf("\t% 12g", vec[i]);		\
		printf("\n");														\
	}


//Possible values for error member of CBigVec or CBigMat:
#define BM_OK				0
#define BM_MEMORY			1
#define BM_NOT_SQUARE		2
#define BM_WRONG_SIZE		3
#define BM_SINGULAR			4
#define BM_CONVERGENCE		5

//Forward reference
class CBigMat;

//Column vector
class CBigVec
{
	//The data for this class
protected:
	int size;
public:
	double *V;		//Points to array of nrow doubles
	int nrow;
	int error;		//0 means no error

public:
	~CBigVec() { if(V) delete[] V; }

	CBigVec()
	{
		V = 0;
		error = nrow = size = 0;
	}

	//Constructors
	CBigVec(int Nrow);
	CBigVec(CBigVec &A);
	CBigVec(int Nrow, float *array);
	CBigVec(int Nrow, double *array);

	//Initialize this vector from a matrix
	//If matrix is m x n, the vector is length m * n
	CBigVec(CBigMat &M);

	void Zero();

	double &operator [](int row) { return V[row]; }

	//Extract a row or column from a CBigMat
	void GetRow(int row, CBigMat &A);
	void GetCol(int col, CBigMat &A);

	//Change the size
	//Does not retain values
	void Resize(int Nrow);

	//Changes size, retaining values and
	//zeroing any new elements
	void ShrinkExpand(int Nrow);

	//Returns a string representing the error code
	char *GetError();

	//////
	//Copy
	//Operator =
	CBigVec& operator=(CBigVec &A);

	/////////////////
	//Vector addition
	//Operator +=
	CBigVec& operator+=(CBigVec &A);

	////////////////////
	//Vector subtraction
	//Operator -=
	CBigVec& operator-=(CBigVec &A);

	/////////////////////////////
	//Multiply vector by a scalar
	//Operator *= (Scalar)
	CBigVec& operator*=(double s);

	///////////////////////////
	//Divide vector by a scalar
	//Operator /= (Scalar)
	CBigVec& operator/=(double s);

	/////////////////
	//Vector addition
	//Operator +
	CBigVec operator+(CBigVec &A);

	////////////////////
	//Vector subtraction
	//Operator -
	CBigVec operator-(CBigVec &A);

	/////////////////
	//Vector negation
	//Operator unary -
	CBigVec operator-();

	//////////////////////////////////
	//Left multiply vector by a matrix
	//Operator * (CBigMat)
	CBigVec operator*(CBigMat &M);

	/////////////
	//Dot product
	//Operator * (CBigVec)
	double operator*(CBigVec &A);

	/////////////////////////////
	//Multiply vector by a scalar
	//Operator * (Scalar)
	CBigVec operator*(double s);

	///////////////////////////
	//Divide vector by a scalar
	//Operator / (Scalar)
	CBigVec operator/(double s);

	//////////////////////
	//Vector cross product
	//Operator ^ (Cross product)
	//Only valid for 3 dimensional vectors
	//(It's possible to compute a cross product for 7 dimensions,
	//but this routine won't do it until someone finds a use for it.
	//No other dimension of cross products are possible.)
	CBigVec operator^(CBigVec &A);

	//Transpose this column vector to get a row matrix
	CBigMat operator !();
};

class CBigMat
{
	//The data for this class
protected:
	int size;
public:
	double *M;		//Points to array of nrow x ncol doubles
	int nrow, ncol;
	int error;		//0 means no error

public:
	~CBigMat() { if(M) delete[] M; }

	CBigMat()
	{
		M = 0;
		error = nrow = ncol = size = 0;
	}

	//Use these constructors for matrices
	CBigMat(int Nrow, int Ncol);
	CBigMat(CBigMat &A);

	//Use these constructors for vectors
	CBigMat(int Ncol);
	CBigMat(CBigVec &A);

	//Use these constructors to initialize from array of arrays
	CBigMat(int Nrow, int Ncol, double **array);
	CBigMat(int Nrow, int Ncol, float **array);
	//Use these constructors to initialize from one dimensional array
	CBigMat(int Nrow, int Ncol, double *array);
	CBigMat(int Nrow, int Ncol, float *array);

	//Change the size
	//Does not retain values
	void Resize(int Nrow, int Ncol);

	//Changes size, retaining values and
	//zeroing any new elements
	void ShrinkExpand(int Nrow, int Ncol);

	//Returns a string representing the error code
	char *GetError();

	//////
	//Copy
	//Operator =
	CBigMat& operator =(CBigMat &A);

	//Either of these return a pointer to specified row
	double *Row(int row) { return M + row * ncol; }
	double *operator [](int row) { return M + row * ncol; }

	void Zero();
	void Identity();

	bool IsSquare() { return nrow == ncol; }
	bool IsSameSize(CBigMat &A) { return nrow == A.nrow && ncol == A.ncol; }

	//Set a row or a column from an array of floats
	void SetRow(int row, float *array);
	void SetCol(int col, float *array);
	//Set a row or a column from an array of doubles
	void SetRow(int row, double *array);
	void SetCol(int col, double *array);
	//Set a row or a column from a CBigVec
	void SetRow(int row, CBigVec &A);
	void SetCol(int col, CBigVec &A);

	//Extract submatrix of A to M or
	//insert A into submatrix of M
	//Upper left corner of submatrix is at row, col in larger matrix
	void SubMatrix(CBigMat &A, int row, int col);

	//M += A
	//Sizes must be the same
	CBigMat& operator +=(CBigMat &A);

	//M -= A
	//Sizes must be the same
	CBigMat& operator -=(CBigMat &A);

	//M *= s
	//Scalar multiply
	CBigMat& operator *=(double s);

	//Scalar multiply
	//R = M * s
	CBigMat operator *(double s);

	//Vector multiply
	//R = M * A
	//Sizes must be valid
	CBigVec operator *(CBigVec &A);

	//R = M * A
	//Sizes must be valid
	CBigMat operator *(CBigMat &A);

	//Transpose
	//Returns Mt without modifying M
	CBigMat operator !();

	//M = Mt
	CBigMat& Transpose();

	//Returns the diagonal of M
	CBigVec Diagonal();

	//Makes M a square diagonal matrix with
	//diagonal A and zeroes elsewhere
	CBigMat& DiagonalMatrix(CBigVec &A);

	//Sets the diagonal of M to A
	//does not alter other elements of M
	//If A is too short, the rest of the diagonal is unchanged
	CBigMat& SetDiagonal(CBigVec &A);

	//Gaussian-Jordan elimination with full pivoting
	//M = Ainv
	//From numerical recipes in C
	//Special case of B = I
	//Errors if matrix not invertible, A not square
	//Returns true if successful and matrix not singular
	//It's OK for A to be M
	bool Inverse(CBigMat &A);

	//Same as above, but M = Minv
	//Returns true if successful and matrix not singular
	bool Inverse();

	//Singular value decomposition
	//Finds U, S, V that satisfy
	//M = U * DiagonalMatrix(S) * !V
	//Return value is rank
	//Given M, size m x n:
	//When Truncate is true, the resulting sizes are:
	//U is m x rank
	//DiagonalMatrix(S) is rank x rank
	//V is n x rank
	//
	//When Truncate is false, the resulting sizes are:
	//U is m x n
	//DiagonalMatrix(S) is n x n
	//V is n x n
	//U and V are each orthogonal
	//The first rank elements of S are > 0 and sorted largest first
	//Entries of S <= tolerance are set to 0
	int SVD(CBigMat &U, CBigVec &S, CBigMat &V, bool Truncate, double tolerance);

	//M = M+
	//M is an m x n matrix.  M+ is an n x m matrix.
	//Returns rank.  Maximum rank possible is Min(m,n)
	//tolerance passed to SVD
	//If M = U * DiagonalMatrix(S) * !V (from SVD), then
	//M+ = V * DiagonalMatrix(S) * !U
	//This is useful for solving M * P = T, P and T vectors,
	//as P = M+ * T.  If M is overconstrained, this gives a
	//least-squares fit.  If M is underconstrained (not full rank),
	//the extra degrees of freedom can be described with:
	//P = M+ * T + (I - M+ * M) * Y, where Y is any vector.
	//This can be written as
	//P = M+ * T + V * K, where K is any vector with the first rank
	//elements zero.  We can define Vr as the rightmost Min(m,n)
	//columns of V, giving
	//P = M+ * T + Vr * K, where K is now any (Min(m,n) - rank)-vector
	//Vr is returned if the second argument is not NULL and rank < Min(m,n)
	//Since V is n x Min(m,n), Vr is n x (Min(m,n) - rank)
	int PseudoInverse(CBigMat &Vr = *(CBigMat *)0, double tolerance = 1e-6);

	//Returns Determinant of M, 0. if M is singular or not square
	double Determinant();

	////////////////////////
	//Maybe eliminate these:

	//M = A * Bt
	//Sizes must be valid
	void MulTrans(CBigMat &A, CBigMat &B);

	//M = A B At
	void ABAt(CBigMat &A, CBigMat &B);
};

//Minimize || F(P) - X ||^2
//F(P) is same size as X
//J is |X| rows x |P| columns
//F and dF return false if there's an error
bool LevMar(CBigVec& P, CBigVec& X, bool (*F)(CBigVec& X, CBigVec& P), bool (*dF)(CBigMat& J, CBigVec& P));

#endif
