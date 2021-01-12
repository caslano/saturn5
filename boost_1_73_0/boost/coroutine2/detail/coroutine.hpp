
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
E2BZtdbDjX9XLlfcm0BEXqyOcVPX+FM7Iw9Wmab8wpyCcuPnVLnecJ86Ov11/Fbdi95NU5ratxJ7jRN5lGk6v7+18a9THmXMw459z88/XWCdeVGbQ1oMS//wiCcvjH9PiX5PUT0+2u6ofx89PgerXpKhsC4cBlvCU2DI/vd/j9nU/pf/JrPnvNp/l9kTn4+OH/EjfsSP+BE/4kf8iB//Z8cv/P7fOad88tSp+2H9v/P+f2h8
*/