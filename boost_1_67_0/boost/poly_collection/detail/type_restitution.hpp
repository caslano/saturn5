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