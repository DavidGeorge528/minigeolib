#ifndef VECTOR_TEST_FIXTURES_HPP
#define VECTOR_TEST_FIXTURES_HPP

#include "../tests_common.hpp"
#include <boost/test/predicate_result.hpp>
#include <vector>
#include <algorithm>
#include <iterator>

namespace algebra
{

/// \brief 
///		Definition of the testing contexts that are used by generic vector test cases. It is a tuple of number of 
///		dimensions, the type of the unit and the traits for the unit type.
typedef boost::mpl::list< 
	vector< 2, float, unit_traits< float> >,
	vector< 2, double, unit_traits< double> >,
	vector< 3, float, unit_traits< float> >,
	vector< 3, double, unit_traits< double> >,
	vector< 4, float, unit_traits< float> >,
	vector< 4, double, unit_traits< double> >
> vector_test_types;

template< unsigned D, typename U, typename UT>
struct vector_test_fixture;

namespace details
{

template< unsigned D, typename FP, typename UT>
struct fp_test_fixture
{
	typedef FP unit_type;
	typedef UT unit_traits_type;
	enum { DIMS = D };

	fp_test_fixture()
	{
		for( unsigned i = 0; i < DIMS; ++i)
		{
			c_array_[i] = unit_type(i) * unit_type(0.5);
		}

		stl_array_.reserve( DIMS);
		stl_array_.assign( &c_array_[0], &c_array_[0] + DIMS);

		zeros_.insert( zeros_.end(), DIMS, unit_traits_type::zero());
		ones_.insert( ones_.end(), DIMS, unit_traits_type::one());

		operand1_.reserve( DIMS);
		operand2_.reserve( DIMS);
		op1_add_op2_.reserve( DIMS);
		op1_sub_op2_.reserve( DIMS);
		scalar_ = 2;
		op1_dot_op2_ = unit_traits_type::zero();
		for( unsigned i = 0; i < DIMS; ++i)
		{
			operand1_.push_back( i*unit_type(0.3));
			operand2_.push_back( i*unit_type(0.25));
			op1_add_op2_.push_back( operand1_[i] + operand2_[i]);
			op1_sub_op2_.push_back( operand1_[i] - operand2_[i]);
			smul_.push_back( operand1_[i]*scalar_);
			sdiv_.push_back( operand1_[i]/scalar_);
			op1_dot_op2_ += operand1_[i] * operand2_[i];
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
	unit_type op1_dot_op2_;
	unit_type scalar_;
	std::vector< unit_type> smul_;
	std::vector< unit_type> sdiv_;
};

} // namespace details


template< typename U, typename UT>
struct vector_test_fixture< 2, U, UT>: public details::fp_test_fixture< 2, U, UT> 
{ 
	typedef matrix< DIMS, DIMS, U, UT> matrix_type;

	vector_test_fixture()
	{
		unit_type mulvec[] = { 1.0, 2.0 };
		unit_type mulmatrix[] = { 
			10, 20,
			30, 40};
		unit_type vec_matrix[] = { 70, 100};
		unit_type matrix_vec[] = { 50, 110};

		mulvec_.assign( &mulvec[0], &mulvec[0] + DIMS);
		mulmatrix_.assign( &mulmatrix[0], &mulmatrix[0] + DIMS*DIMS);
		vec_matrix_.assign( &vec_matrix[0], &vec_matrix[0] + DIMS);
		matrix_vec_.assign( &matrix_vec[0], &matrix_vec[0] + DIMS);
	}

	std::vector< unit_type> mulvec_;
	std::vector< unit_type> mulmatrix_;
	std::vector< unit_type> vec_matrix_;
	std::vector< unit_type> matrix_vec_;
};

template< typename U, typename UT>
struct vector_test_fixture< 3, U, UT>: public details::fp_test_fixture< 3, U, UT> 
{ 
	typedef matrix< DIMS, DIMS, U, UT> matrix_type;

	vector_test_fixture()
	{
		unit_type mulvec[] = { 1.0, 2.0, 3.0 };
		unit_type mulmatrix[] = { 
			10, 20, 30,
			30, 40, 50,
			40, 30, 20};
		unit_type vec_matrix[] = { 190, 190, 190};
		unit_type matrix_vec[] = { 140, 260, 160};

		mulvec_.assign( &mulvec[0], &mulvec[0] + DIMS);
		mulmatrix_.assign( &mulmatrix[0], &mulmatrix[0] + DIMS*DIMS);
		vec_matrix_.assign( &vec_matrix[0], &vec_matrix[0] + DIMS);
		matrix_vec_.assign( &matrix_vec[0], &matrix_vec[0] + DIMS);
	}
	std::vector< unit_type> mulvec_;
	std::vector< unit_type> mulmatrix_;
	std::vector< unit_type> vec_matrix_;
	std::vector< unit_type> matrix_vec_;
};

template< typename U, typename UT>
struct vector_test_fixture< 4, U, UT>: public details::fp_test_fixture< 4, U, UT> 
{ 
	typedef matrix< DIMS, DIMS, U, UT> matrix_type;

	vector_test_fixture()
	{
		unit_type mulvec[] = { 1, 2, 3, 4 };
		unit_type mulmatrix[] = { 
			11, 12, 13, 14,
			21, 22, 23, 24,
			31, 32, 33, 34,
			41, 42, 43, 44};
		unit_type vec_matrix[] = {310, 320, 330, 340};
		unit_type matrix_vec[] = {130, 230, 330, 430};

		mulvec_.assign( &mulvec[0], &mulvec[0] + DIMS);
		mulmatrix_.assign( &mulmatrix[0], &mulmatrix[0] + DIMS*DIMS);
		vec_matrix_.assign( &vec_matrix[0], &vec_matrix[0] + DIMS);
		matrix_vec_.assign( &matrix_vec[0], &matrix_vec[0] + DIMS);
	}

	std::vector< unit_type> mulvec_;
	std::vector< unit_type> mulmatrix_;
	std::vector< unit_type> vec_matrix_;
	std::vector< unit_type> matrix_vec_;
};

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

	unsigned index = 0;
	U tolerance = test_traits<U>::check_tolerance();
	for( ; exp_begin != exp_end; ++index, ++exp_begin)
	{
		U obt = obtained(index);
		if( !tt::check_is_close( *exp_begin, obt, 
			tt::fraction_tolerance( tolerance)))
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
