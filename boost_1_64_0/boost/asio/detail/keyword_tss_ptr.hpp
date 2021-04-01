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
NGPokt3krMgffgGO5CSoLT5THrIHhMtnIbgWvqLCD15YQGiV/HqmNgyQlFGm0W7yOfqUj1/WCxtzfrbb+tTF1d8EnkR+U3k+0OELN+zE6hn79SJ7ma3dkdfhjn0tLLpQLl7hacDKg/Qg7wNZN/8nrH0OiotEhni9jhFec6ur+l0hSpS5SUTxJ/EJTNA34JoVx1sU6Je11gp0EcXKN2Dv7pMgj4VnLBxFtq677J+tLfaWz5uy45V5jZQ3VDb1JoaPeeMWIhBRBwDevTsYjJTuyotiz0LEr/03Y/SP1GHDSGVM+56jhIpSD14NTVmf9+dOmfY70nEzBGgKof6fn96/42u1dnGc/Ob2zrOdF5Z9P3U0XYbgk/lv0SefODsbwbS0uF/dd2kmxMJ3RSUlUrXriK4hZCo5yB/wiErr0WC2IUOWT/fZDNhAcB4Ip2r9i7MvTLZ2YlOMiqoodDfkUWmwLF/+IKa5yfU3IDvymODrmx0kHuG0FqyLuyvH0F1I8r/HXYXSw8I2PzjWm2jjxO7KUl+vlKkNnYmcHgRn8HEmOgubGV22Ejm5hoqR7g==
*/