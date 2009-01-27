#ifndef ALG_UNIT_TRAITS_HPP
#define ALG_UNIT_TRAITS_HPP

namespace algebra
{

template< typename U>
struct unit_traits
{
	typedef U unit_type;

	static U zero() { return 0; }
	static U one() { return 1; }
};

} // namespace algebra

#endif // ALG_UNIT_TRAITS_HPP
