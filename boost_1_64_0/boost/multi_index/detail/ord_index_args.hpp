/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
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

/* Oredered index specifiers can be instantiated in two forms:
 *
 *   (ordered_unique|ordered_non_unique)<
 *     KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *   (ordered_unique|ordered_non_unique)<
 *     TagList,KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *
 * index_args implements the machinery to accept this argument-dependent
 * polymorphism.
 */

template<typename KeyFromValue>
struct index_args_default_compare
{
  typedef std::less<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_index_args
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
    Arg2>::type                                      supplied_compare_type;
  typedef typename mpl::eval_if<
    mpl::is_na<supplied_compare_type>,
    index_args_default_compare<key_from_value_type>,
    mpl::identity<supplied_compare_type>
  >::type                                            compare_type;

  BOOST_STATIC_ASSERT(is_tag<tag_list_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<key_from_value_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<compare_type>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_args.hpp
Hwvr7DE5jxRV9eff5CORT+4K8sdnqCMb7KLo3qJIZzYlfOKs2K2NvRrbOtB5QUVMEXipZKs0D7TDpWWPW5yWVUlIGQn8bbYapzck/TiLX9PmTwuoBzO6fz8kJzZZktIeHUsLg7TeowEYWj/ZligfAATGPK2Wet0R5GvuM6BgIH4G6c+hi55DTQWL1RV1gBSb/i5+5mANSUcqGuhaYJIVGAzjIBo8T+N2yjGMtcz9qCseVHDX06pnfDaO7i1KWP6TVCaAx5qDSl8fogzI9ATkNKfDrkmisGPRFGyIsW/c3faZ5TQQgwKr7TBMBGKKJCsDqN4vsowU3cxCurWQYAKXU6Sco+E+U8d5kDblzscEoJcD1FVkU97L+6fXk4N9KPJGMY1h6qd/lDLhj0lsPSZh/VEIjxjgHij/sUUwPlWmZ0rxiGhyM8SKeGDo7WNzr2QF8w2QD/r31rxibdJRi+/ec88egtheJfybp3QMC72hcFyyC28duFT5hWPqyXcOMbYbg6j5DcY05PSNMn8sh0TzjIG/KoXLgxafT7Rn9LswEJWNo9Yzrljr1RYs9Q==
*/