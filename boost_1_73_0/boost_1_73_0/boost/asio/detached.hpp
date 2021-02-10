//
// detached.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETACHED_HPP
#define BOOST_ASIO_DETACHED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Class used to specify that an asynchronous operation is detached.
/**

 * The detached_t class is used to indicate that an asynchronous operation is
 * detached. That is, there is no completion handler waiting for the
 * operation's result. A detached_t object may be passed as a handler to an
 * asynchronous operation, typically using the special value
 * @c boost::asio::detached. For example:

 * @code my_socket.async_send(my_buffer, boost::asio::detached);
 * @endcode
 */
class detached_t
{
public:
  /// Constructor. 
  BOOST_ASIO_CONSTEXPR detached_t()
  {
  }
};

/// A special value, similar to std::nothrow.
/**
 * See the documentation for boost::asio::detached_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr detached_t detached;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) detached_t detached;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/detached.hpp>

#endif // BOOST_ASIO_DETACHED_HPP

/* detached.hpp
E49jBWZ43ZJKUsVEA6IZT+VA/yDv9o2Gmi9ZSe1j1AvioKUQFLLYc5eyJK/Fga5VogLGaTbnD+hMM0QNbHTISDoK6NAATBWtnNvbeZdFuoA/okzanMUz3ybxJYGcPBg2bDYr3nn1idbLgvkgXJrmA4ymlv+Ofi/m5h/iPEWgiHkW2CWsySauNIRneBLiF9C8wncrdPcAf4Jgtk+1ZMb9LPS1SOQMW9N7NdJTFRhTSABKuMQeBR6vLFcgcsnTj0pqfmxYqo9jx3TK1kc1DIhPWu4DiNd3RKyzeHzNlsXJ02mq1CIHKm8svDJsJWe0LkFwR+LLBdKsGDpEwS7KT3jPkpOBSOtqMO4zkonWLxobdRiCtA/cqr8mDNUsqUQ6gB2qSSI7A3ulcAXJO5qLwiTKc7QGghcdBZauY47pZ40nS1nKvck2i0qkfHX3VW34eISLEJxZ/wTufH9WGMFyz40SpUFEQ9hDSWYdW5pIvoQnS2i8kn83MC8ZjlyvnWgJkmdEGYPfz8RM3C9LmezTidk3MJdIf2Vm6QvZNtV58VvkzbPUCq0AQYk00tpi8adFpSIWkrYQJimRgm78pE1PZpqSHKuW5fSZZrXC5qK/rXulyEufgG+ixAIvLND4/j4Af7CVstVm5JwsOkkQhLyT
*/