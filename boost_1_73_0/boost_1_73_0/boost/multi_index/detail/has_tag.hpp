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
YqSny58eP9nWk888ezQ9eZaeAubhWsK/YOqKD209o5inFTw9BZae0cwTkTzJXz/zpa1nDPNka/kZbekZa+gZunt/jHIVMk+6pmespWcc89C4k3rNIQe6fmHrGc88mzQ94yw9E5jHHQ3lPfbvkbaeicyzGzw9Eyw9k5iHRhcUNdcOeDXf1nMq8zyp6Zlk6ZnMPDRmp349OuXIo7aeIubR243Jlp5i5qH5Hp1p+PW7t9h6pjDPLK1+ii09JeDGPNU=
*/