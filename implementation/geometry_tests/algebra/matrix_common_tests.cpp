#include "algebra/matrix.hpp"
#include "matrix_test_fixtures.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"

namespace
{

using namespace algebra;

#define DEF_TEST( M) \
	typedef M matrix_type; \
	typedef matrix_test_fixture< M::ROWS, M::COLUMNS, typename M::unit_type, typename M::unit_traits_type> test_fixture

BOOST_AUTO_TEST_CASE_TEMPLATE( test_default_constructor, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;

	matrix_type m;
	BOOST_CHECK( check_equal_matrix( &f.zeros_[0][0], &f.zeros_[0][0] + M::ROWS*M::COLUMNS, m));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_two_iter_constructor, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type m( f.stl_vector_.begin(), f.stl_vector_.end());

	BOOST_CHECK( check_equal_matrix( f.stl_vector_.begin(), f.stl_vector_.end(), m));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_one_iter_constructor, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type m( f.stl_vector_.begin());

	BOOST_CHECK( check_equal_matrix( f.stl_vector_.begin(), f.stl_vector_.end(), m));
}


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_assignment_operator, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type orig( f.stl_vector_.begin()), m;
	m = orig;

	BOOST_CHECK( check_equal_matrix( f.stl_vector_.begin(), f.stl_vector_.end(), m));

	m = m;
	BOOST_CHECK( check_equal_matrix( f.stl_vector_.begin(), f.stl_vector_.end(), m));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_addition, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type op1( &f.op1_[0]), op2( &f.op2_[0]), result, zero;

	result = op1 + op2;
	BOOST_CHECK( check_equal_matrix( &f.added_[0], &f.added_[0] + test_fixture::SIZE, result));

	result = op1;
	result += op2;
	BOOST_CHECK( check_equal_matrix( &f.added_[0], &f.added_[0] + test_fixture::SIZE, result));

	result += zero;
	BOOST_CHECK( check_equal_matrix( &f.added_[0], &f.added_[0] + test_fixture::SIZE, result));

	result = op1 + zero;
	BOOST_CHECK( check_equal_matrix( &f.op1_[0], &f.op1_[0] + test_fixture::SIZE, result));
}

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_subtraction, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type op1( &f.op1_[0]), op2( &f.op2_[0]), result, zero;

	result = op1 - op2;
	BOOST_CHECK( check_equal_matrix( &f.subtracted_[0], &f.subtracted_[0] + test_fixture::SIZE, result));

	result = op1;
	result -= op2;
	BOOST_CHECK( check_equal_matrix( &f.subtracted_[0], &f.subtracted_[0] + test_fixture::SIZE, result));

	result -= zero;
	BOOST_CHECK( check_equal_matrix( &f.subtracted_[0], &f.subtracted_[0] + test_fixture::SIZE, result));

	result = op1 - zero;
	BOOST_CHECK( check_equal_matrix( &f.op1_[0], &f.op1_[0] + test_fixture::SIZE, result));
}


// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_multiplication, M, matrix_test_types)
{
	DEF_TEST( M);
	test_fixture f;
	matrix_type op1( &f.mulop1_[0]), op2( &f.mulop2_[0]), result, identity = matrix_type::IDENTITY();

	result = op1 * op2;
	BOOST_CHECK( check_equal_matrix( &f.multiplied_[0], &f.multiplied_[0] + test_fixture::SIZE, result));
	
	result = op1*identity;
	BOOST_CHECK( check_equal_matrix( &f.mulop1_[0], &f.mulop1_[0] + test_fixture::SIZE, result));
	
	result = identity*op1;
	BOOST_CHECK( check_equal_matrix( &f.mulop1_[0], &f.mulop1_[0] + test_fixture::SIZE, result));

	result = op1;
	result *= op2;
	BOOST_CHECK( check_equal_matrix( &f.multiplied_[0], &f.multiplied_[0] + test_fixture::SIZE, result));

	result *= identity;
	BOOST_CHECK( check_equal_matrix( &f.multiplied_[0], &f.multiplied_[0] + test_fixture::SIZE, result));
}

} // namespace
