/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/contains.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* determines whether an index type has a given tag in its tag list */

template<typename Tag>
struct has_tag
{
  template<typename Index>
  struct apply:mpl::contains<BOOST_DEDUCED_TYPENAME Index::tag_list,Tag>
  {
  }; 
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* has_tag.hpp
d8m+DTvlXCmkU8Gnr5krz1CPdsK8VgEroviTaz9slfM924VnpwJWTHeBMib6ZXs5Lqhi/mgyz/zizQdk3/Z0wTyms5SyTM1e7pIy28YFT2YKWBl5Oy7d9Sy5t+vjgn48lgaRrKsry6XMdnXBe1sLGD0MT9i7v+yjoS74lPmrIN4n/LZe0jnMBQsHCxgVqo6+0G+JpOVUF5zGtAyhueKd0iDbO8cF3bcTsP0SdbByd5Tj5RYX
*/