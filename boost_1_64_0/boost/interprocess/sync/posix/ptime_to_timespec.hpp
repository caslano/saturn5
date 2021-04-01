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
p+f4cw/R2T5O3kmV+tcseGl1bG7GsFxuswcohB/3fUnzNoQ3jTjOvqqRdNUnMuU7Abrwy/157Xt7GLn7PPuc88ho2PX2mSxriQfFTLJYiUD3puBrlZBw4FyTOTw5W88PTxa+FyQKHTLvSisZSDhBoQsGdvoJOK1S728cUhOJ6PO0hW5JwlbeDS9tNpp4F+rkGHZMb76nJDjKoaLjLdSdtwN8oNZ7zoDvwCp/73Lm/Tav02SWAAGs4GCYYbJXJtVt3O3vEjk+kH6okH8EZTcevFkB2yPcLd+oxRcdtxY4PjnNxXxjDvov2Xt+VpjYmk8EyPiMSsX/0Se67s/HINGiHCvcxKFOPbz181EkJDcCR/O9R3Ca8FmI8Di6hni3BTnnXOQ7SVwyefcdgx8VOCf4QeIf8FAdPa/fBr8bCyM4uqDytDBzMH4VhaOfzaOFas+972LHghaFn0GHfj2Qq5kFutluVhDpGKGFF5XQHPHbtao+H1aHC/XHJSXNoavK2MOsRQ4a+nNTqa1nfGyNO4312gKFs9oKfDRnNuL+jUginqWo+jnytD9Smfm7aw==
*/