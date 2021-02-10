//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP
#define BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

inline timespec ptime_to_timespec (const boost::posix_time::ptime &tm)
{
   const boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
   //Avoid negative absolute times
   boost::posix_time::time_duration duration  = (tm <= epoch) ? boost::posix_time::time_duration(epoch - epoch)
                                                              : boost::posix_time::time_duration(tm - epoch);
   timespec ts;
   ts.tv_sec  = duration.total_seconds();
   ts.tv_nsec = duration.total_nanoseconds() % 1000000000;
   return ts;
}

}  //namespace ipcdetail {

}  //namespace interprocess {

}  //namespace boost {

#endif   //ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

/* ptime_to_timespec.hpp
JPR91/MCb3jqF5/2e8+dL85Xp5Mm1zerPO3sv73s3t883hWp1oeewuBodHg06LveUdB3+30/dIPw2HOD4WFwHB76oyAcPHfarbP5dCPfbn1Ls+tJ2m59enkRFQcL9r3XmQ2z+Sy5XeWT9ZurdLKcFXNcrGHu8vg1qBj9KRyPnTC+Xt06rrN+/eMunkfRePNunFxH0Xnv3+9kftArBjOi6ckfj/rk1EUskBjjRMlgFp16kXWaPSycKLq62B66CC+1PMgInoiaGYzHBEjgNFYCno7oIUtnkKs7n0MJ1AjvPt0ZXNVTKJRzvs/yM07jySImn1HkeI7Alo8YDSbHeQmEGJOegnaGscZwhXTspPNMP4Q4ASozCVNPpjrjgAg4iQ5Fcd5tAlS6SqVq7tds44sB4+8ZI5qe/IWNHAskxjhRMphFp46fbcwRPBE1M3qeQQNI4DRWAp6KaP162wLrd1AvItH05FVYMBZIjHGiZDCLTr18RQI/hxKo1UvXorePq3oKhXLO91k4awBWPEdgy8dYA2jDcV4CIcakp6BdldhrAM4gHTvp2kRYA1DCCOkomGoy2lWKHM8RUEGTrlXKcJyXQIgx6SlUVy0gAk6io1Bcu8rrqMqxcmAl9ybb2Xy6s7FQ2WjYbEQA+wzZYvl+
*/