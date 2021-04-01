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
cPbajH0ZZlTaEqrP7VM1vbtLYFhv3Bqv41W/+cUzot3W/y6tQncvzY8QgP/H6CA6UZ0ucO4gizg/aqTQWjcvwGfimapRRrNzRh5SViFQNJ/A64qgfDeLRjPohG8MPBbX60EBe2iwbzZVqF/2PXgiT0XDJxUgupq6wat9g6T8ihqWEKT5WAO+dF79EirM6OcGSh8jTNEAJI5Zf9ctyp3gOdVot3hOqWBAKYJjbVfVYJ0oeS6gXupVFJWUeYTZvFOwYNt0SGnCzzGp2NTjXXFow8BOnpt4Fka6/l38F/CCP4Qk0Yfx+YOXXkvm7+aSa3FUnvvDT9X4/Oh2bCnHTQFf5wEx9y1sH3xJOSuAoD7CjIieLcaZ6Vb+YStpzzeN0QzogPhhOhwISrawHMMNo06INT5cc1DRWFbaxyXf9IkQzVLY8ArUp1PZHqOWdChWWPnLN6VB3xgVRWxjinD5nQxNz8FvGB+BfI5ObQVfipRoOIIshxPpT463lBzwDiKH2MR/4QgUQeA6csv6Kncs/c4T8yH00ijF4znTHsZK7NaYhtJ8J4gqsHQxwCKj/A==
*/