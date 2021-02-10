//
// detail/null_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_reactor
  : public execution_context_service_base<null_reactor>
{
public:
  // Constructor.
  null_reactor(boost::asio::execution_context& ctx)
    : execution_context_service_base<null_reactor>(ctx)
  {
  }

  // Destructor.
  ~null_reactor()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // No-op because should never be called.
  void run(long /*usec*/, op_queue<scheduler_operation>& /*ops*/)
  {
  }

  // No-op.
  void interrupt()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

/* null_reactor.hpp
wfKmiEKkEaeKdPJ+sRqTpy7SLLU4xTBOb2JE/IZkLAQc1g4rAUmXpyHGZ8G6OHaeTrICDE/BvMRnEb9LnFI0o1vTmc1nGRxMpc5p6SMjly8Q4xfMCdqs88JOFW24xPEattTGwg2NgBYtuHGGTG5Os0S5rv9u0xNmsoUt5/3C40xjXzpmAGBHam+xVUVcFskAfRv1XMgOJSFOP4ZlW/cPjEJjbRDlQ22xtY+rgDxVheDbsWpR/CN/U9W1eK5WZHdoKhs7g5mqs6ZIkJPLIpzftGllQXpHymm2UI0I4SvqAZR1G6tbKBODkwreeY6Aif52sKPcVXQhobl1MHNgjDBtEplacbU/OIpFGIs3h0ntop5KjbUNPRZQEp1tjDBIJnAYLTmZradKHPt95VBfCe+L+E+8+eHtSbz78uhwy0RixsGJWJ926G1N6lGed9rwHcwTlgYYEJ1BKWq9u8IbOiST2w76CmLaosA8sPETOb3btr2093Bb82IGL6I/J/wbFheAga0ZqVvAkpVVNB45QKszMt4gkPHtQuC4wVNtPkzb7epTXE9L4fqTpeefEGIEEYmvZaAntrOPyK5FL1n6dYgMn5hh0iEFJ+6M5Dp5N2vTd58UTRlZ0BTEzEBcgcmC8UpLMDzEIIOMm22FgF3q
*/