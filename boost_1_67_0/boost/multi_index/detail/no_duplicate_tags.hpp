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
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
*/