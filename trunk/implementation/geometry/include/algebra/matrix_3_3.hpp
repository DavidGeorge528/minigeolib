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
