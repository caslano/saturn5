// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP
#define BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

#include <boost/geometry/core/closure.hpp>


namespace boost { namespace geometry
{


template<closure_selector Closure>
struct closure_as_bool
{};


template<>
struct closure_as_bool<closed>
{
    static const bool value = true;
};


template<>
struct closure_as_bool<open>
{
    static const bool value = false;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

/* closure_as_bool.hpp
gCKk29qx17OzZkzeZS/ancICQwxG+GB7EX6hF/Thh1lj3VMBSX06CVfTheSf2Hn0m3GUoCgxLZ7nLEVHDl1v6skmsT4Y+pNL5At/tcdPcmqkRoG6IyHBGcP/h2N50m32p+PFWflFsgpwIz/7AjALKY6GvqEJ6UXT8rtePzlZu1iysH4hn5ptfKaFdfQVlmrcAZHlgAIDoFq4lKn4yE2aAWxDio6ywMbV4LdVb5Cvp/wKfazvVJFRaiBKHcCU4jerohPMveSsykH3r+OLS0morEmc8MQH+VBdB4747I+/bcd/3y1mPd/3BgbkGqvRA1a1BChzn2jT1tCrMGe/J3tp3YhkPlUBuHZatwYkkCqsRlk1k8ibjoeldkQTx6NledgXi7QVac0kTT/FEVlZMzX2tYTGJentdjXb5rdwDKcSAn84Rq8zDefUbKmdHlEYrgbwcS4Lr3GclbPC/U3nn6OiBwrnxklxLBrKLxazLRTMChgdogwOp82iMbVzJ6NxLiK2fgLfik0C9ZGMQ+7Uqi653mySiL6EGBhr+kkJCToV4vXKtDfJidtm3O7bDoXhEiis48y2rrh3h3FAXquG6Xo1aL7v/NgdD3vv+51TMqjq5/DRRe+i61enoYfPhu/H/XN5RQD0e36M7yKaz7Wd
*/