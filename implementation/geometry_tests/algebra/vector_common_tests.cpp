#include "algebra/vector.hpp"
#include "vector_test_fixtures.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"

namespace
{

using namespace algebra;

#define DEF_TYPES( V) \
	typedef V tested_vector; \
	typedef typename tested_vector::unit_type unit_type; \
	typedef vector_test_fixture< tested_vector::DIMENSIONS, unit_type, typename tested_vector::unit_traits_type > test_fixture

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v;

	BOOST_CHECK_EQUAL_ALG_VECTOR( f.zeros_.begin(), f.zeros_.end(), v);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_seq_constructor, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS);
	tested_vector v2( f.stl_array_.begin(), f.stl_array_.end());

	BOOST_CHECK_EQUAL_ALG_VECTOR( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS, v1);
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), v2);
}


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_start_constructor, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( &f.c_array_[0]);
	tested_vector v2( f.stl_array_.begin());

	BOOST_CHECK_EQUAL_ALG_VECTOR( &f.c_array_[0], &f.c_array_[0] + test_fixture::DIMS, v1);
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), v2);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_copy_constructor, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector original( f.stl_array_.begin());
	tested_vector copy( original);

	BOOST_CHECK_EQUAL_ALG_VECTOR( f.stl_array_.begin(), f.stl_array_.end(), copy);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_assignment_operator, T, vector_test_types)
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

BOOST_AUTO_TEST_CASE_TEMPLATE( test_addition, T, vector_test_types)
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

BOOST_AUTO_TEST_CASE_TEMPLATE( test_subtraction, T, vector_test_types)
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
