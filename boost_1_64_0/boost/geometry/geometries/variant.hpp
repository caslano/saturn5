// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP


#include <boost/mpl/front.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry {


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct point_type<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
    : point_type<
        typename boost::mpl::front<
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types
        >::type
    >
{};


} // namespace geometry
} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP

/* variant.hpp
p2pR3wACn7bh0ahR/j0uSWelLXcruMdyY6+J7de9xqfjTspy4WrksJPjTh2CC0XI6+JOOEVQLupgCDFXv8TSwS6Z1qCr5XzqB27bKD/WCzQgLmH3gOaS4LrQ03Bg0e5WXNT/EUx4o4AdMOMTZvgvRxfFo+N5eGtJJ0Fuss/QqohkSEqW2r7Ci2EKyMjW0L54nIPWJYShB6DyxZ23rvnGSqP/r06K1itpqe2PgvvonbyNmPw7W4+XVkL6VLn1VF/7xpADLor1OMnxCxbkyXpGxK0ipETeyd15DOZhCkoUQ5b3cvcZMmBRa1xmYEABccy7INiDuGWD0jwd3vPb0snZ0QJ6YllSHJmGsRaa/YxaV875RyKPc1qdPHHpydstw6yNDsiFUu+F737iGo6a9Z9YokWX9iz1VaOyk/DO/FkD1dJppN9P9mhKvIkWKRJsatRcsAZjHnQ2DkRViA+qMueO3YQrYR0t0kKoho6D8lT2Dll9jqOW+L0cWlNRj95CHr5PwfjDKxuFUegv4MJ3VCY7lmwyDHiPK1aw2Z3bhx7tzo6RhDopHJzmmjV+Lw==
*/