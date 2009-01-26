#ifndef ALGEBRA_VECTOR_4_HPP
#define ALGEBRA_VECTOR_4_HPP

namespace algebra
{

template< typename U, typename UT>
class vector< 4, U, UT>: public details::vector_base< 4, U, UT>
{
	typedef vector< 4, U, UT> my_type_;
public:
	vector()
	{
		v_[0] = v_[1] = v_[2] = v_[3] = unit_traits_type::zero();
	}

	template< typename It> vector( It begin, It end)
	{
		assert( std::distance( begin, end) == DIMENSIONS);
		std::copy( begin, end, &v_[0]);
	}

	template< typename It> vector( It begin)
	{
		for( unsigned n = 0; n < DIMENSIONS; ++n, ++begin)
		{
			v_[n] = *begin;
		}
	}

	vector( const U& v0, const U& v1, const U& v2, const U& v3)
	{
		v_[0] = v0;
		v_[1] = v1;
		v_[2] = v2;
		v_[3] = v3;
	}

	my_type_& operator=( const my_type_& op)
	{
		if( this != &op)
		{
			v_[0] = op.v_[0];
			v_[1] = op.v_[1];
			v_[2] = op.v_[2];
			v_[3] = op.v_[3];
		}
		return *this;
	}

	friend my_type_ operator+( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] + op2.v_[0], op1.v_[1] + op2.v_[1], op1.v_[2] + op2.v_[2], op1.v_[3] + op2.v_[3]);
	}

	my_type_& operator+=( const my_type_& op)
	{
		v_[0] += op.v_[0];
		v_[1] += op.v_[1];
		v_[2] += op.v_[2];
		v_[3] += op.v_[3];
		return *this;
	}

	friend my_type_ operator-( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] - op2.v_[0], op1.v_[1] - op2.v_[1], op1.v_[2] - op2.v_[2], op1.v_[3] - op2.v_[3]);
	}

	my_type_& operator-=( const my_type_& op)
	{
		v_[0] -= op.v_[0];
		v_[1] -= op.v_[1];
		v_[2] -= op.v_[2];
		v_[3] -= op.v_[3];
		return *this;
	}

};

} // namespace algebra

#endif // ALGEBRA_VECTOR_4_HPP
