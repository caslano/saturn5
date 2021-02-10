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
CEfz0/PJ7H0I60wmmQPZqBpMpupcQMavEDQmKK+2GBXXFlRK4QQupLEEWFupygFxI1jUhXEYjp7nRgG/4jLnMRFxC5m1lXkdRUmtc1IfCZWYKNltf5DZ4m4n5ySi4BtQlQWroDYYgvMMoVBCpm6lhJCxquNcmixs1RBVKSKlwWCeOyyKk2i2shGWTXpC5wYVKZbWLUaVxlGtM1V840h5dChprUsiojyQk1CU5hDqUqD2zn7nO4ompz7Bj5am1StAlSQGOqMlTJYdiLmRJoRPk9WH+dkKPo0Wi9FsdQ7zdzCanTuwj5PZMZVeEpkGvK40GiLXIIsqlygazl93RcFTWSZ5LRA6Fg2VqhPcMxVYCIzrS2+WJVWMfLpJxjX0zxbTXvA1ADiiJ+i70g+bt0QJ110G3vrXMZt/HAb0TaZd58YucxXznMlS2q5zYO+n88PRlI2m0x48aYN64PAB0koTedo1lqqiQ+g8QOlBSu2I4qLs9IY+RqOlusJqvFyx8WLBTkZ/zRfscHTsPt86NQ6EFHos5GbTIA23Qp84+88F3At6QH9fYZIjL+uq+7+VRX14J7Wx1OjW953LsM1o0Ki9eKxqPzrN+IKqNZzOl6sBUDnBl4hRIA2Yz3bo0zk/XTFaQgfldTzu9vd4cThf
*/