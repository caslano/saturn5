/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    forward.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FORWARD_H
#define BOOST_HOF_GUARD_FORWARD_H

#include <utility>

namespace boost { namespace hof {

// contexpr-friendly forwarding

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{ return static_cast<T&&>(t); }


template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
  static_assert(!std::is_lvalue_reference<T>::value, "T must not be an lvalue reference type");
  return static_cast<T&&>(t);
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined(_MSC_VER)
#define BOOST_HOF_FORWARD(...) boost::hof::forward<__VA_ARGS__>
#else
#define BOOST_HOF_FORWARD(...) static_cast<__VA_ARGS__ &&>
#endif

}} // namespace boost::hof

#endif

/* forward.hpp
iEej+ARSFr89OwMhpQpVFzV1Val0/+HGEKxeq5KyUtLZShnZcrZifPS6N8N9YY+4RHvqK4uC2tJjA0qi9qpUVJAdnt+2GPBQdw38OXo6U/MrzticT7MszaJ/Sy/Z1QHp/DxZHhBPbrI5/zzN2Cxd7CkGGZ8tLtJvKvh5kid72mnCVpzl2f+Z2Kckmx5WXd/M89lh1a/z2S8H4+sV1+xyf5MJy0d//efyqU0h6t9xy/0HyjhuqFM1FJWw/aV1RPcPnUa+KwFfd2WJ9vjo2QlojghE34FTf+Dxh13ZrsVGNVSQ0MOkoh4U2lETQCkKT50oOwznJPCQgLq0MBJp0vdU2P6+6HtlaIvr5CufpIvPfPp1mSzCZnexvx32QIQTOiASqeEeqOvhJr84fTdgoKYLYfQ3UEsDBAoAAAAIAC1nSlKtFAa6NAIAAHsEAAAbAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvUkVBRE1FVVQFAAG2SCRghVLBbtpAEL3vV0xzSSsRkNpb1QuipK1aBAqpcgiRtdgDHmW96+6sQ5Hy8Z1ZbJFTMcJer/e9efPeAFy6ivwv5JKnuXC2KF7h9BPMRp7/B0zgDHgtPsAlwCu8z4Cir/BF18UFVRtVpbeJ4jaFLmXHmNV09nP6bb42
*/