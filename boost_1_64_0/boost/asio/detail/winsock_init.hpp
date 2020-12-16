//
// detail/winsock_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
n/WGzgMfABeBfwQXs67QEtYVKgJPgsWgiNQK0AWWgO3AUtYJuhycAnpYtwB5QOW3HCwDK8AbwNXi+OAa8DVwLXic7U7zcZCndJwo8BIwEawEU8H14HDwl+BE8ApwFngVOBe8GqR2VtHGDdA4B8rHENHO6vQgUlk/YgD7h7J/MZgFLgcHgdB6oe2PgUPAP4NDwb+Aw8CXwOF6HQBXw/z+rY3oBXj8tKvx026fy16n4E69jpafdkqAf3bxftpl+2mX54ddOpyH7VLgigw6F79Uve33FWAP8Equf7bC7eNw73C4UHAjh1sh6mewnPUFK8CJrCM4mfUBc8E14GpwLevIXQTeoOkOsv829t/J9vdreoN8nP3g5eCboIfjd1D2ZdK5lSKDPsnH3N59xjoPX3B7dwycC34JLmQ9iFLwG3ANeILr9X+Am1gn4jesE1HLOhEPgye5vTvF9foP4OusD/EpeJrbN0XoGIhrA7rAILA76ARHgS5wLhgAzgeDuX7bqXB/HDiN0xdGemFyTC7pJNWBKax/NhF8hXXCPgQXsg5aNeugbWPdszvYv539B/i57gMQjs5/GDzBz3OhYi16fp4Vx+vNOmijQZyH9am4j4X7hYoM+lRhKuLLOoEpYBSXl2guL+l8PWL5OaMTP2fEgXewfzv7D4BdOL+7gm+A3UChz5kA9gTTwAFgH3AwiG2Uz8ngYlCcpwLsBV4DivOjy4k0Iyo+blo3onG9CNaKYJ2Ieb3+PfoQjWhD/F/oQjRXE8KsBWHUgfBfA8If/Qev9sOZ6z74aj60TO/BTuthfYZJ44H1HZqv7TD6Pit9B/+1HfzRdfgne+cCH0VxBvC9uyQEckCCECAgRp4BIYaXPEQNAspLCBgUFUlCEkhsSAIEChbb8JBiRaWKSi1qtFZRUaOioqJGpS1aVFSkqKioqKjYoqJiRe1/v/t2uLu9S0Lo+0d0+N/MfDM7Mzs7szM7881/i06H2vU5hOtyODw9DqvPRJcCZhtmPyZxJDoaMCMxBZilmNswWzB7MYmjfFY/zBRMJWYtZgtmHyYRRYUZmGxMxeijehaO5O/ft///J4UL8mwNAEe2/78r6y6ntWHsHhdnn/IwKXvk+Imjss/LGTPivFHDc+YUzsqpsId1oifglCA9ARUe95mEs3m5Sg18/wmLSNZuyTeWj9qEnZer334OnZlQ/7MHiUvOHgz5xq/pitcAjTAbSFxW5HQVkzmzbzzq+hrKaDNxVEsZlZTl55VIwODrTva6y+NLBr+5ka/L+r6gcyrqkeeQa/nc1/qaa63kWnpWbdj1LCn7/YODy17lo59Zq/7Rz6zFv8Fn1u4ffPhn1jr57xzjzv8B4qshPXoepjv/7rqn8tHPxcS/wedicq0o52L+d59ncfQbVOAb1AH5BnXpqeVJ84ctyPtdhwO3xvffctfR8ywaep6Fmf/Q8eGxEeZnWgfrc1W5+AhyrYLnP+oZ38p6ytXUIbclxqqXTsHOY3yMWw5vjLjh/qPjxCMZJ/4nx4g77v/fGCf+M/UDNkQ3YEPHjUfHjEc+ZhxLm1SOWYXZgNk55uhY7+jf0b9/5t+/dfxvD///Cfr/+qZbZt9ShY5jt2KOwTyP+XiwxQd7s+/ZNbaKvrbTCZdszjZvYcZhdgaKjewYI9vBrBG/SezT9FxQPQ+9pHhOhepNyzJhfmqls66+zPIha7ujuUbcz2PHxwDVIxC8zl22s5q9H/eKbAX2LKNLokbclvHNcJhZu/mOuJVzpQFGr8f+TrL3V/RAnAQD9vrphdDztV1rE3V/mY4htZzUPdOsTzRlEbLvrKUvyt7TvS0Pf+/p3pYN3vcXbe/pHl+Uvad7Wx4=
*/