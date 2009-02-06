#ifndef GEOMETRY_IMPL_ENABLERS_HPP
#define GEOMETRY_IMPL_ENABLERS_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#define GEOMETRY_ENABLED_IF_3D typename boost::enable_if_c< coord_system::DIMENSIONS == 3>::type* = NULL
#define GEOMETRY_ENABLED_IF_HOMOGENEOUS typename boost::enable_if_c< boost::is_same< typename coord_system::system_type, hcoord_system_tag>::value >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_1D typename boost::enable_if_c< coord_system::DIMENSIONS >=1 >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_2D typename boost::enable_if_c< coord_system::DIMENSIONS >=2 >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_3D typename boost::enable_if_c< coord_system::DIMENSIONS >=3 >::type* = NULL

#endif // GEOMETRY_IMPL_ENABLERS_HPP
