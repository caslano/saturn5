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
vL2SAQW8scorjvPcU7xyLMOqa4bFvl7k5f88A98h5qlXS/NUe4bkHm2q7EU/0HnQdNXuuoCS0hdKP9q+u2M9GNuvRR7OHKpXu4ttHB+Yyusxh/JflhqhZLQevfLDer1mFOtF/bHhN/3/yOQhatC6+xg1vTwogo9Ep2ys4CmK3juJjzjxY94aYs5n6rQkqiDs+tqnynd089tq0f83VdSgPYY1aL/1yL/TNvtfQ3Bjsbmbp18916D9fdITHnl4kidleHzeGJ6UjHtEZvBYYluewJAY5aYUXPdRnpQhMXl9pEDnyeUYV5Od6nd9BbM/5itkiB7CvvYef9pXUSyXegruSIriTo/ca7Wk2urrAuwTBdQmzJ8Ir0+1uyn2lL7qoDfIC9PZKIWsqLN0flVYkwq0oXIDnbm6pVrMj3ibSw0EC7WrJA9OklIGx+eBoFkB9GdwUsFW1XdyLZO8wfFS8uAku+sAdnQVAR1Nt+QDdUcb8+xGFWRvXxUqlVCwDJFydUsyxHtpzUEOkMUirKT/SGuNBLH6vSAJYkdQbWdclKVXGYWRWYnQuKBtjzQWGBIMgSGB3VBo4ifVqyrut2i3SfnFeXojRYygo8coQyIf6wkMR2csZfWfqkrVle7HPV+S5G+ji0Yf3fU3aXgpncb+d9n6PVvb94sa0B0GkIAewX8u3NSKnKcVvE/+T289jUaafFSSU2OY8dgLF1IytpNp
*/