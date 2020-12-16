//
// placeholders.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PLACEHOLDERS_HPP
#define BOOST_ASIO_PLACEHOLDERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_BIND)
# include <boost/bind/arg.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_BIND)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace placeholders {

#if defined(GENERATING_DOCUMENTATION)

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the error argument of a handler for any of the asynchronous functions.
unspecified error;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the bytes_transferred argument of a handler for asynchronous functions such
/// as boost::asio::basic_stream_socket::async_write_some or
/// boost::asio::async_write.
unspecified bytes_transferred;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the iterator argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified iterator;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::basic_resolver::async_resolve.
unspecified results;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified endpoint;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the signal_number argument of a handler for asynchronous functions such as
/// boost::asio::signal_set::async_wait.
unspecified signal_number;

#elif defined(BOOST_ASIO_HAS_BOOST_BIND)
# if defined(__BORLANDC__) || defined(__GNUC__)

inline boost::arg<1> error()
{
  return boost::arg<1>();
}

inline boost::arg<2> bytes_transferred()
{
  return boost::arg<2>();
}

inline boost::arg<2> iterator()
{
  return boost::arg<2>();
}

inline boost::arg<2> results()
{
  return boost::arg<2>();
}

inline boost::arg<2> endpoint()
{
  return boost::arg<2>();
}

inline boost::arg<2> signal_number()
{
  return boost::arg<2>();
}

# else

namespace detail
{
  template <int Number>
  struct placeholder
  {
    static boost::arg<Number>& get()
    {
      static boost::arg<Number> result;
      return result;
    }
  };
}

#  if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC < 1400)

static boost::arg<1>& error
  = boost::asio::placeholders::detail::placeholder<1>::get();
static boost::arg<2>& bytes_transferred
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& iterator
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& results
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& endpoint
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& signal_number
  = boost::asio::placeholders::detail::placeholder<2>::get();

#  else

namespace
{
  boost::arg<1>& error
    = boost::asio::placeholders::detail::placeholder<1>::get();
  boost::arg<2>& bytes_transferred
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& iterator
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& results
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& endpoint
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& signal_number
    = boost::asio::placeholders::detail::placeholder<2>::get();
} // namespace

#  endif
# endif
#endif

} // namespace placeholders
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_PLACEHOLDERS_HPP

/* placeholders.hpp
RbB//2X90x4vak3Qbu9uzyo/SyO4cGGXhYOuO/B2grffftvtx7Zy/ZPgaad9dtorl//yAMErrghe8e6vowoIbtuWv+3iG+6ZTvDXX1/4dWHmF2GCX399w9d9TnrqJYKnnvrVqeuX7H6cYGXluZVdP37xJILvved677aLbz+FYNeus7uunjr4PoL5+a3yW0+62EHw+usnXn/Ou70OJ7hp0yGbjnzugtcIZmQ8lFF79axygk8++fyTSxq8gwnuv3+P/UcfcfAxBO+55+J7WvXJv5vgrFm1sz4f8tBKgmefPfLswKojviE4bNiLw879s/Jhgl7vEu8x3z0/m2Dr1u1bp6a07UjwzjsvvXPM6ILLCJ500lsn3bfio/cJbtiw/4aDX7noeYLdu/u6bzgtawvBgoIxBZHwpWMJvvVW7lvnXXOfm+B3333z3TM9fx5K8OOP7/p46uR3VhA87riTjvto4MOPElyw4PAFwy89aA3Ba64pueaWDQPGE+zXb2m/jLWFBxLMytqQddEvvicJrlz5y8rPppw2k+Bnn5392REnvvIdwUMOGXdI/bAj5xF8/XXt9U9ve2QYwfnzs+dHH+v5A8G1a59ee/Wpnv4EX3rpsJf6vX/+FwSHD988/Ikd1RcQnDw5Z/LJtYuzCP755zt/3tX341KCJ5/848k/XfLDRQQXLz558Q+f5/gIut0e99Pj115HUFHmKz2XT8ghWF39RHXV65sPIXj44dWHb44M30Tw3nvPurf7IPsjBB966POHNp5QexrB0tJppdd0X/Eywcsuq7vsy0/GnkGwd+8FvQ+6M28IQZ/vIt/+n23wEvz224+/fafjnwMJatoW7cmbPn2RYMeOkzsuntX3LIITJvSckH38/JMJtm+vtJ+QnjqZ4DPPHP3M9J3XXkHwyy+v+nLYKc99QPCdd6a+c+Xiu6YRvPHGtTd6jnKvI3jRRQdf1OPs/ZcQzMn5IefHjSdvIHjVVZVXvfjtsOMI2ph75ZUjXhn52tk/Ezz66LuPdpw/PUiwru65uqse/PJDgmedlXWWb2X3Twm+8cYZb/xxx/3pBI84InDEtnkjnyG4atXXq546bl6U4H33nXffoQNy1xI88cRVJ8774LWeBJ3O452PHbT8c4IOxwGOjoUXziD4/fdffP9Ct19HE8zMXJd53a459xD85ptrvzk6+syzBI855rdjPnnm9LcJlpUVlF3a4871BG+66YGbGlJnvkPw888v+byNuvEzgqp6gXrIl5tOJPjYY1sfe7Ta34bgkCFrhqiXnTCF4Lp1/dcV/eO6iwm+/777/bVn3jiHYI8e4R7bA6N/I/j776/+/vjgf0wiOG3agGklvmuOInjppZFLd2wfU0ewtnZj7SVrPv+FYLt23dplHtlhJMELL+x4Yd+lB9xL8IEHvnvg5wkNUwl++umTn3pnbjmX4MEHjz44PLLH6QSPOurUo3Z7x/+DYEXFFRWjfnq2jOBrr8177eubV2UTXLHimhUDsqadSfDKKyuufPaHoSUEf/75mZ+vzf6mguBzzw17rvKfV91MMC3t8rQR909JJThzZsPM75QH7iJ4zjkDzym9t/NmgpHI65FHbt/xHMExY3aMef29yJcECwszCmd5lnYheMIJ6gmbxq65nGB9/e/1/zh31w0EwXrE6Pe2hT8huGhRyqJO5+23lOCWLd4tzz/wZFeCt9567632A2fsIPjRR/d9lDvtrRsJejxXe4bsfrqI4IMP/vPBbx2nTCTYq9c5vTrfOnE4wWXLpiy7/I209gSPPLL+yF2V474mmJt7aG7vkvM8BNevH7u+7rfL7if4229v/vbg0Z8UE2zbNrWt0ql9X4LHHjs=
*/