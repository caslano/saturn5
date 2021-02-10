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
WZlZVVlZz57/cT9Hz1jrj0v/u/ADfxFgkcT/4a+z6sKu+1+M/wdAn+BvSxWnLIf4L/eYtUL8F+sShCvq+At+dt2Waj4hYfjrFAE/ufgRnhw9A7hhvHtMgtu7jHWHx+zlDz/8K+uxVy9evTxhIy8K/JDZmR9d+8ntCfvLhp787c778qWf+n89YX7GvLBPiJy7IGVpfJM9eInP4HMYrP0o9TfMS9nGT9dJcA1fgohldz67CUKfDeeLj+PZxQl7uAvWd4DjMd6z9C7ehxt25937LPHXfnDPUey8JGPxDUAD7k2QZoBvnwVx1IeqfZb5yTYFFFi5F6Yx8+69IPSuoRovY3dZtkvfnp6u90kIlJ9u4nV6upZN799lW9GKj0DB1ntk8S5jWcz2qX/CsNwJ28ab4Ab/Aivg4W5/HQbp3UlOClQUbU7jhKV+GAIqAAv8lJPsM1tw5gRLsR1QG2T4J42jFGt6uIu3RkFgISC52ScRVAMsgDKbGBh8wvbRxk+oLDVa1iC4Sayt6ZKc1g2LI6CEdQY2G9sddu2lQXrCrsbO5XzlsKvBcjmYOR/Z/JwNZh8B17vxbAT9HUBNCfO/7BI/hZoTFmx3YeBvqMI/7gfZB111GgbX+JcNp95nn6EM7TJ4d/3IHD+D/9KM2Gnv
*/