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
3AteB74Cflvva/mr/hral+Ut/xXQ2XgN2Fb9HWw+sJvqlz5e9UufrvqlR4NrNB03gDNUv/RFql96geqXXqz6paFh3syUC4Wo9VHSE2wHo2mMHYyMevjKlO8i5btY+Spxucp3tfK1AEuVr0r1ky8E+6ge71Gqx/tc1Z9fBC5ReS8Fbd5lms9vgktU3z73oI+W82597nEhbzl/BF1vtQ8wDfy3yuszcJ3qa9+uethfA9PA/6ke9mTiSgXTwOagPk/1dEgZep63g3jbg0/rc38C9gfrwIHgM+BItZ9zMfis1qudYA34C/By26/5K4rouwAz9XlNwWE+dlBSwXlaLpVgGjgfbAEuADP0vrY/1SHBPZ/294jm41GHHZ2TwCfASSAyk37rSW2H28Ay9Ru7Fhp/uu2P0S/eRdOdC9r3u2o6u4ER/q3K38yHP0v5Wyt/tua3jSN/dcq/1Cd/N2v+bgH7gt8D7bBbwXHgnVoP14MlavegQu9r+vSMPeXvk74HtL1vAe37D4LNwIcc/JXKf6YP/0ZN390q/3u0H9ys/Gvl/Le73h+jdVLtdkj96wUeDzKuCf/x4FngCeAEteMyFewPrgMLwC3gQHAHeBr4G3Aw+LLaP/kXWKjtZAhI2zH2TIrMWV/6Bp/6OjKk9gbAPuBocCA4BjwTHA+OVf9E9Zv6UBJcH9ppfWiv9aGD1oeOyp9hzoDKuVTh72IRBygzvZquy8EO6u+k/jz191T/yeAV4AhwKSj9lI6XV4JXgrXgt8GrwDvAq8HN4DVgW3ufPngceB2YD64GR4I3gJPAG8GZ4M12fOAt4Grw++BWcD24A7wN/Bm4AfwluBH8DXgXuFf9yUnUI7AJaPtbgptULpvNOUDypvVI7X3IdU5yeHw8F+wPFoGng5PAieAM8H6wBHwInAX+DJwNHgRrwP+Ai8CkEM8AjwGXgV3BK8EBYC14GngteAG4EpwOrgJrwKvBsN0iPc+lZ8J2Ou0W6fhs6ficpPbSWuo43RbcB3YEX9d2VIir1fgGar1KBQs0vjk6bpWDXcG52g4rwHxwHqjvW3q2iLT6vG/BI/aT+oGdwf7gceBJ+t5xstq/GgyebfODs8BB4CK9r+OsnpOhDH3G2Ska/3ngcervof4B4DQdZ8/X8fUb4KXgdLAanAVerfZVVqpf64meGYHWp568kxSWy9/AM8H3wPHgP8CLwYNgLfghuAL8GFwHfgLeA/4HfBb8DHwZtCjvd4AQmGyXMZgGpoEZYDOwHdgcFBlo/UkH1c6Gnl/gWSInt52N55PCcvo12A/8DXg2+DuwGHwZrAT3gkvAV8H1ev8+8A1wC/g2uAPcr+n/A3hA7xu7PrqHvZ3I0f0+9b7dHu00gpnyXRW1r1GpfDlin8NtX4NvJUO3Nk66rXHS7Y6T7mCcdBkVwXRPOvKbHyddkYOuznLTUfei8ouTbm0wHeOiQ35x0u2Ok+5gnHQZ8+Kjy3fQzYmRH20sKj9DB4+P3RYjvzjp1tZDV2I55Bcn3e446LjPXp7gdpWTFG5X7cBMR30cZel+Gt2rc2rM+LE1pPYkwc7gD3W83waOAR8HzwOfAHX8YO+LpsNn/Nis7yX3gc3A+/U9/AGwLbhF40mL7FXRvS+n6jrlIY3nKe0fdoAdwWf1/ek5cDD4C3AkuFO/3/8KfgN8Qd9LdoHzwF+Bi8FfgzeAL+p7325wvfrvUP8j4GvgLnAfuB98E3wX3A++D74Efgzu0e+kl8Hzwb3gDPAtcBb4NjgfPABeBb4D3gj+Cfwu+C64BfyryqOd2UvAO4K+r+WKfTidV6A8u4MZYC8wEzwebA2eALYB87Xch4DtwclgRx2POoFXgbk=
*/