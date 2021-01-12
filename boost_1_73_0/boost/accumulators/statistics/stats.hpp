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
B6QEY786Glqwu2bbOKU2JpuaH6SwDyX2MsZ+Ta9fJ510V476QiP12uoeSg5ds42nf81zwHR4t8+7md5qFm5bjEDnBTXbuE3dthRvWKeq8fBAC/ftt85iTQabrMndPUzWJIZ/jEGyRD4PvPUP2CQKV/NN999p+iXqFEwPS/NplnGmV/Wg4Jneq3oFz7gCbj0sSiGdvfWwO5njMJyMZwE+v79HaFp1CIHOlMi0ar2yWq7uxi73
*/