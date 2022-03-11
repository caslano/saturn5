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