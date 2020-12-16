//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DELETER_HPP
#define BOOST_INTERPROCESS_DELETER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/intrusive/pointer_traits.hpp>

//!\file
//!Describes the functor to delete objects from the segment.

namespace boost {
namespace interprocess {

//!A deleter that uses the segment manager's destroy_ptr
//!function to destroy the passed pointer resource.
//!
//!This deleter is used
template<class T, class SegmentManager>
class deleter
{
   public:
   typedef typename boost::intrusive::
      pointer_traits<typename SegmentManager::void_pointer>::template
         rebind_pointer<T>::type                pointer;

   private:
   typedef typename boost::intrusive::
      pointer_traits<pointer>::template
         rebind_pointer<SegmentManager>::type                segment_manager_pointer;

   segment_manager_pointer mp_mngr;

   public:
   deleter(segment_manager_pointer pmngr)
      :  mp_mngr(pmngr)
   {}

   void operator()(const pointer &p)
   {  mp_mngr->destroy_ptr(ipcdetail::to_raw_pointer(p));   }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DELETER_HPP

/* deleter.hpp
y5k+q+/Za//Xe+3XWv+1/ojdaSlDXo+h2d2H9Oyb1/Pi3LzeOfxdVSeBypTn9T2C8ytlJ5KsomyQlXpn16FemyFfj5FNJr+6Zpb+KtJJ4TzxmDj7UdqW9nNdYLN7QPeO3A+Nss80ZncCuk8gjO0+oSgn5AK/J+R+6Le9T9u1ujLDZheA6mK8URcz82c786ZMKnQG+r03PsD6GB9EfbDsGfs2duvt72htt81yv9BtMa4Ry1s2Tinfm28i2YH0/M5Wj0ciPmVdqJ/3Adz/Hqh0/ys/Dfc/vqa89qMOrKD6Fflj7pTHNo8bdYXhwzlOMT5T4LTPs6dC9juSO6KqH45Dvdd13Bc4h1nVrrh/lKG9VmZC702803SPawqt8fPgWuJXA7gBUWH4OmgRNxxfCQlxDaJiwsPjGonBgFhpH4jmm9cnGn19NfV1kWOpu9GK0nvC1KtIp+OatryRXTw6N9E4NmVHsV4IyQodNbPdHqfzKV71QG6j82fjeyiW9IaGtUF7ZLKORrhrAW2wfbYPe0ccpiST9TQcruVKnTyuy+2Q20ByGY7wmppdD5jlTkLuCSGnJzliYh1Rrmexf7OXPLjj6BjAft1yvNf+DN7fzhBcy9fmGriHhW7HMY/+VuD0O0ZtyOte27sxnV+lvBY5rLLtp9O54V7b+hE6n+a1rW8+ZrY1va93xvU1tp27rftSUzfytpc6y7vaudt5vK3tLP1dpU8R4LyzqLMUqjOrvYuFF9ptDvxN6Hhz+0zjrUF69M/uOczDDsRG33YHEL7qdiA2SlsClneh69rb8/p0HXETU+XVOdNJht2M/Mb7ts+BOOT9uhv1QxF28pwZ+ar7u5SXawYCLx/ywuWTei4izRSZpqWNpnSwl/sZlDtBWW6yDRFQGyV8GbhtiIQvq24bYmMAtiHcZa3d0V7WJ8T9wixrr35Dh+XlDoJBPE9bMY/5LivCV70/Im6lrRj8sOV1PWQz7HnlZgksrxlBtEtGNdrlsSDaZYOirK+iH2eZZe2TnZM9pPvAvJzuF5MVH6Os3Wr7LmtWNdoFcSvvEysvsuf1deQ1V51XbpnA8psbRNvkVqNtutUOvG2WdLaX9xrxnWuW16I6PRkWMXg9mq+ycni5ttC7jRwpK/WsgrgfTlX0Q6THNnKsZe3cxV7W+QjvVJaVLNXRPX0x5T8fS4WxItnb93ClMvQJoAxu/UURf4qM32r/SpHnxeL7RJlnee3M89M+rmpcO/O8PGMrutrzugCyxcq8mg/ZgPpTsccz9vba/p+xxdV4xiIvtmcs0vT6jC3rpr6GVivLTYamAirz6iCuodVfVt3OVCDXkLuNt2bZy3qD0CNQl5Xvj4H1yU1B3B83VeP+OC+AZ5fZp3sZMXRGwDii8c1bapTX2IcAg5wYTZIaJrP5+7fSOMEuCtMy4lh4mPZLeDjS7iHyw3ElRDTXPgm3jE/LPo93UB4HJqU2qdPf+Wta/xx2Ul9p+OGo7TfCrwRfFYstY8iaJsN1ETI4P08LV4Xz/N4xdYEvpbTywpKgWf6gdr7+oe5E/EYZPqe8JkXIvdNELcjxivjj4nwzc7yiAx07KH/Pki72REOe84dM4/wUTcZHBTd1Uo7S+c58rGtNKW/JJP8cxefMn+oR39Ukv430BkqzcM1ic6Mn6Xt2/q2OyFhHuPimnY/l6N6+qznccYTbSPZ/5q+Tfc8qU7sn+ifpDt+YWXldcF2WWQiZv8EvfMGjGKpIxsTMORGVdIX86h6lIQ4XnKF7tOClyrpHwt0OvwaascfcU3BPw3WEuxxuM/9+hBzb3GK/vzM7W4/hrPr6q01/+Hn83kLzEbIs68jPrv8UYxsPcBh23qg=
*/