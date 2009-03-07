#ifndef ALGEBRA_MATRIX_3_3_HPP
#define ALGEBRA_MATRIX_3_3_HPP

namespace algebra
{

/// \ingroup algebra
/// \copydoc template< unsigned R, unsigned C, typename U, typename UT> matrix< R, C, U, UT> 
template< typename U, typename UT>
class matrix< 3, 3, U, UT>: public details::matrix_base< 3, 3, U, UT>
{
public:
	/// \brief It initializes a zero matrix.
	matrix()
	{
		a11_ = a12_ = a13_ = a21_ = a22_ = a23_ = a31_ = a32_ = a33_
			= unit_traits_type::zero();
	}

	/// \brief It initializes a matrix using the sequence of elements pointed by the provided iterators.
	/// \pre The provided sequence is of the size of matrix.
	/// \tparam It the type of iterator providing access to the sequence of elements.
	/// \details
	///		The order of the elements to be used for the initialization should be from left to right, top to bottom.
	template< typename It>
	matrix( It begin, It end)
	{
		assert( ROWS*COLUMNS == std::distance( begin, end));
		for( unsigned int r = 0; r < ROWS; ++r)
		{
			for( unsigned int c = 0; c < COLUMNS; ++c, ++begin)
			{
				m_[r][c] = *begin;
			}
		}
	}

	/// \brief It initializes a matrix using a sequence of the elements pointed by the provided iterator.
	/// \pre The provided sequence is at least of the size of matrix.
	/// \tparam It the type of iterator providing access to the sequence of elements.
	/// \details
	///		The order of the elements to be used for the initialization should be from left to right, top to bottom.
	template< typename It>
	matrix( It begin)
	{
		for( unsigned int r = 0; r < ROWS; ++r)
		{
			for( unsigned int c = 0; c < COLUMNS; ++c, ++begin)
			{
				m_[r][c] = *begin;
			}
		}
	}


	/// \brief It initializes the matrix with the provided content.
	matrix(
		const unit_type& a11, const unit_type& a12, const unit_type& a13,
		const unit_type& a21, const unit_type& a22, const unit_type& a23,
		const unit_type& a31, const unit_type& a32, const unit_type& a33)
		: a11_( a11), a12_( a12), a13_( a13)
		, a21_( a21), a22_( a22), a23_( a23)
		, a31_( a31), a32_( a32), a33_( a33)
	{
	}

	/// \details
	///		In case of self assigning, it does nothing.
	matrix& operator=( const matrix& op)
	{
		if( this != &op)
		{
			a11_ = op.a11_; a12_ = op.a12_; a13_ = op.a13_; 
			a21_ = op.a21_; a22_ = op.a22_; a23_ = op.a23_; 
			a31_ = op.a31_; a32_ = op.a32_; a33_ = op.a33_;
		}
		return *this;
	}

	/// \brief It provides index based access to matrix elements.
	/// \param r the row number of the element (zero based index).
	/// \param c the column number of the element (zero based index).
	unit_type& operator()( unsigned r, unsigned c)
	{
		return m_[r][c];
	}

	/// \copydoc operator()( unsigned, unsigned)
	const unit_type& operator()( unsigned r, unsigned c) const
	{
		return m_[r][c];
	}

	/// \brief It creates an identity matrix.
	/// \details
	///		The identity matrix is created only when called for the first time.
	/// \warning
	///		This method is not thread safe. If two threads call this method at the same time for the first time, there 
	///		will be a racing condition and undefined behavior may occur.
	static const matrix& IDENTITY()
	{
		static matrix I( 
			1, 0, 0, 
			0, 1, 0,
			0, 0, 1);
		return I;
	}

