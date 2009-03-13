#ifndef GEOMETRY_IMPL_ENABLERS_HPP
#define GEOMETRY_IMPL_ENABLERS_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace geometry { namespace impl
{

template< typename CS, typename Tag>
struct is_system_type
{
	BOOST_STATIC_CONSTANT( bool, value = (boost::is_same< Tag, typename CS::system_type>::value));
};

template< typename CS, unsigned D>
struct has_dimensions
{
	BOOST_STATIC_CONSTANT( bool, value = (CS::DIMENSIONS == D));
};

template< typename E, typename Tag>
struct is_a
{
	BOOST_STATIC_CONSTANT( bool, value = (boost::is_same< Tag, typename E::tag>::value));
};

template< typename CS, unsigned D, typename CSType, typename OutType = void>
struct enabled_for: public boost::enable_if_c< has_dimensions<CS,D>::value && is_system_type< CS, CSType>::value, OutType>
{};

} } // namespace impl // namespace geometry

#endif // GEOMETRY_IMPL_ENABLERS_HPP
