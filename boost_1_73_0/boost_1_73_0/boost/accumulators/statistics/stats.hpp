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
XHfimIMlGeziIRmQwtBTd+F4LbOFfOadEQSXwCCZEYyx1nlTOld9R8tDhovP2vm+3QRDp7TL8pPROUssLiwgR2yYwRNdOR+XsTjDtfhkmcTPUktEhfxbb+ef3w9efc1n2d8eGZUfXkTzw4/Li68bfJJU/1etRnFYnN4Fro1FzR0ZYz6hy7fQTlowtDbLHsk12LEK2nZuTb4Ndds41qNnyoNpFEAVjcBrXHr5tmqZGnq7rcMufT79XJWIci3wWPyEi0B2G4M4ysaivNIs31q6eVnM2/a93Bqht8q8jqZZ5p3n3fpouO6iAZvmVTQWaHV6mrkmTKKl1E+tzRfqeNM7y98XgY/YErUXXc1XNM2kouu4Q6VdnOI1/20YzSbBFMM7nnRGtpVRHrqfc28f8j8H1+gEhP8Dcv4sSo8MC75ZVPW5ScOn0KbR+ODaM7+jEGEFWTn996xC7SNORhiA7lmrPcSOa8LcMZQVMUjiH11jsdr1XS6+lGyXZgQTPMjX6yzRomfcO6N8T1McD+5tHYjY0kJ8mAu1fe9PCZD1PS82b9udk1azmxcdwYgVuvLD+nrnsbqbxI1jiw8CPKjPKqAW/sxak7GqEJhBwVhA+VavViVdHcncDyzutb9kivHqmBwas+/yvQZ58j2GBb8P
*/