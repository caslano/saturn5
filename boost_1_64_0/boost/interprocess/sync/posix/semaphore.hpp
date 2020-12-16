//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/posix/semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_semaphore
{
   posix_semaphore();
   posix_semaphore(const posix_semaphore&);
   posix_semaphore &operator= (const posix_semaphore &);

   public:
   posix_semaphore(unsigned int initialCount)
   {  semaphore_init(&m_sem, initialCount);  }

   ~posix_semaphore()
   {  semaphore_destroy(&m_sem);  }

   void post()
   {  semaphore_post(&m_sem); }

   void wait()
   {  semaphore_wait(&m_sem); }

   bool try_wait()
   {  return semaphore_try_wait(&m_sem); }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(&m_sem, abs_time); }

   private:
   sem_t       m_sem;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

/* semaphore.hpp
6Q/fD/kU/RaXsN96/cebTh2+49DM25o2eHHRSMQ1juL7yh1T7s5atHrc1w1OPnc4oxlmjEtDhH2ie2y/DwfuL27V/L6Fs2YuP4z2vUPY90gpPHLDqPHnOKePj5q1t/Bj1Etk/9md3266sLDo0dm/XDfmhdRn4MdrmrCvunBA8rSM2xf9rWHX2yMqf98HnRQUnqS3Zi06kTbsjVtmXPLX+a//ZTPm17OEffQW94JxaV93/+X1nJcSivtNQN6gdJj39EOffPdOdvbsdwbPKFr85/1Cl5GwX7912A/PTGq859RdFb2/SHvxIOoTki9LWnh49sAHR9zc6spHYnIidmnavRTfZx59qvdcl/P3Cws6Li/5pmM+0pPs9y9Keaj1hpITsw8++eqcJ5uuQFtNF/aeLcXzD1e13PTxXb2Ss77thPe4md7v2+64NXk5Oeu7h5zTeUqTi1CGjKR4XRd737p1U5KGbnnsmpcrM0dipv51Ss8Xe/Q/dKJLh4/v2fv1OwV6wQea9ii9x+zsp4Z8v/V4w0Hbr08e9EjyRqz9oPSc0jQzZVWDpX89NvOVBR8uPDgI+mYoPANeWXb5zlMr+v20/N77I59t/iesexJjjHwWrag3Z4BNcaXK36S7oxIy+eLsEfmb6rqN+N3Q6V07ux12XTXaQ0H2IbD/1vI7PE7+/s5iv8/y+3vL70rL7wjpFmt75XMPWn5HWsLzu8XeYbE/abH/1fL7R8vv45bfP1l+h3EcO+MK4d9dcO2Klb+dbH8+LpclTb5mmYtFGvLvK3Ht5N+FuA7S2UN8BjC1qege/TbW9ndE1c5yfPYu8rhC7nyLnGd/YP9aW+Qq2L/oavzLxbWW5RawXBiu3iz3iEMrF3wUjBJ+gvXAx8DG4OPgLPAJcB74JGiG82jg+HS1xrua+LSzyC1h/6Kr8W+luFjupO6VixPhYrl4VFpNwUQwFWwEdhP+gw+DqeBTYGPwFHg26NC95hBQmM8CW4BNwNZgF7At2AvMAK8GW4El4HngFrADuB3sCO4Gk8F9ZJbxyz4eOL26WNJhdDXplWGRy2X/ogP7R5YelnvVCTne13GI5fCdlCeIdAJ7gE3Ai8A0cDibx4DpYDHYHJzM5qlsvg7MBF8Fs8HFIt7gIbA7GI8yrgd4DXgBeCvYC3wA7A0+CV4EvgD2AdeDfcH3QBGO79ndPnAA+DM4EDwODgLdiNcQMAO8ArwDHAneA44COb1w1Q+Y/p2t6VpN+qdZ5Hqyf9GB/aMyeTTLTWA5N65JLBeL74nmZ8AGYALYFmwEdgIbg93BZmAPMBkcAjYFrwZTwAK+PxZsCI5n80F6Np/DBBbz8yNwGfqc+/N3fxnYDBzAzxsIDgAHgUPBoeCV4GBQxCMXnCjs+Tke4xwe8EZ+jvB3LD/nao5nHtgIzAfPA8eAHYUcOBAcx/EZD14DXsPPmQBeBxaBN7A9py+f64IyQJG+Y/D+HcJ/zueFYFPxHHAI248R8py/izlfl4D3gZPBR0APWCGeCz7BZvH8nuaZJPgW+PkhuHL4+VcgWQSRdpS+I8FUNqezmctpPmcDYVOU0/O5nL4FFOG/jd//HWA+uAQU8VgMFpJZpk8F+3uZIn3Oc3nfS3swAuwAivvdwGiwI5gCdgJbgZ3Bdmx/AdgV7M3yfcAuYH82i+dP0PmcBT73QTxf+DOK2zDLEc4m4IugSJdVYAuwPtK3A/iqw+vva6AI/+vg5WwexOarwDXgVJafC64HK8AN4HPg2+Bm8A3wQ/b/K7Y/BqKsoXL/fbAZ+DmYDn4Btgd3gLngl+CV4FfgMDaPYPMoNo9m80SwEnwC3APCTqsCfwN/BgtEmwa8BRT+PwY=
*/