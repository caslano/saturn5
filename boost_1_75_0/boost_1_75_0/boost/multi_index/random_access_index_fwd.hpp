/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/tag.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename SuperMeta,typename TagList>
class random_access_index;

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<typename SuperMeta,typename TagList>
void swap(
  random_access_index<SuperMeta,TagList>& x,
  random_access_index<SuperMeta,TagList>& y);

} /* namespace multi_index::detail */

/* index specifiers */

template <typename TagList=tag<> >
struct random_access;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* random_access_index_fwd.hpp
goveFdJBiUDhfNWx6T82fbEaAYglRvcJ0IA0zm3IKD7XYvm72OCzb3DaN53VG/HBxUFiyVjoOtuV/C7d9nXB6oCD2xlhiB+9SbG0m2FxhscZ3S+D7nGpjvkbMJ40wAhvEYxDb1CSS3wpOkPqHQygF6l/+6I2xosiWnyRz/wiUwTyF6/bggiGXXXMhaao3exRVMECACFy4euG1LH4dfO0a6GPZh5ucmmyGytbD4sERBim9Qd4J+FxXUd4ZWJFXXdAJC1iPKmRuoP9tKj+WwSRsNOWUDlHxi9A14EBXf8C4erLFWgs+0LJXMAxk68/ywLBkmcN33w91ixypllrdqCR28bUFY2VQVLBtHwLMvHtyjW4vgs+xnG05NGVgbexAvznMPY8oT7+sSKkPqeR58no8KA4tBB2hlEzWrQz7Px3KDvDDE3vtI8pxzGXhTc9Evv+zmPkFKA++28m3cF+VFqe5pZ1cEttzVklap4xjTvZtaiUd4Yk/yRcludOF5/mbmAzUiZsVlFapjoyjbOqjye6gvaiamXJVpSh7SYF272ZRMby+1QOGsNXvA0I34UwI5NJN488KdYjT8NsJqM2a8/bzM/bizmpl2NyNVJdb6kSvcKq70rcRwDW03D5CODZa4Qadtj09T2Omz53Be75rjtOez5vDRFJd4UkZ5Sq6ZnY8ydMz8d/IXqevwLlAuyg9kejg5M/NtsBlwp2pGwX
*/