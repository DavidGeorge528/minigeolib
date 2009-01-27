#ifndef ALGEBRA_MATRIX_HPP
#define ALGEBRA_MATRIX_HPP

#include "algebra/details/matrix_base.hpp"
#include "algebra/unit_traits.hpp"
#include <cassert>

namespace algebra
{

/// \ingroup algebra
/// \brief It implements a matrix.
/// \tparam R the number of rows in the matrix.
/// \tparam C the number of columns in the matrix.
/// \tparam U the type of the element. It should be an arithmetic type.
/// \tparam UT the traits type corresponding to the type of the elements.
/// \sa unit_traits
template< unsigned R, unsigned C, typename U, typename UT = unit_traits<U> >
class matrix: public details::matrix_base< R, C, U, UT>
{
public:
	/// \brief It provides access to the element at the specified position.
	/// \pre The specified position is valid.
	/// \todo Implement for generic matrix.
	unit_type& operator()( unsigned r, unsigned c);
	const unit_type& operator()( unsigned r, unsigned c) const;

	/// \brief It provides the identity matrix (if applicable).
	/// \todo Implement for generic matrix. Enable only if R = C.
	static const matrix& IDENTITY();

	/// \brief It adds two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	/// \todo Implement for generic matrix.
	friend matrix operator+( const matrix& left_op, const matrix& right_op);

	/// \brief It adds two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	/// \todo Implement for generic matrix.
	matrix& operator+=( const matrix& right_op);

	/// \brief It subtracts two matrices.
	/// \param left_op the left operand.
	/// \param right_op the right operand.
	/// \return the resulted matrix.
	/// \todo Implement for generic matrix.
	friend matrix operator-( const matrix& left_op, const matrix& right_op);

	/// \brief It subtracts two matrices.
	/// \param right_op the right operand.
	/// \return this object.
	/// \todo Implement for generic matrix.
	matrix& operator-=( const matrix& right_op);

	/// \brief It implements the product of two matrices.
	/// \todo Implement for generic matrix.
	template< unsigned R1, unsigned C1, unsigned R2>
	friend matrix<R1,R2,U,UT> operator*( const matrix<R1,C1,U,UT>& left_op, const matrix<C1,R2,U,UT>& right_op);

	/// \brief It implements the product of two matrices.
	/// \todo Implement for generic matrix. Enable only if square matrix.
	matrix& operator*=( const matrix& right_op);

	/// \brief It implements the product between a matrix and a scalar.
	/// \todo Implement for generic matrix.
	friend matrix operator*( const unit_type& s, const matrix& right_op);

	/// \copydoc operator*( const unit_type&, const matrix&);
	/// \todo Implement for generic matrix.
	friend matrix operator*( const matrix& left_op, const unit_type& s);

	/// \brief It implements the product between a matrix and a scalar.
	/// \todo Implement for generic matrix.
	matrix& operator*=( const unit_type& s);

	/// \brief It implements the division of a matrix with a scalar.
	/// \todo Implement for generic matrix.
	friend matrix operator/( const matrix& left_op, const unit_type& s);

	/// \brief It implements the division of a matrix with a scalar.
	/// \todo Implement for generic matrix.
	matrix& operator/=( const unit_type& s);
};

} // namespace algebra

#include "algebra/matrix_2_2.hpp"
#include "algebra/matrix_3_3.hpp"
#include "algebra/matrix_4_4.hpp"

#endif // ALGEBRA_MATRIX_HPP
