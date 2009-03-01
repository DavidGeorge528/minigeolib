#ifndef ALG_UNIT_TRAITS_HPP
#define ALG_UNIT_TRAITS_HPP

#include <limits>

namespace algebra
{

/// \ingroup algebra
/// \brief It provides utility methods specific to the type parameter.
/// \tparam U the arithmetic type supported.
template< typename U>
struct unit_traits
{
	typedef U unit_type;

	/// \brief It gets the value zero (neutral to addition).
	static U zero() { return 0; }

	/// \brief It gets the value one (neutral to multiplication).
	static U one() { return 1; }

	// TODO: Test
	static bool is_zero( const unit_type& value)
	{
		return -std::numeric_limits< unit_type>::min() < value 
			&& value < std::numeric_limits< unit_type>::min();
	}
};

} // namespace algebra

#endif // ALG_UNIT_TRAITS_HPP
