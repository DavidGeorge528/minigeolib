#ifndef ALGEBRA_MATRIX_HPP
#define ALGEBRA_MATRIX_HPP

#include "algebra/details/matrix_base.hpp"

namespace algebra
{

template< unsigned R, unsigned C, typename U, typename UT = unit_traits<U> >
class matrix: public matrix_base< R, C, U, UT>
{
public:

};

} // namespace algebra

#endif // ALGEBRA_MATRIX_HPP
