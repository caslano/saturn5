 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/windows/winapi_wrapper_common.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class winapi_mutex_functions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_mutex_functions(const winapi_mutex_functions &);
   winapi_mutex_functions &operator=(const winapi_mutex_functions &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_mutex_functions(void *mtx_hnd)
      : m_mtx_hnd(mtx_hnd)
   {}

   void unlock()
   {  winapi::release_mutex(m_mtx_hnd);   }

   void lock()
   {  return winapi_wrapper_wait_for_single_object(m_mtx_hnd);  }

   bool try_lock()
   {  return winapi_wrapper_try_wait_for_single_object(m_mtx_hnd);  }

   bool timed_lock(const boost::posix_time::ptime &abs_time)
   {  return winapi_wrapper_timed_wait_for_single_object(m_mtx_hnd, abs_time);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   protected:
   void *m_mtx_hnd;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//Swappable mutex wrapper
class winapi_mutex_wrapper
   : public winapi_mutex_functions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_mutex_wrapper(const winapi_mutex_wrapper &);
   winapi_mutex_wrapper &operator=(const winapi_mutex_wrapper &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //Note that Windows API does not return winapi::invalid_handle_value
   //when failing to create/open a mutex, but a nullptr

   public:
   winapi_mutex_wrapper(void *mtx_hnd = 0)
      : winapi_mutex_functions(mtx_hnd)
   {}

   ~winapi_mutex_wrapper()
   {  this->close(); }

   void *release()
   {
      void *hnd = m_mtx_hnd;
      m_mtx_hnd = 0;
      return hnd;
   }

   void *handle() const
   {  return m_mtx_hnd; }

   bool open_or_create(const char *name, const permissions &perm)
   {
      if(m_mtx_hnd == 0){
         m_mtx_hnd = winapi::open_or_create_mutex
            ( name
            , false
            , (winapi::interprocess_security_attributes*)perm.get_permissions()
            );
         return m_mtx_hnd != 0;
      }
      else{
         return false;
      }
   }

   void close()
   {
      if(m_mtx_hnd != 0){
         winapi::close_handle(m_mtx_hnd);
         m_mtx_hnd = 0;
      }
   }

   void swap(winapi_mutex_wrapper &other)
   {  void *tmp = m_mtx_hnd; m_mtx_hnd = other.m_mtx_hnd; other.m_mtx_hnd = tmp;   }
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP

/* winapi_mutex_wrapper.hpp
ybRLyqfqz9LjN67PkJstuLhqlcM5ekW2QnJ5L6nU8nOrsuR9egV6nfCwZgwd5JpxhsrlJtNmrteJNGQxDep63clOxj12BrfdcYTXpLEbme0Uu5Wb97A42w1hueO0a7LZwR2vXawdyrWcdpOp7+xkO4ff8/AXjuhbMm1i6bVlU0tLbyqeVTZ+xqSy0uJZU0H8U7no9qoVNVzHe07qIC950fMx2fJebkbQ6qzK5ifHLyeq7Mpkrv863X9nseXPYMdXXdgyg7YUOmZRR5YrliGpi1GukGaWK5ODHWnTcrCmcv18DiP8ONyH8xDG/UircscMjS31vDnDtHUGy9qVUn6cb6ivm87+CE9rf4NXe5j8vRhpvESXJ/Cvz5Oe9F8if++lyyP41eSR4vdG+XuGPc8UvxnIsyTen/Bzj/l2c0b75Vu0jTjfxX430MuibbXk28KammDZ0vmLlrGevJQn63pFTa0DN4lpK/I1B0Fe59CeUpblWdrlpAe7iLRkMS20CzmXZZwx5bSQ6/tXMqAr4F6B/0aLvuxG1Pv/jHw+ImUv0emNcNz3I433u+9HGi02OuWxH9mdnng/UtCN92BEz5zB/Uy0qxqblSEXnOx2Vsrn6dtVxRa35gh/MiB9u6qxxWttsIWIL4vxqWVlW3d7f3JK7HfZbOgtWePYqMm0H4rff8Cv+/6jcLP7/qNws/v+g7KG/X7hsR06dAH6D1+q3da/gK0Diq1nFX8spv9Ylx3f1gEPtg54sHXAg60DFlu/7tHW67Lb39ajLzLH0T6eQX1DtPkWW6tt4KsZlrG0lO2hszvCcd8Ghja7bwNDFlu+4bENfDUj8TZweE/73dBvibG03WZsA/V2Oy7lu+rshrDct4FNVlt4bANfzXDXBub0stfLt0Xbb9Gbrw/UOfb94ZyzzgjH3ftD2Kqvx/eHiL7lcTmxX2RItzGAW+G+Lbgzt5i6qu1PVbpm/Cpli30jnMavW1oZv8rfpyFtQ3V2oH/n8Wup/D1DW3/o13n8Kn/P0rVj8Gsfv77psS2rugD9xtF0+/j1V2KPt5lnnseu9YqdvpAp2y95jbEtPyirlss322HsKuLMYpxqGzSlt/SPskWOIZbPJkXX4Mr5aM+MYmopp1p94d99P9m0xX0/2bTFfT+pyPLeHqih3PvwI/l7vmHnt2CLjS72/16IshdtL2oz7e8Sv87DfyEzP9Q+tMIyHk4OOb5HIAz3fagv5L4PpaxhxxaPfWhFAu8R0bpanWV/j/gt7FWk2ov9p5PNJoUc3yEQjvv+s8hqB4/9Z4XTO4SljMzjZvnruD/zQ3DvQuc6U2f2naq+5cZ9XOuk3Gjfxfp7/RGOu/6Tckb7/bY4vyH7UDdndBSd9X2ocQZrOhvifj7zPMUfoG9zyDhHMal0fMnyRXfi8NU0tFSiWWY7tSRN3qkbdNpD36zk78xc2aatKNflL2XVPfS/dJG30bZCpCOL6YjmL+LDd4jPem4kx67vn/JEI+6g74KgTH9LhMPeSVf4d68rZQ1df+VB15YIr70rXQddrM/bwhhdy0pumjCteK7IWJf5WuhB18IvfDD5mtZXn68Bra7Sfq7yNeBB18AHlK/nNbr+RbwPmroWT4ytsq7yNaTo+nGpa1UFOgr9e2A756uIL4vxqbqe7mfX9W/iPU6vK3LWXb42edC1qZ3z1UnXE7n6fA2rurIIe2mHwx50DV/gfI2OLZ7O0+dr/la7rm7b4Pyt7vXM33ph8zSqZ0N/+/vOP8T5NFNPuc7lJT9LFD3PyXej4LXac4qUVcdN70DPX3vQVZenIs4sxqmOnUID7Lr+C7JBi65u8zPoQc+gRs/feNCTeRpXzwnUc20=
*/