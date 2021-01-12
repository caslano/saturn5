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
YadpghNNn3VlCH8iCr2S/bFvhG6vl5kf+GqMPz2s5M9WCcJSj6tv2o9KYWv0oVcKAHt00DsgNFSA1mDrtKuV0GRL4BVeDW0NPxYVsjVgTuhketu8dLv++CITrY6o/b9qnzeW/wftg/ualhHi6CqwvGB8LWvl8jj3AygAEGs+l9dECsZ3CM5Ye0etFUKGXXfJrC9KIsr00IoiNn1W018eSudeDmLZ6mVfsCB+/vFyZy1ze2pn
*/