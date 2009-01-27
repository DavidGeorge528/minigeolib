#ifndef ALGEBRA_VECTOR_3_HPP
#define ALGEBRA_VECTOR_3_HPP

namespace algebra
{

template< typename U, typename UT>
class vector< 3, U, UT>: public details::vector_base< 3, U, UT>
{
	typedef vector< 3, U, UT> my_type_;
public:
	vector()
	{
		v_[0] = v_[1] = v_[2] = unit_traits_type::zero();
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

	vector( const U& v0, const U& v1, const U& v2)
	{
		v_[0] = v0;
		v_[1] = v1;
		v_[2] = v2;
	}

	my_type_& operator=( const my_type_& op)
	{
		if( this != &op)
		{
			v_[0] = op.v_[0];
			v_[1] = op.v_[1];
			v_[2] = op.v_[2];
		}
		return *this;
	}


	friend my_type_ operator+( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] + op2.v_[0], op1.v_[1] + op2.v_[1], op1.v_[2] + op2.v_[2]);
	}

	my_type_& operator+=( const my_type_& op)
	{
		v_[0] += op.v_[0];
		v_[1] += op.v_[1];
		v_[2] += op.v_[2];
		return *this;
	}

	friend my_type_ operator-( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] - op2.v_[0], op1.v_[1] - op2.v_[1], op1.v_[2] - op2.v_[2]);
	}

	my_type_& operator-=( const my_type_& op)
	{
		v_[0] -= op.v_[0];
		v_[1] -= op.v_[1];
		v_[2] -= op.v_[2];
		return *this;
	}

	friend my_type_ operator*( const unit_type& s, const my_type_& v)
	{
		return my_type_( s*v.v_[0], s*v.v_[1], s*v.v_[2]);
	}

	friend my_type_ operator*( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]*s, v.v_[1]*s, v.v_[2]*s);
	}

	my_type_& operator*=( const unit_type& s)
	{
		v_[0]*=s;
		v_[1]*=s;
		v_[2]*=s;
		return *this;
	}


	friend my_type_ operator/( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]/s, v.v_[1]/s, v.v_[2]/s);
	}


	my_type_& operator/=( const unit_type& s)
	{
		v_[0]/=s;
		v_[1]/=s;
		v_[2]/=s;
		return *this;
	}

	friend my_type_ operator*( const my_type_& v, const matrix_type& m)
	{
		return my_type_(
			v.v_[0]*m.a11_ + v.v_[1]*m.a21_ + v.v_[2]*m.a31_,
			v.v_[0]*m.a12_ + v.v_[1]*m.a22_ + v.v_[2]*m.a32_,
			v.v_[0]*m.a13_ + v.v_[1]*m.a23_ + v.v_[2]*m.a33_);
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
			m.a11_*v.v_[0] + m.a12_*v.v_[1] + m.a13_*v.v_[2],
			m.a21_*v.v_[0] + m.a22_*v.v_[1] + m.a23_*v.v_[2],
			m.a31_*v.v_[0] + m.a32_*v.v_[1] + m.a33_*v.v_[2]);
	}
};

} // namespace algebra

#endif // ALGEBRA_VECTOR_3_HPP
