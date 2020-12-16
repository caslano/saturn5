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
29sdIt+8sScpXy7y2MlkHkbIRzIThmeL8mRChkUUJF4p4G6Qql1/ZxvPdYQp32XWRo7wwyqPILgaRDiGtx15ZmfMHP7GZ/I4odqfuRjN4S+u8UO8W8b7Avq3TArf6l7sUK65xJfxw0xOJKIyTqrUDyePJ10cOo86rjlDs+otvaTK/QT8NGum00PjggxyqAxhZPzsmXx+KOO41Fs5i/+xPsLU589UhheJMHJTWSX+fzkW0d/wwc9iZcm9Mk3L0BXrRgxUp878NOr0s3ifyMyrfDcU418izdc3fe9TvqVUplFYplKY+R7j/Zs6ViyfUqReAVss3kHfbzIJgiTssyGTkwtZOFVROgWXM1mIKfs7qYxTbpVnXpamYohKU5f9gsnzOsszEWEMq7oyPajsoDv2ee2XmYxYeI7reaHvcxljApzC6BnjL0Sl/guLIh7XeXg7Tkna7vTA7K8v2uJ1W5wnpp7N5omiKrI0KhPBuIGDxIE/TnnmXQcWd5mrP6M4d8H98o+p/R4SKL2+c27Sah8FXA98Apha7qmFenmv94iof+Srp4FeBXkb3x3XGP18aeciOXcB3IrOYn1ve1OHX58i/jgzSNebFCYjfHd3dkSHNqDr/uERpNFSYh2O3hbosGqA+yi7+7bv+8OPIr1mr+2q0btftwM6PCmqSwbAURyX2ysaxhiA6puaj+QfvwNgQGnaevzVtxBG9D+P6Fsbe7Dm06GcMf+735HR4WIM0t7IaXDHAGkLd2I0WE4j7Tqn6f0k3P+6M9J0QeocR/T4OKfXuZL62HTImdCfcxdKH+gS0L2E7G5A1zNce6BG35DQPnR3oA0uwEvrttzj9yA0c5mP8G4z+v5FWqcfERpuPiAvxHiidLUhSGjfJzSzGMbzhns1NDLgmvZCzDcmYKD8dF/zyfcex2A5qayJOCgvKdN9xjF2ub+BGJwUdLGZHtx3DMPuWH5+nD5xXye+3zhOF5nWaxxTF5mW5/41hoTJZnsXnxmjY7VxX2XpAYCBQze11UnG0o94+mCK8IgHElp/G3nu/SBMr99SI+fMw1Xm5+mVflgWsQhK662w7Gl0rZ/4AcSnCAQGU6XY5zBsEHsyTotQsAij88ampPlnIkjLtMpSJViunmFBkMl+52tXeRzTKopyP/QEBK6xufAuAS3TKenkXl6EUtBovcUTzXd/1XrT1i+9wpexQS/6gXIKltWqCbpPYmDcoLxLSZz5QRykwsTkMPjKlOvzFL9QpaFTZJkUy4HBkvtvu7QOmUgLGeROmgs7Cuspc35NZZ/WIWJlJHVsEfhIqH2IE3A+NZbP93mf+J5bRU5RCBJ9leXzK55PEkYqg4jmc5LlY/j+zPlyN/FS6VO+hYl8f+d8RZGp1goo3yLjwzuKy/xNutDx8zJyhG4+6dGqYV7ZMrf9wzSWWRb4YlJIcNpXlO90mLux6xSVsKKBT0UYn/ssW/tlhZMXbpCJp0s/KFWMn0lxq2dZHkmZq5ETuUI6fAg8HN9aYuMylmXm+4Vgwb8dU+93A5bG4U0LVyauKyaF/SZtfO+zrI1zx3X8UHEtO1Usvclxoed4v6S+k3huKVicJJvnkTwfP/WDKsxKwaOg8zr91qpTkMSx72SpmBRSnOjb0lnWl1EcuJFfEn2bPz1xHD2c9Y8rXcfNw0JYUchH62Sf5nMq95IqSPIclmUDut5AfMbwXuLEnhdFAi6GMrxZW6xSPFw3zN3U8aT25ayj/JiYOfBLYSRMG/4Nyp8Lr0pKP4+lXjdO4Df5I/+Q8xdOEeR+IfXS5lb8GIua9UNVFWUeVBn2g2HGrjD5XjvL94TTwqu80K+E66gd9OXAO7u8IssC5vVqNR4=
*/