/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/any_collection_fwd.hpp>
#include <boost/poly_collection/detail/any_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Concept,typename Allocator>
class any_collection:
 public common_impl::poly_collection<detail::any_model<Concept>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::any_model<Concept>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  any_collection()=default;
  any_collection(const any_collection& x)=default;
  any_collection(any_collection&& x)=default;
  any_collection& operator=(const any_collection& x)=default;
  any_collection& operator=(any_collection&& x)=default;
 
  template<typename C,typename A>
  friend bool operator==(
    const any_collection<C,A>&,const any_collection<C,A>&);
};

template<typename Concept,typename Allocator>
bool operator==(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Concept,typename Allocator>
bool operator!=(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
 return !(x==y);
}

template<typename Concept,typename Allocator>
void swap(
  any_collection<Concept,Allocator>& x,any_collection<Concept,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::any_collection;

} /* namespace boost */

#endif

/* any_collection.hpp
L2lblAGjQXWr2Mas9LbjHeaIJhJdTZYwkE4I1Sa7ocqpPMW34oadRd6CWTvWqwWx6R830koz34HpBPEvzq5DZX56Gz2hzIPYCcNaY5gvWXswClsguLygoHqqhjQYiqLB58pkPcqiG+HstuQ+qQ8Sy51duNM32RC1C47lsIVOkk4RDcCSM4/9haR2xMXjp3gSic/MBwyEU7ZyMJnuiBM/64+7e1To7D40SBx2prr1+moL5G8+hezhPs8z+vW+T4ekzs2Z3z8iguKBHdxrpltZuNZIH1zp62JBlBJ+RMr3ewSsXfmprtQT+ipOFyo7biHHP0nX6fGBcAcD2Q9ZbN7sFs+H51e4VuG+fwbs0hUnKWmwVrX5x4Qezay/xA+Pmk8WBxSUJEXKc6+j1rBrFfgwa5mWzakTLeos/pSVOZvt35kKmzhGRZW18k81dJ2xx9n38utVyh7dZW/kpgc9ewPgT+kY/W1sHCzbDHiBj5jrEnu9pkoXYVsP89KIIQDuH4rt4rM8l4TONbJtmjnuyO8xALT7pWu8Edn3qsultBnjAUY4PTudSx+0JAhhYQ==
*/