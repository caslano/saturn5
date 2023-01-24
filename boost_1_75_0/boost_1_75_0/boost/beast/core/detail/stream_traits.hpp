//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STREAM_TRAITS_HPP
#define BOOST_BEAST_DETAIL_STREAM_TRAITS_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/type_traits/make_void.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------
//
// get_lowest_layer
// lowest_layer_type
// detail::has_next_layer
//

template <class T>
std::false_type has_next_layer_impl(void*);

template <class T>
auto has_next_layer_impl(decltype(nullptr)) ->
    decltype(std::declval<T&>().next_layer(), std::true_type{});

template <class T>
using has_next_layer = decltype(has_next_layer_impl<T>(nullptr));

template<class T, bool = has_next_layer<T>::value>
struct lowest_layer_type_impl
{
    using type = typename std::remove_reference<T>::type;
};

template<class T>
struct lowest_layer_type_impl<T, true>
{
    using type = typename lowest_layer_type_impl<
        decltype(std::declval<T&>().next_layer())>::type;
};

template<class T>
using lowest_layer_type = typename
    lowest_layer_type_impl<T>::type;

template<class T>
T&
get_lowest_layer_impl(
    T& t, std::false_type) noexcept
{
    return t;
}

template<class T>
lowest_layer_type<T>&
get_lowest_layer_impl(
    T& t, std::true_type) noexcept
{
    return get_lowest_layer_impl(t.next_layer(),
        has_next_layer<typename std::decay<
            decltype(t.next_layer())>::type>{});
}

//------------------------------------------------------------------------------

// Types that meet the requirements,
// for use with std::declval only.
template<class BufferType>
struct BufferSequence
{
    using value_type = BufferType;
    using const_iterator = BufferType const*;
    ~BufferSequence() = default;
    BufferSequence(BufferSequence const&) = default;
    const_iterator begin() const noexcept { return {}; }
    const_iterator end() const noexcept { return {}; }
};
using ConstBufferSequence =
    BufferSequence<net::const_buffer>;
using MutableBufferSequence =
    BufferSequence<net::mutable_buffer>;

//

// Types that meet the requirements,
// for use with std::declval only.
struct StreamHandler
{
    StreamHandler(StreamHandler const&) = default;
    void operator()(error_code, std::size_t) {}
};
using ReadHandler = StreamHandler;
using WriteHandler = StreamHandler;

//------------------------------------------------------------------------------

} // detail
} // beast
} // boost

#endif

/* stream_traits.hpp
QrbpE0hAjE9wRSmAYbc4zPV4z/8LcwRhRL4VrwBxq+QP6o0vNRjyWHgKqeat0UehtoQnWZP2sBZvRmDRfsn8U+IntZ/LkgurOMppU7/I6FEmIICd6nirMphp+JKZlM0jaj1pE0Z+hvXpanOyn7myC08rHLn06oO/cvme4A38FLpqPt0Q+unSkt4SoLjjnEigCLEt1PuLtFZ09zObHzto0g5sVxmTMELGlpX1JvNCIDuB1qp1+yPwBQS9P91sjiwiNnVbIOFqTt+cC2bJyFEJxqhUPbio+PKF9g75PJeYf38aD9H5HO+Q4EVmPLm7EBef7flrwYY8Xx2d0ZDdWpaU9VoCEcqXb0Gv+OTSjmB5W2NSG6Jf+Z3po2ikS14IuQOYysC4c7mJMus6usm1ya8HHoM5ipDYJCCt9WtkEDVF2tlOfZvsR1ED722UThA82oO/VBRMLBk8s1/EXvBZunKzAPi58WK2ReAW16ijxK9Dx7t5qwOo0tFysUEKcvH56vJ8rFPsCh7bshare3jvDZeFbDknPowTpNa6kM9YyEFYcXu24fWOigOlASLlxx8IHvcADwoYAMMQwOdGpe+5ZRFQ8/u1+Rg6JHkmsRju+eDkbx8uHP09k/P8Bhl9FHBYMpfcDeZxiBgbON/tcMMGWLeydfJ9VFFQOsy+NdGqwzuHk5bXr6/o1K3uTnWWBi2Ricka6+k5kRmYtJ1cp60P
*/