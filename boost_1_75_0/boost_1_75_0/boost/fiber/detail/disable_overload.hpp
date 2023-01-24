
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/disable_overload.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename Y >
using disable_overload = boost::context::detail::disable_overload< X, Y >;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
PzLXB3CB6XkNPreUH4JnWZ4V7ivEmwtXwBuP1QlZ1dkz5a00+vjScFh6TyVAtwrXV9+hwnWlCtcFHK45pivsSav4IIaLZYsDKwMsdK5ldT6rXI32bbuVT5LhvRuDLMco329OMOXKVRQbmR18j6UlmfhnC5WPhiJycJMVuhxuhUzRDBGsIbO5vDUYwnwnSvrZsnKZ12UoaZ+pUKF8hQ1xkSiIBMUBnQxigh4fg44th3QFmVCAvSOwzV9GjYAOLhc1EssEUlpGOzAPoMeLNLsqShc4uzm0ukY8WyOeVZyCRWfbKrEHgzQCRGKUw3ogwUJw3Y4DP29nhXi2Qm0nCOw0x/555cct5WRje0C5/sdgsL4zB7ShZu6hDl8KWsqjzSCUsK8xUcrUBqXHmSRcqxz4LxNs0NIpV0we2pylUe6wjG0oHcGMom0RH7Ce+CM3OBE1sP3jqcmZ54E9xGhTiT59D0LpmBoG4kXaByA1BPyX5iStcX4Dl7vsEBov8mDADcYA12+9+xUd69IFcRmkuxeqjxVQGQVTdarqg0qg6uNwqUPMX1tt/jhGxkdLxCN/A5c6pB1FghyOGJ3UAdOIRg6gQ+3vPPW8G5BDRoQ/D6Tr93lU5Ms8Ogdf2nk+uHNNWxNmUK1aG8dgz8emyQuPWfH3BpLc4d+82qsD6foPfn0Om9mhzOW/vVAOTBGn8geP8O/cz6/35hlzzLDDcg1p
*/