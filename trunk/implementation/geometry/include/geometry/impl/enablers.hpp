#ifndef GEOMETRY_IMPL_ENABLERS_HPP
#define GEOMETRY_IMPL_ENABLERS_HPP

#include "geometry/coord_system_tags.hpp"
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#define GEOMETRY_ENABLED_IF_3D typename boost::enable_if_c< coord_system::DIMENSIONS == 3>::type* = NULL
#define GEOMETRY_ENABLED_IF_HOMOGENEOUS typename boost::enable_if_c< boost::is_same< typename coord_system::system_type, hcoord_system_tag>::value >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_1D typename boost::enable_if_c< coord_system::DIMENSIONS >=1 >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_2D typename boost::enable_if_c< coord_system::DIMENSIONS >=2 >::type* = NULL
#define GEOMETRY_ENABLED_IF_AT_LEAST_3D typename boost::enable_if_c< coord_system::DIMENSIONS >=3 >::type* = NULL


namespace geometry { namespace impl
{

template< typename CS, typename Tag>
struct is_system_type
{
	BOOST_STATIC_CONSTANT( bool, value = (boost::is_same< Tag, typename CS::system_type>::value));
};

template <typename CS>
struct is_hcoord_system: public is_system_type< CS, hcoord_system_tag> { };

template< typename CS, unsigned D>
struct has_dimensions
{
	BOOST_STATIC_CONSTANT( bool, value = (CS::DIMENSIONS == D));
};

template< typename CS, unsigned D, typename CSType, typename OutType = void>
struct enabled_for: public boost::enable_if_c< has_dimensions<CS,D>::value && is_system_type< CS, CSType>::value, OutType>
{};

} } // namespace impl // namespace geometry

#endif // GEOMETRY_IMPL_ENABLERS_HPP
