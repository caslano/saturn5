// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/algorithms/detail/intersection/interface.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Box1, typename Box2, bool Reverse
>
struct intersection
    <
        Box1, Box2,
        box_tag, box_tag,
        Reverse
    > : public detail::intersection::intersection_box_box
            <
                0, geometry::dimension<Box1>::value
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP

/* box_box.hpp
ZMEk7ERcK4Ci6LQ/SSWzB+fUDbgTGTNcNaRAm9W5VtZZ4IkBmrMWLvJwLGJhoAU9ujQYtQyjKw2VLMIJ5ZHSvpMIzW4ZBGxjwFLOOWc7lnzoECy/nrOS4DZ4PutXKyZJG9cqWM3rxFPiF+/e+aKacmch838pnlda7SZQ3d9zee85PgEwWsC0DzGVR4j9U/St4J8CCR0g0LNIrekD+teAIPCtpRr2uPUrqtpjw8vCbnIEqVOeWdRJnCH61RnaHa8SrzpyGZXeUGptvjv/QbFE7mjcFdw6dLe8WPtuWpF6PU0ntowj2mfRhqQN+yRMLHWgwOHC9+j6xmbmVAvpK4haBL4wq8Qpsk2GI/A4whRkYpt2cHAr3rM5rJgMZxdR3OXB7Eya4i1u/YR8t7D0IgzCzpUnJftF1FTc+xnLof3hVRgEJkhd7XGY4ughl+SCCrp/g95/igdyt/+uhvqkYFOwnxwmelKQ1VyEsmeGwgrGjic+jkqL7ks7uq8XCFwrkF8Wp98Ai4DQ233EGoTm3MyDNMkYTF2BZOprArUmu+LLm7QMgUShNfaFfz55EQ==
*/