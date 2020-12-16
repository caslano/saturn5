/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/detail/assert.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class F, class ValueTraits, algo_types AlgoType, bool IsConst = true>
struct node_cloner
   //Use public inheritance to avoid MSVC bugs with closures
   :  public ebo_functor_holder<F>
{
   typedef ValueTraits                                      value_traits;
   typedef typename value_traits::node_traits               node_traits;
   typedef typename node_traits::node_ptr                   node_ptr;
   typedef ebo_functor_holder<F>                            base_t;
   typedef typename get_algo< AlgoType
                            , node_traits>::type            node_algorithms;
   static const bool safemode_or_autounlink =
      is_safe_autounlink<value_traits::link_mode>::value;
   typedef typename value_traits::value_type                value_type;
   typedef typename value_traits::pointer                   pointer;
   typedef typename value_traits::const_pointer             const_pointer;
   typedef typename node_traits::node                       node;
   typedef typename value_traits::const_node_ptr            const_node_ptr;
   typedef typename pointer_traits<pointer>::reference      reference;
   typedef typename pointer_traits
      <const_pointer>::reference                            const_reference;
   typedef typename if_c<IsConst, const_reference, reference>::type reference_type;

   node_cloner(F f, const ValueTraits *traits)
      :  base_t(f), traits_(traits)
   {}

   // tree-based containers use this method, which is proxy-reference friendly
   BOOST_INTRUSIVE_FORCEINLINE node_ptr operator()(const node_ptr & p)
   {
      reference_type v = *traits_->to_value_ptr(p);
      node_ptr n = traits_->to_node_ptr(*base_t::get()(v));
      //Cloned node must be in default mode if the linking mode requires it
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(n));
      return n;
   }

   const ValueTraits * const traits_;
};

template<class F, class ValueTraits, algo_types AlgoType>
struct node_disposer
   //Use public inheritance to avoid MSVC bugs with closures
   :  public ebo_functor_holder<F>
{
   typedef ValueTraits                          value_traits;
   typedef typename value_traits::node_traits   node_traits;
   typedef typename node_traits::node_ptr       node_ptr;
   typedef ebo_functor_holder<F>                base_t;
   typedef typename get_algo< AlgoType
                            , node_traits>::type   node_algorithms;
   static const bool safemode_or_autounlink =
      is_safe_autounlink<value_traits::link_mode>::value;

   node_disposer(F f, const ValueTraits *cont)
      :  base_t(f), traits_(cont)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void operator()(const node_ptr & p)
   {
      if(safemode_or_autounlink)
         node_algorithms::init(p);
      base_t::get()(traits_->to_value_ptr(p));
   }
   const ValueTraits * const traits_;
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP

/* node_cloner_disposer.hpp
YnwJ3i4JMaSn6Uq5nLI55U/XsrWqviG4XB3xt7DOV6rfHa/f/KBcMzER7IdkfMcOHGvRdmn23Yld/Qp2kYkucDOck0H4mIDrQof6pfNvcEy9/5iw68BUJ884jp384oVzi4uKiovMmQT1bekukY/ztvU8q2HsdGGF4WfPMv846DfffjtZwm6U79GjpV1KNp3+eJAcv9O7kStqGy14mZd2oXtcfCnHkv3XALqGiv9B+a78lNzTdRKD5k3aDHJJjr1+f9bNvRXGiI7rvdWebzWMUU0J+5AevL+MNbeTkxdQbOe+c4nItkTOX+ZV4n/Hcxz1ejrlln1NyMPlEj7WywxM855Qsrii0vneXysyS+XaW067W039nMCBhPiqgGvP7LMv4kR2QiZbnx1uNvbjSvRGNg4o/bfL/AO+H0v9UbeEB9at2S4P9hC9fFHn24ryOnTlj3PaJdNSllQWO4sTzb16ZCGq0//e74/jvdnTzrVdojP8uIm26yuQQcK1/zbj53Ugvjk+oHMSHhGZZc6chJbj9Z6rfc0P5PhYnld8Tn9zWMJaur6nmGn+3XwnMp6B1onMGu/9aHR5d3F0yBiKDx3m93xj7sPjIrfEyXuG5D3e6SfPF3+Ssxb0epE/2XUfSzPfd9tj/BdyDw8a5z8/TcdZGKIwr607Jf4q752eRGNfG/I7r3K+vKNrHqdLnp7kLpfL81eGnsf6Ok0NGsuR6UXGM9F6kTvBf6/t4Jcz5xu8LscneTM82Xqt2bpHslZjNjrEboWMt6+lktYk+6+lPin1Yzc/JOw2eBL+E3XsvXeKn53xIyvXXEITxt7Jg/u+GHpNuL/L1I/F0H7NsRjnXZA2Zo7dyHWcDGk3buNAch7vljT0/AZ9uxrdyyN/X+g6s7dwdyBfc7Ze37IHgDyGOc8bXuN5w342el7kf4u9mPbYCE50u75Vp1efm2w9Ou+EuvuVHP+Dc908Lf6XsVW6wvV6V32uz+mfy7FLsQKRIvn2pTrPSUzWGyD63tdnjrQMOVZSZFyzcROIj77JnlQNIyUJO98Tq/tnxUu8kgpz/fRgkWmjfnog8UeJnZdDPWiDPfWZyzs9ISY6wZvDY4rbM0qqym9BPt2Sb1WQEB3rCbt3yzUk/lPcF4R3SbX3Soqsvdr3COvcppjPkuYzvp4rZKXefKmEGfVptqmEk/0JTdE+cjJuAd8p6iaYbUrfP/W9z2u899nn4B2RH+/Jct/nEX3anpx32MD31w/l+JmeU93fPYkfvv18IseGMzfFF/ye5+zfdlBkhsl73iBPdIPvdr6J9e9247nmVve23+0S3d7tRGZTb/vdrlPIeTfeU11s8Lh/U7DqOcWoZz2/+m5nhQXe+7f21b5BykHauLuseYkT9TzKtJKgZyfqYLr0ERLg1OdcifO6Z5m7DRp0hpwL5znsPTl2nnPvmedPn29lMW73Hqf9FInclXw58DnvVp9L2DTXPaI+kGMziW8f42a0pFTU2/MdnhOZVSIztJ1xrs05dyJzsu7PzBur+H/niSXsItrAdbSrhuJ/I/LIaHx/nicRf7h8v0jk+trbR58ffW0SvC2lKxnAv+7vOxrHw/nMkL6ka0h76qgymX1Vr7f6poSYFgmxIz0N6sxxdFbf576vrHw3VbtRcu/V76iRv0dNl35J2pPsJ9l5kn/d5OHOge01p78/8mKdV3Yx7n7irp1kt9eSioolfPmqYDZQQWkeuyg7/bhX+3H72r5Z4pR68qxRDff+B70u9zOjzd8px2d5znHtf5z4Rr/hz5/Zhp8VmeHMlYuWPb9qqe+d/bRfiM1w32tb5Q720z4mLsnoYwLvG0/pd6HbcZe3a/y7tn1O4uU=
*/