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
nQmNG1WtsuLKUpZ+hoFrVQMRFJ0mTI4ldcB0Q10jPw+2n/WLCwTOig6++mhM3mCHC+bdRpQwGwi3DL5SxlXbddGSAU0QvgHKkVJ0h5vTdXT4Kk4e8NWYK/z8+ekb0LXb/RxSwm7kkBYe2wui0ABFM8Qi5haU/fj0DY9LPZt/l8TCt8dQ9DmgylZFm+08nnYNz4skMAc0dhCDqgcaSd4Syf86ltJrALMScRDTte2mUagozS2gc26Qckxw0zpUFW8=
*/