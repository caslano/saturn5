//
//  Copyright (c) 2018, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen Germany
//


#ifndef _BOOST_STORAGE_TRAITS_HPP_
#define _BOOST_STORAGE_TRAITS_HPP_

#include <vector>
#include <array>

namespace boost {
namespace numeric {
namespace ublas {


template <class A>
struct storage_traits;


template <class V, class A>
struct storage_traits<std::vector<V,A>>
{
	using array_type      = std::vector<V,A>;

	using size_type       = typename array_type::size_type;
	using difference_type = typename array_type::difference_type;
	using value_type      = typename array_type::value_type;

	using reference       = typename array_type::reference;
	using const_reference = typename array_type::const_reference;

	using pointer         = typename array_type::pointer;
	using const_pointer   = typename array_type::const_pointer;

	using iterator        = typename array_type::iterator;
	using const_iterator  = typename array_type::const_iterator;

	using reverse_iterator        = typename array_type::reverse_iterator;
	using const_reverse_iterator  = typename array_type::const_reverse_iterator;

	template<class U>
	using rebind = std::vector<U, typename std::allocator_traits<A>::template rebind_alloc<U>>;
};


template <class V, std::size_t N>
struct storage_traits<std::array<V,N>>
{
	using array_type      = std::array<V,N>;

	using size_type       = typename array_type::size_type;
	using difference_type = typename array_type::difference_type;
	using value_type      = typename array_type::value_type;

	using reference       = typename array_type::reference;
	using const_reference = typename array_type::const_reference;

	using pointer         = typename array_type::pointer;
	using const_pointer   = typename array_type::const_pointer;

	using iterator        = typename array_type::iterator;
	using const_iterator  = typename array_type::const_iterator;

	using reverse_iterator        = typename array_type::reverse_iterator;
	using const_reverse_iterator  = typename array_type::const_reverse_iterator;

	template<class U>
	using rebind = std::array<U,N>;
};

} // ublas
} // numeric
} // boost


#endif // _BOOST_STORAGE_TRAITS_HPP_

/* storage_traits.hpp
8nUlOgDQ8VuII8fXXCf3SACsBOGHh458iZyfwvgTjBVcdrAndWnTieUMikRDhUMsrtuQZEOWZZdjEf1shzLgMI7oMM5F6laGs+l+t/czFh5d3j38J4YjEY+1ZnQXkmcWTNecSWbYMIKFxxv54oFbRH6duMiCIOTwSWWxsAN6KR+eOVdmPDBWQV9qv0t2QMoiH+19sqTZQN2GCnPdRf8r4lBSpK9hDpN6rpHfP08n4W/dNwJFDQfGHAsBSn9ONbYH9bA9fBEwzCyyikzC5esF07s/qeMtCS1mcPi+OHEVj0b8ItlQWxZlkkSkceNT8KGebb+9hzfQNU8Pvyv23yKeW7+H5nzDPR097HKugGGhL07lqXUe/1kopvXrJ52E0E30iA5pNHXcz45T6qFWCv3mOm7wDD/deuZ8bxAu5CtFJsFr5OmhEo8i+IqLcGPcwLk6qtAbXh3MfTJEHw6WuY7k0ykaTfGpRhVyKANtcDPviTS3fykqDDPHEZQaiDKvds7YRZtnmJtoL2syBaVJp5ifxWjsgnd9FLzo/2pQmJJV5VcFoXrWON/Ber+DES75F08x0q/o3Bx9hm1z6HnKhPSB9IU8j/4Jwu/gxmZohpy/rdwceSAYhNfZyY6Ay34inm540p4wIH4w1MhTialVJrmkxkg6NhZhDMAdqd+CPZTBmYGG2209F3TgL9wR3BNfkDPNu0qydCHTvvLw+WyA
*/