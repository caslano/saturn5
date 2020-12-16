// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


struct envelope_point
{
    template <typename Point, typename Box, typename Strategy>
    static inline void apply(Point const& point, Box& mbr, Strategy const& )
    {
        Strategy::apply(point, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point>
struct envelope<Point, point_tag>
    : detail::envelope::envelope_point
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

/* point.hpp
8nB9kz/f+dSH8+c0nyl/4dZejJwh42JYt77vxfxkcq9qMnosA17KPBBTAMdOMUMbnIkE/QNwR65+XwtcylODfzFewokFUUV/DCzg+ju+v4J2wlbUO0PgCpSNPfd60yebqZb4zNurfKzpRt+h2zUfnSyItnXz1SFdWf97aeGXouVUINirK6evNfkyZ2roCd9d2Y0uPsDHAdtrcOqIBr3ko0Ev4TOIPYI6xOgB/QDixQkBf+KaAmO+D/EJ3ohJX3fg4gxENiK/9rfxxUSbMV9gxro31+Gs26CX6w7SG+u+j0/gRlxzN5/A3bjGp5/APb8r9HMr+q5FP4eFwBWon9TVLPe3Nlp96naO7PjiiVoeMDJ4OzSAF3y02A+vlmfYDxcTyKMENI9vQQ8kvi/7IvA2+yLgchEm3GZfBNxmXwQ8aF/Gbi/hNvsi4Lp92QHauwaKug44R6aTgB2BTOMabDKwm4BtN0DBdt5e1t1vhK6/35Xsyr6lLR01ny8ZPsqwTapGK9twbgfjiOA6nHI2fs5GRxSa7O5ocdJXdQ62vacLks5Sf2J29J9DMgcla9kvX7DdncGSxXpy35PNkYhbJ5vm8O1+wQ+/XGVbmXGrXFrBURApj2Knj5YixecSB3Zekb3f4Lu9Zm3vwoWB7sx2R5J8i3S7UBKzrVm3kfBg3caDC2VjLIMvwsD72eLpndcWxdNir3nMU789SDuv5jjfWXN0cOG61dpiqwf9QOmWqTO0CSoW+9yg8SvVaItOtcIb068AFevS5E5fOaFr9h+Y//kneA5MRpMBOoZCXzSZARMCC7YVwvLJAZgQQr+/U8PjaaIjbtrqWaOs38+v84N2ui1bruNSVl7RArjOKyA2GyrgQRt6twsXXLPQ22wrcPwx3LP0E7Std7pwwcV+vsvO4SE1QNuzNgtGBe9G92wPZGvOxUPsjwJ1vzPeaRmj3CqndZosaCdOjsyYCIzdRvLoHCjdB4t3fzn9BP0z/Fc4cX0vePYETtVjAm1EX8H4BLhRw/op6wHu5T/DA/2wTl/sA8wa+wC3xj7AjZrDQ3zCCaf7wvTBKfQHzzBH9VXnzzh1/mAd37Y/BNy2P4ATu8M8G725PyRcMMrSj21/CPi32R8igDL5sb/OD5sfdwMvU0ddDOuZajkPNyw+dJMtdH6r79dbgbfxXsAl7024jccCbuOxgNt4LOB6HPdz+DEHm7EQ/IHu94o7sD0ErJ93ops7SE5KnP9Zz1VWW+VxgpBHdemScElzpDLBpXYNd6KGqwrUHU/RcEtTxF1aXeM0cM5EiM47U0QYvntTZ2h49jzPsWk5WgBHvkUAQtxiaSvilo4olys6YKqWk50HjTi3mTNL8vgC/k7Cz109HkPHz0XAuWGYhs6DXQIs95D/zJKQaHup07Ys0PY3Lh2NBd1lDl2TJserHDnuHoL7DuwaBzZJwL6NbDM22R5ile11nowyhmxvUDhDtrconCHb2zz+Z6yyvUPhDdnerXB+2Zpt88r2Hke2iCfHz3sdvgukTne/I1voTJnNmtuv72l0+I7zkwpn2rhjrXx/gHHCy+rdZrOLtTkcjn1qFbLQ5noQsKDvOwRYd473/Xs2ITDXjDnXX/djrpmS2XMkX/8I/Lfw9fkQfiHUz7vxXfxHntVivqd6lO255IeFntWKBqEgLNPdbMC6BWEQJggLmFvGzF3PtvLlz/SfWwxxdzLd4tPxxySuJdHj4pSOPyFxfL2uve1TCs/2aY7OCuXHzdV8x18VrjPZRR3EGM8c628Sl1mTdsfKj5ur4Z71cG6fBl9gu8IJfXne0Zd/QpNy77MDWw9sqID1Nx7u4j+0kbMXSzx8xShbjekNqQs=
*/