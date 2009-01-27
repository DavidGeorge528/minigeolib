#ifndef ALGEBRA_VECTOR_2_HPP
#define ALGEBRA_VECTOR_2_HPP

namespace algebra
{

template< typename U, typename UT>
class vector< 2, U, UT>: public details::vector_base< 2, U, UT>
{
	typedef vector< 2, U, UT> my_type_;
public:
	vector()
	{
		v_[0] = v_[1] = unit_traits_type::zero();
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

	vector( const U& v0, const U& v1)
	{
		v_[0] = v0;
		v_[1] = v1;
	}

	my_type_& operator=( const my_type_& op)
	{
		if( this != &op)
		{
			v_[0] = op.v_[0];
			v_[1] = op.v_[1];
		}
		return *this;
	}

	friend my_type_ operator+( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] + op2.v_[0], op1.v_[1] + op2.v_[1]);
	}

	my_type_& operator+=( const my_type_& op)
	{
		v_[0] += op.v_[0];
		v_[1] += op.v_[1];
		return *this;
	}

	friend my_type_ operator-( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] - op2.v_[0], op1.v_[1] - op2.v_[1]);
	}

	my_type_& operator-=( const my_type_& op)
	{
		v_[0] -= op.v_[0];
		v_[1] -= op.v_[1];
		return *this;
	}


	friend my_type_ operator*( const unit_type& s, const my_type_& v)
	{
		return my_type_( s*v.v_[0], s*v.v_[1]);
	}

	friend my_type_ operator*( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]*s, v.v_[1]*s);
	}

	my_type_& operator*=( const unit_type& s)
	{
		v_[0]*=s;
		v_[1]*=s;
		return *this;
	}


	friend my_type_ operator/( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]/s, v.v_[1]/s);
	}


	my_type_& operator/=( const unit_type& s)
	{
		v_[0]/=s;
		v_[1]/=s;
		return *this;
	}

	friend my_type_ operator*( const my_type_& v, const matrix_type& m)
	{
		return my_type_(
			v.v_[0]*m.a11_ + v.v_[1]*m.a21_,
			v.v_[0]*m.a12_ + v.v_[1]*m.a22_);
	}

	my_type_& operator*=( const matrix_type& m)
	{
		my_type_ result = operator*( *this, m);
		*this = result;
		return *this;
	}

	friend my_type_ operator*( const matrix_type& m, const my_type_& v)
	{
		return my_type_(
			m.a11_*v.v_[0] + m.a12_*v.v_[1],
			m.a21_*v.v_[0] + m.a22_*v.v_[1]);
	}
};

} // namespace algebra

#endif // ALGEBRA_VECTOR_2_HPP
