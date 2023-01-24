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
+49GXmk6DE7EZJBnoi+AmC1/jb22lZIjLJ9GWnxdUuVdUiB6B9xRbv4Kc5FG70dhHNq4JKHudcmb02QswAHCVBonaE+SZA1ZCBe1sAqS+5CRIe4DcmZydizOWRyIHgtd11ZV/6Wyn5pHPlC0Oy+yvL0lbHbdYNzOR5bjkNfBrjv6bmgLUBdtQxhBpoqORxif+5Jg7I8w+tvDUV8BbRR7g8ETwm1N8zPS/M1e+tDwNxOeZoOUtED0pqnhsN4H7Uevu7eexsobXBS1K9Ncv50yhNXZE3fj2q77mhd6AtZCsGvxjp9LchgswqKD+d10z7K2t/J8iOqeMEOTtlotQT63s6fGoCdKdabI3vmHL5tSZIL8Ngqu97wPlsggsURscGEVNRyES+TNnrhEdE++kV83s0Q67Tctka0p2OoRc27ZzaZccjhKk9aYvfL+EB+oSV8/HLA1dsoLDI1ShhBNy79N54WfHbC1wvfu+C3BI1Sl3P1ZKB8xYw+TBRDu+sBImKH54KbJR2nDWAEbxgoE4NYDTTeMsIXR3HBRNxDKDfem24LccGPMrreaWy4cJxWPdkr+0SCnREwbwVlaAxEX0dFgmJyIdj00x9tOiQeDXW298o+06/mI8KpOc7rtpjpu2Et5q3qqjo1wBKimpM75gremLvsQJVU+4y46mX/l1sFOqzh2oCftrXH6LnMozHVdVt4DAMyx4RpYTw1nsCoH
*/