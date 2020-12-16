//
// ip/impl/network_v6.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

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
    std::basic_ostream<Elem, Traits>& os, const network_v6& addr)
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

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

/* network_v6.hpp
umXy7p3uMnk/dmeZPO0hd5nEbsrkNZ14b8k6umXy8E5HmdRrPJUVvUyuw/3xrMbLpK3jYNZ/R5k80s2S3xNcvB/cCF+w28mHHGUyxnHaQJhRZs+pz8T+fV/U92ktl5+KTB8tl6qD0pWl5TLnYdue4MsiJSdivm2t8R7j1eecT0THFfo+ENQ5NPqYr5brAyJzuYQ51YTJ8RoDNmm+QuLX2dn/a1gds21wTNgte32MY8LOMPWOMMmav1JjHWU4S+J4GvchtBbmA9ExDL1mHYzm9WTyWuu/M39VaXD/scMSfp3PH5Q1eSqCZg+wL0TukpBOk49G1rRh/xDZ83xDKPcpWu7VmDqw0G3MOHhBg3PuE9vuftisP9G9uyLf01d6jIvXNTAuvs5jXHx9A+Pi10d576+PYVx8fk9NlZ7R9YGOi1u/jKirjT7TBML0Nd/d+or9VWsG/3qOf5lwvcw5UL3E3lXtXEXsfSLLvK79yhb/16yZ+n2vzOjM9i77Wo67BtJpnaJjR6easF0bHUezftm0cTSnfBlWU87ddUz7T+65xo1Vd9I3Wt15p+mhY2hJtfRASfFdpUvq4Bh2N32j6Y+Ob2DsLBNeK9cpco6NmXp+k/idKuNiW7OJaY9gP3Vraj9HP5WLewVG+6k7ovZTquP6HqafeogB9W+sn/pPjZM561eXPpb8fo3JxPxcx5vzfuWsXw2PN2v9Ioy7fi0W+08ou0lWQ/3hWciZ/tDo6WzWOT4o9uTI+qXlo1j8b7NO41+tX6qjV6P162yRu9kqCNUvDdut0fqFXOg7aAz1yym/LoZxaqf8eu/6iLuuZxX5H3EfU7m/3XV8OlRGJ8bQbzTl+6n2KRHldGUD5bTOo5yu8xjPXe8xnjsk+Cyn5fcsTDvliXb53RUsv4tXlJZ6759xushNCZVhsfvNfgo/FrtP2pBsrrUVM8tuG9L9pl04XduFYH4X0EZ92S629/rItWTuPTKv6atz1TVQGuYt+1nVpG9JaU1uoXbSWkE91sCRPg3XKubvV2Y9W1i8cvoFhBM1UILGa7c7Xmw0Qs8cQ7x272rad7XweI0O5pcuXtqg5eEGzO/tORjueAUKpve7pspnmrk+h8V+OeWOL+uY8PWQXEvDdJAw7bF/JvZLrRzitxgj/RD5dghzul2GWk41ZWiLlqFuKpNJOs6wZeLG8X9Sanwmb3UJLUUmqGc8MnNtmdS6NaoHn4Ae867XxLFL934azrG1cvf9HxAIjEV+6Xr/tz4Smc+x3P9AuLYN3f+TGrj/pj/bNSB6fdntjheNiYmVV5wI8/XqisaJNaWRdeV9u0y64uT4iO1dLgnTtHri1a4c0jgByas+mA/s72DOOBXqXM7QWKcpr/OlL5kt8z6nT8YhKWLep+nfEx6VbzGN7kXjrMcPE295F9H42Y5/4lq5jzrjV7oymGEpJr9WaF6prGucvLxkJdT6qv5ZJk1zOsSy94mzvV6h635NHUF/2PhXjrnn5qynA6Nwd6ZD31+kB/WuIxomIeZ779VG7o8Sp4+IU5EzTnrPG9xzo4nx8SqLKwdHtCWSR1Wu+GhTYh4PPPOJcI22JTH1celDosdrfdR4lS9rLF7rv2a8gmVqw5DIc9Y+ttteV7x0B4+aVVWl3nHSMPFfO055QyPb3U+I065gnLQ8SdRkd7MVju8mAT9H2SJcbG2v346X+S6iesLu436PuO2OEjcqIdsgETl+DcVv91GIXzDvVudGj9/+KPGTfewaybv9RyFuJ2rceg+LjNvBUZhocdPXEjODorLheB48CvE0/X6UeP6ZeFqPRcZTdpRvOA8Jd/TiNn949LilR4ub7HjRcNzSj2LcRo4wbZs=
*/