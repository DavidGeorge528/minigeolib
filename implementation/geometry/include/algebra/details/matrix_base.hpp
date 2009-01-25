#ifndef ALGEBRA_DETAILS_MATRIX_BASE_HPP
#define ALGEBRA_DETAILS_MATRIX_BASE_HPP

namespace algebra
{
namespace details
{

template< unsigned R, unsigned C, typename U, typename UT>
class matrix_base
{
public:
	enum { ROWS = R, COLUMNS = C };
	typedef UT unit_traits_type;
	typedef typename unit_traits_type::unit_type unit_type;

protected:
	vector_base()
	{
	}

protected:
	unit_type m_[R][C];
};

} // namespace details
} // namespace algebra

#endif // ALGEBRA_DETAILS_MATRIX_BASE_HPP
