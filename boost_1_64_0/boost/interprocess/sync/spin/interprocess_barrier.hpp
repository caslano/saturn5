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
aDiwVO8UjW6IeqgTSR+x0dG6s+kuI41nV9xog1QbEE95yqwbX+C2gzamcVIhekwIx9JmkxCVM+joQ6ou5yaeLnak7MWgl/NlYrHG6STDNioTuJ6RPGvWSL9kCScfS07vrK+MLbse07LMCPlB9Vl12w26++w0WKaBT+/ksmtkowCQGnLSeVlE2gNSOfFF+HDhjyNlTVSTgz/DRZGAjf/OfEe3XM6/aDWPcfMVaqMUT8B23zbIINnW1bwrJ/pnAKDNgOp1Xf/CpNd+epmfWksDrEauBpMd0BsK4LF4MBHw+qhlvu/R2miTwmV1yk2lPfYu87ILwxzWwURIrshXkVBQqSZBX2geKXH2Pg74aAm9WG79eONYepQnIY9MRocTRV5OZ8JF2IYfj4jGQQ0eBselj+++fafoKS41bt0gRQ/4xZJRXUl/bezX9wEqpryPzj3xyPG4sknuRpNF377WgBlWRmPGlMS74F0SMu0P0TdEfuRX1qKvQmECPaLCyNoeZ6POVmxp1+4DAxEJeds8gH6pWRkvIZDZzOYEEJJu09a7yC8B++fY9nHQTA87Wg==
*/