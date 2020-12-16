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
yAbfQSa4Dsopm3upUaZKng1m86zFbPSXwWooUhUSH/E5sLzvp8FiXyLNu5fwdsE3FLVJZGyfVKt4TKnFY96+TnjMDMVjxv1fcRlRHTtrjvRHnMRp6g4JbwF3rpGRawbvL3tHyBkEtu4VP/e2V1IcusryqDgB4uwkWslSqhWo+uXoQcfcrwS9a0ln9/VM42RIaLWvOWjfCnqXeddWbZkzGGs23/XlkXiJy7vKrIMb1741tc39cBC8P8SuktZ9m6I77NxP698Y7r7Mt272OjE+Og6OgNExZNZFsE31x+YnuNJHDoXpiaav94tFdd0BLqBY+csMpufFh5uomL5m/Vv0un1NbKJWX75vY/Rte3S7nbZYinsCAfJQ1sp+x4Hs6NtpVonCTiWQn/q2BN5S+9YyZ1e//k37Nkd3ImczVfQcwQL9irmvWLvdIeyNjotUFxZ6twBRGoT7+/5InKsoKyuFvtl1fUlY34qvnKF9WzQHDhe/L27v4Xiu+PdFHFtgDDM0oFDrvxzR6zW9tDXghX4ScLZq/Tdo3ddE+jcM18MbW8Pd6/zxq81Q/5UAMdS90b9vjd+s8xMv/dekAO6/RusOuwHADjFu/aMatuwVYEAj1+2H+SLO7jq6EaJS74CxXJUaHuu7P2Q2CM5xD6773tMpEHCVl6/YZVXVBNBRMFbhMsxTUp43ipD+23a6lD8IOuxBnAC/LHe8JA2TxL9up993rcvvHnktdhI2V62dUxgpq/UuC5WtHRHPbIBh88Wk0beDf2BI7xXWncs1szYSg7Pecg0G+ISmoxGFJh0tfRz8eJcfRrP1Hy//o3L5Q/q+TXptKr0k5Q5S/SvMfOOpQFJeefyHKXllHnLorpctfgVvk65cDia9Q3qzyWOzqGh45HyZpDZR6B1On0Lie8Zem50rRSHdYUpE8x6waJqlneUq7Wz6K9TO4tDOWgx/gQgzJ2QAx9wEejD3YcI3s0SsTbD3TMaT3orVMwuMzYOrN7hUbcaxk+Y1EAx82+hj/EMlwbhH1nMSG4XjlADj6Cl/CalG7+J3e6TeJxivJ1+SvuaGsQ5J8i4L1HZxKb4YjXAhnWCDryqfqfCfkW5JP9l80IEIOd0kHCdxvlEKrVSxCiZIQVt6x627k4ZZBmMIdyLKxLVDgfgMx/w2EYG6+vVtonANnt92uA52RrRtJN6dyfce0bY+7pGNQH+BvunvpMX5JiuZO2C+aQlQz1m7f+ZIvli7fybEqP2QoFqjc+CXchIB47mLy8UfvItG6BNnyR8amLBwK9ePF2n/iCjoTxXPnPf53S+CIhCcLl6k8FO5dLSIeWMJj5yob25xEKdAB/yCoMhyEL95gmVvE8Iqh7zShr2Qb1jSSYklJLFdNnHCEFX6FyzNkx7QI9W8rtM3w/eEgt2GyqstfwTW7/QofRIJarS+7EhVvZSi3gyMhYoU8ccrVeWaIyXkPZNIl2b8giA3EETD0b2XieNODpDCL5W/wgtAyr1hS+yVufMeyy4MCFJOSiLlrFGW807zK2myphCQlbBZwSeB5HpXpqqiHrl+eGVPm9PeymK0Qix0sQDlECsJID4SQj36rwTbqzr23231357sf5rSpylhWaPK2kmRf/CreoelpRDwNMxnGENNyRkf+PX3gvp7MIEatw4VnzVKh03oG51nVqAXxqLulrKNOgLoXakfh8Lc9yyx8/uGYPxWk67hnKHVaZaGinfQBPR/brwrRxw1PjWsGwQuwPW0gHscNeE4zVfE6RgqE9Uc72mC5LEBahP0nHTAmhd0vEfRu4/kVfSGP5LfXIpMJqapD95SSof+UtD3+uxTFsp2lMM0Xu0ruWncE/LDl+kNHJa4ne0=
*/