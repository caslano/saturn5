
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

// http://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
template< typename X, typename Y >
using disable_overload =
    typename std::enable_if<
        ! std::is_base_of<
            X,
            typename std::decay< Y >::type
        >::value
    >::type;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
uh7Pcu0AJjuMrwbEc8HGMB42hUmwGWwHm8t2tYF9YDvpnx7SP53gbWLL+JLzRo41HMYXdVXjax6MgAtgHbgQNoEPyzhZJPkNcMk5gJxXrYKe+N3kOtjPxPOFl2Ft6PJh/oH+sBUMgD3hTfBmGCzzXwgc/Q/2zgO8iioLwDPvvbyU90J6SAJCCKG3ANIEAUEFAREVFFGMkQSIBhKT0BQVFDsqKvayqKioKKiIXXFFRUVX14Zl
*/