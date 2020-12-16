//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_LOCKS_HPP
#define BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class Lock>
class internal_mutex_lock
{
   typedef void (internal_mutex_lock::*unspecified_bool_type)();
   public:

   typedef typename Lock::mutex_type::internal_mutex_type  mutex_type;


   internal_mutex_lock(Lock &l)
      : l_(l)
   {}

   mutex_type* mutex() const
   {  return l_ ? &l_.mutex()->internal_mutex() : 0;  }

   void lock()    { l_.lock(); }

   void unlock()  { l_.unlock(); }

   operator unspecified_bool_type() const
   {  return l_ ? &internal_mutex_lock::lock : 0;  }

   private:
   Lock &l_;
};

template <class Lock>
class lock_inverter
{
   Lock &l_;
   public:
   lock_inverter(Lock &l)
      :  l_(l)
   {}
   void lock()    {   l_.unlock();   }
   void unlock()  {   l_.lock();     }
};

template <class Lock>
class lock_to_sharable
{
   Lock &l_;

   public:
   explicit lock_to_sharable(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.lock_sharable();     }
   bool try_lock(){  return l_.try_lock_sharable(); }
   void unlock()  {  l_.unlock_sharable();   }
};

template <class Lock>
class lock_to_wait
{
   Lock &l_;

   public:
   explicit lock_to_wait(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.wait();     }
   bool try_lock(){  return l_.try_wait(); }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

/* locks.hpp
JOLF+jqeAEeCy8Bh4LPgcHAFOAJ8ke+/yc/5iMO3ncP3OTgK/I71Te0Gh4K/gFeAh8Ge4FmicgbjwHEinuB4EU+wiNNpo7kuj9YPUjolgmu4HMM3Vk5tGJDW+IFNeb9/FvgrlxPHwAHgKS4HNE4XHbyW7W8GQ2FeIp4D3st6k+4DHeBfwChwFdu/BB6Hu/fZfivbfwz+Avsf2L6K7KU+EFq/BT5Gz/HRB0L7ZZ1gJhgCtgLDwNagkGvLelqywQzwXLAX2A68AuwG5oHdWX9KD3AK2BMsBTuAc8GO4C1gZ/B2ln+I5StYXoR3gbE2CXyEwxsNzuLwnsX6WuqDSWBzMJn3UWeBjcAcMIn3ZZ8NjgObcPiagpPZnQdMAa8Hm/F+7VTwT3z/IOVbXt/C635EeFrSd8CTpaIbC/YFu4H9wFGs5yCP9byVgQgLpcMAfu+DwaXgEPBe0nfA+R5cwfoN1oFXgxvAMaxnqAD8CpwARop8C9YDi8EEsARMBieDfcGbWO9BOZfvU8CxYCk4CZwKesAy8A5wOvh38FrwPXAG+C3L7WX/jrN/mtB7Jp4PzgLjwXlgC/BmkR7gfLAPuBC8GLyV64NhxtoIcBulKy7xfVv0TzQDO7I+jU78PXUW8XB47UvB88HpYFfwRrC71AfAc8is47wa/QIVQcqtDFJurUVuiZ/cUxa5LUHKVQYpVxWknNYtOLmYIOSyhSzLNeLv1aoX6WauV+aDDVl/30H2rye7W8Lu6oHz2F0xtwemgrTem9sD03TWE8XtgWvBC8X74HbATDCP9QqO4/vXsj7B69jd9eBNrH+uHLxD2HO49pjjl3inXE8mkZ4vqQdLcD8YCh7g8P3E+iKqwAwwhMujSLA1eIjry8McziPgSPBX1o93lNspv3H4joGLwePgUvAE+GfwJNeLv3N9eAr8O03CeuvDcPAQP/cw6GS9Ei4wCQxhPUiRXL5VmONweBa/h/rgUo7ve9we3gK6WX+aSP+tYCvwO673tvF3+gl4OetNe4D1pi0Hv+X27C7wb+zuTUpXb7i/Ar9hf35l/WnHSI71TBrjJOBIfi/x1A7mc+85vzTg99GQ80kj1tuRDbYBG3M7MRkcDjYBn6F37Q1nM24PpoK/gWlgBDxuAzZgPYFng9ncrmsJ5oCZYHdQ+H8lmAWOYLld6H95jjpq1DGxtEvNeiQMHRIxl4vC7z+jNyKAzoj/eX0RtdUVYdcR4a8fInjdEMHohfDqhDg9fRC+uiBqrwcikA4I1wU23Q+s96F2Oh8WrPfX+xCczodg9D38t+l6qEnPg9TxUDv9DjnDoGMB1wxcS3GtxLUZ1x5c4cOdWgauXFweXEtxrcZVics1AnofcOXiKsO1FNcqXNtxHR1xRvfCH/X379v/P7FwZr7QAHB6+/9bYH1oS7G/v2UImiEXDB1y8YBB/YYMz7v0ouH9eudNLZySV8ZnofWv/5lFT0C5znU3x1tYvpWEOtM7n+PnEa0TozmSUwkBz31kt3JuYlwtznKEv3SWo3Wu/yiHMZQdhAi7OMRVHcaiMi2YtTbu+icToROB0mvS5IL8SeTQ+tyxrI8s2uj34lonzjVVPpcOKJNnTwQRZ+uzFjjtZxS/DUN5pjyj2Pd5Gr2H9dWd45wZ/FnF5ZnBn1Vcnln3s4rX1+GsYiONJrnsZ5O+A/8qMo2zSW1pVGNercisxRmlmXU/oxRhCHRGqTzL4t8wz/RHnXFR23mjI4OF/c3dPfVn9JqZ/0STo4+Ht9+8/F8/b/RHzQ+dOcuibvNPpl7ITKnnfLvfOEYD6/kJLBeqkEuwyI1muega/CtnuaQa5CpYLjGA3CqXVz/hspHOGvuPq8o=
*/