#ifndef MATRIX_TEST_FIXTURES_HPP
#define MATRIX_TEST_FIXTURES_HPP

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
	matrix< 2, 2, float, unit_traits< float> >,
	matrix< 2, 2, double, unit_traits< double> >,
	matrix< 3, 3, float, unit_traits< float> >,
	matrix< 3, 3, double, unit_traits< double> >,
	matrix< 4, 4, float, unit_traits< float> >,
	matrix< 4, 4, double, unit_traits< double> >
> matrix_test_types;

template< unsigned R, unsigned C, typename U, typename UT>
class matrix_test_fixture;

namespace details
{

#define INIT_LOOP( r, c) \
	for( unsigned r = 0; r < ROWS; ++r) \
	{ \
		for( unsigned c = 0; c < COLUMNS; ++c) 

#define END_INIT_LOOP }
		

template< unsigned R, unsigned C, typename U, typename UT>
struct fp_matrix_test_fixture
{
	typedef U unit_type;
	typedef UT unit_traits_type;
	enum { ROWS = R, COLUMNS = C, SIZE = R*C };

	fp_matrix_test_fixture()
	{
		INIT_LOOP( r, c)
		{
				zeros_[r][c] = unit_traits_type::zero();
		}
		END_INIT_LOOP

		INIT_LOOP( r, c)
		{
			c_array_[r][c] = unit_type(r + c);
			stl_vector_.push_back( c_array_[r][c]);
		}
		END_INIT_LOOP

		INIT_LOOP( r, c)
		{
			identity_[r][c] = (r == c) ? unit_traits_type::one() : unit_traits_type::zero();
		}
		END_INIT_LOOP

		scalar_ = 2;
		transposed_.assign( SIZE, unit_traits_type::zero());

		INIT_LOOP( r, c)
		{
			unsigned index = r*COLUMNS + c;
			op1_.push_back( unit_type(r*c)/unit_type(r+c+1));
			op2_.push_back( unit_type(r+c)/unit_type(r*c+1));
			added_.push_back( op1_[ index] + op2_[index]); 
			subtracted_.push_back( op1_[index] - op2_[index]);
			scmul_.push_back( op1_[ index] * scalar_);
			scdiv_.push_back( op1_[ index] / scalar_);
			transposed_[ c*ROWS + r] = op1_.back();
		}
		END_INIT_LOOP
	}

	unit_type zeros_[ROWS][COLUMNS];
	unit_type c_array_[ROWS][COLUMNS];
	std::vector< unit_type> stl_vector_;
	unit_type identity_[ROWS][COLUMNS];

	std::vector< unit_type> op1_;
	std::vector< unit_type> op2_;
	std::vector< unit_type> added_;
	std::vector< unit_type> subtracted_;
	std::vector< unit_type> mulop1_;
	std::vector< unit_type> mulop2_;
	std::vector< unit_type> multiplied_;
	unit_type scalar_;
	std::vector< unit_type> scmul_;
	std::vector< unit_type> scdiv_;
	std::vector< unit_type> transposed_; // Transposition of op1_
};

} // namespace details

template< typename U, typename UT>
class matrix_test_fixture< 2, 2, U, UT>: public details::fp_matrix_test_fixture< 2, 2, U, UT> 
{ 
public:
	matrix_test_fixture()
	{
		unit_type op1[ SIZE] = { 			
			10.0, 20.0,
			15.0, 16.0,
		};
		unit_type op2[ SIZE] = {
			23.0, 43.0,
			22.0, 34.0
		};
		unit_type result[SIZE] = {
			670.0, 1110.0,
			697.0, 1189.0,
		};

		mulop1_.assign( &op1[0], &op1[0] + SIZE);
		mulop2_.assign( &op2[0], &op2[0] + SIZE);
		multiplied_.assign( &result[0], &result[0] + SIZE);
		op1_det_ = -140.0;
	}

	unit_type op1_det_;
};


template< typename U, typename UT>
class matrix_test_fixture< 3, 3, U, UT>: public details::fp_matrix_test_fixture< 3, 3, U, UT> 
{ 
public:
	matrix_test_fixture()
	{
		unit_type op1[ SIZE] = { 			
			10.0, 20.0, 30.0,
			15.0, 16.0, 17.0,
			18.0, 28.0, 34.0};
		unit_type op2[ SIZE] = {
			23.0, 43.0, 51.0,
			22.0, 34.0, 45.0,
			73.0, 32.0, 55.0
		};
		unit_type result[SIZE] = {
			2860.0, 2070.0, 3060.0,
			1938.0, 1733.0, 2420.0,
			3512.0, 2814.0, 4048.0
		};

		mulop1_.assign( &op1[0], &op1[0] + SIZE);
		mulop2_.assign( &op2[0], &op2[0] + SIZE);
		multiplied_.assign( &result[0], &result[0] + SIZE);
		op1_det_ = 560.0;
	}

	unit_type op1_det_;
};

template< typename U, typename UT>
class matrix_test_fixture< 4, 4, U, UT>: public details::fp_matrix_test_fixture< 4, 4, U, UT> 
{ 
public:
	matrix_test_fixture()
	{
		unit_type op1[ SIZE] = { 			
			111.0, 112.0, 113.0, 114.0,
			121.0, 122.0, 1.0, 124.0,
			11.0, 132.0, 133.0, 134.0,
			141.0, 142.0, 143.0, 144.0};
		unit_type op2[ SIZE] = {
			211.0, 212.0, 213.0, 214.0,
			221.0, 222.0, 223.0, 224.0,
			231.0, 232.0, 233.0, 234.0,
			241.0, 242.0, 243.0, 244.0
			};
		unit_type result[SIZE] = {
			101750.0, 102200.0, 102650.0, 103100.0,
			82608.0,  82976.0,  83344.0,  83712.0,
			94510.0,  94920.0,  95330.0,  95740.0,
			128870.0, 129440.0, 130010.0, 130580.0
		};

		mulop1_.assign( &op1[0], &op1[0] + SIZE);
		mulop2_.assign( &op2[0], &op2[0] + SIZE);
		multiplied_.assign( &result[0], &result[0] + SIZE);
		op1_det_ = -878400.000;
	}

	unit_type op1_det_;
};


/// \brief Boost Test predicate for checking vectors.
template< unsigned R, unsigned C, typename U, typename UT, typename I>
boost::test_tools::predicate_result check_equal_matrix( 
	I exp_begin, I exp_end, const matrix< R, C, U, UT>& obtained)
{
	namespace tt = boost::test_tools;
	tt::predicate_result res( true);
	int exp_dims = std::distance( exp_begin, exp_end);
	if( exp_dims != R*C)
	{
		res.message() << "Different number of elements [" << exp_dims << "!=" << R*C << "]";
		res = false;
		return res;
	}

	U tolerance = test_traits< U>::check_tolerance();
	for( unsigned r = 0; r < R; ++r)
	{
		for( unsigned c = 0; c < C; ++c, ++exp_begin)
		{
			U obt = obtained( r, c);
			if( !tt::check_is_close( *exp_begin, obt, tt::fraction_tolerance( tolerance)))
			{
				res.message() << "Matrix mismatch at position (" << r << "," << c << "): "
					<< "[" << *exp_begin << "!=" << obt << "]";
				res = false;
			}
		}
	}

	return res;
}

} // namespace algebra

#define BOOST_CHECK_EQUAL_ALG_MATRIX( B, E, V) BOOST_CHECK( check_equal_matrix( B, E, V))

#endif // MATRIX_TEST_FIXTURES_HPP
