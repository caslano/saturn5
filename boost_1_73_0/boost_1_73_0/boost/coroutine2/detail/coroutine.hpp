
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
DmnBfZVE4n3oREWV2++I2KP0LDvK3yjZY+4VSIFZwSDMIM4GsCKaaR++xvl1Ms/ha5im4TRfQHIF4XTRx/scTy9RGwxRFdD7taIas1DA2jVntHoG/l073QvyaxjP00kyy4urNMqui3EynUbjHE5hcHIGf3TCivvnAQw4W9nqw1lwehYco8F+FZTobaGpsXXGGyWlMWp2DdPwJvJeD708glqqEusMgm6wtkLg1EBXW5MVtWKpXIxsMU1mWZx5PzBR8q6icG5BdypsPnoufinR/jKXof0HDhvUB0eZvJqHD1yKW6iR7ebgNwd4GWXjNJ7lcTL1ZgSLQNyeADLqZHxiHy35mzqBCHqPVkWErrFumHV/oOEu5JODeattf2QmtKGkchpTW4b4GFHRI+ctsPioJGuVggawE9qO1n1vr6hn+YENqgVK4rrYtYEUfAusdnPAKVoba9402L7YHpXE/sFRgK+2LzVVTHaabz0UGSld+2CGLRElit1LKSdWzHUn3AEIZ2Zrlb6s429kJulFfFmk0TyLhqcHy3q2m0eOIOyPTjmavCf1xQAll2621abnDEeN6XPcSPGjsQrYEYLC9yzxiOkYtQjI1rF9uBG3lyQxhrYoQOdm2XvK5JMqDCtak45bCPRnUh0Efdmvwvkk
*/