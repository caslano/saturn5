/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_ARGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_ARGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/functional/hash.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

/* Hashed index specifiers can be instantiated in two forms:
 *
 *   (hashed_unique|hashed_non_unique)<
 *     KeyFromValue,
 *     Hash=boost::hash<KeyFromValue::result_type>,
 *     Pred=std::equal_to<KeyFromValue::result_type> >
 *   (hashed_unique|hashed_non_unique)<
 *     TagList,
 *     KeyFromValue,
 *     Hash=boost::hash<KeyFromValue::result_type>,
 *     Pred=std::equal_to<KeyFromValue::result_type> >
 *
 * hashed_index_args implements the machinery to accept this
 * argument-dependent polymorphism.
 */

template<typename KeyFromValue>
struct index_args_default_hash
{
  typedef ::boost::hash<typename KeyFromValue::result_type> type;
};

template<typename KeyFromValue>
struct index_args_default_pred
{
  typedef std::equal_to<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3,typename Arg4>
struct hashed_index_args
{
  typedef is_tag<Arg1> full_form;

  typedef typename mpl::if_<
    full_form,
    Arg1,
    tag< > >::type                                   tag_list_type;
  typedef typename mpl::if_<
    full_form,
    Arg2,
    Arg1>::type                                      key_from_value_type;
  typedef typename mpl::if_<
    full_form,
    Arg3,
    Arg2>::type                                      supplied_hash_type;
  typedef typename mpl::eval_if<
    mpl::is_na<supplied_hash_type>,
    index_args_default_hash<key_from_value_type>,
    mpl::identity<supplied_hash_type>
  >::type                                            hash_type;
  typedef typename mpl::if_<
    full_form,
    Arg4,
    Arg3>::type                                      supplied_pred_type;
  typedef typename mpl::eval_if<
    mpl::is_na<supplied_pred_type>,
    index_args_default_pred<key_from_value_type>,
    mpl::identity<supplied_pred_type>
  >::type                                            pred_type;

  BOOST_STATIC_ASSERT(is_tag<tag_list_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<key_from_value_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<hash_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<pred_type>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* hash_index_args.hpp
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
*/