//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_CHRONO_HPP
#define BOOST_CHRONO_TYPEOF_CHRONO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::duration, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::time_point, (typename)(typename))
#if 0
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::system_clock)
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::steady_clock)
#endif
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::high_resolution_clock)

#endif
#endif

/* chrono.hpp
/2G+1/gX5MP4aR+X5kvjfy4/8PG3ytfgf74K//Ng/B9T/M/7v8P/PBj/msDwP88b/6GP7WgfU/Nk/M+rbfwF34NrnSId2oa2/lO5pz6Bxg+J01F/045OGDgEisck8oWDwcrGGbxrWJyuygQnhf0Jx8CJ1v99D9tUsWhddwBeRhIG7whECBGty8kHYFTmkyfZWbILbeiNnHBJNr5QiT0VoVKHg+Kg4h614gBM1CBabKNNMAOVf5FOF/wFUnm+CTeHsD6FwJQe2yepiC2LdlKOjqRZMW19CevhZyWQqQIzoSJPG91kSpkB7fDk6CZiChGt+bCyLVDLbFI4kS9O9SS3T+EPCU8N0OmKDCAL8eOjhJNxsMrDyGwltyfPcH58tLCffovkx98q7KDvEXxyjHtYtGzm91tpHWZ+Vc02gak8NdLfRHKqQqccT9Tc0E+Qldl7tfx0DcxfCidf/HOQavKh1qoo0RpCVo6w2kREupMrAE2HaH2wjE1Vi/0G5KEVlpbeCUJ7QrpOcXerY0YSkeScb8CYJqUG74Ax2ReczeiYTpE128Tg2nNnAplsoWU/mKfhHB6QH8YzcjKl5h7B7uHt+eQmPZKN7uGR8vSt2WcIIMzMhmGqezxo8sV4YQngZqb7xLyJxiFEQyMp+wxS4MvdeE+UBr4kL0TCjkHpwTM8gbt4wt5ud2qXYkdUCr2lEBN7AIIXp2F3saaLeynb
*/