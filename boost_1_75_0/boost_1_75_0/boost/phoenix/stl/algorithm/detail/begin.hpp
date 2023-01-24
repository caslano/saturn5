// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  begin_(R& r)
  {
      return boost::begin(r);
  }
}
}}

#endif

/* begin.hpp
1o0QR/sYiaWHGBIm1QI4LJXWdtrnbsf2eYdl2Y8EWXeTdBeHZ9iv0hr5zo0jnBr6+v3SP9lkj/jjQ9MGSUt0YY/KJR/recAcd6VqRSTWm2okoaPGfbKbOESiTrmwl83PuRGzgtDFYx8rdvq7bwNNC9Zi8CAPp9vRTVIjtqSnERP2Ofw88WczxwO0h1fKq8bti8PWq5TR2mEbwulZ9LEyjZeV+JMMer1qpNwGYz4Rddeqc3F+U7id7zynRGBfzxY8ByNMcpwMxZQldELJbgMFl8r056Aa/AwCvB4AuKrMRKfgOW8n+xhEIWxbMdD7mdS+/LYFkK54K+4wh+O67DEY+4E27KfMD9ISaDVNSjP/rsDbYd5DCx8bPkh7gbY/x/R62Ad7vnBwJEV48AX68egmySwmCGCuSHmnLSWhkJjf5Nm0JJWGEt/yblN24LrwpnT6PQGp5PWYAsMm0JIrcMlKeWHMeXpH7zCHzOdPO2Jrer+H85jAzNuP27RSRjxPkMQTlx7d4hC+DxG3V3gb7NpWHwaLrxjRV3i8pEgYdRUPO68twVq158QPogyMZH6Z3LFiftHHnVO73n0SBW3tt+afliTEVBcg3rtYXUqHBFZpce/naHk/53YnzxX6JualIsIZ6HAMU1MPXBzxFc9Y9jYY706zZSd+8EFTLfn3vlnl2cdb0xSN4zYkef/IYT/lJ78/mU2dejeuI55fPB7C
*/