/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/fold.hpp>
#include <boost/mpl/set/set0.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no_duplicate_tags check at compile-time that a tag list
 * has no duplicate tags.
 * The algorithm deserves some explanation: tags
 * are sequentially inserted into a mpl::set if they were
 * not already present. Due to the magic of mpl::set
 * (mpl::has_key is contant time), this operation takes linear
 * time, and even MSVC++ 6.5 handles it gracefully (other obvious
 * solutions are quadratic.)
 */

struct duplicate_tag_mark{};

struct duplicate_tag_marker
{
  template <typename MplSet,typename Tag>
  struct apply
  {
    typedef mpl::s_item<
      typename mpl::if_<mpl::has_key<MplSet,Tag>,duplicate_tag_mark,Tag>::type,
      MplSet
    > type;
  };
};

template<typename TagList>
struct no_duplicate_tags
{
  typedef typename mpl::fold<
    TagList,
    mpl::set0<>,
    duplicate_tag_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

/* Variant for an index list: duplication is checked
 * across all the indices.
 */

struct duplicate_tag_list_marker
{
  template <typename MplSet,typename Index>
  struct apply:mpl::fold<
    BOOST_DEDUCED_TYPENAME Index::tag_list,
    MplSet,
    duplicate_tag_marker>
  {
  };
};

template<typename IndexList>
struct no_duplicate_tags_in_index_list
{
  typedef typename mpl::fold<
    IndexList,
    mpl::set0<>,
    duplicate_tag_list_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* no_duplicate_tags.hpp
TIaw4wJhGi5v5sHMhbuMJ5klOcoKdCYrkULGDggKE+SHhqNkyoDcUTiRp1wbIqwMl8WItBEMqlxbDivPhJbADowLtiUhZiAzptQfPC+plKDsvVQm2ku67Y8ykz/u5IaSyNkRZGnASKg0umCRLuQy5Ts7kiE0WVZbwXXmPmVDUkXqSQUahbBcFMdRN2kjrFt7XAuDkjLmxg5aFtpK3WUy/xeQfLQsu0oVJEQ+ECiVZLMLVZGiqsH1zjuJ1tPa4G+W5infFGRByUDPX8N83YMt01y78GUefQ43EXzxVys/iG4g/AR+cGPJrufBJZWek5gCvC8VahJXwPNScExbze/3eI7XbAK1gYRpJE+LAyqb+06RX9tqT31SSuqON+Mfx+9ge4QlGgWBPLA/Ow8muJO0+ab37t2mi4zlLJXcK5YThyGbifXnczoNm9XiKp6FURyE0WcydECdqw2y1JKR1z89gvxJuIquLuPJTTz1F4uJP70eWFXPcd7wIhFVitCzSqOs93wqxzxFSr6e1oYZnpBGmw+Zes2FQNU/SJ7CkNEJdL59ylNZ2T5PhZGGiVchC3n3Clz1asbKMg6cvwlZ5zyglC8eP9rMnk8Q/OmzerledeulIlN2/d5yFc5WV+v1p00wjeZhQL1A/qS3RW9g
*/