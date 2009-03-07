#ifndef ALGEBRA_TOLERANCE_POLICY_CONCEPT_HPP
#define ALGEBRA_TOLERANCE_POLICY_CONCEPT_HPP

#include <boost/concept/usage.hpp>

namespace algebra
{

/// \ingroup algebra
/// \brief The definition of the tolerance policy concept.
/// \details
/// The tolerance should provide a way to compare two values for equality. A concept implementation should provide 
/// the method <c>equals</c> for comparing two values.
template< typename TP>
class TolerancePolicy
{
public:
	typedef typename TP::unit_type unit_type;

	BOOST_CONCEPT_USAGE( TolerancePolicy)
	{
		bool b = policy_.equals( op1_, op2_);
	}
private:
	unit_type op1_, op2_;
	TP policy_;
};

} // namespace algebra

#endif // ALGEBRA_TOLERANCE_POLICY_CONCEPT_HPP
