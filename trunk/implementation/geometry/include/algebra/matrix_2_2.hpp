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

	matrix(
		const unit_type& a11, const unit_type& a12, 
		const unit_type& a21, const unit_type& a22)
		: a11_( a11), a12_( a12) 
		, a21_( a21), a22_( a22)
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
		static matrix I( 1, 0, 0, 1);
		return I;
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
