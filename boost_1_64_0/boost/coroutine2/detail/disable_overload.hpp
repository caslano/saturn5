
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
ZqrjYILCZGANePwcii4U+6vEKRBpuoqjZYDI/KOm/U3gZX/nJ0zj7pJqgGbvLDwt5v+a6c8eNcTUR1pvTK4TjHnKu/oVr8SKI3aXHYRD2ZOBqQ3UzYHimdQqxFRwHwt7xVtTUbhSYegf3mSCLuqbKlXX7irvbftSZmTXc+LTy7WQRiHoO+LgRnAee9HdkPoI87TAsFmkRuMJknHzq9Tl45DE79ELSzYW5R+WsZOK4HBfMdXqU9Auin8Xr3ViuxPyqA3/iHytRMHfspT3MK3v8x74QRLkGf634HCgxZYTLI/4K4Zn435ItJw6E6aeTrH4LVHltVw1P7dtkqpX5JN1wUKEeclYaxdVVA1lwfS/9DTMixgWW6fVW/ZcaCpYziuSy4zbPgSKVIrDGlC2721Sv3+1WzjcfUn67cdB324bOTyEaIc2G9MYOUwp3zTNfGLLLFpg/Oqa4ARbE0Q0OdcN9u3Uv0Q0BaR2BzTcm0De2D6y9Gc9j2U3e5or3qaqViHSDMEHOvAcqWeBxyBn2OUfRg2oXXnAebKB8z68Yo61ZpXbaPwcgWrVnYWP4A==
*/