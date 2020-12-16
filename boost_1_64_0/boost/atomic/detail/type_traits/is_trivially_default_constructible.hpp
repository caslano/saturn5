/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_default_constructible.hpp
 *
 * This header defines \c is_trivially_default_constructible type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/has_trivial_constructor.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::is_trivially_default_constructible;
#elif !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< typename T >
using is_trivially_default_constructible = boost::has_trivial_constructor< T >;
#else
template< typename T >
struct is_trivially_default_constructible : public boost::has_trivial_constructor< T > {};
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

/* is_trivially_default_constructible.hpp
TGPzltqu5arPffc6fPIerj0lbNezbT7SH5M8xTF7egwiFBe3+joeBg4pbn/eUA6M2xbMHsu0m3NGX4Z3x3ljB8b3nfbjCV0sOSp0/4SzCQ/Z3IOtMf6HK1fEzIdLtf+cfP1N/42U+GxX3gozdw6TtFnaZ45sfuA3GDngWZKeo3F22pd4pnwT8BT29waKHI7OUvtnjsqckTkGz9bQadEROk4FL6OQNA1h15goZQ7xXcO978K2Ds/nSz0cyIoYnvVC/fbmdNX5LNX5+lidt3aYqD5Y9+s9ur9b4pMDdX+npE1q45S2o/sHPHp5QfXi1237e1IkohtnXrlKudfXczMdDH4SPGMcf3y9TTfRpSshXq9auVzn8RHCr5W46sbJP0PSt+aJP8aaegaLtl/TRxn/8KMkfl6KK3+0fmVr/jKTv1ji5cSLJb4iJv/Sxhq9bzn5p5pv9KZK/DTJ35gh+VkUxfjERsbvjz6aYSdI1U1fnnOf6XfiMKol3ivS3eSPmnnnLEk71cgukWvcb75ZypX0Scqp5us8iTM7kEPmN3PuZjnXVqeKVctc3ySdLOWektKWLuoza49bJf3kCJ4rdD52yr3XmoBNZdo2l+MPS7Plngu6QoL7OAz4hsu3L3GuJ/FW+5Fbrdx/P9DzK6pXLHb7hh8hnGaxKzlXA9LXnBNbUr/w5pw0WP3Cm3PYhPELT79zTvqd+h2bc7boBB9uvVvjKffFxis98ctM3HAcmfw+PB+Z1wh3sGdL1rplQ3/5kXe/PfHBPivm1CR9Z3bWd+bl4jvz8yUL9r8x5dEd1T+d+ei43y3dk/SdmYjvTKWyy3rgiYjwDi3l1ehvNNIs0jz+yV4x/gj1t4b+3nrC7Y9QeU8TwIngVHAKeDJ4LLgAPA5cDp4JXgyerbzGheAnwI+CN4EngluUV/YtcDr4vMq9C84Ee+re7MeDp4BngaeB54BlYD24wPCwdB2ra/EnPDysfron8kBwlPKnjgYHgVPAwaBwzsD54JFgGThE+VlDwfPAYrAaHKbtGw5eqXHlrel6jjuD1sPw1pTX2R+8UHmRF4FzwRXg2WCdy5/mei3ndC3H7U/zXC3nfLAIXAyOAJeCk5RfeixYpdep1nLXOfdkXVtQrvDrLgPlt7bw3Iirni4H7fQ12s+fVr18BlwCrgNrwS9ov38RvA68GrxFeaB3gevBJ5QP2gJeC/5ceaB/BG9Wfudm9at5GzgWvAOcCt4FTgPvAcuU37kQbFZ72AbWgveDdeAD4MXK/2xU3udnwR3g55X/ebXyPO8CHwG3go+Cj4F7wCfB74O/AH8A/h5sAT8AnwIHoL9nwRLwOXAm+Dw4W/md54M/VR7oXnA1+DPwk+DLYPZh4rFt33bouGxJn4CHj8vWER7b3m0+LtuHwmM7GD+A7287fL4As+5HlrTRoIfP1mEu2+HwBZjkr8Xy1wqfT7dKCUsITYRNhF3PJzlqySN5JI/kkTySR/L4zzzSCBf+O97/1zTar/8P+t1/drFlfLrs19/5N+k7l6sJ42z/JzfH+P5bPL18Yesu1zXVS6sox36ePWac7PFX2bi67Z3f50Tu41aW2SvcKau/652EvE6U9HkmfaIrXT6jp0x99ynpn7bydL/1MiOTz3+LctLUV9OXsxUTeC/lvC+kDTx7dtrA+xfzfFvqKOdKzTmpV8w7K77ZlKOM0FtxPGWW3OLX37KV1dUke3Vn3kHMEpljVW9OGfkaj1ifknjEvGtaYZ77t/+uKai97j0qy9UHZLrLpieQd3NAO2RDT/ulQEVtfVh7qL/Kpie8f6a3bse59/BX3fayG6Q22uyvG0OkMUpyqH0+JTJH8xzP7N2v5Qw=
*/