#include "algebra/vector.hpp"
#include "vector_test_fixtures.hpp"
#include "../tests_common.hpp"
#include "../test_macros.hpp"
#include "../test_traits.hpp"

namespace
{

using namespace algebra;

#define DEF_TYPES( P) \
	GEOMTEST_UNIT_ALIAS(P); \
	typedef algebra::vector< GEOMTEST_DIM_NUMBER(P), GEOMTEST_UNIT_TYPE(P), GEOMTEST_TRAITS_TYPE(P) > tested_vector; \
	typedef algebra::vector_test_fixture< GEOMTEST_DIM_NUMBER(P), GEOMTEST_UNIT_TYPE(P), GEOMTEST_TRAITS_TYPE(P) > test_fixture

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v;

	BOOST_CHECK_EQUAL_ALG_VECTOR( f.zeros_.begin(), f.zeros_.end(), v);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_seq_constructor, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS);
	tested_vector v2( f.stl_array_.begin(), f.stl_array_.end());

	BOOST_CHECK_EQUAL_ALG_VECTOR( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS, v1);
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), v2);
}


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_start_constructor, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( &f.c_array_[0]);
	tested_vector v2( f.stl_array_.begin());

	BOOST_CHECK_EQUAL_ALG_VECTOR( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS, v1);
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), v2);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_copy_constructor, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector original( f.stl_array_.begin());
	tested_vector copy( original);

	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), copy);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_assignment_operator, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector original( f.stl_array_.begin());
	tested_vector copy;

	copy = original;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), copy);

	copy = copy;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), copy);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_addition, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( f.operand1_.begin());
	tested_vector v2( f.operand2_.begin());
	tested_vector z;

	tested_vector v;
	v = v1+v2;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.op1_add_op2_.begin(), f.op1_add_op2_.end(), v);
	
	v = v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);	
	v += v2;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.op1_add_op2_.begin(), f.op1_add_op2_.end(), v);
	
	v = v1 + z;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
	v = v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
	v += z;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_subtraction, T, algebraic_traited_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( f.operand1_.begin());
	tested_vector v2( f.operand2_.begin());
	tested_vector z;

	tested_vector v;
	v = v1-v2;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.op1_sub_op2_.begin(), f.op1_sub_op2_.end(), v);

	v = v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);	
	v -= v2;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.op1_sub_op2_.begin(), f.op1_sub_op2_.end(), v);

	v = v1 + z;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
	v = v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
	v -= z;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), v);
}

} // namespace
