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

	/// \brief It checks whether the given value is zero or close to zero.
	static bool is_zero( const unit_type& value)
	{
		return -std::numeric_limits< unit_type>::min() < value 
			&& value < std::numeric_limits< unit_type>::min();
	}

	/// \brief It checks whether the given value is not a number.
	/// \details
	///		It relies on numerical limits for getting that. If the unit_type doesn't have support for NaN 
	///		representation, this method will always return false.
	static bool not_a_number( const unit_type& value)
	{
		return 
			(std::numeric_limits< unit_type>::has_quiet_NaN && std::numeric_limits< unit_type>::quiet_NaN() == value)
			||
			(std::numeric_limits< unit_type>::has_signaling_NaN && std::numeric_limits< unit_type>::signaling_NaN() == value);
	}

	/// \brief It checks whether the given value is infinity.
	/// \details
	///		It relies on numerical limits for getting that. If the unit_type doesn't have support for infinity
	///		representation, this method will always return false.
	static bool is_infinity( const unit_type& value)
	{
		return
			std::numeric_limits< unit_type>::has_infinity && std::numeric_limits<unit_type>::infinity() == value;
	}

	/// \brief It checks whether the given value is valid (not infinity or NaN).
	static bool is_valid_number( const unit_type& value)
	{
		return !(not_a_number( value) || is_infinity( value));
	}
};

} // namespace algebra

#endif // ALG_UNIT_TRAITS_HPP
