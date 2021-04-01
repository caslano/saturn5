
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
nq8XFZ7oqLN4cfEjzRk7uucHgQp/MuG5ocxtmQzHLNNhTNGtsoEqiGNk6kTiKqMBds+ypUbZcnPxTCxXNSINYQpS4MZ/6J0YXoFBhF+/fjdn4X3dQ9wuOm108CD9l9KY4xKGLFk6gfd/vX9CmvbN3QOfgpUgEPV3wv1wz5HeuSuD8xCdGlhGAlyrnW6vm4c60WraX1KAaVSN0ZWZEsqMd7+JekvPFfxJ9uuclpUhYJeJOB60LAZA46lj4gysVYGQu2QeiLCcmNqtOINLonl8l+qhTOJzL7NIrkEvhPh3NyMPP1be7s171wyrQM+zQPsujYm7exOUEX+/kHR1PhMnp3FYBNWSWODgZKyov0xuZu9TPRxQveMtwW15zeSbmbMc65c0sNsMAlH0OW8jMHTA6JQuemBP8pKJghOgJEXoTewFJDNJPyCxno5+UBhaQueT4+wNKZPd7wzAzB2OxP2oFkxsW716GEtwcw3QT1gGgJt/IUkfYrIeXNzrs6W5Nd5frJbEGGmBupOrG3ADYWjplzWigVSFyxsueKqM9DILvtxBraCw5ynIkF+IVw==
*/