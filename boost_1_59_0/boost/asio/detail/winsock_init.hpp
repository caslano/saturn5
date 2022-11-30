//
// detail/winsock_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINSOCK_INIT_HPP
#define BOOST_ASIO_DETAIL_WINSOCK_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class winsock_init_base
{
protected:
  // Structure to track result of initialisation and number of uses. POD is used
  // to ensure that the values are zero-initialised prior to any code being run.
  struct data
  {
    long init_count_;
    long result_;
  };

  BOOST_ASIO_DECL static void startup(data& d,
      unsigned char major, unsigned char minor);

  BOOST_ASIO_DECL static void manual_startup(data& d);

  BOOST_ASIO_DECL static void cleanup(data& d);

  BOOST_ASIO_DECL static void manual_cleanup(data& d);

  BOOST_ASIO_DECL static void throw_on_error(data& d);
};

template <int Major = 2, int Minor = 0>
class winsock_init : private winsock_init_base
{
public:
  winsock_init(bool allow_throw = true)
  {
    startup(data_, Major, Minor);
    if (allow_throw)
      throw_on_error(data_);
  }

  winsock_init(const winsock_init&)
  {
    startup(data_, Major, Minor);
    throw_on_error(data_);
  }

  ~winsock_init()
  {
    cleanup(data_);
  }

  // This class may be used to indicate that user code will manage Winsock
  // initialisation and cleanup. This may be required in the case of a DLL, for
  // example, where it is not safe to initialise Winsock from global object
  // constructors.
  //
  // To prevent asio from initialising Winsock, the object must be constructed
  // before any Asio's own global objects. With MSVC, this may be accomplished
  // by adding the following code to the DLL:
  //
  //   #pragma warning(push)
  //   #pragma warning(disable:4073)
  //   #pragma init_seg(lib)
  //   boost::asio::detail::winsock_init<>::manual manual_winsock_init;
  //   #pragma warning(pop)
  class manual
  {
  public:
    manual()
    {
      manual_startup(data_);
    }

    manual(const manual&)
    {
      manual_startup(data_);
    }

    ~manual()
    {
      manual_cleanup(data_);
    }
  };

private:
  friend class manual;
  static data data_;
};

template <int Major, int Minor>
winsock_init_base::data winsock_init<Major, Minor>::data_;

// Static variable to ensure that winsock is initialised before main, and
// therefore before any other threads can get started.
static const winsock_init<>& winsock_init_instance = winsock_init<>(false);

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/winsock_init.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_WINSOCK_INIT_HPP

/* winsock_init.hpp
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
*/