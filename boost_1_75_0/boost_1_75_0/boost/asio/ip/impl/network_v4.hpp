//
// ip/impl/network_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v4& addr)
{
  boost::system::error_code ec;
  std::string s = addr.to_string(ec);
  if (ec)
  {
    if (os.exceptions() & std::basic_ostream<Elem, Traits>::failbit)
      boost::asio::detail::throw_error(ec);
    else
      os.setstate(std::basic_ostream<Elem, Traits>::failbit);
  }
  else
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
      os << os.widen(*i);
  return os;
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

/* network_v4.hpp
t7+bNdv1je+uYnn8spXmq/tJeaxhAgmTySFpTfJ5TTK+sQSMipc8dN5Z/enBAHKpuF043ig+P7sBMjNWClwjB7hauZCKxw4kj4yGahL4QpX6UyXvlWgir3mS51T7RbK98FFVtnckuaG0NFtj7XLQi2xL5WZ3trbP7mT1ylZY5dnKlBmlEd2iE83fkhrByz+T+UeUXCP0N1xjF9aHa+zFeuFFXWtnvOMaoeFqv8ebruSaKyYtjVBGz0gsJe8B0juu3aro/h2hh1wemmF+owL8Hga5Yn3F+4o+CeY9+TftqFWU9jFm82Fc+haeqtvYX3p7lTx3UHOLvF5Db0Djc7tT/fkQTSDe5hohIw5ffAIT3H7gloOPeP8OTykGKwUvp1t66OV8lQ99nK/7kWTOdwJD/Lk5qtvU+IMaN6lxnRq/EENBoyhoFAWNoqBRFL+Il77jVQmJMebv7mEY0oMuRMk5XGHpugNHCOT5ur5VemXJt+rixyBogmB/FN+8bMTXENRcKNhjzEmj8QalAnHggTWu8Sm1Ec+IxZYmG/jKvgc74G9jZHflG5IHHTn5S3YX0/KGkz+WPtLuZO1Jc+AhSLa2gjyYosHbAcnaCTWsAiLW8lFK/LnoopJDejXUzoSqglH6Pnih1dodn0PwKjmt97H24Rrlej+wdoMoJYfYTqUTJxuQfogQuhczLg19qqK2K/ldM8OPWCifg31P+1Q+
*/