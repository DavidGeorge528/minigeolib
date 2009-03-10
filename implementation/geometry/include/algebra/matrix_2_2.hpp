#ifndef ALGEBRA_MATRIX_2_2_HPP
#define ALGEBRA_MATRIX_2_2_HPP

namespace algebra
{

/// \ingroup algebra
/// \copydoc matrix
template< typename U, typename UT>
class matrix< 2, 2, U, UT>: public details::matrix_base< 2, 2, U, UT>
{
	friend class vector< 2, U, UT>;
public:
	/// \brief It initializes a zero matrix.
	matrix()
	{
		a11_ = a12_ = a21_ = a22_ = unit_traits_type::zero();
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
		const unit_type& a11, const unit_type& a12, 
		const unit_type& a21, const unit_type& a22)
		: a11_( a11), a12_( a12) 
		, a21_( a21), a22_( a22)
	{
	}

	/// \details
	///		In case of self assigning, it does nothing.
	matrix& operator=( const matrix& op)
	{
		if( this != &op)
		{
			a11_ = op.a11_; a12_ = op.a12_;
			a21_ = op.a21_; a22_ = op.a22_;
		}
		return *this;
	}


	/// \brief It provides index based access to matrix elements.
	/// \param r the row number of the element (zero based index).
	/// \param c the column number of the element (zero based index).
	/// \{
	unit_type& operator()( unsigned r, unsigned c)
	{
		return m_[r][c];
	}

	const unit_type& operator()( unsigned r, unsigned c) const
	{
		return m_[r][c];
	}
	/// \}

	/// \brief It creates an identity matrix.
	/// \details
	///		The identity matrix is created only when called for the first time.
	/// \warning
	///		This method is not thread safe. If two threads call this method at the same time for the first time, there 
	///		will be a racing condition and undefined behavior may occur.
	static const matrix& IDENTITY()
	{
		static const matrix I( 1, 0, 0, 1);
		return I;
	}

	/// \brief Addition of two matrices.
	friend matrix operator+( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ + right_op.a11_, left_op.a12_ + right_op.a12_,
			left_op.a21_ + right_op.a21_, left_op.a22_ + right_op.a22_);
	}

	/// \brief Addition of two matrices.
	matrix& operator+=( const matrix& right_op)
	{
		a11_ += right_op.a11_; a12_ += right_op.a12_;
		a21_ += right_op.a21_; a22_ += right_op.a22_;
		return *this;
	}

	/// \brief Subtraction of two matrices.
	friend matrix operator-( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ - right_op.a11_, left_op.a12_ - right_op.a12_,
			left_op.a21_ - right_op.a21_, left_op.a22_ - right_op.a22_);
	}

	/// \brief Subtraction of two matrices.
	matrix& operator-=( const matrix& right_op)
	{
		a11_ -= right_op.a11_; a12_ -= right_op.a12_;
		a21_ -= right_op.a21_; a22_ -= right_op.a22_;
		return *this;
	}


	/// \brief Multiplication of two matrices.
	friend matrix operator*( const matrix& left_op, const matrix& right_op)
	{
#define E( i, j) a##i##j
#define ELEM( i, j) \
	left_op.E(i,1)_ * right_op.E(1,j)_ + \
	left_op.E(i,2)_ * right_op.E(2,j)_ 

		return matrix(
			ELEM( 1, 1), ELEM( 1, 2),
			ELEM( 2, 1), ELEM( 2, 2));

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
			s * right_op.a11_, s * right_op.a12_,
			s * right_op.a21_, s * right_op.a22_);
	}

	/// \brief Multiplication with a scalar.
	friend matrix operator*( const matrix& left_op, const unit_type& s)
	{
		return s * left_op;
	}

	/// \brief Multiplication with a scalar.
	matrix& operator*=( const unit_type& s)
	{
		a11_ *= s; a12_ *= s;
		a21_ *= s; a22_ *= s; 
		return *this;
	}

	/// \brief Division by a scalar.
	friend matrix operator/( const matrix& left_op, const unit_type& s)
	{
		return matrix( 
			left_op.a11_ / s, left_op.a12_ / s,
			left_op.a21_ / s, left_op.a22_ / s);
	}

	/// \brief Division by a scalar.
	matrix& operator/=( const unit_type& s)
	{
		a11_ /= s; a12_ /= s;
		a21_ /= s; a22_ /= s;
		return *this;
	}

	/// \brief Matrix transpozition.
	/// \return the transposition result, as a new matrix. The original one remains untouched.
	friend matrix transposed( const matrix& m)
	{
		return matrix(
			m.a11_, m.a21_, 
			m.a12_, m.a22_);
	}

	/// \brief Transposes this matrix.
	/// \return this matrix, transposed.
	matrix& transpose()
	{
		unit_type t;

#define E( i, j) a##i##j
#define TR( i, j) t = E(i,j)_; E(i,j)_ = E(j,i)_; E(j,i)_ = t;

		TR(1,2); 

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
		return a11_*a22_ - a12_*a21_;
	}

private:
	union
	{
		struct 
		{
			unit_type a11_, a12_;
			unit_type a21_, a22_;
		};
		unit_type m_[2][2];
	};
};

} // namespace algebra

#endif // ALGEBRA_MATRIX_2_2_HPP
