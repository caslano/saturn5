
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
class pull_coroutine;

template< typename T >
class push_coroutine;

}}}

#include <boost/coroutine2/detail/pull_coroutine.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>

#include <boost/coroutine2/detail/pull_control_block_cc.hpp>
#include <boost/coroutine2/detail/push_control_block_cc.hpp>

#include <boost/coroutine2/detail/pull_coroutine.ipp>
#include <boost/coroutine2/detail/push_coroutine.ipp>

#include <boost/coroutine2/detail/pull_control_block_cc.ipp>
#include <boost/coroutine2/detail/push_control_block_cc.ipp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

/* coroutine.hpp
9WNqYCXt9TXGLmmUaf7L4vIpVsKTqbfJnPeOHTL5fNO5Hsl8VG691x4HijjnLCdwd+y/Z5dSOlE5IFH3fBuX0B71KFj2lOaY0J5oTXzCw8owv6EkU/qUivFxo2OdZR44yZ/325LuZSQSK++3Kw+ee8l165d7sRo893s1FPQZrgqCUaplGBV5twlQnSv9wTIJvHyzW50G+9nesuObPjBjthqZvlHmZiRo/OOsT8ckTdpLw3vVwvNcwbdXHfbYLU/h6uW9rrhaHO0SVaUp3v23XCjrlaAM/pSehWvJl9evZQC5ElXgtGCremONuDlu8QXJskhsnspVTtLUAVwHVydIbF2tB33kjgMlL8wbLjUgeHRhiOM/BZHiFEdtn1/b8PlWQa3Hzxomu6FRP98aE75JYB95VxWyQh11dRuYTlerDGWKaAX12s3PeO1ZiBJCPmRCqLc7OLSJkpmTmQMnHKzjasw5jJ37JqbDgbv0lFTpsYidm0TvvPFxmFNmq5pmxG3/K6VLw4iFOryKApKKAuyKAWLXse2viCW8ZjkMHTR9bo79br5LOHu896nWlKqTy5+R2sYPpFlmu+Wkv8dcHa40nE4yIlTXKyCbtk2ZZ/NZdF0RXYG2qaqfQTaSbGN1niOG7PJKTcsxh6ZhZTg8P5HvMVSegV4Vfseu7CrNBxebWt9Ca/pHG7Bf5zaJOCsioghEvAH5I6yVJZP7LDkO
*/