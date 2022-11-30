/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_REFCOUNTED_HPP
#define BOOST_FLYWEIGHT_REFCOUNTED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/detail/atomic_count.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/flyweight/refcounted_fwd.hpp>
#include <boost/flyweight/tracking_tag.hpp>
#include <boost/utility/swap.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

/* Refcounting tracking policy.
 * The implementation deserves some explanation; values are equipped with two
 * reference counts:
 *   - a regular count of active references
 *   - a deleter count
 * It looks like a value can be erased when the number of references reaches
 * zero, but this condition alone can lead to data races:
 *   - Thread A detaches the last reference to x and is preempted.
 *   - Thread B looks for x, finds it and attaches a reference to it.
 *   - Thread A resumes and proceeds with erasing x, leaving a dangling
 *     reference in thread B.
 * Here is where the deleter count comes into play. This count is
 * incremented when the reference count changes from 0 to 1, and decremented
 * when a thread is about to check a value for erasure; it can be seen that a
 * value is effectively erasable only when the deleter count goes down to 0
 * (unless there are dangling references due to abnormal program termination,
 * for instance if std::exit is called).
 */

namespace boost{

namespace flyweights{

namespace detail{

template<typename Value,typename Key>
class refcounted_value
{
public:
  explicit refcounted_value(const Value& x_):
    x(x_),ref(0),del_ref(0)
  {}
  
  refcounted_value(const refcounted_value& r):
    x(r.x),ref(0),del_ref(0)
  {}

  refcounted_value& operator=(const refcounted_value& r)
  {
    x=r.x;
    return *this;
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  explicit refcounted_value(Value&& x_):
    x(std::move(x_)),ref(0),del_ref(0)
  {}

  refcounted_value(refcounted_value&& r):
    x(std::move(r.x)),ref(0),del_ref(0)
  {}

  refcounted_value& operator=(refcounted_value&& r)
  {
    x=std::move(r.x);
    return *this;
  }
#endif
  
  operator const Value&()const{return x;}
  operator const Key&()const{return x;}
    
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
private:
  template<typename,typename> friend class refcounted_handle;
#endif

  long count()const{return ref;}
  long add_ref()const{return ++ref;}
  bool release()const{return (--ref==0);}

  void add_deleter()const{++del_ref;}
  bool release_deleter()const{return (--del_ref==0);}

private:
  Value                               x;
  mutable boost::detail::atomic_count ref;
  mutable long                        del_ref;
};

template<typename Handle,typename TrackingHelper>
class refcounted_handle
{
public:
  explicit refcounted_handle(const Handle& h_):h(h_)
  {
    if(TrackingHelper::entry(*this).add_ref()==1){
      TrackingHelper::entry(*this).add_deleter();
    }
  }
  
  refcounted_handle(const refcounted_handle& x):h(x.h)
  {
    TrackingHelper::entry(*this).add_ref();
  }

  refcounted_handle& operator=(refcounted_handle x)
  {
    this->swap(x);
    return *this;
  }

  ~refcounted_handle()
  {
    if(TrackingHelper::entry(*this).release()){
      TrackingHelper::erase(*this,check_erase);
    }
  }

  operator const Handle&()const{return h;}

  void swap(refcounted_handle& x)
  {
    std::swap(h,x.h);
  }

private:
  static bool check_erase(const refcounted_handle& x)
  {
    return TrackingHelper::entry(x).release_deleter();
  }

  Handle h;
};

template<typename Handle,typename TrackingHelper>
void swap(
  refcounted_handle<Handle,TrackingHelper>& x,
  refcounted_handle<Handle,TrackingHelper>& y)
{
  x.swap(y);
}

} /* namespace flyweights::detail */

#if BOOST_WORKAROUND(BOOST_MSVC,<=1500)
/* swap lookup by boost::swap fails under obscure circumstances */

} /* namespace flyweights */

template<typename Handle,typename TrackingHelper>
void swap(
  ::boost::flyweights::detail::refcounted_handle<Handle,TrackingHelper>& x,
  ::boost::flyweights::detail::refcounted_handle<Handle,TrackingHelper>& y)
{
  ::boost::flyweights::detail::swap(x,y);
}

namespace flyweights{
#endif

struct refcounted:tracking_marker
{
  struct entry_type
  {
    template<typename Value,typename Key>
    struct apply
    {
      typedef detail::refcounted_value<Value,Key> type;
    };
  };

  struct handle_type
  {
    template<typename Handle,typename TrackingHelper>
    struct apply
    {
      typedef detail::refcounted_handle<Handle,TrackingHelper> type;
    };
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* refcounted.hpp
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
*/