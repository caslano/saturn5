///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE
        T &as_lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        BOOST_FORCEINLINE
        T const &as_lvalue(T const &t)
        {
            return t;
        }
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_lvalue.hpp
oFDUoZXjrsLfQ1ujcBz6/AWQwU5K2SPuhxmG72aa2lnizeymhoaMqdDJlWT5xQ/wA+PvUevATsRfePBWoFMFJAFI9XeIDMEP9ucEG5lUrClOm8j6yLunHOoi+t4fBCatzdLRAel3z1tB4bgDSH1r5C2djIeDRe7yPM2BNuvKz5ItNxwxGXlcu8LnPrkM4gmcscJIm0Ma62kIO0S5m94YqI6OJWFAQgreQ3EBBlDYtfSC/72/4mLCa7JhCrUZ20ub0xcJTonZIrzRa06ocg0wBvVLs35JvKtyb/R6puCCDmedXFoN4YqFuc+3Fa/YV3KILamrHD3U2BmE97Akfm6QuLZK3JRpW67lqcilHH7kkuHvnC5LmcCRYLv4Df0bU3M49Vlp7Zk9eF1AxP0+fyHyS4QcB4Zg8XD7mRzGpQVL3BQpE/5+9R7BsDjEPatCQqGBzNZr273vfB2oYQ+TR5/+rcdpI3lde4sd/NYE9WPVnVibTf+0/zHV6uVYZfpjUkfTNYYdcH2I/nUqS5ODJiDpoHpXdFw7bVZH9S6e2/hekn6kXh+HW+qzJQ2E5w==
*/