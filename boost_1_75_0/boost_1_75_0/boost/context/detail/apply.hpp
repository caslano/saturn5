
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_APPLY_H
#define BOOST_CONTEXT_DETAIL_APPLY_H

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/detail/index_sequence.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename Tpl, std::size_t ... I >
auto
apply_impl( Fn && fn, Tpl && tpl, index_sequence< I ... >) 
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    -> decltype( boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#else
    -> decltype( std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#endif
{
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    return boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#else
    return std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#endif
}

template< typename Fn, typename Tpl >
auto
apply( Fn && fn, Tpl && tpl) 
    -> decltype( apply_impl( std::forward< Fn >( fn),
                 std::forward< Tpl >( tpl),
                 make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{}) )
{
    return apply_impl( std::forward< Fn >( fn),
                       std::forward< Tpl >( tpl),
                       make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{});
}

}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_APPLY_H

/* apply.hpp
AlMbnA30tsejtURoi9FzfEaYbuscs511xupB0JbJXg1ZBs6CCUShtxasBuuj6RyItPlCMz84gptNqcuQiONxWOEJY0RFyNJTojGdg4sQetFJF+LHoQ9fuGGkTV1mRZtw4qNpGev7k+/nfIzz+1YQSWSg9di6A1oOhA2g6G3r98souMnXFw0o0FgUbUSBJnwYvj+AQxpOGdKRIwgAwmoWuzmICpVbtFNUtaS2NUI4Ct3DUaE0UIdstlrWVK5GWRksC+nx3mKsQVlCUk+2h5vHnvcijQiDbtisyw145xtSzcUqSedciHzIEJgNK2nkltRbYvQ7Qh4ogLZycCmkF78+/BXDgB3N/2btxUXjsizXDXS5gAYMSFEAT105jh0RKGkxpp32s6r9Yx2AD1/VAgEh/HfpzaXq7a3bAgB8UdwBZIF3C6opMcDCC0w2xR/fAyfxXoGBuZmFISF7FiElmY4suYox9dByNZi4JoQTTW0oejkXX3wfzgBzQIy/zSnGmqq2bbvt2JJKWAFa4JVACdcAgJBh9LaMf6vGdAQSg92QXMG3ddDE/92SK5CEPLD1OBeAykRN6Gj4Dm9d6HbsXKPBUy2xiGZ9kxloOvtNfciS1+A8mDapJlgdxOiDQwgF0pFtXmOrNycXOZV2qEwGrYVFKA8o1LBHjsKjsRhknmGVwzqL8w4jalxdwmJBZWsqsY/WMW4poiUgoknf0eA0
*/