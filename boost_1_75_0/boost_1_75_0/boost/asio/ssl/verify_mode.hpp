//
// ssl/verify_mode.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_VERIFY_MODE_HPP
#define BOOST_ASIO_SSL_VERIFY_MODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// Bitmask type for peer verification.
/**
 * Possible values are:
 *
 * @li @ref verify_none
 * @li @ref verify_peer
 * @li @ref verify_fail_if_no_peer_cert
 * @li @ref verify_client_once
 */
typedef int verify_mode;

#if defined(GENERATING_DOCUMENTATION)
/// No verification.
const int verify_none = implementation_defined;

/// Verify the peer.
const int verify_peer = implementation_defined;

/// Fail verification if the peer has no certificate. Ignored unless
/// @ref verify_peer is set.
const int verify_fail_if_no_peer_cert = implementation_defined;

/// Do not request client certificate on renegotiation. Ignored unless
/// @ref verify_peer is set.
const int verify_client_once = implementation_defined;
#else
const int verify_none = SSL_VERIFY_NONE;
const int verify_peer = SSL_VERIFY_PEER;
const int verify_fail_if_no_peer_cert = SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
const int verify_client_once = SSL_VERIFY_CLIENT_ONCE;
#endif

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_VERIFY_MODE_HPP

/* verify_mode.hpp
LwJsBzgF8DtAJ8CBT3pPB1ggEOrv+Xz3P82M/87fBrnWYa/ybLLfUDrs2vUqhz16n9ph73els2gvemFdF9Huv2tPd2pX7D3U8++j0L7x56PHelaenK71t72yPX/Q5ve+eDlLe3z2HwH/6vH3R7tbOe0TL3y7NrSjZ+mDH7yibdy7IexnQ+dnDMad2r0Tv3nzK/uU3osrT2rzDtSuthQdmvzZ85uDd5XMj+8/rvR6fu2ykF3n/36h8eWb1iffmRG68YeF3x/97cFhxYYHwgZour7T8L7m+y/23wizvnXq9+vWi1OXrv0qXHf04LMd33x/Q/fvX4/ooOuq0hue1i88FBmVFFL31vPjJoze8dHPsVFv/Wv2pC9mT+BfeW6mffabto3+5XFvrH4o9es/+Jl8dcBsU+PZee+sbfi9/97XqmafL8qdduilF/1XyWPm7A/Q07KD7N+y20eDFe8JIhPwF5bE78ujXx6l382gJya1//b1fPzXEDQzfcJ3j5a+mNuZuxq07+RgXfdLSV0//frXoOPqvsWTe07e8sVbl4O0b36SlfOB5+6HnrYGBU7aFbL0X9+s2Xv6x6DKP/44llrcadHRd+uChk177GLU/j1r1v5wKOi5/bET9GFf+u755wdBF+Z9tmZc+Hv3ffjVmqB+fQ9c2vXZhBGp/NKg1Pjkiic/jF3W+fOUoG8vDyv12vNcyb03w4L6Bb1hGfdG
*/