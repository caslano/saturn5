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
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
*/