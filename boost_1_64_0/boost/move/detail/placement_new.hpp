#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
BwzoytJX8VQoj0CCSlO99H14vUMAu1vyEVEoSS0n8ClBA1jSmwDHBIXvhaQdkMksZfCQTLzcx+xZ8nDBerYrEdlZ9qXmc4WzQx21oj6BykKk2RiQBT/B1QGFkmrEbKzC4CMZeGPc21QSrm++3wExEYVqdMQ/GbrZadu+rFQQI+DyFQLgj24oUF8rpwguJ+FFKerTQSxxEG66LRiVnKpdJ2RJWkJOvIzSEhz6+R8cKbx2ayCpsfqf40UdASyBrpDERyMN3cMZCkxsYPMZPehBlognx3t9nRRYfwrXGWNl5mqunc31zxe6HoApZC2pRnjl04NW/irT76pqsNdM1omeR+TP8NwLVmm3f/ZIgUIM8YQw30xT4qObpzahI/jNqh5Z9LDDiXuYEzOz9dMScrND+w4xDhsO8LXATEX+lZqPRnDeaMd4ayN+7kzWfExl46nHEw4/R+lRKPfx1wxnUozYb4ot4Bcykxi8uZhfC56WgQhae7SI07Cq4ccqIWrtA181NRFzZIMbFWg2NfijIwCvU51wrU7ILvbs3+3tqg67e79+eKJim+jaz6LHJA==
*/