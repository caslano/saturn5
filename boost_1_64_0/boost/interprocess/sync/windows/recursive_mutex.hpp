//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

//Windows mutex is already recursive
class windows_recursive_mutex
   : public windows_mutex
{
   windows_recursive_mutex(const windows_recursive_mutex &);
   windows_recursive_mutex &operator=(const windows_recursive_mutex &);
   public:
   windows_recursive_mutex() : windows_mutex() {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
dDVIqpXLvPighasKtBQduX3IeFsNsz3C8DEe3gQDVNf+o+zqe3CiwMDR57sjzJqq3yE17jXynHe0dLMr6sjkhjm8XPYvUE+N0Kl/W6riNntI3DHfaY6VAPug8F9uhvrqmaABaKcG4ihpmPM3XdawVtP2KCjeKMUTbuYzlHSrRtcpo6wk7dbV5UEA4zWxEEk8fZcWtHnLyIx8XlL/nl1vCtFmoPUaUTRVguH13DZwCvk6pGbVkTM6Y+ntXn/pETJ1Hc7GErWSEJ0TKYGy/ctynvUIzlZnilKXr3ryo3w0tB0/8Ya6xoleQON/LRtuMx2a8KKfFU1gs0YqxCruZl6u70R+AhIb5IaXzepJT+tjQ/t0XRxVLGKowURDrLJwSnAKgWWnA9rOtPXQW5in+kCRK3ZgA9Waq0IURWDIRW94I6ZgteNvTOHECZ9cy5IDUdTc5scbf5k/8em4jq0tUE8br3a37auZRFHDYqhgipVt3/XN0eaUCOr7HJc1nsyOWMEhq+MXxx5GQc4WK1/QmivRm5I9NmU282F/AfcybHqmB3YKdsomfWsGO19NMQ==
*/