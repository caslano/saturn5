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
qQU50x6IcVingic+UQat1APxza9sv/G/Oe89r/1/UEsDBAoAAAAIAC1nSlISM5bPoQEAAC8DAAA9AAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzEyL2xpYi9saWJjdXJsLnZjeHByb2ouZmlsdGVyc1VUBQABtkgkYJWS246bMBCG7/cpEPcOhHM6hBVsQpu7VU/3wQzgCNvUNilS1XevabrSSlXbVJp/pLH+Gc0nT/648NG5otJMir273fiug4LKlol+786mI5n7WDzkz0pekBrno5Sj/vxij1a7HSD03h2Mmd54nqYD8rPecEaV1LIzGyq51+IVRzmh8rhuZja2XuD7oVs8OE5+MsjfKjlPa2Xrmo0GlXMSdJxb3Lsf5KwoOvYZtXvzWNcnwb7MeGpRGNYxVMW3qH5Kw7Tekqe0jEkUpgkp/SQhQRkGhzQOyqCuv+feb40vE4+LQbFy6YJOE1CgNpYFWuxAtiMwq2G6QHM2cNZ81ZJ7r7pu63u3/f8A8w7Pra3/CbMLd7s4zHyS7aoDiRo/Ill2rEgSxHV1jINjVVd3wgww2LBEg4UZODBhWQSFRbf/vf571Hf+RpIeyqSsElJnvk8i6mckq9KSZGFVbYNtWR787Z0AigKjEuisoOET
*/