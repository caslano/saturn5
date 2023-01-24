//
// detail/base_from_completion_cond.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP
#define BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/completion_condition.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename CompletionCondition>
class base_from_completion_cond
{
protected:
  explicit base_from_completion_cond(CompletionCondition& completion_condition)
    : completion_condition_(
        BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition))
  {
  }

  std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return detail::adapt_completion_condition_result(
        completion_condition_(ec, total_transferred));
  }

private:
  CompletionCondition completion_condition_;
};

template <>
class base_from_completion_cond<transfer_all_t>
{
protected:
  explicit base_from_completion_cond(transfer_all_t)
  {
  }

  static std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return transfer_all_t()(ec, total_transferred);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

/* base_from_completion_cond.hpp
5sK52FyWUo9nKXmkzIWTsRO9jpEQOXwj7YNGvjCbhaYujKNC4wswtb0rQDxkUxEzFNn84mMyHx+vFS8VX9HV4BvUUe78/St1mbRQCl21kcmdhzeGyB2z+zUa9uYk+cEWeJk6SbmbIo3KHrZijp1T8CYg3oQHSOzdTBBZSX9M3JYSx0TS1GKtSBovPwlpskgaWqwVSXHykzBAwY6ffDBDgx3PCTxcDrT9Fsb/wpRHkc13YXjZWdEI9isQ+dfXoutXFVx7r9XQvCy4Pp+knHuLxXilvIeY2mG3iTlt0hmyMFOZ0m50SjHVCR7jtraBFeypFGhYZCHFFNF/FQhgDGRTdqbvYSdekPdmpEUEaHIwislKAncCcCnEfyeae3aWoPSknWzG6yBwmZJvMWK3PcAbxBTfWERfFNmHr1K6CwmkBJulYLOPVyLFzbaLWSfJ4Ta58SIMiSJkPBvhfCVdXF0azZEz9i4lwS0NW23ml7jb2/l7nQ5mH2IuRVzLDmYhokCW2n3JzOJ0+yNgMU29ExcTzWk4g8ZCYMZ35YI/G5H+gSet800O+cpVmqa1J5g9otEXTcLVxnjFU4jJ9PMd6iLtliZLpuTDuakWvp4ZTd/kpvbgq+cwA87RuTH5ZrCTPRPlThzJTbmp1/AmZiyF56YmQcXVwYovsoq++Assu1NMWQ6Fc2qw5R0Tu4aTgWnQX2BnhgXbD1bbV+amRkF7
*/