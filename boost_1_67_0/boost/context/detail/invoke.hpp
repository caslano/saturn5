
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
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
*/