#ifndef ALGEBRA_MATRIX_3_3_HPP
#define ALGEBRA_MATRIX_3_3_HPP

namespace algebra
{

template< typename U, typename UT>
class matrix< 3, 3, U, UT>: public details::matrix_base< 3, 3, U, UT>
{
public:
	matrix()
	{
		a11_ = a12_ = a13_ = a21_ = a22_ = a23_ = a31_ = a32_ = a33_
			= unit_traits_type::zero();
	}

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


	/// \brief It initializes the matrix with its elements.
	matrix(
		const unit_type& a11, const unit_type& a12, const unit_type& a13,
		const unit_type& a21, const unit_type& a22, const unit_type& a23,
		const unit_type& a31, const unit_type& a32, const unit_type& a33)
		: a11_( a11), a12_( a12), a13_( a13)
		, a21_( a21), a22_( a22), a23_( a23)
		, a31_( a31), a32_( a32), a33_( a33)
	{
	}

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

	unit_type& operator()( unsigned r, unsigned c)
	{
		return m_[r][c];
	}

	const unit_type& operator()( unsigned r, unsigned c) const
	{
		return m_[r][c];
	}

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

	matrix& operator*=( const matrix& right_op)
	{
		matrix r( operator*( *this, right_op));
		*this = r;
		return *this;
	}

	friend matrix operator*( const unit_type& s, const matrix& right_op)
	{
		return matrix( 
			s * right_op.a11_, s * right_op.a12_, s * right_op.a13_,
			s * right_op.a21_, s * right_op.a22_, s * right_op.a23_,
			s * right_op.a31_, s * right_op.a32_, s * right_op.a33_);
	}

	friend matrix operator*( const matrix& left_op, const unit_type& s)
	{
		return s * left_op;
	}

	matrix& operator*=( const unit_type& s)
	{
		a11_ *= s; a12_ *= s; a13_ *= s;
		a21_ *= s; a22_ *= s; a23_ *= s;
		a31_ *= s; a32_ *= s; a33_ *= s;
		return *this;
	}


	friend matrix operator/( const matrix& left_op, const unit_type& s)
	{
		return matrix( 
			left_op.a11_ / s, left_op.a12_ / s, left_op.a13_ / s,
			left_op.a21_ / s, left_op.a22_ / s, left_op.a23_ / s,
			left_op.a31_ / s, left_op.a32_ / s, left_op.a33_ / s);
	}

	matrix& operator/=( const unit_type& s)
	{
		a11_ /= s; a12_ /= s; a13_ /= s;
		a21_ /= s; a22_ /= s; a23_ /= s;
		a31_ /= s; a32_ /= s; a33_ /= s;
		return *this;
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
