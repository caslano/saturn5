/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index;

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator==(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator!=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
void swap(
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& y);

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_impl_fwd.hpp
qvA7uQK73kbfqWyYe0vLVwGft5rW6qJEFOVJgUmpyzLp9VOSPesoBXPaojpch7ClsTZp3KB4KRBbKTl3T84WESNEFCZhKmcGBBo0cyTL4ji2xaC0OLDFx90RD+QaBuoFpNOpRnLueWQlNb/nF2wepYmw5XNuCUkZUynA0uYGOdY63qfnJOuq5ViLN0YrDSVZC/d/rtQH25T/s2JpKtfYmsgGucbGQ72/d3qe7W6Ya+zYDha1hI/lpoIWxyI1N5ZBa1oay/JDTY7l6Yb54l451JqxrJQajqV3k2N54N7/v3WZXtHSWH77pcmxNMoB980vrRnLkUENxzJyu6nZHHCoTN5XHnJIbzoH3GABvpkU4WYT6fAMucuOmBrlgEMMo2TR9qwXRj6D4uEvEf5SJf+gTPhNgL9kTE9TNhYohrES/OX6x+Yh3qF5joar9nQ1CHCNtUNKi6neRohkZUMTVMeAH0kDmKI6tsFVo2RlHSU5WiQrw7Qpbn/PYJf1gzLNerI48kUf87PFmK0sLPlQyBd91kDODpXbRLayZuZ74uq/m++9P7U438HG842YV/nW/T+ab5humOE7xmtzfdl4fa7f7dvqud51UJvr8T/87VxLzcz18R9bM9edsv/Hc21e9Xdz/fCPLc71ocZzjaePUiC1eq4RtAPWe8dp83zDOH2eb0xu9Tw/fECb53MH/r9h+ukfWjPPiwY0P8+Sr85W
*/