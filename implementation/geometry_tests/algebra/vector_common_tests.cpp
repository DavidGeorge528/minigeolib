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

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_scalar_multiply, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( f.operand1_.begin());
	tested_vector result;

	result = v1*f.scalar_;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.smul_.begin(), f.smul_.end(), result);

	result = f.scalar_ * v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.smul_.begin(), f.smul_.end(), result);

	result = v1;
	result *= f.scalar_;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.smul_.begin(), f.smul_.end(), result);

	result = v1 * tested_vector::unit_traits_type::zero();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.zeros_.begin(), f.zeros_.end(), result);

	result = tested_vector::unit_traits_type::zero() * v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.zeros_.begin(), f.zeros_.end(), result);

	result = v1;
	result *= tested_vector::unit_traits_type::zero();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.zeros_.begin(), f.zeros_.end(), result);

	result = v1 * tested_vector::unit_traits_type::one();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), result);

	result = tested_vector::unit_traits_type::one() * v1;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), result);

	result = v1;
	result *= tested_vector::unit_traits_type::one();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), result);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_scalar_division, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( f.operand1_.begin());
	tested_vector result;


	result = v1/f.scalar_;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.sdiv_.begin(), f.sdiv_.end(), result);

	result = v1;
	result /= f.scalar_;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.sdiv_.begin(), f.sdiv_.end(), result);

	result = v1/tested_vector::unit_traits_type::one();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), result);

	result = v1;
	result /= tested_vector::unit_traits_type::one();
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.operand1_.begin(), f.operand1_.end(), result);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_matrix_multiplication, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	typename test_fixture::matrix_type m( f.mulmatrix_.begin());
	tested_vector v( f.mulvec_.begin());
	tested_vector result;

	result = v*m;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.vec_matrix_.begin(), f.vec_matrix_.end(), result);

	result = v;
	result *= m;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.vec_matrix_.begin(), f.vec_matrix_.end(), result);

	result = m*v;
	BOOST_CHECK_EQUAL_ALG_VECTOR( f.matrix_vec_.begin(), f.matrix_vec_.end(), result);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_dot_product, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v1( f.operand1_.begin());
	tested_vector v2( f.operand2_.begin());
	unit_type result = v1 * v2;
	ALGTEST_CHECK_EQUAL_UNIT( f.op1_dot_op2_, result);
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_norm, T, vector_test_types)
{
	DEF_TYPES( T);
	test_fixture f;
	tested_vector v( f.operand1_.begin());
	ALGTEST_CHECK_EQUAL_UNIT( f.sqnorm_, sqnorm( v));
	ALGTEST_CHECK_EQUAL_UNIT( f.norm_, norm( v));
}

} // namespace
