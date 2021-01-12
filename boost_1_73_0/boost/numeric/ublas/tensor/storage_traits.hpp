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
XPGt64F3sk493mL7oummZpTLtmL47fPEdsTPfivRXhfaJzd4b+MzkTptdzV+NJmCiQeLQceWqoHw/dlLZ0ogCdlfMS4/XRO3inCds/nCOBYAH95E8MFCtkKCeyoxLndxrHOf6Ep1V9mgPNM7miKj5fxYbpCOyUxNPB/37DCOayK45xJuluxG+7Ply7Rd7/O9o4OlmXFahtMhm+IXeEeHcsY8ety7AG+y3q5494VeJpnCdoe9
*/