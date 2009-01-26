#ifndef ALGEBRA_MATRIX_2_2_HPP
#define ALGEBRA_MATRIX_2_2_HPP

namespace algebra
{

template< typename U, typename UT>
class matrix< 2, 2, U, UT>: public details::matrix_base< 2, 2, U, UT>
{
public:
	matrix()
	{
		a11_ = a12_ = a21_ = a22_ = unit_traits_type::zero();
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

	matrix(
		const unit_type& a11, const unit_type& a12, 
		const unit_type& a21, const unit_type& a22)
		: a11_( a11), a12_( a12) 
		, a21_( a21), a22_( a22)
	{
	}

	matrix& operator=( const matrix& op)
	{
		if( this != &op)
		{
			a11_ = op.a11_; a12_ = op.a12_;
			a21_ = op.a21_; a22_ = op.a22_;
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
		static matrix I( 1, 0, 0, 1);
		return I;
	}

	/// \brief It adds two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	friend matrix operator+( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ + right_op.a11_, left_op.a12_ + right_op.a12_,
			left_op.a21_ + right_op.a21_, left_op.a22_ + right_op.a22_);
	}

	/// \brief It adds two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	matrix& operator+=( const matrix& right_op)
	{
		a11_ += right_op.a11_; a12_ += right_op.a12_;
		a21_ += right_op.a21_; a22_ += right_op.a22_;
		return *this;
	}


	/// \brief It subtracts two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	friend matrix operator-( const matrix& left_op, const matrix& right_op)
	{
		return matrix( 
			left_op.a11_ - right_op.a11_, left_op.a12_ - right_op.a12_,
			left_op.a21_ - right_op.a21_, left_op.a22_ - right_op.a22_);
	}

	/// \brief It subtracts two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	matrix& operator-=( const matrix& right_op)
	{
		a11_ -= right_op.a11_; a12_ -= right_op.a12_;
		a21_ -= right_op.a21_; a22_ -= right_op.a22_;
		return *this;
	}


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

	matrix& operator*=( const matrix& right_op)
	{
		matrix r( operator*( *this, right_op));
		*this = r;
		return *this;
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
