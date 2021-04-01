///////////////////////////////////////////////////////////////////////////////
/// \file stats.hpp
/// Contains the stats<> template.
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_28_10_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
/// An MPL sequence of statistics.
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Stat)>
struct stats
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Stat)>
{
};

}} // namespace boost::accumulators

#endif

/* stats.hpp
xiXsLBl/40m6TwQl6qd33hFhSIzwBMCHUWyBByjiVkCKhxGxaYZFsjnRuj8ADUc4p4MZZv8H1VgoHM2jzb487BwD0ag32yHes3RUhtT9hvbHcQSqR91hgOjQGcvKP2t3m9lW6WEurkAfHhLKe8CWlMC4EUwGnF1ws20+uwRlTT8EjHmohJkrdNH1h8HtbCp5FjGx9EHBJOKUC48sfSSKB4CSckilsEdW9db0Q1sOocQsv10LbqkTLlj0G20T13gk7dwJE/BXxTt7FDvaewvIOu3oLr6gtA3RoWTYJQZi9Mcrt0ESW3zxShkqkRcqUooPae36XuM1QYsUV+Sg5t0aG0xoWXbiKUgcIHe+LNT1/30CmHFD1rqeUuUG8HtP9EHYTPs1/OxShaDKWHwC3LVi7SX6ic5YNI1TUEhKBqTvOd1ngaEGhvhhADIghmz+AAye+QTiMq7OeRHJoaRRbc5lGjbOOVAs1BVEbTIQ+XsLkKGVYK7oVhOxYLzHDYZbtpMifzh42S9maY00QmZRgpnUmPPkAU4iAGQgeMEvQeQko7rgKUW1LVIXajweig==
*/