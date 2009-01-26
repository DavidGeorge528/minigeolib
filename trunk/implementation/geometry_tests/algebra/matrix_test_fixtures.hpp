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
			c_array_[r][c] = r + c;
			stl_vector_.push_back( c_array_[r][c]);
		}
		END_INIT_LOOP

		INIT_LOOP( r, c)
		{
			identity_[r][c] = (r == c) ? unit_traits_type::one() : unit_traits_type::zero();
		}
		END_INIT_LOOP

		INIT_LOOP( r, c)
		{
			unsigned index = r*COLUMNS + c;
			op1_.push_back( (r*c)/(r+c+1));
			op2_.push_back( (r+c)/(r*c+1));
			added_.push_back( op1_[ index] + op2_[index]); 
			subtracted_.push_back( op1_[index] - op2_[index]);
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
};

} // namespace details

template< typename U, typename UT>
class matrix_test_fixture< 2, 2, U, UT>: public details::fp_matrix_test_fixture< 2, 2, U, UT> { };
template< typename U, typename UT>
class matrix_test_fixture< 3, 3, U, UT>: public details::fp_matrix_test_fixture< 3, 3, U, UT> { };
template< typename U, typename UT>
class matrix_test_fixture< 4, 4, U, UT>: public details::fp_matrix_test_fixture< 4, 4, U, UT> { };


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
