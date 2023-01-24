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
z2l4tk/HHfcb8HzYlMGaSUTYoia3Ve4cHG2SYuWMhKQ9fsUEhY0MeBpb/2MekI7mHQvmctSVLIUb02GW/WUeemSVM60FktWRT/yUdTo7y+YFgj6IGCrVWd398AJNm38AfZKXp3Yj3kAnaW2UGi8ESuFxQ6GF8nIiVhCnGqO+cnw9iHFIo7KHt0NuJw6aCw6UBZQpu9WPKVOZHUevP6mCyWTE5be6FyrnP5nUevytJH5sZEzEhYPVDaD733RoALGseLcQ+ISeJCt7Y2FyI6H9LZZu9PSAhzcHQjEvfdBkyK8SxOGEompY4xXUi9qBINLfnCIEfDQoFXxRPm4PxLdov6qjiDNVZudRKnMedjxUWRvyoRRK23bNk8T7qXe26i/i1OLRIIbUh0YjTkfLLOCb8Uao81j1Xb6YXjgy7cIaoZXNge05So/b2tiwbFTW2mIyfHQVTtPiEFPqav8ymqmvc6kHJx6MAGtgQIHJoG4DQXxICNyOh9cjD7fhYZNO5Ktbf9H/Hon8vZ+q8ljUzL/R8ZZ9Vr2R/iobHqOaC76nrRyj3gEZzhBl1I9Ux+2faFrHWnXqFr7XErf9i/IeQjzzK7lCmGi1JMqZ8eorWyBZIJLpbUqoV/8A1+IeRhJb6nTlh/pPWA9dJ6y2/EyVfgaTKp2MmngmErYZsjlQK2jox950Tkfb+jE2onpa0giBqg0uzAN/bISUEL2Sv/R/
*/