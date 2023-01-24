//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include<boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace interprocess {

inline barrier::barrier(unsigned int count)
   : m_threshold(count), m_count(count), m_generation(0)
{
   if (count == 0)
      throw std::invalid_argument("count cannot be zero.");
}

inline barrier::~barrier(){}

inline bool barrier::wait()
{
   scoped_lock<interprocess_mutex> lock(m_mutex);
   unsigned int gen = m_generation;

   if (--m_count == 0){
      m_generation++;
      m_count = m_threshold;
      m_cond.notify_all();
      return true;
   }

   while (gen == m_generation){
      m_cond.wait(lock);
   }
   return false;
}

}  //namespace interprocess {
}  //namespace boost {

/* interprocess_barrier.hpp
ycPTY6NRrnm+66ffde+3bJiOvzb6Ey9YjVVTGrXsXNEcRbigNUROVTBrM1BWmnvamK18is/vlE0y41ZRKBgoryLwMTBHVHQPiWIMKNuSZIVjT5SfVSGop6CAqc84AwQdUIvU6YNwl9RkNWlrImcmErKXgco0NonWDLgfkN0nZNV/m0oBWsvM9UGxDG2nB7+44DnIp7jLPNDYM4jhQKIz4z43ebVBvWBZ9iK5mx/3r4N/QUeTdSs22+Lg7jNWBDiMJUu1cvDYH5aY8eQvYjbUCIRe4M40Dzxn5VDO/TpY59jykjyWrgYFMJKI4d283bTaEjCJ1SdXSneVzXRwOdpw8FQv/GXkHryQYKZPw1Mm9FDuTntDGwv1oamvuJAizyc+W11bLoAz2sbXrks4rnqdJJJMhnhot01mCCIgl1MsqavnpMzaESn2qZxyBArbV5c5q7ycV12cKGeoT/L4KmphVslqOXAXgeC+6JM+mFIbtaU76KtUM87IlMQE89YwZteiPPiRtmHGuBGOZk1+pgBOP1/E2fWV0s3IaSxgSrdw2anzpac5fQULatYoMmdEybCIWDKREBim2Mnfr7amf4TEHGYuiimG8/FbYH5pU3reoFbi+Ry5+0Pjq6zmV4Df5C8O6GxMfsqxNSCytEtyy99rBK8pyUUWYW8rtmfrp1HsrKn1l3YhQgxPjyjB9fVYlGnVZddpD7XMcqygy1ar
*/