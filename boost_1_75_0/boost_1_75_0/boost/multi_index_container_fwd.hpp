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
GG0NL72Fd/cUJtRzK/4IEQgk5ZhEa4TUxQkvI0h6hPS9VIvWC+FijklqwntgvgHciu+2wbLijoVVg2/QJ0GPhiSkW8q/gR9AguPn0dIw9QyMEFcsGcBfLA7C93Dq9Anfl5+E7pteWFAbTp/KqggfCAXbcf+++sevDCSIUDPlW6FxBXWiyTv5CHCH+7zp3wN3NMnPbmN3u2QX9QAMLPPTyOcArK7UXJJ5B0yGi1uBwX2LFIIXt/wUP57QVzJgPbIf0+5k1aGMVy8P2RZ0z3Gv0vs+Vvf7IRZ29cqcm6fEyW0/QJ4KS77ExQyS2hLOcsvf/0zdfcfNdyM7KrvsUR5vzHH1GIJaiPxmhQ6nF/R3bpptOFczFk0hBhcn3G03gcqGNgMyVwOdNyAGTwADTxVxy1I+pyer9LmiScev9vAQt+yjn/xvCTWxIyA6w0FBfIjObduDUo4FJ2/oWRjtTpiThM7PyfZ2pKQ2YHgx5wCPYtF4resRdjY3Gd/0wtSf25C9FNTJTd+j4TWEpNAEPSf8sF2zT2vejkZsxoRk0OBSd2ixn9JYU0IyqIY1/tj3aKw5IdnMCXd8qcWuorGWhGSYU6/5YxfT2PCEZGBFpp1a7JM0NiIhGSbSIn9sOo2NTEiO5ATZH3vfdpRs82MOGM4amhMOcHwS6hGHGukQleqC7F8OqVxbPv0/bIvhb7vQIMJc13lgWE/n95rEIONj
*/