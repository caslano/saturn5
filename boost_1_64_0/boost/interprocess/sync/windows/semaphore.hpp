//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP

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
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/assert.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_semaphore
{
   windows_semaphore(const windows_semaphore &);
   windows_semaphore &operator=(const windows_semaphore &);
   public:

   windows_semaphore(unsigned int initialCount);
   ~windows_semaphore();

   void post(long release_count = 1);
   void wait();
   bool try_wait();
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   private:
   const sync_id id_;
};

inline windows_semaphore::windows_semaphore(unsigned int initialCount)
   : id_(this)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Force smeaphore creation with the initial count
   bool open_or_created;
   handles.obtain_semaphore(this->id_, initialCount, &open_or_created);
   //The semaphore must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline windows_semaphore::~windows_semaphore()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}

inline void windows_semaphore::wait(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   sem.wait();
}

inline bool windows_semaphore::try_wait(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   return sem.try_wait();
}

inline bool windows_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   return sem.timed_wait(abs_time);
}

inline void windows_semaphore::post(long release_count)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   sem.post(release_count);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP

/* semaphore.hpp
1ENT/vTzK9b89HCvJPU2x0StlMm0UXbdF4g1Oa3usuK70rneosNXEtQh5v7a0fa0fly8C+vTKnsgt21Uo4c+qLENfVCpizuNzwJPd/LOY67no28/3nn9+WPnc8B6fnNnPvRzkXPMf3h+2JODh25599SuaV985VhV+/HUe+Wj1/P4O/Hstx9/vRMf/dSe4vvv/3TO7x+t7nf631vrJ7126RPvO/PRj+glvm/81dxLHggc6r6ux4v+7L8efMrp3Ln389btyTt/1Cc/cj9LGvwf9EXWzI7DTyn+Pqb8jXVwKXPAB1spf2NOVMq86UOalb+PKX8/rvz9deXv7yt/f0/5+6jy9zNK2p5W/jbOV+8zz4mHLeemCxS+5yDlumjkpqnnsCnXM054Y+CaKHcJ5ZKVPTHPkI/xO8CLhCwwX+hI/wuFH/ovon+Vv/1r9P91YLawH7Av+a77AY8ABwK/ARwG/CawEPgk8FryY4+jPOPjuRWMszTxXQM5P3lxewCvYzzXA0eRB/c68uAWkQd3PPlyRRg3AMv4vXEuv945X4Yrci1x5C6j3JTouQSerQgzH8dSrhRynYCzgb2ANwFFHs1luucAb5DPZnglDG+gJrzptP9HgT3J39uf/L0DgDOBl8hnk5+zjuH1YHgqP+ePGN7zQGH3FxT9Q19yLpcDFbl6yvV0shPT0US5LE066pmOLwGF3wOKvxb666Xxd4z+nqM9fiD98Vwd9xf3kf74TkB/k+ivmP4mM94Ps1xPUeLPf9g53YUMZyT9j1LsUvSwc/kZosgF4sgNUuVs7YSer6GO4fWME94uP/dicr9pmLpuIs/WbvLZ7iGfbT1wCPBrwGvJIzwd+ASwBHgEeAt5hBeQJ3gl8Bng/cDvAXcCnwUiLMnr+2XgS8BH+HyIz08CXwY2AZuBPwHCSd7qn5Kn+BXgH8iz28kf8ZcNPEWe5TeBI4BvAQuBfwWOBL4NvN5Pfl3gb4QewL8AZ1GuFPg74K3A3wNvB74HXAb8I/BTwDDwbuCfgOuB7wv9GM6DDOch4EHgj4ANwFeAjwJfAx4Cvg18DHia/t4T/piPJdF9f2y7w5xPn6TcByLwKmAX4Gjy119Dvt+xzK+rgZcDixhug7E3DchwM+D2MtwKtlcLgKnA21muFwIvBt7F9n4RcDSfEafk976RvOXTgZ8EBoDLgdXAFcBPAlcC1/D3LwJrgTsYzgPAO4H75HOUB5t7trg/LGzhwS7l0aG5wL7kPx5I/uNL+f1QPl8t7yyIpLMceJPQ1xdJZyXwDmAIGARuBdaQB/mz5EG+lzzIm8l//DB5pR8F1rC8rgS+QN7oE+SVfo280r/hvQTvAtey3K4T6QfeC8wBrgdeAVzL8nkfy6dI/3ygSN9i4FbyZC8BruQz6z/3vKBNcGqPKReMI1eg9gOGnHN70myswaOOUa4P3DHK3c3+5R72g+uBffk8gM+inG5gebqP5Wkjy9Mm4G3A+4HzgZuBC4APsnyFyIv/BeB9Iv+AokxvAz7G378jyjnwe/T3HO8FeQm4A/gy7wd5g78b/NbUa4Cm/Z/H9v9W9sNlit0aabfsVvKh2Sanz4ewKuecD1zngs6afPgn241/sV3/NzCTvPd55L2/FJgMFDp2BhYAuwKvIP/9lcBuzKdUjmcuAo4F9gJOEGkATgZmMP96A0tEeoFzgFnAcmA2cJFII/BOYA7wM+QN3wLMVe1EvTqL8DvF6n9Q5XFyKRd2Kec76Cx3QJFLcymXr8gdt9wnUarIFbqUK4oj96baLriUC7iUC7qUq3MpF3IpV+9SrrEVudwuER761V8C1xHc03AtcL6HkyQ3/SCBcPE46g8/Ce4l9Jg=
*/