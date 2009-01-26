#ifndef ALGEBRA_MATRIX_HPP
#define ALGEBRA_MATRIX_HPP

#include "algebra/details/matrix_base.hpp"
#include "algebra/unit_traits.hpp"

namespace algebra
{

template< unsigned R, unsigned C, typename U, typename UT = unit_traits<U> >
class matrix: public details::matrix_base< R, C, U, UT>
{
public:

};

} // namespace algebra

#include "algebra/matrix_2_2.hpp"
#include "algebra/matrix_3_3.hpp"
#include "algebra/matrix_4_4.hpp"

#endif // ALGEBRA_MATRIX_HPP
