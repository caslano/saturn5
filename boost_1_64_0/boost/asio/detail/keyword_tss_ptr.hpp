//
// detail/keyword_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class keyword_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  keyword_tss_ptr()
  {
  }

  // Destructor.
  ~keyword_tss_ptr()
  {
  }

  // Get the value.
  operator T*() const
  {
    return value_;
  }

  // Set the value.
  void operator=(T* value)
  {
    value_ = value;
  }

private:
  static BOOST_ASIO_THREAD_KEYWORD T* value_;
};

template <typename T>
BOOST_ASIO_THREAD_KEYWORD T* keyword_tss_ptr<T>::value_;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#endif // BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

/* keyword_tss_ptr.hpp
xFjXMs04eQam2B4+5Wif0eHLsVCHV6ChC8dYp8e6Lt3gT4+z3nSez8U4x6zy3SjpBnd8xxrTOb4CI3Sdl2G4bvIaFHWbBx7nHDrLO2GwzvMoDNVFPglduswzMExXeT7GGU+dl6Gkm7wGZd3mgd91Lp3lnTBa53kUJuoin4SCLvPjWOT4Lf4YXef77HjvPSyxPTzweHOkwxms1SXe8Xvm+XzNU1GxPfwXzNThl1HT6fud6QSUdYX/jsFxrpL3AabE9fIvMdz28BvYW4ffRlFnf9CZdsUEXeCTMEmHp2GqDm/+Q/dahwdhoQ5vhYYu8kkYqss8A8N0ld/EkJ8Z8wmed+R0gcdjtX3C92KdDt+PAfZp8cETPNdxTH4Ovba3OXuiZ8T2HO+PvO0lrmCqrnILfTqdZFwYrcMno6jDp2OirnEb03X2ZMdDQRf4eMzSZX4c/brFH6OlcxOtU8zT4WuwUIevx1Ld4C+eYg51gW/GWt3kNubqdGpn2g5tXeASRlSclxvYEOfljRhke/ibp5kLHT4MvbrCTYzUbc5O8o7QOd4fY3SJK5ijq9zCWJ1ON1eYoMMnY5IOn47pusZt1HT2R+YK43WBj8cCXebHsV63+GNs1LkzXBMaOnwNluvw9WjpBn+x7LeiLvDNGHCBueI2Fsc4z+xMn0eX7eGfYLAOT0Ne1/h+jNQtTmd1pqrOcgljdIXnYrwOv4EJOvw2purcjz1nmKOrXMdY3eCXUdNpsnWNdTrPFSzQNV6CxTq8xdmuXYcz6NcFrmK9rnMTdd3i/2Gjzp7jNwAKF/Vs8h0YrcO/xyTd4k/9xBxdaMx8AjbocHaKuZruOJzDcB3eFwVd4fxPzaH9SzwbeV3nl9Cnw2swVoez5zmvDt+Kqg7fhgU6P7UzPYkVOk3rTHeh9HPj5L+f7x2l8z/z/FWcTzd49wusB+Mp8qWo6vDrmKPDA39ufnSBX8KSGMOFfj9fZN5tb/DAGc6lc3wiFjl+hb94sf11kb8609h0hRdhtW7ycb9wH3WFj73E/Osq/xEtxwxf8EvPrw7fggHmv82ZS82t/Us85jLvqJhDHvkr98v2Mt+K/hgnn1i1tqJ5xuW2X6T5XazX6YrO9BVs1EW+CDld45fRq9v8qSuNYYbr5VHo0kW+F0Ps0+QfznZPdZvPvcrc6vApV7tfOjwNS3WLv3KN+dRFPglDY/w8A126yvMxWNd5GQboJq/BMN3mI661j/HUuYmRusU7/NoxdYUbGKHTXNsxRuf5IozV4T1q5kqHD8FMHb4Ac3X4IizStRv9DrzJWtLh9+e5vzq8/XzzqcP7Y/DFrusWv3nQq5v8ndvMlU6/845CUTf4byjp8EZM1OEDFporXeJ5mKPT7a4VbR0+4Q7zM7OHzT2G6fBvMFJnf+/PIBinw9MxSYerf3C9Ovw71HT4ISzS4UexUlfutO7Q1uHv3uV+/aJnk8/BMB2+9m7PtS7d43m51zXqPB+Bkg5PwkQdvgsV3eJhi12jLvIlWOAaw7v90b3U4YOxSlf4Liywf3iP+zyDOnwE+nX4+1iva/y9P/mOu8T18jrkdHaJNfKA+6KbvNODxqwL/EuUdI1XY6LONtwXTNHhX2OmDl/5kPHo8EIs1eGX0a/DryL90vw87FqR0+G/YG8dfvoRY9Dh1zFRhz/AVB3+EHN1aan5W+a7QGcf8+ygXzf54OXeJ7rE87BBp8e9859wXbOsT84/6R2iG3zVU+6Bzj7tWXnGXOkab/dX60ZXXrKeV/ndotPL3qVYoOvcREMXXvF3Jpgd/bfOdCHmXtrDnhcs0uEtW96TusBnIV3m+Nzzqvm0vcgz0NY13mK1dRPNd6OiG/w=
*/