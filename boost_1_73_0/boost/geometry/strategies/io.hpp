// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP

/* io.hpp
nZyc5flEp+IJrIWKNo015tmdAS/sSL9zL+owOazds14U3TtegvTdTe9/N94kzh85dPAuLu0GY0P2eQZusrf6DDyIlTay/T/qPoJZA1WhOHLoirBXGBL2yo56Pmdc9c4v9i4IOVSmZ3C4mr3Y7XVp3+B40zqwni0Gd0AR45g8j+sSntSw+Hfn+gwl54nhFJGpd6nh/fkoeULZxhTXNTTUZefjKSl8cMfwII6dMK5lmboC7NQU
*/