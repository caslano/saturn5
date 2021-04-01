// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP


#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename T>
struct bare_type
{
    typedef typename boost::remove_const
        <
            typename boost::remove_pointer
                <
                    typename boost::remove_reference
                        <
                            T
                        >::type
                >::type
        >::type type;
};


} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP

/* bare_type.hpp
rhp08RouiHUdxKOIdDg2C40Xl0LmN9EEu9Z6K9Bdgknhp0As6sDtl/dCwq32vZJXdwuy8Drj1V0tCx1oHKkr/aB+6TvAd5NSIigWrSTbSGyQomM67YPhftx7PXzAO5A9aD31f27nbBq+n2LV2jTTt8IFZwrHNBlMBjXISnEwJr/zgLFJ0dzK7nD/elZxeIPjciSiimsZ39k+Wb3Ihs8dapZa8fQAM4wyZ3VPouKUFut6Q6o5n6JA5CeKbjwHGyJSO0rHpH1ykM3jXNSgxgg87DwUx0FiNChkR8KiGgMfZzX/wrwIbe7fG4L7C3dNxf3pOAtZBLP8UT+DQDiR73QqDLVBxNaMC9x/GaVrhkOB9jhLVvE7+WLkpo6VhYy9Ls/jsRm1AjrJvyVlaPPV8lddgc4OflHcw9BrgiytviP+EmORyudbCXgmkmr8o9b6tmzFQs26HVWYcu8HyrwTODcyh/1u7WDhcT12gxoPH/5t8RNU5t4W+dJGftyaVg5pZ0gwCe6CTYNruI9f8gxlbqhp/iMRfYs+foXY1zTzg2syLnazmCLRVt1cyBqmJA==
*/