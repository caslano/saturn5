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
HdJkxQHuQHYhe5HEmVwfGY3kIcuQjcgWJGYFaYZ7LDcrcIPs5+/4WZT5Ctwivfl7HcyBy5A1yAZkC7IV8x3wIyQ+B7fIRKQYWYc0Yb8Zbrf+RvYjSedzLcR3BflrCX/PgNmwGi6Dq+FmpOF8iOxHdqHvRTrNJp5I4kriBEuRDP6ug+uRzcg2ZAZmH8GD43HD34f4ux5uQTpdQH2Gw+FEZAayD739lZQpf4+Ga+AmZCuyE5mD2TuwDh6C7efgH2lAnwjzkGXIemQLshnzHfBVeBDpvQp3SCmyBtmE7ECaEN9V1FNkLFKMrEO2IHuQA0jSatKI5CC1yAZkO9KE+K6mLiBZSB6yDGlAGpFdyF4k6RriisxB6pCNyA5kL9L+WuyQHKQaqUe2IXuR+DXECSlF6pFtSBPiu45rIjOQOqQRaUISryfvkBykDtmI7ET2I+1v4DrIHKQOWY9sQ95BfPXkD5KFlCJrkEZkN+L7Lv6QHKQWaUB2InuRxLXkCzIZqUDWIVuRXcgBpNONxB+ZgdQiDch2pAmJWcc1kclINbIO2YrsQRJvos9Asm/yHfsd+x37Hfsd+x37Hfsd+x37/Z/+YuS7rz8Z+CaOmVNeUbSoqrymsqBI/uT0iUFza0pKCwcNHTx0cMa8QYurMjOGjjJ2tSOHDwqc1jiosqi0KL+qyHaB7ZzqodbRRoPL5zIBYYxvbLL1QXKXrx3vLJ/J9xlOKSmoLK8qn1ed3u/c/unTKqpLykouLlk0P30Ch16XlBZV8u5pcvJ5qbyP1zPpeut61Wt1XcZiZOtxjH/ZUM2a8jN9cu6EGTm5+YWFuYGDKTkuqaq6vMyKDU7NOTR+x/kuMg90v+V/up5XYYfXT8//1bPocuXMMj0/0nbTx5zTGSthFImfgXL+hUSDzxTBc2Sixc13RM821+klfoaIn3mVRUXiyZy769NwLf0c4ydd/ETH2dfJr+R7hONMH3WnZ/BUoFvuM+UaFfmVVXIR4z4jxD15o+EH3XMF4350iPs6X/Dc0bvJnFnNOHPLPt+po5xhEiiPVMxyIHmOmclzc94J+Yq55qu6L4ZDxFzzTs0rIPHHXPNHzWthprg3+SDmdcZ9ML2cOWLq3pxY/tG5Ra2R47Tu1e8PrXt6ImIz6h51Tf23P1xdUze9veuW1iV1E7EunRN0c8S6U7//6OpO/f6jqztO9+S7ngsTrDdZ/0P1hjUP8hsfgMzZik3jud1dbzgjOnKftTIprN7gX/sB0TmFS/QezH9LOlxdUn/j5azTvFjeTRC/HPI9Ma5FwskJfRP6JIyKi0+MTrSue0cnDaMqWM9eFv9jnGffmvr1Gnb2+cesWeZXVlRdHDz/+Fdif5zqft8fRW+l5w+m4OPw5R4PyQtXuSd5lLvzvGf2KpHf4ABkHt7v+aiZ/oXJfzxyV+P4PjkatbyympP1IuZhik/9EuJh4nxWssYv3jt+5qz2A63EvZzX0V35BfHLC8QvWBmsrsXndb6SutUzN2ehrxX9dv9afwvn2XDSLTnOQFZ/Q8RfGf5uEH2D/xY9E3VHsrRhOYDNPvNtTSBe/pHsnq51QsPhnFQt1xcsHftTqCeX+B4x7VzPPMOulHt9tdYb239/cxbx1aLf579Tz16uDvRVTCkM1qXuX1pu4h39loaj/Uq9Xm+9dXPWOpyi99RV4u4B/0biqnHSc+aC57A9IG5W+ev8Ue5znvVe/pDYr/RX+Vs7ziAtryEMcz50ivqLt8zlpK1g+x0j8c827eoa0QPnwabY+799EXDTU8zk46vmbRklVMU581Qe/urqTzTnuWl58yuYm0uSFpNt9llsfeUa7XxpotvltNAuJ0qsr+mLs5M=
*/