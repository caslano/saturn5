
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
+VAipqYzfLE4dGWI4xo560zAyA8Ngp8TpZLFjUrXZJBnSdmAK3pFdt7TK24ioaFFhQsJwZr4fgGYEJCyEh313KbD2qvRUKwmkX7BOxDMaCFEl4f7RorKhDvY4G9GG5jpjo9AgmiGZGQsq3cTSI8L2QA5KT02h4tM7Cm51otYuqOCJ3EyfzmRCPWtKJG6CYzakFJSzFU3pj1Y/iDpJig98fAH2pUPVCr4AaZCv5pwA73Tq0T0Gi8XyxeBRIDozTCSNSvM2HpjEaAohF8CemV+yTksEXLrKPW5WjeMJcBZkE9RS++1rEd8GwhvUWftpd67/HR4p0akqyVNNdgqZ3vey7aAxkwUkkT/aT1hAXsN02+1Gwft+XlxHXT191mSxolcT98JK1GEp1WdLHdUTaxfth9qPErCtxatldD7O/6l3cWWoZvKnYBbTpCZMaEPkpyg+ClL/YkPNdOk2HjZbagykQ+50CtlXgur167rggD9BhiOh1ezSkv5sKlhL0XT436TOrqzYjLi3fw0Olq92+RJPtThSoxBuOjKyq9Uzuy/rvco5cgZzFLev5GaxA==
*/