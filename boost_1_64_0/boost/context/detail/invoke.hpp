
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_INVOKE_H
#define BOOST_CONTEXT_DETAIL_INVOKE_H

#include <functional>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename ... Args >
typename std::enable_if<
    std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::mem_fn( fn)( std::forward< Args >( args) ... );   
}

template< typename Fn, typename ... Args >
typename std::enable_if<
    ! std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::forward< Fn >( fn)( std::forward< Args >( args) ... );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_INVOKE_H

/* invoke.hpp
vGI0XEhDxtVZmnK7LQ5aadgL+XqXFT8Z9W9j9LMPjxcbbfC3M3f5X3jdbB2eWUFovbAUSGWB0fYnqI8zdBMBtE7EdtkI1n1hXgtcaT7/iGdMjpFXGwJO72ljfNCk5QpLGZq/vyQYl3mseNb8z9Wy4FVR1Awoc7D63PRawXRuhYD4VOdev/fY1hN+o87lAmgxngc6V5+rl1wQOVzxgWHS4DBpkxdHZGH/n4nilnE4awljtQ1SNsfhzQnl83i3qjDk9+xjkDicGnMyxqXfxRBPYiSuCoi9dXFPN/xZqOhVXU1paUlOfQ+dQhf97cexaVBgjDXBE5oxwAPCbUw7YliEIZV5WbpvsiUljaC44HiGncjJj9uiTuY4AueUHkp/8pinYDJg0OVlcoVUi18t+TdtpubHvc0+HxZBrDnD5WoUO9bRzzMiyo9y4PJm8L42Q4Jcjvhppo5c9052ktXXJGIRxSkL07QV5xbzY0I/qZr4bqGBwzKR0ArIKL1y7L4HbwX6S9s+zaGWwrVgnTum6S2iv7XM0O1ySu8ZQuq+c8prRYuE4NUSjUdUij2OcA==
*/