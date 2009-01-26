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
