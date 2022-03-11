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