//
// detail/gcc_sync_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_sync_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit gcc_sync_fenced_block(half_or_full_t)
    : value_(0)
  {
    __sync_lock_test_and_set(&value_, 1);
  }

  // Destructor.
  ~gcc_sync_fenced_block()
  {
    __sync_lock_release(&value_);
  }

private:
  int value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__)
       // && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4))
       // && !defined(__INTEL_COMPILER) && !defined(__ICL)
       // && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)

#endif // BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP

/* gcc_sync_fenced_block.hpp
X+YkXTWn6EFzmh42Z+jk56PPF9y/OUdnzT4dRO2cvwqNBrbXYX2+4fGbS2xvRe3a/w02P9q/uU73mBt0wdyky+YWPRA9XvuPHk83aSwc/wg9asH7U47vC9H7RT6f5HVyl3yG3CNPCx1/f3qqXFD7Qrksr5Vr8iJ5UJ4uD8szQsffdy628e6I3s/zepbzck6eZeORZ4eOvx+dI5fUviR0/H3mUrmq9lXWLvfKI3IhdPz95jIb7xf1eSF0/H3nPBuP2pfLWXm1nJdPkwN5vo1f9m288gp5QO638yWvtPmWTwmN5Ua93w0d/73h98sptRdt/HKfecUj79cejiU9yHnMKOeVC8pF5QrzqKX7q1zfo+wrB8ol5WqY42WH3CY35P3sZVo+yN6/yY+W22+hk3JKfozcJT/J3hfd8hCvl/S4zvB6b9j9nh6AdX8MPWhu0MPmLPu3f81eT+gUjYVOm1t8fLc5S/eYc7RvbtJFs09XzRW6bq7RTXNAj5iTGu+t9nrD9g561IL7YdjeqfYZclaeKeflWXIgz5HL8jS5Jk+XB+W5clOeJ4/I8+Xkbbof2/jkXrn7tod4PTxMS/cu7r/+/cfyfTSzFrhJV34Qr7+/5Qn2NXTd4/NNuamc/jxzoNxQTt3A7CvXmfE6zZxTrjHjCcucVa4ot2z9F9VfOXmjtq/cUE7f5D2oeS8OT+LjxjyO+2MetfiP4vrcfo97UNtv//EDuw7qj35w2/2Lfx84ILzef2nPR7pkztKVyOND18xJukGjgf2b5hzdMvu096vo/WzoDnOK7jL7dI854OP9yGwvmkt0zVynh2g00N6v7XjpFI2FzphL3F/OnObx+uY624vmBl0zN+khc4bbHzG32N5xT3S/DZ02J+luc4rOmdM6/shsr5kzdMOcpYdhvb/nfPzGzPYOWJ8XOR6zr/GYA42HxsL+BXOJ7WVzReMz1+hBc51umhv0iDnF7SfvjT4PcHzmJt1tztG5qJ3bK5qzbK+YG/RAtH3NHz1qwf2d86n20+UReZrc/lu9vw4d//8dfXJK7dPlLvlUuUc+TfblQC7KC+SyvFSuySvkQXmVPCQvlFvyIhv/iF4vbbxy3sYr94eOf99nrZxV+xo5J8+SC/JquSKvtPHLp8gNebaNV54TGsvv6F45LS+2+ZTnho5/PnmZza/aCza/8vzQ8e/v+Ga1L7fz+7sHdt9+ZOGylb/bFr+urjtk1Pzx34n2fp1TjX9v4vrG7+9v3uP38SX1a6rf6n36PWqffi31W7VPvzF79cPyB7u+917226dfUv1O26ffWHsdV7+U+m3bp9+4ffp1qd/H933fsPd+8fcE7f70r13Sb5jIeTyBufvMQx7Q88LOz10vnIz8F+dZ63drfZsd73Y+H4c6ud7O44j6Jacw23mbJHeGOT5PU+Sjwxyfl265J8zxecjLATP/7tcDWIrqX5my9/ENyI0pex/fcGgsR+59fB1y+si9j69b7jly7+PLy8GRex9fSa4cuffx1eR6mOPrqiE3j3xwx/1wL7njHs/jYR61pLQ+c9zjH9B1pwX9eVxdx07i+bH1r+L67nB9fH56tD7PHP9dE1vP/vF9Q+uDcH18fipaX+L6+L6g9bVwfXweshrnoNaP1/oh9W8p72/Pk2PojmP+Oeet+QJdR1N1vRzP7CsPKWdOYK4qJ9/AnH2v8gt13Z3MnHomc1E593xt50TN11HKz9D+MhrHcZo39au/Wtvv1vcz79P6rPpN1nYO13r1q7xW/V+j8b5On/u0PjC/Uc+Lt2v+tb71Vj3uzcrv0nGdpP0erf7P1OMzGsfH+D5xRDn3cf271vTJD+p6fqCLrun4fH738Rw=
*/