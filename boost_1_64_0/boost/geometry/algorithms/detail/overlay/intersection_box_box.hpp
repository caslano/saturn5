// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct intersection_box_box
{
    template
    <
        typename Box1, typename Box2,
        typename RobustPolicy,
        typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const& box1,
            Box2 const& box2,
            RobustPolicy const& robust_policy,
            BoxOut& box_out,
            Strategy const& strategy)
    {
        typedef typename coordinate_type<BoxOut>::type ct;

        ct max1 = get<max_corner, Dimension>(box1);
        ct min2 = get<min_corner, Dimension>(box2);

        if (max1 < min2)
        {
            return false;
        }

        ct max2 = get<max_corner, Dimension>(box2);
        ct min1 = get<min_corner, Dimension>(box1);

        if (max2 < min1)
        {
            return false;
        }

        // Set dimensions of output coordinate
        set<min_corner, Dimension>(box_out, min1 < min2 ? min2 : min1);
        set<max_corner, Dimension>(box_out, max1 > max2 ? max2 : max1);
        
        return intersection_box_box<Dimension + 1, DimensionCount>
               ::apply(box1, box2, robust_policy, box_out, strategy);
    }
};

template <std::size_t DimensionCount>
struct intersection_box_box<DimensionCount, DimensionCount>
{
    template
    <
        typename Box1, typename Box2,
        typename RobustPolicy,
        typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const&, Box2 const&,
            RobustPolicy const&, BoxOut&, Strategy const&)
    {
        return true;
    }
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP

/* intersection_box_box.hpp
9kmFqv1km36t0hexKpNBhrXmvQBD0QztUHMMPLiDmLlg6JrlJr02RKlS/uobaVXKLCO6XbMgkyEZmRQt+7PpDzPT98v05w9kvxE36Tfc9Dtd5T2K2ZZokhhWZN9pyJwFUiUwnNuVuvpO00ZKOSIHBE3UTAXTnukSPrHQ+CUCwk90GtPxRQSfijd2HMDxvrNzMDHc2RjPwuuORhxKe5i9MVtOJ5ycTt+emq6ya0ahtpAxNbOLU/0bGtsJbTzNERprdEqlJFY5Fi9l7A/aUrFzagYh9kmI/Sdi+MUt3Lmstab2oTWnJ2eM+9rUFDIwCVjWpmqyCG/RCkQYE9dQI4HJTA561/rgxazIZOR5fjf9YIm6L3Br5BENPu1F3gZ8XIXcIE0KtQNNN8ilEutko4GlkilSjIBV8SWg6BiP6/1ZT5Ft8HUmfxGSn4yD/OS8mvb3PSMx41SiTjFrzcfxcnBLz0SgEuArWKVd05d5xNh2dTwgN9Gv5dpsZXBxrCOtzyVbQEARxVzGBJcxRcQX2BURf3y5FK5xvUwS7v9xgvP//47pJ+23ZcoXOUiM75YliaRnE1mZN2GJBx1WsiWl9B9kUlrPoE9APEZqJ/QHm1IzcAJQKAHWeotcvc62cjSM2arG1ue2ckUw1Ar9olKe/eWlcoWechlW6E+2wJ+rMVbmEcY4Gatdzt/nW6V8m4lMApigL0uJ4/4jDmRAj1mIHldOqsxkLpuE3CjG21CtWc4nx2dPx8ccn0CwOOLk+OCcJsX9CDdDmrfCxzdhcwqva3QwTRsNQq5lGH5cJ09t77Icxfpan8FrOnOLaoniLZlqEvchBNupepRSk1ieSoRgr5iQ5wULOKBR9E9bdIFopUNU2j3hK4dLFn5Sl6Fc8p5oyKU0IFcQULbFSrXhrpFKteEpJo2sPt0s5/rMC5acY5QU07Ao02pHSDH1+nxT/2Aay9qwWS44j1PFAG6pYvCwgt2jCsmyMOQKBY2wNyq7tU3NF4wvSM9gsamagbo6qlAbs71U2X86QilOekiiIcEKxDnyHM7JvugEnDp73Tk4k55xSnpGkJQ7/p99Lf4/7Ff2X65f61zVOHTT/jZ9aENvACgPTV1YQmp7IUQF9Qt5FGHTGckpq89n5pRVN1GSvPLScP2ZYgsdT7fDwYvclfrSXnh3ArKukr4R78LHrYGIHCzeO32Ryct8kaqwJwJiBeTScIccCwkLZrNZAzzRcd/EjHX2RXLGugovw93KPcWWADeILNJX4Ob4bsZbtJ5zn40HjygdUZ+LufEJddqD38QJtPJz7iWsbrUcVlX3GmtblS7OEzmgyIokNOuZPFJqp/8SXp7o+UbsBKsZ+GYz8BIG7qsCv5ErA1+tAn8SezuZ8gIz8MUMXKAC98tlE5VaZJQrGYWVHv0yYnbGHk7GLDNjFjEmA8fn1sZ+jnIHLyX9frpe/45iXn5uqmyV2yajVUbhcE0Vt0zvZlvIrK+KfC72eraZ4nMtKsVt2UhxoCrLS6rgDS2y4O/FS2XIp82QDyAktErWFKiyPsxQmNmGI2JDHiVUs2ZCeni3Q8P3Ok5S1H0JcNvGLvd5IC8b5V38cvAEj/idhYFCzblerUPCPeJpA7WBt9Sh0ldnS1mkt7Vsh6fkgAcplYsWr9ZV0oh6gLESuRIMEK1Zh06L1qSLQ1pzx34EBe9HtHTQ1OmYsh00qIU9zICO/UgWjutwOkVtUebkQztHLzmAli51/qZrXPTsw8iOuTvrVjJjkvxRMlZx4DF6docx/B3gUR0LfQ6naVhnrp+gZCKrLpTt/fkpaO+nNiRD+cTkhWYKKJPxOhQSYBM1/yKEgkjC1Hdp+th5w+IshIE=
*/