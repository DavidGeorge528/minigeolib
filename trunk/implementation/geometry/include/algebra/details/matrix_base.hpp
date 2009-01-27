#ifndef ALGEBRA_DETAILS_MATRIX_BASE_HPP
#define ALGEBRA_DETAILS_MATRIX_BASE_HPP

namespace algebra
{
namespace details
{

/// \ingroup algebra
/// \brief It is the base class for matrix implementation. It provides the common utility functions and type aliases 
///		used by matrix specializations. Defined for reusability.
template< unsigned R, unsigned C, typename U, typename UT>
class matrix_base
{
public:
	enum 
	{ 
		ROWS = R,		///< The number of rows in the matrix.
		COLUMNS = C		///< The number of columns in the matrix.
	};

	typedef UT unit_traits_type;
	typedef typename unit_traits_type::unit_type unit_type;
};

} // namespace details
} // namespace algebra

#endif // ALGEBRA_DETAILS_MATRIX_BASE_HPP
