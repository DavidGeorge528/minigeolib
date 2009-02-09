#include "algebra/unit_base.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"

namespace 
{

using namespace algebra;

struct test_tag {};

typedef boost::mpl::list< unit_base< float, test_tag>, unit_base< double, test_tag> > tested_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, U, tested_types)
{
	U u;
	typedef typename U::unit_type unit_type;
	ALGTEST_CHECK_EQUAL_UNIT( 0, u.value());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_explicit_constructor, U, tested_types)
{
	U u( 10.0);
	typedef typename U::unit_type unit_type;
	ALGTEST_CHECK_EQUAL_UNIT( 10.0, u.value());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_copy, U, tested_types)
{
	typedef typename U::unit_type unit_type;
	U u1( 10.0), r, u2(20.0), u3( u1);
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), u3.value());
	r = u1;
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), r.value());
	u2 = r = u3 = u1;
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), r.value());
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), u3.value());
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), u2.value());
	r = r;
	ALGTEST_CHECK_EQUAL_UNIT( u1.value(), r.value());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_arithmetic_ops, U, tested_types)
{
	typedef typename U::unit_type unit_type;
	U op1( 10), op2( 20), result;

	result = op1 + op2;
	ALGTEST_CHECK_EQUAL_UNIT( 30, result.value());
	result = op1;
	result += op2;
	ALGTEST_CHECK_EQUAL_UNIT( 30, result.value());

	result = op1 - op2;
	ALGTEST_CHECK_EQUAL_UNIT( -10, result.value());
	result = op1;
	result -= op2;
	ALGTEST_CHECK_EQUAL_UNIT( -10, result.value());

	result = op1 * op2;
	ALGTEST_CHECK_EQUAL_UNIT( 200, result.value());
	result = op1;
	result *= op2;
	ALGTEST_CHECK_EQUAL_UNIT( 200, result.value());

	result = op1 / op2;
	ALGTEST_CHECK_EQUAL_UNIT( 10.0/20.0, result.value());
	result = op1;
	result /= op2;
	ALGTEST_CHECK_EQUAL_UNIT( 10.0/20.0, result.value());
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_conversion, U, tested_types)
{
	typedef typename U::unit_type unit_type;
	U op1(10);
	U::unit_type v = op1;
	ALGTEST_CHECK_EQUAL_UNIT( 10, v);
}

} 
