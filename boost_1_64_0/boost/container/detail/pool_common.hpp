//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP
#define BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class VoidPointer>
struct node_slist
{
   //This hook will be used to chain the individual nodes
    typedef typename bi::make_slist_base_hook
      <bi::void_pointer<VoidPointer>, bi::link_mode<bi::normal_link> >::type slist_hook_t;

   //A node object will hold node_t when it's not allocated
   typedef slist_hook_t node_t;

   typedef typename bi::make_slist
      <node_t, bi::linear<true>, bi::cache_last<true>, bi::base_hook<slist_hook_t> >::type node_slist_t;
};

template<class T>
struct is_stateless_segment_manager
{
   static const bool value = false;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

/* pool_common.hpp
MJWx5sb3D2Q1wuzjF1idqGX2iBIPrFWM2d9rni6HmRd7243dQpJgAWQms/V3fD8MFiriPg/4eAAsmoz33T5vhKWQ8TodDy/KwXYpmwz9e98Y57VPzfU2Ni63GvnMNnmN52yjkNW52ZhpsHt7jXLFahVrVsxxCdXCjNdikrmZ5cxI+w4WROZhdmrn886zlmhEk2HMSo2+hn2OB0siczLLLTsxGZYu4lJ/O/gwLI/MYlY7Jfk/sBLFqhRrEDZgeacPzlpvo42NywcYFxxPXHrOthi9vcypmKWYWzF/xQLJTGZ8Px0m4vj71iKE2dd3YVFKXAyZixl/b1oKmcWMv7s9S+T0Oo5UaslT+l5A5mTGjxlKlFqqlPZqRP/6dVp8HqxZ2Ie7Yj0wp+XLbjUCyNDeh/xdGGRBioUoFqZYhGJRZE5mBeUbDFgcmYtZ9+DbMmBpwt6+51QLLFfkXBTRaR2skMxiNv6//7oJVi5yPvrQDZ1gdSLuvGNrl8FayExmoz+clQxzXOad8/yq9M0wfzI3sz1p1S2wcDKe077PGBZDxsaTnSPQmIk4+5vysJTLRN8nv/oHLEvUGfvizZNhhSLuwmPfjYeVk/Gxbpgz0h9WLeLm7DW+gjWi7+jDnOjZ2Mc5up/rX5lxq9f+3RRmryswlzC+f/eQOZnxd1kG+bREI4zl3Go83l4LLEKxKMViyFzM7HulYSlkJrOtrwzpDMsk8zB7eOjQH2FFIs5+9h9WTuZkxvtXTWYx23G38xZYo7Dh/311Ecy43Ks99g102q+Qoe/bxHm/WzF/xQKF8XPDYGH2N5FhoUrOcCVnpGLRZCYzvo9LUCxNyZkh4uzrdbBcJWeREleuxNWQOZnZz67CGsgsZu9/2Xk7rI3Mxfuw/VID5nLROs1s0PPDe5y16UYIGfr+kTGxfb2FhQmz5w8WQeZm9vyY8EhYgojj78xJEmbPOyyVzGRmjxksi8xiZj93BisQtZz/yO5YWIWIe31vVN5ZG2fUsfbK6W/Vmc4rYM1kFrOuK/L7whxXeMf1vzhpFMxNxuMa0wa+AAsWdmSAX2dYpMjZvGlb3VlLMeLIMGbb+XvWyRIUS1IsVbF0Yfb6AMtkdZK1zxEsj8zJzN6ewYp8WrJRxtrbQdcnu3448gCsgszN7L0tHS+ENZC5mK0J/nA/zLiS6mSWH3DBVzBLGHu+2AggwxxVGMHGwrczf4CFCTtzS8fvYTHCtsY9UQ1LIjOZfbjmoWRYhrArH9ix6aw9YeSSoe87jfD29xPBSoXNXrxrKKxW2JPOqAdhrWQms/ZvGOLY9KpzcZ8Ys9h7+ek7OMx20Rh2O3LFFbBIYSPP9HoPlkhmMvv2ySdmnLUkI50M81dpxBqrRt9XDssjs5hdManxQlgJmcksalDJj7BKYfZz87A6xZq5ie/Z+Ll9m4uM92HW5aerz9p4I5jFfUrHL1t3j9hz1mYaEWRY5ncb49u3kbAoMuc5Y99c723EkWFc9tD/e9/GJTthqWQuZlNS3AdhOcJO7uj0O6yYzGTW+tr7/rAKYfa3NmC1ZB6e8+mCDrA20d6M1qGfw1xX+84ZSOYrZxSZgxl/N30MGdqrov931dSF/f65NsNy7qXzd0/JwH3/7MOZ7aN9o/3uFKybZWSYh8+oDat14YuwKjIPs0MLn54DayazmKXvX7Ue5riG+s6s4ETcPphbWPs7FHEsTIb+VdN6Nc6ZEvXPvoPZfmOCMXrkx+dhW5dAhjE7QG3wby4ksbiD9v87cdYziMticTXiXYg5iuUJs9uDFbD2yFiddCxMhm3IITpuPfHqgROwemFzYzL/OS4wrj2X83NjEvt2yUTDTYb5O2xMad8=
*/