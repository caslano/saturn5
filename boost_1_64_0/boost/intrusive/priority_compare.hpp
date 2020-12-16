/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP
#define BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

template<class U>
void priority_order();

/// @endcond

template <class T = void>
struct priority_compare
{
   //Compatibility with std::binary_function
   typedef T      first_argument_type;
   typedef T      second_argument_type;
   typedef bool   result_type;

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T &val, const T &val2) const
   {
      return priority_order(val, val2);
   }
};

template <>
struct priority_compare<void>
{
   template<class T, class U>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T &t, const U &u) const
   {
      return priority_order(t, u);
   }
};

/// @cond

template<class PrioComp, class T>
struct get_prio_comp
{
   typedef PrioComp type;
};


template<class T>
struct get_prio_comp<void, T>
{
   typedef ::boost::intrusive::priority_compare<T> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP

/* priority_compare.hpp
jXh8Lnqo8i/x2Ie7ANU+of5eFtZX7mArlW4YKXqU6D3gAdgbvgzj4CGYLeZzVT8KF6p+FC6Fr8M8+Dbcotov3KbqCtwD34cqbsfgcVXPYbH4d+Vn3DVGOu6yyc9mPkb9ai7towWsodomDIKtYDiMhKq9tpd20QGq8omGGbAzzBJ/Kuyu8E7RXc/HQX2MeMy2eT5+1MuIxzaorvs4DBO9vuiNVL2DHVV5w+6qnGGMKl84UJUPTBbzVFXPoIrfHpityh3eIrpZ3yReTmf5/HkGd16qvKG/Km+o7J+DjVW5w+tUeuAo+Bocreq7XO8l+Ijqv9X9Ch6Ev8LDkIvi3vJesJ/0izbvHTZL/jwk6X5Y/BUgceLvNfFXC8kXf/2dhr+BsAYcBJvDRKdRTwfDzjBWnufj4CSxnwyHw1w4Ai6H8XCDmD8Ob4BPi/u9cCR8XswPi7lrfB3X34jnYJvx9YZAI54bob9KF9T7W8MGcDu8TKUbqnx/BLYQ85ZwC2yv6gscJOau+02hXHeUzf3mG+lPvoURsAQ2U/229Cc/wjbwB5ggugp3ohpbDDDC7Sj3/9Y6vbKnpdSTTjBKj9WM+a1uMBb2kvrSG46B18DJqrzgIlVO8A6VV3CFKh+Yr/IfFqp8hqqfvQ6qfE+C/4BjYAkcK/UjDfoQp0kwEGbAOjATtoIzYE84Ew6Ct8ARcLaKF5wn467b4d3wDlWf4XK4Dd6p4gHz4LPwbngYroTvwLUqXuK/xKnzQ89vFkAvL+5HsAqcDBvDdNgSToHttL08J+GneJDOb30GxX5pG5GS33WrGPUnHAbA+rAWvBEGwxYwEraE/WErOFSVGbxW3A1X4UF1/2sHb1HlCFV5dIC3q7KGm1W5wm2qXOET4l+VS1eoyuVKWAR7wBPwavgFjIFOp2FfCybCMKf2r9/v9IMN4UDYXcyvgDwr63KKhaPhEHiT2CfBODgZJsDbJNyl2l7qK1IUa+TfBmkH/qq+SjtYKP3EWukf1sFouN5p1NsHoHK7RZ4PHocr4RNwtQoT3i+6ut4epGCIcb2/SXmFINsd0j68jXLqAOupfJXnv96wqcpf2ELlL+yq8hVeBbvDGJW/MB5eJc93PeCNoic4yW9l7jT0JaIvc2p/+vmhl7eux/p6j8OecIfoKv45Kr+GlX6fG4iku747CjTGH7thKNwL28J9sIO6TwTKcxfsBp+DvdV9Aar4vgKnw4NwATwM7xb3rueLvDjj+jnO8s8XzOXkesO3YVX4DvQXPUj0cMi7NF2OH8LB+rt7o75/Jfepr+EUeBrOUP0gnC3uboM/w3tgA/LlPhgJ18PzXsbzsRNdlakX3A295fnYR56PA+CHsDo8DRup8nUa4ai0BMvzb215/g2Bqr43k+fe5nAEbCHl2QpOEf83w8vhTNF/kPPuMvR5/LQlybdGKj6Sbxt9jP5+k4xzHoB11H0V1hO9geit1P0Gtlb1HnaCW2FfdZ+Bw1R9hqoePibPB0UwCT4p46KdcC7cBdeoegO3iL1qI8/DA6o+wHdVfYAn4SH4m6oXsLrTsG/sNMJvAnfDSLhHxUvMo+FrUOXfEdhLzH9wQIec167Clvqs9wGX+jxOnrtSYSAcD2vCObAWnADrw4lQ5WcabCr2zeBkeS5Lh5FirtrDVKjq/zSon/1gIrwZZsBMuFTsVf2aBXfA2XCXhKP60yx5bs2GB8Vc0iXniZPXNun63dsoby8pX294GfSFKn5VYEdVR6R8q0r5+sH+sBocCAOgind1mAxrSvnWgrkwGN4Ga8OFMBQuh3XgSgk/H4ZJPagPt4n5E7AefFJ0la6lSImkK1fSVUOlW9I1TN4vXAsD4Agpn3g=
*/