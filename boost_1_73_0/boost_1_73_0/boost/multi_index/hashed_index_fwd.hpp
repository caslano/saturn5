/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_HASHED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_HASHED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/detail/hash_index_args.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
class hashed_index;

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator==(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator!=(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
void swap(
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

} /* namespace multi_index::detail */

/* hashed_index specifiers */

template<
  typename Arg1,typename Arg2=mpl::na,
  typename Arg3=mpl::na,typename Arg4=mpl::na
>
struct hashed_unique;

template<
  typename Arg1,typename Arg2=mpl::na,
  typename Arg3=mpl::na,typename Arg4=mpl::na
>
struct hashed_non_unique;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* hashed_index_fwd.hpp
9unMOgvaQTjRby2qNmI/Zns9ZHX5o0oqkeFqyTL8StIbr06artKb30/eDCM8Qitzy9UdjFZnxL6wJ8vQGs9Mkx1mdH+NZFevWpQihXdPbZpm/oz2thK8P7A9tXXEdWW/mm/PWutu5b/Dohb+aPtjK3TmmJanChAlVzGLeEbTAoec/oL57ipfENcjc3uO/CMTbMqxNTkP/qr9CtHkBNmKpf8PUEsDBAoAAAAIAC1nSlJrqfTlGgcAAE0TAAAlAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9NYWtlZmlsZS5hbVVUBQABtkgkYMVYe2/bOBL/e/UpBmmBi1s/kixu97bbLqxYaiLEL1jydYPtQZAl2uJGFg2SzgPoh78ZSvLb8V6xwKlJRZEzvxnOi8O8eff3PdYbOPmE5jfEB9/EMJTiTxbrw8Rh+A2Kf8j0Fd8nRLRgzfEtrMFJjm9wbjjCUsZHGofhCTFfSTH6r0WMX0Ma4oz1Bvk6YvEi+SzVcN6pweUvv/wLGnB1cXVRByfKOcvA1yyfMDmrw8fEzLTT6Pm5qdhvdWAaoqxpgIKUK1Biqp8iyQDHGY9ZrlgCkYKEqVjyCX7wHHTKYMozBp3B8N7r39ThKeVxihgvYgkqFcssgTR6ZCBZzPhj
*/