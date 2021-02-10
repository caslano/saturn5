/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/function_collection_fwd.hpp>
#include <boost/poly_collection/detail/function_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Signature,typename Allocator>
class function_collection:
 public common_impl::poly_collection<
   detail::function_model<Signature>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::function_model<Signature>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  function_collection()=default;
  function_collection(const function_collection& x)=default;
  function_collection(function_collection&& x)=default;
  function_collection& operator=(const function_collection& x)=default;
  function_collection& operator=(function_collection&& x)=default;

  template<typename S,typename A> 
  friend bool operator==(
    const function_collection<S,A>&,const function_collection<S,A>&);
};

template<typename Signature,typename Allocator>
bool operator==(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Signature,typename Allocator>
bool operator!=(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y)
{
 return !(x==y);
}

template<typename Signature,typename Allocator>
void swap(
  function_collection<Signature,Allocator>& x,
  function_collection<Signature,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::function_collection;

} /* namespace boost */

#endif

/* function_collection.hpp
rCiJgt2AqgwYBY1GDyzSg0IJmVpLDSFn1SS51Jl3nw1JlcJXNWjMcxuLeBL1Jm2E5bY9noVBRRlLY41WpbZS15kqHgCpjzZK2tQlCVEfCCQUtdmDphRYd+Cu8juJbU+7Bv/yaO7zFaBKSgbc8RKmSxcSpqX24PM0PJ9fhvB5vFiMZ+EK5u9hPFvZYB+msxM6ekliNWBb1ahJvAZZVLlEsdX8fcN3XsmS541AcO3h8Qz590HmOo/8cSFGnVsbZiSHyeXiI1e025TSxBpNU/XWSoq+848DdLEM9bQDncbzD8fOj59EC9qSjLrnWMTlbBqGp8swXobjRWgzSOkU0i5MfDJdjv+maJPF6iKcx+PL8JyEOB2tAZ4xuhPU8/Jq+OUrvAV36B4/txtsdjO6PmqX3obdVKm8gzalllclHViHVo2pGvPl08mIdM9sSh9PZ2fh+den0B2D2lQUdcM5dggx2TZMmt7G60Fvk8sjbv8ua88ucix72+d+vwu0xpreiLjAQtU3vU7Jcx5/g9yoPUyiFoc0edTuH0XtAT0PR1HLRNS+ZlH7x+uoTWgeEGZEdp9ssEd25D4XbihcD54U3/9/tQWPagv+Y23sgBLap8k39Rwg1UJTUI0J+dLDqOWECaiuIdUUECYgPwbP1raX
*/