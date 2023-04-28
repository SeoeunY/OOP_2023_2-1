namespace ooplinalg {
	class Matrix {
	private:
		float** data;
		int rows;
		int cols;

	public:
		Matrix();
		Matrix(const Matrix& mat);
		Matrix(int rows, int cols);
		~Matrix();

		float getElement(int row, int col) const;
		float** getData() const;
		void setElement(const int row, const int col, float value);
		void setData(const int rows, const int cols, float** data);
		void setRows(const int rows);
		int getRows() const;
		void setCols(const int cols);
		int getCols() const;

		float determinant();
	};

	Matrix& add(Matrix& r, Matrix& a, Matrix& b);
	Matrix& sub(Matrix& r, Matrix& a, Matrix& b);
	Matrix& mul(Matrix& r, Matrix& a, Matrix& b);

	Matrix& elementAdd(Matrix& r, Matrix& a, float v);
	Matrix& elementSub(Matrix& r, Matrix& a, float v);
	Matrix& elementMul (Matrix& r, Matrix& a, float v);
	Matrix& elementDiv(Matrix& r, Matrix& a, float v);

	Matrix& transpose(Matrix& r, Matrix& m);
	Matrix& adjoint(Matrix& r, Matrix& m);
	Matrix& inverse(Matrix& r, Matrix& m);
}