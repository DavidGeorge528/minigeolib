#ifndef GEOMETRY_IMPL_VECTOR_UTILS_HPP
#define GEOMETRY_IMPL_VECTOR_UTILS_HPP

#include <cmath>

namespace geometry
{
namespace impl
{

/// \brief Utility function for calculating dot product of two vectors with three elements.
/// \tparam U the type of the values in the vectors.
template< typename U>
inline U dot_product( const U& x1, const U& y1, const U& z1, const U& x2, const U& y2, const U& z2)
{
	return x1*x2 + y1*y2 + z1*z2;
}

/// \brief Utility function for calculating the norm of a vector with three elements.
/// \tparam U the type of the values in the vector.
template< typename U>
inline U norm( const U& x, const U& y, const U& z)
{
	return std::sqrt( x*x + y*y + z*z);
}

/// \brief Utility function for calculating the cosinus of the angle between two vectors.
/// \tparam U the type of the values in the vectors.
template< typename U>
inline U cos_angle( const U& x1, const U& y1, const U& z1, const U& x2, const U& y2, const U& z2)
{
	return dot_product( x1, y1, z1, x2, y2, z2) / (norm( x1, y1, z1) * norm( x2, y2, z2));
}

} // namespace impl
} // namespace geometry

#endif // GEOMETRY_IMPL_VECTOR_UTILS_HPP
