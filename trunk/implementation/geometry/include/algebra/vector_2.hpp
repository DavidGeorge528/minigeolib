#ifndef ALGEBRA_VECTOR_2_HPP
#define ALGEBRA_VECTOR_2_HPP

namespace algebra
{

/// \ingroup algebra
/// \brief It specializes a vector of values and the operators specific to vectors for vectors of size 2.
/// \tparam D the number of elements in the vector.
/// \tparam U the type of the element. It should be an arithmetic type.
/// \tparam UT the traits type corresponding to the type of the elements.
/// \sa unit_traits
template< typename U, typename UT>
class vector< 2, U, UT>: public details::vector_base< 2, U, UT>
{
	typedef vector< 2, U, UT> my_type_;
public:
	/// \brief It creates a vector with zeros as elements.
	vector()
	{
		v_[0] = v_[1] = unit_traits_type::zero();
	}

	/// \brief It copies a vector
	vector( const my_type_& org)
	{
		v_[0] = org.v_[0];
		v_[1] = org.v_[1];
	}

	/// \brief It creates a vector using the elements from the provided sequence.
	/// \tparam It the type of iterator providing access to the sequence of elements.
	/// \pre The provided sequence has the size of the vector.
	template< typename It> vector( It begin, It end)
	{
		assert( std::distance( begin, end) == DIMENSIONS);
		std::copy( begin, end, &v_[0]);
	}

	/// \brief It creates a vector using the elements from the provided sequence.
	/// \tparam It the type of iterator providing access to the sequence of elements.
	/// \pre The provided sequence has the size of the vector.
	template< typename It> explicit vector( It begin)
	{
		for( unsigned n = 0; n < DIMENSIONS; ++n, ++begin)
		{
			v_[n] = *begin;
		}
	}

	/// \brief It initializes the vector with the provided elements.
	vector( const U& v0, const U& v1)
	{
		v_[0] = v0;
		v_[1] = v1;
	}

	/// \details
	///		In case of self assignment, it does nothing.
	my_type_& operator=( const my_type_& op)
	{
		if( this != &op)
		{
			v_[0] = op.v_[0];
			v_[1] = op.v_[1];
		}
		return *this;
	}

	/// \brief Vector addition
	friend my_type_ operator+( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] + op2.v_[0], op1.v_[1] + op2.v_[1]);
	}

	/// \brief Vector addition
	my_type_& operator+=( const my_type_& op)
	{
		v_[0] += op.v_[0];
		v_[1] += op.v_[1];
		return *this;
	}

	/// \brief Vector subtraction.
	friend my_type_ operator-( const my_type_& op1, const my_type_& op2)
	{
		return my_type_( op1.v_[0] - op2.v_[0], op1.v_[1] - op2.v_[1]);
	}

	/// \brief Vector subtraction.
	my_type_& operator-=( const my_type_& op)
	{
		v_[0] -= op.v_[0];
		v_[1] -= op.v_[1];
		return *this;
	}

	/// \brief Scalar multiplication
	friend my_type_ operator*( const unit_type& s, const my_type_& v)
	{
		return my_type_( s*v.v_[0], s*v.v_[1]);
	}

	/// \brief Scalar multiplication
	friend my_type_ operator*( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]*s, v.v_[1]*s);
	}

	/// \brief Scalar multiplication
	my_type_& operator*=( const unit_type& s)
	{
		v_[0]*=s;
		v_[1]*=s;
		return *this;
	}

	/// \brief Division by a scalar
	friend my_type_ operator/( const my_type_& v, const unit_type& s)
	{
		return my_type_( v.v_[0]/s, v.v_[1]/s);
	}

	/// \brief Division by a scalar
	my_type_& operator/=( const unit_type& s)
	{
		v_[0]/=s;
		v_[1]/=s;
		return *this;
	}

	/// \brief Multiplication with a matrix.
	friend my_type_ operator*( const my_type_& v, const matrix_type& m)
	{
		return my_type_(
			v.v_[0]*m.a11_ + v.v_[1]*m.a21_,
			v.v_[0]*m.a12_ + v.v_[1]*m.a22_);
	}

	/// \brief Multiplication with a matrix.
	my_type_& operator*=( const matrix_type& m)
	{
		my_type_ result = operator*( *this, m);
		*this = result;
		return *this;
	}

	/// \brief Multiplication with a matrix.
	friend my_type_ operator*( const matrix_type& m, const my_type_& v)
	{
		return my_type_(
			m.a11_*v.v_[0] + m.a12_*v.v_[1],
			m.a21_*v.v_[0] + m.a22_*v.v_[1]);
	}

	/// \brief Dot product
	/// \todo: unit test
	friend unit_type operator*( const my_type_& op1, const my_type_& op2)
	{
		return op1.v_[0]*op2.v_[0] + op1.v_[1]*op2.v_[1];
	}
};

} // namespace algebra

#endif // ALGEBRA_VECTOR_2_HPP
