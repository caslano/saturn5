//
// detail/null_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class null_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  null_tss_ptr()
    : value_(0)
  {
  }

  // Destructor.
  ~null_tss_ptr()
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
  T* value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

/* null_tss_ptr.hpp
lCKihobkReqisjww5KznsIA8OfTl6Eg22nK7I5/bHfEfnbSlPVkIn2XAMX9iMnG+cR95p7jRaS1YzBm3QHw2Sbsaf/vZTie+FeR/9R0rRTUeHfYR8PG8rHMzw8lPC0RyjNY+1ti8JIj1oc9tsmytidr9ip+v9YSpRlXThnl6K4u9/fn07MObW6SQ3344vTr/81qsRthPTw1obVyeR3CfmI3JFTaFkGxu8nR/Rm0aQDbZ6j1Q5Yfzu21zI3iD0OH+3uHLXQDxO7n4pmhqVJ09BOpuSuut+Lc7inm/3UnoTiOhhrYEXx2Ejdp5Oz3Jd9KICw7zIrmT4s0byM2Rjz4nedHDRNdLAkQcSJ+1Tk+RQkFm1cuH1JOX+y8J3qWjNuZT4oqYjpWM4LSA9LnkQF8vNECmDA3AUeWRD8u0WTnZn2nh1o1P3Iw3f8qqYVaVdfzH/a3I4ozyKu1qJJ207+IDtWnkcLQ6geldlk9TOSRy9N6LfOX66SgPlilFKwrb46rs+nq42qdWTlCnBWHuTrGSKf+5ywUPUsdD1UsVI4zRcQEygXlVw3EQlYJgB+dsZG2kMvREhD0mdpBoO1vktZq8F+tTf+VPxGKx6AmeKFkBFWzyWb39IVlA4Rbq8j+wFhfkbKkIgvUWxKtGRQLA
*/