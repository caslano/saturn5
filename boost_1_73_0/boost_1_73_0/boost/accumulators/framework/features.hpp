///////////////////////////////////////////////////////////////////////////////
// features.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// features
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct features
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
{
};

}} // namespace boost::accumulators

#endif

/* features.hpp
VsHR1fuXVwbKIwFElFChurt4jq2IYpg2urrooRzXCyDtUSijQyIC35ccUO/j90yUwAyQwIWNDqkdRlC2CsXVXe65Q30VZxXKuzBQjnQc7kTQYSgNFPM4FRA9YF3ERAmVzqklG5tx7mLMIdFTY5kdupAjBGAjavImlwwcDktT0jDG8lzL8rlQMzTXxW2wq0DPwhAG9zxXVfDAY0hQENuSBFM1Utd1nIfgzMBjKhQ2UBGLWGC5rhrKQEkqIovYCmU=
*/