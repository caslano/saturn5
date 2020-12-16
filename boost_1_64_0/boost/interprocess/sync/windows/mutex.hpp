//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

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
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/exceptions.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_mutex
{
   windows_mutex(const windows_mutex &);
   windows_mutex &operator=(const windows_mutex &);
   public:

   windows_mutex();
   ~windows_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();
   void take_ownership(){};

   private:
   const sync_id id_;
};

inline windows_mutex::windows_mutex()
   : id_(this)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Create mutex with the initial count
   bool open_or_created;
   (void)handles.obtain_mutex(this->id_, &open_or_created);
   //The mutex must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline windows_mutex::~windows_mutex()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}

inline void windows_mutex::lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   mut.lock();
}

inline bool windows_mutex::try_lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.try_lock();
}

inline bool windows_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.timed_lock(abs_time);
}

inline void windows_mutex::unlock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.unlock();
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

/* mutex.hpp
RhprQFuiT+yl3ifxmpT5dw4mYFvuKyRPJdZFLFXltnR3jpxvkLl5BhRRtgLn0/SR4QwwOOfUQvLVgm+O+Nz0Dod6h8MZ4dR+ztiQZore/x0M3gOQntGMTexobXDnIv8xH1V7PSvLba+TUWbpfZa9jtnGNlfRzx4Oez3/Pk97RTnx7XX9+7T2inwue8Uxf/aq1l1a5LbXY+6Lb6+H4Lxqrx+jP4uzetZeZ97nttfbEtjrhPvi2+u299n2OhCTZUf/xPZq8hVl+bPXQ2ivh+Ymb697dNFeo/6Yd/OhXK51SLOQdkOZ7Za9xs6tZ+TRVqm7dReZfIX6+4IEtvqBnJ9hrI7fsbatMl9+7H2DT1slv6edFInc6+BeOs1pF9a9bCp5MowUyBjS2sb3Us9ksY35Wag7J2obo/S2Qb6NcmgbfdLD4f4wDMMd51buL2jvB2jjSerfcZzRw3FrZ+S757SKImh0kWUjuzqvwXs75rTXFnnOaSgnvp00LdLOacjnmtNwzJ+dqHVP1FyDlyyKP6fduyh2TluESr/L69k57dpF7jnt20Xx57SzFsWf045bZM1povOleYnnNJOvI8/fnHYYbfdpH9fgvbs4p1nx3wvcfvgTUWbx/bF++DRYPsd6vm9EvuR98IvvT94Hv/h+Xz74GOPqs6F/H/yofl4YYMi2J5LEnUeaivLK7rf81F331Abfx0Zjf44R3rHynL+e/rkQ5SUfWxW8+vma9jxRzm+D988pfHZ0v9s8RXjCRiH0mSZL93c+gx+Ouo8QO0z8jEb9QnFxY3baMb0HuXU5A7pcaOnSfb9XWhSryzuS0OVCH7pcmECXDyehy988dHlkF3SJ9mp16bwXuabQ1mVfpElI081x+4ClyxibnKzEyTYLGCF8ebimp+h0iHKS1yF5PfUzS85nOuZf+x20Oa+uAtsoKuS82mfrcEame17NIV8Z+JpNvpxSV9zZ6P5RSbyfj+p8cvyY0iKjvIeg3DFrsgx223Qd+qHF6gf39X6iY344+4HENt3ioz/AG9emr3wgsU2/CR6dTR/dBZuemOT88EKRGxNUax570NKlei1K+O3LeDB5PJDxoC88kO47mXdse2JN5jEw9xQ7tqHggdrvlPbxDZKJCNJigqyx+77wr4po7Lm6dqO85HFC7XcmjxNqvzN5nBB5ccx67yzNMxQbW0G+rxXRxsSmJB2DFEGam4SN/VX4oE3YZx9z0aqrOb6vQtrGnGcftGMts+Oqa6bNrq6R9vHZDzaOE7o+Qn7Hdx/HvfR4OX+QsZ3RR9dvyO8e4yjAmlNK5PzFRjF+m5CGQsfpyjjeDHmOlffuyY1l8937PShTffeeoz5Dsa3Uu/ptUN6/H0YsSAN0Z8U9/g9hoc7YSDBG5ReN+fi62lEtw9ue/vK3U1b3j5GqEYxUSXFNyvKlDy/LezWv4NLTLjogwEj9XRip80T/bxxTfepVA7694+P8qe8sm/vgmj2LnWLcY3mu7QC9F6mRf2+M1Kz8PZt/tyDNUY43KH9bOJu7bFxThwPnszHxODOQmslXT76+yjXnWpw2968DXR30BsYHvRF0PdCbQNfn+Zk8XsvjddyPmPusrzLqYwBawfr6IE1gfaewvhbQFUHPBF0N9GLQUYyjugnjqO7MOKp7gZ7O+KpXKe1qYT1batpVg8nYpNNBw6D7guaY+UALQWeCDgPdD3Rt0FrQ9UFngW4MWge6BehsUAvPxfrSNfreUMW5ka9fnH5ptb7Foq3ky0e6nXybgU/aBtqH+LMw6D6Mv7w1cVdjGJd2W+pvO9AtQceCIhk7gCIZE0F3Z1zgSYxPXQ06GbSW5c4C3Qn0QMZxnQO6C+gpjLc=
*/