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
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
*/