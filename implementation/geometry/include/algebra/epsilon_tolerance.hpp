#ifndef ALGEBRA_EPSILON_TOLERANCE_HPP
#define ALGEBRA_EPSILON_TOLERANCE_HPP

#include "algebra/tolerance_policy_concept.hpp"
#include "algebra/unit_traits.hpp"
#include <limits>

namespace algebra
{

/// \ingroup algebra
/// \brief 
///		It implements a tolerance policy that compares two values using an absolute tolerance value. For a given 
///		value \c v1, the value \c v2 is considered to be equal to \c v1 if it is in the range <c>[v1 - epsilon, 
///		v1 + epsilon]</c>.
/// \concept TolerancePolicy
/// \tparam U the type of the values to be compared.
template< typename U>
class epsilon_tolerance
{
public:
	typedef U unit_type;

	/// \brief Initialization of the absolute tolerance value.
	epsilon_tolerance( const unit_type& epsilon 
		= (std::numeric_limits<unit_type>::is_integer ? 0 : std::numeric_limits< unit_type>::min()))
		: epsilon_( epsilon) { }

	/// \brief Equality checking.
	bool equals( const unit_type& op1, const unit_type& op2) const
	{
		return std::abs( op2 - op1) <= epsilon_;
	}

	/// \brief It gets the tolerance value.
	const unit_type& epsilon() const { return epsilon_; }

private:
	const unit_type epsilon_;
};


} // namespace algebra

#endif // ALGEBRA_EPSILON_TOLERANCE_HPP