	/// \brief It adds two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	friend matrix operator+( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ + right_op.a11_, left_op.a12_ + right_op.a12_, left_op.a13_ + right_op.a13_,
			left_op.a21_ + right_op.a21_, left_op.a22_ + right_op.a22_, left_op.a23_ + right_op.a23_,
			left_op.a31_ + right_op.a31_, left_op.a32_ + right_op.a32_, left_op.a33_ + right_op.a33_);
	}

	/// \brief It adds two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	matrix& operator+=( const matrix& right_op)
	{
		a11_ += right_op.a11_; a12_ += right_op.a12_; a13_ += right_op.a13_;
		a21_ += right_op.a21_; a22_ += right_op.a22_; a23_ += right_op.a23_;
		a31_ += right_op.a31_; a32_ += right_op.a32_; a33_ += right_op.a33_;
		return *this;
	}


	/// \brief It subtracts two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	friend matrix operator-( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ - right_op.a11_, left_op.a12_ - right_op.a12_, left_op.a13_ - right_op.a13_,
			left_op.a21_ - right_op.a21_, left_op.a22_ - right_op.a22_, left_op.a23_ - right_op.a23_,
			left_op.a31_ - right_op.a31_, left_op.a32_ - right_op.a32_, left_op.a33_ - right_op.a33_);
	}

	/// \brief It subtracts two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	matrix& operator-=( const matrix& right_op)
	{
		a11_ -= right_op.a11_; a12_ -= right_op.a12_; a13_ -= right_op.a13_;
		a21_ -= right_op.a21_; a22_ -= right_op.a22_; a23_ -= right_op.a23_;
		a31_ -= right_op.a31_; a32_ -= right_op.a32_; a33_ -= right_op.a33_;
		return *this;
	}

	/// \brief Multiplication of two matrices.
	friend matrix operator*( const matrix& left_op, const matrix& right_op)
	{
#define E( i, j) a##i##j
#define ELEM( i, j) \
	left_op.E(i,1)_ * right_op.E(1,j)_ + \
	left_op.E(i,2)_ * right_op.E(2,j)_ + \
	left_op.E(i,3)_ * right_op.E(3,j)_

		return matrix(
			ELEM( 1, 1), ELEM( 1, 2), ELEM( 1, 3),
			ELEM( 2, 1), ELEM( 2, 2), ELEM( 2, 3),
			ELEM( 3, 1), ELEM( 3, 2), ELEM( 3, 3));

#undef ELEM
#undef E
	}

	/// \brief Multiplication of two matrices.
	matrix& operator*=( const matrix& right_op)
	{
		matrix r( operator*( *this, right_op));
		*this = r;
		return *this;
	}

	/// \brief Multiplication with a scalar.
	friend matrix operator*( const unit_type& s, const matrix& right_op)
	{
		return matrix( 
			s * right_op.a11_, s * right_op.a12_, s * right_op.a13_,
			s * right_op.a21_, s * right_op.a22_, s * right_op.a23_,
			s * right_op.a31_, s * right_op.a32_, s * right_op.a33_);
	}

	/// \brief Multiplication with a scalar.
	friend matrix operator*( const matrix& left_op, const unit_type& s)
	{
		return s * left_op;
	}

	/// \brief Multiplication with a scalar.
	matrix& operator*=( const unit_type& s)
	{
		a11_ *= s; a12_ *= s; a13_ *= s;
		a21_ *= s; a22_ *= s; a23_ *= s;
		a31_ *= s; a32_ *= s; a33_ *= s;
		return *this;
	}

	/// \brief Division by a scalar.
	friend matrix operator/( const matrix& left_op, const unit_type& s)
	{
		return matrix( 
			left_op.a11_ / s, left_op.a12_ / s, left_op.a13_ / s,
			left_op.a21_ / s, left_op.a22_ / s, left_op.a23_ / s,
			left_op.a31_ / s, left_op.a32_ / s, left_op.a33_ / s);
	}

	/// \brief Division by a scalar.
	matrix& operator/=( const unit_type& s)
	{
		a11_ /= s; a12_ /= s; a13_ /= s;
		a21_ /= s; a22_ /= s; a23_ /= s;
		a31_ /= s; a32_ /= s; a33_ /= s;
		return *this;
	}

	/// \brief Matrix transpozition.
	/// \return the transposition result, as a new matrix. The original one remains untouched.
	friend matrix transposed( const matrix& m)
	{
		return matrix(
			m.a11_, m.a21_, m.a31_, 
			m.a12_, m.a22_, m.a32_, 
			m.a13_, m.a23_, m.a33_);
	}

	/// \brief Transposes this matrix.
	/// \return this matrix, transposed.
	matrix& transpose()
	{
		unit_type t;

#define E( i, j) a##i##j
#define TR( i, j) t = E(i,j)_; E(i,j)_ = E(j,i)_; E(j,i)_ = t;

		TR(1,2); TR(1,3); 
		TR(2,3); 

#undef TR
#undef E

		return *this;
	}

	/// \brief It calculates the determinant of the given matrix.
	friend unit_type det( const matrix& m)
	{
		return m.det();
	}

	/// \brief It calculates the determinant of this matrix.
	unit_type det() const
	{
		return a11_*( a22_*a33_ - a32_*a23_) - a21_*(a12_*a33_ - a32_*a13_) + a31_*(a12_*a23_ - a22_*a13_);
	}

private:
	union
	{
		struct 
		{
			unit_type a11_, a12_, a13_;
			unit_type a21_, a22_, a23_;
			unit_type a31_, a32_, a33_;
		};
		unit_type m_[3][3];
	};
};

} // namespace algebra

#endif // ALGEBRA_MATRIX_3_3_HPP
