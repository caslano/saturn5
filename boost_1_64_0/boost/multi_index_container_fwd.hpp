/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>
#include <memory>

namespace boost{

namespace multi_index{

/* Default value for IndexSpecifierList specifies a container
 * equivalent to std::set<Value>.
 */

template<
  typename Value,
  typename IndexSpecifierList=indexed_by<ordered_unique<identity<Value> > >,
  typename Allocator=std::allocator<Value> >
class multi_index_container;

template<typename MultiIndexContainer,int N>
struct nth_index;

template<typename MultiIndexContainer,typename Tag>
struct index;

template<typename MultiIndexContainer,int N>
struct nth_index_iterator;

template<typename MultiIndexContainer,int N>
struct nth_index_const_iterator;

template<typename MultiIndexContainer,typename Tag>
struct index_iterator;

template<typename MultiIndexContainer,typename Tag>
struct index_const_iterator;

/* get and project functions not fwd declared due to problems
 * with dependent typenames
 */

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator==(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator<(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator!=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator>(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator>=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator<=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y);

template<typename Value,typename IndexSpecifierList,typename Allocator>
void swap(
  multi_index_container<Value,IndexSpecifierList,Allocator>& x,
  multi_index_container<Value,IndexSpecifierList,Allocator>& y);

} /* namespace multi_index */

/* multi_index_container, being the main type of this library, is promoted to
 * namespace boost.
 */

using multi_index::multi_index_container;

} /* namespace boost */

#endif

/* multi_index_container_fwd.hpp
7PmUvAa9kdUpeXDGSdXYfMz04xmMHqBMjpb5+QWDvb2mmPiyhEpel/0mVkus6dqP46xjy6LTtX/p8ByM9GonniOGahRoYnheh/RktV7GKVSAuN2eTzo+olmO+L1BZlAcaawiOotSxw65G/4ptQX9UOjXaUZ9gATMWUSYlwMUImfFd+YN/Edx5pJ49nfDJxjTanfrRplspDj6C6LakkdE15qLlV/GobSho/lt3OgER3KuQnJh7WMYgTqTmZZcTl/v1t8Q7ATxntFdRhyAvFJe8q8tIUz8Ye2kJYS7uAl+wVqxaqmFhpQQRANEldYqYyH7DQrPNQ+TZdNTcKlzkgxFOIZ7pC+EFre0xuIZOWDJqDNSNhegkast2DuxrddX5py9P11c0paiJgu9+I8FJ4703cPk4zk7cc+FwR2A93bCwUJmVpvsPcoG5tg1NMKLMZiiTHDkaClm1GRcNkUsSx/5kfTDkRaPS0xnZHejkj18+xMOBXX19Qd018voVJXPWx/wtVhtW//uX9V874l5Xxx1AFrUNcSPLFIBF15CL5NByh/MbpiZrOmz7xSw5g==
*/