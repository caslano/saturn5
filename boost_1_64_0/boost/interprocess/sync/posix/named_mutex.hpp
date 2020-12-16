//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP

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
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>

#include <boost/interprocess/sync/posix/named_semaphore.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class named_condition;

class posix_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   posix_named_mutex();
   posix_named_mutex(const posix_named_mutex &);
   posix_named_mutex &operator=(const posix_named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   posix_named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_only_t open_only, const char *name);

   ~posix_named_mutex();

   void unlock();
   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   posix_named_semaphore m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline posix_named_mutex::posix_named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_sem(create_only, name, 1, perm)
{}

inline posix_named_mutex::posix_named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_sem(open_or_create, name, 1, perm)
{}

inline posix_named_mutex::posix_named_mutex(open_only_t, const char *name)
   :  m_sem(open_only, name)
{}

inline void posix_named_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_sem);  }

inline posix_named_mutex::~posix_named_mutex()
{}

inline void posix_named_mutex::lock()
{  m_sem.wait();  }

inline void posix_named_mutex::unlock()
{  m_sem.post();  }

inline bool posix_named_mutex::try_lock()
{  return m_sem.try_wait();  }

inline bool posix_named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return m_sem.timed_wait(abs_time);  }

inline bool posix_named_mutex::remove(const char *name)
{  return posix_named_semaphore::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP

/* named_mutex.hpp
wl/lWQ8sJ/tZsj+iPO+B5c22lMZlltFOitbF/cu0jryueZkhw3ES5Z4oWx+GfXyCUdZfqdnKcZbpBJl9Quas7ra1qkZ++CEWdpwfXP+i/BDN5zYgLYUclZ/xZj9Dphmdo2mWq4i33ze6kRew3shl0Q24jorxP12Zl0pFsaAFmZfghyovmW2km+l+A2pThRvyCMklWluZz8g++HwmZY18JmoHzZ7X1LKoXTRlPpOy6nz2AN3Px7q3MFs+M9rxn5BMukb9Ro7zu2SXE7DtGws+RTLNNW77wi3sYfMb2YeQfvw9COi2BkY7ZKI9/7LMUcjsI5mBtvzbhGWSG3rbb85GlsabZs/je2Jr3jd2Onk81ieP4z2yXLy0w/uS/sk87lvnLWHlMk/ynsAncB2DXYrDlseN3plf/pbvuQW5eRBrSsPU7QRH4HNFMujeQ9q9vvWLHEN1+O7HKCNzGJ1lvxkPX9sIOh+pXe0QZxvo/QOd5cHyuyD/I7Vvi/3a6lImHOnwk187ucpPJgUyPwuZs1v62PeG/UFqiybY29h8fscvuH8I1/I65hWf8Us+3685O0oXaQ67Kvt7HF9Ylkd5iM4Y957XZ+6jOUTyKfiuI1XvkP3Ta2zrGO07j/dsPp9ydRKfUzeO23aFIr4Ia4pTFVbfcnWZMSZgGV/vRe5y1HnOGXydDVll+UhlCngp3c9Sn+3mVJWX6rIVsurxUmX5KuXlOCTikGe4kXuQziW5IWZZmEvvCeODSNttyUa/U4sK8et3Gvlzdy3aabI8qabMUpRPMb7lk1/dLOMk87Y85+8ybiv35zKqwp5fuJ081a+MkmO1T5GbvloY/u2BS7n/zhm4nPor3WuvZUNSVU69Q/dDqVzyIJ8Pa8Llkh5Nhww1C1QusfysJka5kWIrN+paRhjfXQYXDs9AKBFcCiIdEWl7OhqDcegn2dLSGKdpQu5uc6XyOFQSmSe63BhvegnXVjz9c1yVmC1UpDM/V7eNTclxJ2t7Qo5Zp4cId92dSTxmXUH+nHCegzmBebD/ypmoHMtaox7LQn/Zdj40vevO5O9Z5p61m8l81NkHz3kPJ5ff6Mwz9/j1oXs98E7O47yma7kUzksxjvW843XHQi2WxzBvJdmmrgvgj2oMcFkY1W1mnutE/ngcKdDSDj9oLMAb5wgX4uwbV47TZp84TTT9/jqU9hRSGMWvRvSs2fpZyNOXa611rhNE+pjh9cbtfvTrLtDk/Xy6v9K8X+BK0i9wKNpq5hno+0nuBXOc8jpnG+s3RPGNo/xJYcLIZRzbYdYinL5b5Ko05ZjiREqjLuaY4lIhj6eoxgLHU5wjTb0EI4RbTiM64ZHuh5pnkr1L9z9yOLV3HBxna/orn/EX+CHHGzn8CL1x3mNZqlEudOAxvtActzNMPb7Hbh5O5bJBv8wdFqIY32O5tSyH/YU2mVSWOWo+v/xmnC7vds3d7tZDAp8zb4Q7OY3bv+WVllrEN5yd0rhN1LT8Obejnc+90WlG2MorsPkxYBzmpfH4Y8TsdLPt5ReHNYaMPru9kYhz+rmdUQHikMTu9sDdt153V7odTrQXA6elO51lw2bnBpLJTjfGSuc+JsPqKzPE8Cdy7jJbuQ5zKMyHY+X45BFJqpOH1HKM0r9PsV8xHrmm2rFDKh/tY4w0Bl6fygVPPMmReSWZ7WN54TxZ+CP3Lw7gcqM9Uhlhq3NwRtxUOoc+UtY3Ztn7Pcl/rb2PcvEz1B47cCVqFyKu7BeeUIx50i9wX9YxfA//ST/HmPMmB+nex9o7+PcDXEq9JBGB2wI5kd7zYG/gtR9cjuVb96X3JZk+GIvqBBlveHuS3Wxl2T+I7oVZ/RujWc4=
*/