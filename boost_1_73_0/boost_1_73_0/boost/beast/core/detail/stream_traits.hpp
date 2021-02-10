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
GAroizDLw0nk6SNYk/FAnSBxvCN2hfSWMWMPoOfh4eHg0V3G8YEHNz8T1d5Ba5RiMfwfa2dFBCGUP6+YCqxUrB73Ick+bW197VRrBivnc2gPelMbg0GFqzgjBWa5G+UhsAvAaCSmc8Nxw4TjVCpd7RAWQwalYnkfxEUGHf+7gLlkDK1ZHoShmElyEuMD5PaVVSZFKkPShS9XMbkZbApLUgnMkQTmvpu7NDEjzHgkNPLcFETIUYjxA/yGNI9VM9f7Atrw3J0/BJEXFnDQ92SSB8uz2gic5RA7zJujBUAz95tjcw9qWFuc+5sEcz+Im0MyTaO1IbINFVEwvPMHX86DSIrryQeHwHPhJCksl6I9Ii1OhHFKtBYOSMWwI0J82ipdgCFGCaIMmckPozvnx/74+9GkL7pCkZlIjklRHO3/R6awWiCvdnpEpYywMNsgcjMefRj3JxOmsoUIrmXEgZK9igDd6J5oEWh+COOZS44PhiuGG4qJqxVgB6vpeL0Y0ODRExYgf0wkZMC+0gJZk6MIDLBe/LojxDms7Vp02K9OcL8oSFN5gMjqMJzQIA2xuTkaU052nkRF6IQlG1QiwfkB1oFL6MUhAO6YSC+YB17d3beJdw7pG8KJDq0gKQB6OBcomG5q2+gs+Lqcwof6
*/