/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_TYPE_RESTITUTION_HPP
#define BOOST_POLY_COLLECTION_DETAIL_TYPE_RESTITUTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/functional.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* Given types Ts..., a const std::type_info& info and a local_base_iterator
 * it, we denote by restitute<Ts...>(info,it):
 *   - a local_iterator<Ti> from it, if info==typeid(Ti) for some Ti in Ts...
 *   - it otherwise.
 *
 * Using this notation, restitute_range<Ts...>(f,args...)(s) resolves to
 * f(restitute<Ts...>(info,begin),restitute<Ts...>(info,end),args...) where
 * info=s.type_info(), begin=s.begin(), end=s.end().
 */

template<typename F,typename... Ts>
struct restitute_range_class;
       
template<typename F,typename T,typename... Ts>
struct restitute_range_class<F,T,Ts...>:
  restitute_range_class<F,Ts...>
{
  using super=restitute_range_class<F,Ts...>;
  using super::super;
  
  template<typename SegmentInfo>
  auto operator()(SegmentInfo&& s)
    ->decltype(std::declval<F>()(s.begin(),s.end()))
  {
    using traits=iterator_traits<decltype(s.begin())>;
    using local_iterator=typename traits::template local_iterator<T>;

    if(s.type_info()==typeid(T))
      return (this->f)(
        local_iterator{s.begin()},local_iterator{s.end()});
    else
      return super::operator()(std::forward<SegmentInfo>(s));
  }
};

template<typename F>
struct restitute_range_class<F>
{
  restitute_range_class(const F& f):f(f){}
  
  template<typename SegmentInfo>
  auto operator()(SegmentInfo&& s)
    ->decltype(std::declval<F>()(s.begin(),s.end()))
  {
    return f(s.begin(),s.end());
  }

  F f;
};

template<typename... Ts,typename F,typename... Args>
auto restitute_range(const F& f,Args&&... args)
  ->restitute_range_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

/* restitute_iterator<Ts...>(f,args2...)(index,it,args1...) resolves to
 * f(restitute<Ts...>(index,it),args1...,args2...).
 */

template<typename F,typename... Ts>
struct restitute_iterator_class;
       
template<typename F,typename T,typename... Ts>
struct restitute_iterator_class<F,T,Ts...>:
  restitute_iterator_class<F,Ts...>
{
  using super=restitute_iterator_class<F,Ts...>;
  using super::super;
  
  template<typename Iterator,typename... Args>
  auto operator()(
    const std::type_info& info,Iterator&& it,Args&&... args)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator>(it),std::forward<Args>(args)...))
  {
    using traits=iterator_traits<typename std::decay<Iterator>::type>;
    using local_iterator=typename traits::template local_iterator<T>;

    if(info==typeid(T))
      return (this->f)(
        local_iterator{it},std::forward<Args>(args)...);
    else
      return super::operator()(
        info,std::forward<Iterator>(it),std::forward<Args>(args)...);
  }
};

template<typename F>
struct restitute_iterator_class<F>
{
  restitute_iterator_class(const F& f):f(f){}
  
  template<typename Iterator,typename... Args>
  auto operator()(
    const std::type_info&,Iterator&& it,Args&&... args)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator>(it),std::forward<Args>(args)...))
  {
    return f(std::forward<Iterator>(it),std::forward<Args>(args)...);
  }

  F f;
};

template<typename... Ts,typename F,typename... Args>
auto restitute_iterator(const F& f,Args&&... args)
  ->restitute_iterator_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

/* binary_restitute_iterator<Ts...>(f,args...)(index1,it1,index2,it2) resolves
 * to f(restitute<Ts...>(index1,it1),restitute<Ts...>(index2,it2),args...).
 */

template<typename F,typename... Ts>
struct binary_restitute_iterator_class
{
  binary_restitute_iterator_class(const F& f):f(f){}

  template<typename Iterator1,typename Iterator2>
  auto operator()(
    const std::type_info& info1,Iterator1&& it1,
    const std::type_info& info2,Iterator2&& it2)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator1>(it1),std::forward<Iterator2>(it2)))
  {
    return restitute_iterator<Ts...>(*this)(
      info2,std::forward<Iterator2>(it2),info1,std::forward<Iterator1>(it1));
  }

  template<typename Iterator2,typename Iterator1>
  auto operator()(
    Iterator2&& it2,const std::type_info& info1,Iterator1&& it1)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator1>(it1),std::forward<Iterator2>(it2)))
  {
    return restitute_iterator<Ts...>(f)(
      info1,std::forward<Iterator1>(it1),std::forward<Iterator2>(it2));
  }
  
  F f;
};

template<typename... Ts,typename F,typename... Args>
auto binary_restitute_iterator(const F& f,Args&&... args)
  ->binary_restitute_iterator_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* type_restitution.hpp
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
*/