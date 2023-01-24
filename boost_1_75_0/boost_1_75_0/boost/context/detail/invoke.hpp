
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
ulsw3j/LqSd+kbx+FwyClhLWBw2tPF70cF6Gxv8+lB47kYHKuPLsD2JmY16sx0g1p8agjaUvFmgEc18wiz3dZGwflSbtIkQM9ScLxjXQnW4AIWiERMQIAJ7YH9A1pb0+hviatGHfVv+lfoCpmo/0fgr5xQ5K1obeAqHNmm+IRqxr8tJ9jE8JHN5rZM/hN66S+5pprdgtDZW3gWy0nh4CYx3KhY7LlfUsrGPhQt6DV55cCKRVeAVeWvxCIr/HafRCiGhpiUSSMZvOmc8WXL+2jRACnWkGwz4b6+tsbq5zz8NH+MufuIPB8G5mpeLGzTlf/86CF7+zz1PPXOSLX73KdO8G89kG2AEM16A3RhankQMZ/CUTwECYnWAtuAp8Fa+gjJaAgKXw4tKBN9mFrYUQyVgAY1kbSpSW+Bi26fj9wnsvpZR+sVhIY0wthAiTbdr16vd0It9i3RYAkFv/uvGxbaMQMa+2429Bx7lKJ9SBUMwXJeNxgfzOuzh1vObYu5/k+myHvc1XGf/Y77H1xTVyfycuU1QmEEOmMlivEXIA0uKFp3IC6jXyQuPUOm88dwdeF1ig6IM0NU4/gSsMZvYjiF4eBE90mk4K34JXtGKa2XI+/JYQ4YwC7GNLMR+qzEKVoOgU9kThjwIuvA+JSTFduEnzdS0AJAFPmt/aoPFTOBBDmxKcwCAxlB5QHlcL1PWj7J/OmVYLFlJglaY2
*/