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
7/kntP1GU65gEOYFHfv58G3MC2BSqH50zzei7Kk9Yt6xHmqPpCY66d8UjoHN4ZmwBZwFM+Ec2BJWwtbwUtgGfhe2gzfA9vBG2EHfkY7wftgZPgS7wNdhN4WrO/zMhCPRaQf2hq1gNjwGDoYzg455GTwZXgBPgRfDHLgYDoU3wZHwHjgGPgjHwpfgOLgHng73wYnw8gTH/Ho4Cq6BU+HdCY75RjjJ/d7qvAy4yOd72y3BaUd3h02lbyX9mSZ+cAbsCY1bveFs2AteKL3xZ4V7bgJ1hfwx7i6VPwMTnH7OibArHAR7wcHwBDgU5sJhcBo8FRaY5/LvNFgCx8Jy6SulvxKOg9fD4fA+OELh2hTaow/XKFwmnusVrvrIpcEGsIH0jaQ/HTbU+5EBp8CO8CzYCM6CjeG5sAk8HzZT+FoofJl6j1rCRbCV3qfWcBlsk6D2MbwKHgt/In9C7Y49Cv+dPv3MZxKc8v88PAW+AMfAnXACfFHp9zJcAV+Vu6SF9gDTVlP9YeK9Uu6uU3vhdtgF3qPv973wbLgx6Lh7H3xV5h+b9IZBM4cG0yBl2b4fD6v9bcyz4SNwAHwMDoRb1O427s2H97vtUu1NhAt9yu8s9QOLAk75na1+zlz1C0vgSHhewAkveWTzpRReIDn5o318/v5UyJ958qdK/lwify6UPwvkz0Xy52L5g1y4vSZ/rvNpr+1Te/QdfZfe0/f0A31PP0p0yvuBRKe8vA9/LL2+89onZedlY77zw5KcdtqIJCfcIzXuNAt2hqNgd3ga7AfHw+NhATxFciNMeOEYmZ8u80kyz4MT4TlwMiyE02ApzIML4VmwWva+J3s/gNOTnPd4BrxJ5rfJXN897XvCzOe7l6D4JCse6fAseIrGzRrBy2AT+H3YHa405vKnhcbHWsHNsC18CLaDj8Fj4K9he/gU7Ah/BzvBHbAb3AX7wN2wH/wUDkhy2v0nwA5wIBwBT4YT4BB4htErntUB7dOB31M+1odVimdJkjP+cz7sCstgb1iufKuAOfA78DRYCccb+8qnC+AMuEDjihfB80x5heXwEk849iscZT7hKFY7aA5sJn2m9H1hCewv/UDpR9i5aydcpWoflcFpti3j1PtzYaHVq73t7sEgLsr3Dp4x6Es1znQZbAu/C9vDpRpn+h4cZscvnfJ6BTwDLoPT4ZUaH/s+XCi5K2x7z3m/fhhwysmP4E/hVfDncAX8BbwarofXBJzyg4wtL8jYdhsytp68Gf7V3h3nlIvbYBJxWAfrwtthM3gnbAl/CVvDX5n4wLtgN7hB403Xw1PgDXA2XAPnyNykW1ZA+yA0vseYt/0dOpvhdo9cRS3lVnjkqqPkjvHIbail3I5ayu2vpVxGj9rJZfeIH99bvOlXS7mKWsqt8MjlJETKXedNv1rK7ail3P5aymX0DMttiIrHZO94o+S6BmLHG+fx3moPl30Pq2AH6btI/6H67xVyZ6jcSYelcuc9ufM+TIEfwLrwU5gB/wHbwc9gN/ilxh/+qXGwxARnvCMJngSTYQ6sAzX+ovVhzrf5YNT4y2upTvj/AI37f4S58A0o+1pbZeujmPGbJzR+sxW2gk8qvOjVbtYaKH2vo9vNpyNn9BPVHpsEjdtTYC94jurXyfBEPR+s5yPhVFgGp8FqeAZcBvPU/zwTXgPP0njLOQpXwF3HY+tqwuWMTx1QuJYnOP3oH8LO8CrYzcQnwUn3H8NR8Fr1I66DZ8NVcCG8Hl4Lb4K/grfATfA2+BBcBx+Ft8OX4Qa4G94N/wTvhX+BG+E78D74AXwAmjBuhn83aWrCZ+pPEz54F+wZdMJ3EnzchBNuhePgE3A8fFLlY11AazU=
*/