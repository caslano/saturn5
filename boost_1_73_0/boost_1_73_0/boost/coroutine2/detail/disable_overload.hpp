
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/disable_overload.hpp>

#include <boost/coroutine2/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename X, typename Y >
using disable_overload = boost::context::detail::disable_overload< X, Y >;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
OXvG+r7uLxsuOPupgxe8uY+xe4k+5khkSPtVjev+Z9ANyfETfb9g7D2i77i91f9Yv/f/+6ltF3y95Sc3bmPs0j5I77MtVjZ+1fEZJZ+VWIsfb/kvxn5M9N/f+ta+Oi1295qPlrc8UnZ/f8b2En3HIwN+PeGHmz6v3jpwV3Nwy0uMnSD63+u8ozvLN23895EzNw06+tXfwDj6Iv3wilf3ff3JLR8v6x434tGNV4DubiV6ybMrN544r+mpH3XNffg=
*/