#ifndef VECTOR_TEST_FIXTURES_HPP
#define VECTOR_TEST_FIXTURES_HPP

#include "../tests_common.hpp"
#include <boost/test/predicate_result.hpp>
#include <vector>
#include <algorithm>
#include <iterator>

namespace algebra
{

template< unsigned D, typename U, typename UT>
struct vector_test_fixture;

namespace details
{

template< unsigned D, typename FP, typename UT>
struct fp_test_fixture
{
	// TODO: BOOST_CHECK( is_floating_point);
	typedef FP unit_type;
	typedef UT unit_traits_type;
	enum { DIMS = D };

	fp_test_fixture()
	{
		for( unsigned i = 0; i < DIMS; ++i)
		{
			c_array_[i] = i*0.5;
		}

		stl_array_.reserve( DIMS);
		stl_array_.assign( &c_array_[0], &c_array_[0] + DIMS);

		zeros_.insert( zeros_.end(), DIMS, unit_traits_type::zero());
		ones_.insert( ones_.end(), DIMS, unit_traits_type::one());

		operand1_.reserve( DIMS);
		operand2_.reserve( DIMS);
		op1_add_op2_.reserve( DIMS);
		op1_sub_op2_.reserve( DIMS);
		for( unsigned i = 0; i < DIMS; ++i)
		{
			operand1_.push_back( i*0.3);
			operand2_.push_back( i*0.25);
			op1_add_op2_.push_back( operand1_[i] + operand2_[i]);
			op1_sub_op2_.push_back( operand1_[i] - operand2_[i]);
		}
	}

	unit_type c_array_[ DIMS];
	std::vector< unit_type> stl_array_;
	std::vector< unit_type> zeros_;
	std::vector< unit_type> ones_;
	std::vector< unit_type> operand1_;
	std::vector< unit_type> operand2_;
	std::vector< unit_type> op1_add_op2_;
	std::vector< unit_type> op1_sub_op2_;
};

} // namespace details

template< unsigned D, typename UT>
struct vector_test_fixture< D, float, UT>: public details::fp_test_fixture< D, float, UT> { };

template< unsigned D, typename UT>
struct vector_test_fixture< D, double, UT>: public details::fp_test_fixture< D, double, UT> { };

/// \brief Boost Test predicate for checking vectors.
template< unsigned D, typename U, typename UT, typename I>
boost::test_tools::predicate_result check_equal_vector( 
	I exp_begin, I exp_end, const algebra::vector< D, U, UT>& obtained)
{
	namespace tt = boost::test_tools;

	tt::predicate_result res( true);
	int exp_dims = std::distance( exp_begin, exp_end);
	if( exp_dims != obtained.DIMENSIONS)
	{
		res.message() << "Different number of dimensions [" << exp_dims << "!=" << obtained.DIMENSIONS << "]";
		res = false;
		return res;
	}

	bool success = true;
	unsigned index = 0;
	U tollerance = test_traits<U>::check_tollerance();
	for( ; exp_begin != exp_end; ++index, ++exp_begin)
	{
		U obt = obtained(index);
		if( !tt::check_is_close( *exp_begin, obt, 
			tt::fraction_tolerance( tollerance)))
		{
			res.message() << "Vector mismatch at position " << index 
				<< " [" << *exp_begin << "!=" << obtained(index) << "];";
			res = false;	
		}
	}

	return res;
}

#define BOOST_CHECK_EQUAL_ALG_VECTOR( B, E, V) BOOST_CHECK( check_equal_vector( B, E, V))

} // namespace algebra

#endif // VECTOR_TEST_FIXTURES_HPP
