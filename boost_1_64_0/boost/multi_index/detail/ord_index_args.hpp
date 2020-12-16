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
Uw+nr2x4ePG4aki9GOLUBPLpfXI7P//hSN1wTv7N+MZXUhCLIeknG64/40h4ifYW02ETz4P+y1/pBf/M7Lv3hsMCtD/2BDvL72Nefewc3buPKHTOzjL0+1/Iz3+ovFT+DBtSEq2pmjR0+BBWo6ALMXfc+X4x22AXyzbYV4yCbmiGbui/ih+bUq4bya7xzdwYGKAEyMau8vvF9pG4fzBYkJOjN03vFQbdwL5XCMmj/6qqClb9aGhYOrJ/TA76W3KwnxjikgP6hF0OyjgdB87o5jxl14DJTaQ4M7mJpNZoBqcdqBEV5ZeB0kiduiakbXn518NyD+QE4z/J2Tk84vDZzcLngC74LPYeH8YDyP8iZmOTv9pPGfA/7y4bdpm/bwm8jWIQTOnoAKJspT8+8QIbZjTce6vP/HQnZGOgbFg52d+ke4eKRqeuVhr8rtw+x3DFuAjn+hE3vnn/n/jpJPC/h2y4Y9JA5HgaJuZhb7kWd3boRub3H+K/s2JIuHXESr+xsfaU3+nL94DfdbjIEU4uYPie85nlICQLwHFuMuPGN/PgbT89ma7530udyc88ATb2CMP/vFScyXrCP+PxQ9z4xuf2jJ8GQA8Okg331mxHZcFcMQfzoCBL2w8d3PZDWUVNSU0lH/8Y39pjL/TTe9ADe8uGFbPPgWP1QNEM+yktVe8xCj/1gH/O6DSMb8n/3X7KxPvfRzac/V0ZeDxItGAmLJFykKO+V3vAP+v5myFgr4XX+mlBisZgX9mwx6GB73VvnsgHBu2ZGoNBazzAgO06v0XAxqDJTz0xDwbLho3HbTpQ9x4sihJj50+9lM5gxaC2Vn34KgrGE7AxoKulTYC1cD+FQd+32nTvIaKfcx6fgJofXmDAVm/VImDbA5V+ug9yoOyCR7P3R920Q0VjP3jfdtIYtH3PjwEr/+49wYV+c3/3ABWP0dRQqnsPE1WmHgRsoSM5bYHx4yrGR4rry0pq67hcCjYJWwbKYzgMkQ25+xZeonsPF1EXDqs8wqF0PNe62JWGwSHip/OBw1DZUJMzCBEpI8Umx/+eDHk4yhMcopV86R3+k4qZG+GYTAyTDad9cCLitY4QYZdMtF7NGa9lnjIS4ovZsom450dZDAtVNfGW/peN1b35XfTEoCZPsAjz6wmQiI9nHeOnMcBBZf6OjJhWo3uPFB3JWCuSIRMe4cDpSXBRsX2RF8RkIlc2zJp8dJ3m9igxxi0T13iDBbueAAWzlyqOycOBsmFkaSbmxdFd5cEbDEIV0XK2O18uKra+PCu2dhwkG/qs6JcIbsWmjJhfYReFybWeYFFaN76af+2Io2LO8U72m3P8PNkwacaaKzS3x4qZAeyxfZALD7CQXyX1pWVVXBF+Lip27lSJhXMn+GARfyf4OLPHoASinTrvwzHWU4h7ytowu3kVT8aOfT0hpjcPUf7H17ofpXuPF+3OPfEU6M0Z3sgG47UIm4g7/m2kn/YBFofKhqNPLkx0Mkquz8IfZmid0eoRFvr/4NqG/jcdo0OH+ekZ4HGYbGib9u0AzfEJwqnDEM2AbMz0Bo+qCmbzwhBx+Sb28dNOwOJwFQs2txxYnCg+x65kTCZ0qGdYcB1YWDTsmMg9/TQBOIyUDUeGpiCfwEkiDbOl3bGzZnmDA18KXhcRt79igJ9OARbqXtk7za/g/sgo0T0JWCRDX3iExViuks02Ddv27u8392jyrXs0J4tiJx+t0LEgzaxneeYZGa/SdKVhYoKy/TQTOVeOlA3TJ+5znub0FNHhw0riw9y4zht5CE/icuNaNOy7FCl+qoM8HCUbBuz+98Wa01NFXqp9x7DVIxxC9bX8iyiIWDoiJWZvHm3Zm4U=
*/