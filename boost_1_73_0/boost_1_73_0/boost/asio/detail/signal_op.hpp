//
// detail/signal_op.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_OP_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class signal_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The signal number to be passed to the completion handler.
  int signal_number_;

protected:
  signal_op(func_type func)
    : operation(func),
      signal_number_(0)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SIGNAL_OP_HPP

/* signal_op.hpp
iriLEkmuWAhLn3+q2SAFFXMJ3XKU8nlopfed2mOm63tLvBdsuHHlGITLeC1CC/PUUtNRxC9NLuO60jK325p0kSXVxrug4jlsk7fFbV5Oi2Ym6fllpwTc++w1m1zjV1v7Y7VwJSIjIY2juNmQhbhlYtUXsH/8agu59rcY0949inrGACj5iMRNrRBg9UibiovY8nEtc7/8wO92QO0Qljgl1IGzSfa3ap0Zs1rQ5g1EDs4+hU3AQ4079BLUiylTVuhJW19JPfEvkP/uNw74f9iDKlpnDtCuTG+C3j87/tc3QbkotU44PrzNaqQ8v722TS5y9Kxf4aYS0+D1Zx2LWgufIg6nNi6X7LX1Q3JBLE7E4uUjxQ9l/u3pGev/1K/qTWG4Srz8zfobqVmzZvWsLWz5zpoOBUMpjd7ebQKB0o6nblaTZa/dyby88yJaLuHMQmqbNOmPnvhG7RxzotSNXVfZOkOQHv/34ThtVJo1UEZ2/GYrQvognzPkFj7YxIcoL4GEo7telNTA++PD8d0kuM8bA7dITDAxPLFtNwjsXqeBM4ZKr5TGycrvtxzMH2k5kC+vntymxOwJfXl/xtUGIavSdz2BxapePrEnKGyU+lqulUrJPJA5LJWf5a9SPUxNvW4AA5Zkq0k2m+1085Qr
*/