
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
g5Lbaf3FCt6K6Yqy1rGtfuK2sBRPS4ApJqnLq+FtaaOgV95WONOx/BkXglMtrhDwqTun2e8NmiOlNfYasDnXBVT30LWrcGJdidCc0I9j9XHWcS/BclBEiUjww9+2CtMdl08iq3W4+j3R5uMAua7M5XbDzZHivNZlEbjOhVLcJmrD1WDMCZBPUwLoWbEK3IHii22zxowQoWySJSRD1lk8ZbJrWiJ38p9XdhbUfLx2W2PDI8yJrEUV17VuE1z5pL/Uvu9PU7gJVneUuSZfmFGY0HL/wPECqiQvvIts05XjDKAsaxz/NHj7jlC9JZouVq0m+uXvFLXAYIMHwY1g4D2t4MfzQs8+UlElKWmi2QE3OsnRGobv7Z9St9Ofxfwx8WG4cEwEq39CAE7HyvmMZa02gt+fXHz2CAqB8tbt+aGJjy3VaT+LdwXR7vRAe47/hP8O6eZ6QmVTPqByyMZQRz53KFFCr3BNGqcPT5v0s5Iwy0ajJ1p15148GOR8Gukn83Qd5ubnpDyCxk6Loz9/2b8nZvhQGEuRTWbjd+e+0oJwjsRQRFzNSpyWTYo7V36Jxu0UE1K9cEqMxZ1gjpOQQulBwkd3o6lMy5yD62Z1LCoBi5QVg5RfmW2c777ekA2S3M+wJt1GWpji2PP/GGUjLxgE3FFmDQ/IdagFk54Y7iU5c8YctSIN5FKdjftXI1wsoRvDRL7IRnkt7B4KpM1D
*/