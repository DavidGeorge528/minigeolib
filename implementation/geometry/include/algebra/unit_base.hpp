#ifndef ALGEBRA_UNIT_BASE_HPP
#define ALGEBRA_UNIT_BASE_HPP

namespace algebra
{

// TEST
template< typename U, typename Tag, typename UT = unit_traits< U> >
class unit_base
{
public:
	typedef U unit_type;

	unit_base( const unit_type& value = UT::zero())
		: value_( value) 
	{
	}

	operator unit_type() const { return value_; }

	friend unit_base operator+( const unit_base& op1, const unit_base& op2)
	{
		return op1.value_ + op2.value_;
	}

	unit_base& operator+=( const unit_base& op2)
	{
		value_ += op2;
		return *this;
	}

	friend unit_base operator-( const unit_base& op1, const unit_base& op2)
	{
		return op1.value_ - op2.value_;
	}

	unit_base& operator-=( const unit_base& op2)
	{
		value_ -= op2;
		return *this;
	}

	friend unit_base operator*( const unit_base& op1, const unit_base& op2)
	{
		return op1.value_ * op2.value_;
	}


	unit_base& operator*=( const unit_base& op2)
	{
		value_ *= op2.value_;
		return *this;
	}

	friend unit_base operator/( const unit_base& op1, const unit_base& op2)
	{
		return op1.value_ / op2.value_;
	}

	unit_base& operator/=( const unit_base& op2)
	{
		value_ /= op2.value_;
		return *this;
	}

	const unit_type& value() const { return value_; }
private:
	unit_type value_;
};

} // algebra

#endif // ALGEBRA_UNIT_BASE_HPP
