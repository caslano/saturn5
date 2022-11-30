/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_ORDERED_INDEX_HPP
#define BOOST_MULTI_INDEX_ORDERED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/ord_index_impl.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no augment policy for plain ordered indices */

struct null_augment_policy
{
  template<typename OrderedIndexImpl>
  struct augmented_interface
  {
    typedef OrderedIndexImpl type;
  };

  template<typename OrderedIndexNodeImpl>
  struct augmented_node
  {
    typedef OrderedIndexNodeImpl type;
  };

  template<typename Pointer> static void add(Pointer,Pointer){}
  template<typename Pointer> static void remove(Pointer,Pointer){}
  template<typename Pointer> static void copy(Pointer,Pointer){}
  template<typename Pointer> static void rotate_left(Pointer,Pointer){}
  template<typename Pointer> static void rotate_right(Pointer,Pointer){}

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  template<typename Pointer> static bool invariant(Pointer){return true;}

#endif
};

} /* namespace multi_index::detail */

/* ordered_index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_unique
{
  typedef typename detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_unique_tag,
      detail::null_augment_policy>                        type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_non_unique
{
  typedef detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_non_unique_tag,
      detail::null_augment_policy>                            type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ordered_index.hpp
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
*/