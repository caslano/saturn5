/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/tag.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename SuperMeta,typename TagList>
class sequenced_index;

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<typename SuperMeta,typename TagList>
void swap(
  sequenced_index<SuperMeta,TagList>& x,
  sequenced_index<SuperMeta,TagList>& y);

} /* namespace multi_index::detail */

/* index specifiers */

template <typename TagList=tag<> >
struct sequenced;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* sequenced_index_fwd.hpp
Z06Zrq9bhVDKgwuh6pWBW7LYQyIXxKOXeJpX2iQDh4V08sPWG+Cu3uEsoiTD6kdmwVzd078VSG3YnhzoJJOG8ohZ4q+qh/GLBK7FC3XVlt4DaxdyGY62gbeaXif0+S73F89d9RZ0+eS72dDg94OI0d9f5Qai8k0kw9IReuw9cahF6AH6k079HCzxd7ent1icyW/qQUB+6t/P7/v5Z6ETLtbSWCHeTY4KA9QcFuD90cj5P0W8CUqbXeom0EF0tiBg89hOxwmjBQpWCb/q/1QAPYCkm5o1aEANGBjT7nx9GfZPF0qlTZ5VQGJrVwMCS6SZXVLOhDpn7HKKpZ4fq5x6wDwRCtxccabIqwWpsXbddpprsn7gcM7NSk6kK4AxnYzPUPtS/EoiHdhwpC5Z5bL3dF6bM8oNVJbzh/1ArHPeUzDY7K1AzoCoUxbJnht72Trex/LgpbaFDN5cwGTwvGquwT/qzEbCun8M3/eavtX1SIpUMTPFqCjyXPpVrKkqroJJzAIUiPyJMXj4dU+nZA+Sn3FcP3uk6qi26Nj9BNeTlPMdPlX2cvYhE7yDYg==
*/