//
// redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REDIRECT_ERROR_HPP
#define BOOST_ASIO_REDIRECT_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Completion token type used to specify that an error produced by an
/// asynchronous operation is captured to an error_code variable.
/**
 * The redirect_error_t class is used to indicate that any error_code produced
 * by an asynchronous operation is captured to a specified variable.
 */
template <typename CompletionToken>
class redirect_error_t
{
public:
  /// Constructor. 
  template <typename T>
  redirect_error_t(BOOST_ASIO_MOVE_ARG(T) completion_token,
      boost::system::error_code& ec)
    : token_(BOOST_ASIO_MOVE_CAST(T)(completion_token)),
      ec_(ec)
  {
  }

//private:
  CompletionToken token_;
  boost::system::error_code& ec_;
};

/// Create a completion token to capture error_code values to a variable.
template <typename CompletionToken>
inline redirect_error_t<typename decay<CompletionToken>::type> redirect_error(
    BOOST_ASIO_MOVE_ARG(CompletionToken) completion_token,
    boost::system::error_code& ec)
{
  return redirect_error_t<typename decay<CompletionToken>::type>(
      BOOST_ASIO_MOVE_CAST(CompletionToken)(completion_token), ec);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/redirect_error.hpp>

#endif // BOOST_ASIO_REDIRECT_ERROR_HPP

/* redirect_error.hpp
39lHeRpGYg7iMxn5tkjA3eAMznF1DFHYiw7s+oegKjM15UBQXAZN6Q7MmrE17PovTAysMvTLRG5rhSUe3nj36tVGDy8RYWJVtwKE3v/aLA4Vk8ASHAV9vyGes8TVyRH432dVEYyPf9pk6a6PS6upRwGBt3iwIoMDdNkKKx8Hfij6QfD0pgCNTTIa8VmxYZ7ywrS4CgV+pKbIgJch/NHGNrIFBG+vi4yiQNzI4up99x+bY5vl/sMvMUK5AID3+JITcj7+BS9m/gwZjoPA8joysuVu0dj39cYy8E5CKh0wBCxUciIrJKJa2Hs4KMHvgRW24T++eplNN8k9avmusw7PMcIuExa+1jZHZ/n/Gwr7DkSt19rtfgO1IqwONM0dFXScRgUSPjJ3wpOcfI78QyYtb23F6N87MtqjvudLPM2bGxk0XBIPYSOYijwhFKSORHS+QW8k4f3IdwI62I4uxBqPyOzYzvUhBx/ONH5XNutP5qspmH/d9zvvts0Y4UNeWWyuh4TvmMDbfSIFKHHedvm1Ovy12rS1KFQtnEI7443CksKGg2r7IhDguS8kwg==
*/