#ifndef ALGEBRA_MATRIX_4_4_HPP
#define ALGEBRA_MATRIX_4_4_HPP

#include "algebra/details/matrix_base.hpp"

namespace algebra
{

template< typename U, typename UT>
class matrix< 4, 4, U, UT>: public details::matrix_base< 4,4,U,UT>
{
public:
	matrix()
	{
		a11_ = a12_ = a13_ = a14_ = a21_ = a22_ = a23_ = a24_ = a31_ = a32_ = a33_ = a34_ = a41_ = a42_ = a43_ = a44_ 
			= unit_traits_type::zero();
	}

	/// \brief It initializes the matrix with its elements.
	matrix(
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: a11_( a11), a12_( a12), a13_( a13), a14_( a14)
		, a21_( a21), a22_( a22), a23_( a23), a24_( a24)
		, a31_( a31), a32_( a32), a33_( a33), a34_( a34)
		, a41_( a41), a42_( a42), a43_( a43), a44_( a44)
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
			unit_type a11_, a12_, a13_, a14_;
			unit_type a21_, a22_, a23_, a24_;
			unit_type a31_, a32_, a33_, a34_;
			unit_type a41_, a42_, a43_, a44_;
		};
		unit_type m_[4][4];
	};
};

} // namespace algebra

#endif // ALGEBRA_MATRIX_4_4_HPP
