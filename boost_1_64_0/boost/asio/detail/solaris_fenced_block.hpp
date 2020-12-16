//
// detail/solaris_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__sun)

#include <atomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class solaris_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit solaris_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit solaris_fenced_block(full_t)
  {
    membar_consumer();
  }

  // Destructor.
  ~solaris_fenced_block()
  {
    membar_producer();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__sun)

#endif // BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

/* solaris_fenced_block.hpp
LSQ+ma2/+Ti5Y3c68yFfcTpTcdofHad55QsuCsUsXn69Ycf8KYme/PLELZd4HfgW4hYqhxsVtzRZqGfq0Mak9xvhuFWG4mbfL9+2g+TTauwfm7CkxknnirY6h84BJtRx5s5f37D4p7PCIzt1rJnOAdM33jU77LAavbGg9aKR4w3tHIvnoOrre/OkORvLG/b5FRXl86qKi8I1lv1eT23s3FPtaefKXmO3Px/A3JnFdNbZjoY3WZmx9tteRdpltsOe+bZ37hyei9S3PdQ/uqgr/diM2s9PEjZ7R3OoLTra/TYrPLqj/Snium1oCn6FY4lxZWj8o5fmbDOPCaVTuJ745HjGs/9s0ynU7bH5tjcyTyVzTo3nEYbyba+3jMn/KVmx48p3N+O7/bz89zST8wvnleZXlpxb5jMupHW1sjeOVmTT0PiGN+y6Lzws1yrQMLL9K7fmRMqE8x2ZfNsNCbcDf2vl3PYl/bqa16przDE8LqV0GhhOJ+V5RNtL7Q3d0Xys4+B5Srtipd2eHT5pV1aZz6oC3td5FxTPi5d+souLXQJ1/dJP/TZXLjrt1DcIm9szxMnjLoR1HemSVp+2dRMzZZqcVsc0tNMb1K/NfNPXkV65HRwHFyi9KpVeGX5lrXJuydzi/OIyu9gi7jik7DY5VFpJprk7j36c1c+KV+4kX04fuInSMxi4zD6rG9MXbqwyWKpwJASSVS5dO7bvtIz0P9CePpk9j6c+J7iPTxtBV6cobW7aMMYVz0vryKhDch1PGT5kmR8q/6L9+qbzMlRvZHbyz8uK5+Llpa054uUj9mrOR2Qi8vFy9HHzUfLR+fjH5w6dj9ufi85H2VE+TulgxjO+vny8Uf6F/fp287HLcfruKB/PCNVhv/fLRyqwwtISjgGLU3/JHq71rqH+klz8+kvmoXT85Tdcp4fSY2Bn//SY6Venhyv0eOmBvdqlh+T808OaH1Z6jPmq6eHU2cjJgx+orf+9UJ39gk96VPGas2ptboXedf80kd3+fNfr6VkwMNE+G0OroZdfOrl7pdojZ/T1eT8r+KX0k5uN46WfzCdJzyiR1ad6x5ZMK9R9L8useQP3vVxm9clqnxp5pD3rXBbKPbt3S+/9+lbMBaMu7lrzeOdXyavQ3qwDXR0Hi+RwodqSK7xtScpsnPYkckoj5cnfrD7Rt/5qpXR6wMoMsnVYM1zN4n+lmWv/eDNWQjna0tVJl7QAbZBMO++czDmJiSnmR4OUVOdHctpIgwynnV7bPonSKKJtvaZb7FqO35g1JnttetAczy80g4L1tM7RczavZJI9ZrNU1oxZjWs6vO1urV8sUH8ppJ8VUe8s7R4b1oEIZ0WENX/Y5BFDJ506Ov/U03PzR45XOzwlw4Y9P2LdicIYNp/lmo8NmzvjoN3wqztlz55dWbt0D83rptg5e/zWM7R6Zv2LyI+lPUL9WMVVdcmWF5w4ljuj8vHaCJJLsfVDqm89GilDMPzrgyg5hrpq7Pv6zGMrPyPfz8z476fdl2S/ufq2dFD8dzjxLy+srMifU1xaEb9/IFlcaFbD90RyceMv82+tzxRao7yql+PgHKVBIeppc965U84jWowY+dVTkp3jG7cmgZB5V+mZEbb6nodsh51pZRqrHRi2kxA4rrZpFL6TJCo9Bh6iTBzMVpkIOnPpbYPOeNMWJz0Y3plfYfrdRRW+4zqSO8Y9f/ePVp8Y9Ds7d781+5Q6h7UN5MNM/N5o5kAL0rqapbSoXmmdGWDrTLewYX2mdlqkdU+bmjYhrT2Vc1JaJx6npWpuWXN7J/V0ympju3+XUHrm1Y990/j3sPScwmv1jQJRYbPvTLk1C+lDsvmas7eyzpo=
*/