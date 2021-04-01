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
6U556KUG4GVJbtm2RKMMqxbHV+dW2AzJrkfau5s5eTPfBQieBNUT7SzVenrXJ5i0tyIl7+9R/m8mJ8B9osqa02VIsLPsx9ShL8jFj1kGrEozwEErPf770NPdt1hlT90YynzMAoYpNd2ETX6kzgHP9CdgB59Oc/f6NQKL3kMLoRa8YSPc+QsWBqMexzOR0O6wgIaGycPBEgoZuHPZcJ5FXRhY2wHxEAyp8cwTlbIkw3bHq/bXzbFrtbZYkBMeNke7zyLhEc9t4nO1se33GhX1bxrss7ubENu572o52ZGMlyGJcCIaP3wT2LYoLdA6mBnK6kq6bRnY8I/1fJUOoYsTOgLEw5+csageE/miud5ltrPZVuhd2JhusHAYBxvfmF8Wda00zJsPxwveB+xILpihuAIiDD+0jBlk1x28iRPBBGpKvE3VZfv+Xc23ZYCI+dHIGusBpfO6k7UyKHHDeYRa8I5xk4b7iFMBZt88aIm9CWnJMbKDfhwLJUfp6Qr580IEGJYl1vWJ7w/dy1sGnwRQhQUNWtXSlY8XJOSEICdhMHingukjgqg9Gm2P4w==
*/