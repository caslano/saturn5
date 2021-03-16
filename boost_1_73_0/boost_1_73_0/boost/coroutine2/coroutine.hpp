
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_COROUTINE_H
#define BOOST_COROUTINES2_COROUTINE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

template< typename T >
struct coroutine {
    using pull_type = detail::pull_coroutine< T >;
    using push_type = detail::push_coroutine< T >;
};

template< typename T >
using asymmetric_coroutine = coroutine< T >;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_COROUTINE_H

/* coroutine.hpp
YQJiLspI95gRhKi+02t4Pb8ngVHC4PViYUrSXZoLOwKtaJM69At10mES0p/VU2gtHtFPapHLocP1CE9yQttGAApx4ML8YpXVdHpT74VlVTy/sfkbaIqL9GMIskzJMmJYLfgwauwlc45iSlGwP5bjijj5QIn0Reyc53XVkxXIBcLtbQlyK+RrvsEKRPQxm8FE6RUgIIcCi8vopKVS8YSoABdjXULSx80gSqZTST1jweUnGOahYzquNGRR5nFTslk=
*/