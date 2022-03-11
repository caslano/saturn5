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