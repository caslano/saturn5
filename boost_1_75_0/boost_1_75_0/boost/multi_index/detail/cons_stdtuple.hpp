/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/tuple/tuple.hpp>
#include <tuple>

namespace boost{

namespace multi_index{

namespace detail{

/* std::tuple wrapper providing the cons-based interface of boost::tuple for
 * composite_key interoperability.
 */

template<typename StdTuple,std::size_t N>
struct cons_stdtuple;

struct cons_stdtuple_ctor_terminal
{
  typedef boost::tuples::null_type result_type;

  template<typename StdTuple>
  static result_type create(const StdTuple&)
  {
    return boost::tuples::null_type();
  }
};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple_ctor_normal
{
  typedef cons_stdtuple<StdTuple,N> result_type;

  static result_type create(const StdTuple& t)
  {
    return result_type(t);
  }
};

template<typename StdTuple,std::size_t N=0>
struct cons_stdtuple_ctor:
  boost::mpl::if_c<
    N<std::tuple_size<StdTuple>::value,
    cons_stdtuple_ctor_normal<StdTuple,N>,
    cons_stdtuple_ctor_terminal
  >::type
{};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple
{
  typedef typename std::tuple_element<N,StdTuple>::type head_type;
  typedef cons_stdtuple_ctor<StdTuple,N+1>              tail_ctor;
  typedef typename tail_ctor::result_type               tail_type;
  
  cons_stdtuple(const StdTuple& t_):t(t_){}

  const head_type& get_head()const{return std::get<N>(t);}
  tail_type get_tail()const{return tail_ctor::create(t);}
    
  const StdTuple& t;
};

template<typename StdTuple>
typename cons_stdtuple_ctor<StdTuple>::result_type
make_cons_stdtuple(const StdTuple& t)
{
  return cons_stdtuple_ctor<StdTuple>::create(t);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* cons_stdtuple.hpp
GxdJm360AcJh71XKZbiZDIi8GuzEAHiBMe38hqcuQZ4VUKzs8BOh/POzMIuf3pLm/xAvw+vNcKex+kv4WBDsT4ej+HAco4wS6BvmfWEj+q6pyuQOVUTOpwt/iP7hTHZ5PIGiOLbHBo3ncm08lxvj6Vsucb67GcvlahzR80zni6mihbdYDOhOtYRTZNiLP7PRmBb7OkITvJMeU9uLEph4S5WXJtPQFuOw5qdsQLXfxFyXXE/aNtPAHqjEgW3AgfXAwHq1gd28iwc2Rx9YCYghDix0HtedRlXL6hChtN+Co1pB7GYDXoY340pj0IG0lFNWTAP2bPRgkE8h+PZ5sWS4Pg9b8XIYywbeES2mDxYb4+v5UxfbC78j598Alm1SPvThN8JeUJwfyLqgNuoEprOBiNZi0dO3YTyZ2Nm8u63MwnkuG6w8l/qePB4feJ3qKKmch1D2rURylZJaHknWCsfcfuHsmn7RWDJA2T0FWztmpxbcdr0vHA7DPFw5LEnZ8DB7JUIfN72xMBJVkUTqMqU5KhZsnNQJ9nKV8N4S5dm3kfn4SupuJTJoz7JZ0h7G6J0+qTT+JcqwsZzTsoHYQCUFv+7DRzAt33nYPMHYu+XJICjtpfZV49nvNuHLMIt2rfRxkRfTyrviTKmgdjaj/7C4fKVtuIX2jiXKlGyrmSqXZJk2eEgHs8j1z5UydrF97vvo+EcOndqqSRM1hHmG
*/