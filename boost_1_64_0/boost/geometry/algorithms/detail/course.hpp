// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

#include <boost/geometry/algorithms/detail/azimuth.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/// Calculate course (bearing) between two points.
///
/// NOTE: left for convenience and temporary backward compatibility
template <typename ReturnType, typename Point1, typename Point2>
inline ReturnType course(Point1 const& p1, Point2 const& p2)
{
    return azimuth<ReturnType>(p1, p2);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

/* course.hpp
s+88PuKMgq0/lstixcNp4HV1llfTHni9eo3qJ1ooXKf6ibWg0Sr0YcE8Pe+px+FYp0LadpF2kU6Lsan2ZdYj7Qbl+/AarMLfCPxO4HO7FGvTvy2VdabmXwjeAxqbpFyAp99sPxO4Jk7PB03z12VRtuIQv+tspH+1Kh/RC8U/B/hRUb5idRaoV8apMvXJMoGvMU+tbwC3X9TXBaq+0LZ4PmEMcyIJpN2BtBofsmb8IeAPl+n7t3KvuY4izVieNMiH0ySRJoU0tk3ivQcPYwmEqf2ZfYVjfK44U6bnVQmf3gQaZgMuQPADrXyho1pn9pTleM9tkrTtOaMQ365G1eN5tswFRgZ81+r+Mn6Dy4an+vtTEL4A8d9DGPIEPsICP+Jlz+ieDpm+zsrL3W/0+jKTNs2/O71++/sN9HubGsM9IN5MX4k9X28Usv8jnVfq3Rlv3C5PBUkQ5CP5mib5tPLx+MykgXm4v8LfhObDC8wZUAANP4CTVPt7R6jHlLCp4j6nN5eZPOkoZb+fGPfdFLt702PxKAa32fRFDm6JSLpzvQS5kcnA/ri32LFcMm53CmHv62fMGiPemkPY7Lel5dZROnpJfiHufrpIyHI1yxJjMkhTAvOOhyZZF/aMltRV7Ld4u+pf3kFh2GMRh7vlynL4U4dRBqMDl7Duwy4jL+5HhJ29lOASZ5pcqwDOewmONsFtIHAnHtrfJaKv/aCUBWhfRp+cg72cZeHylfP2V1Dc4oAPOzrCc082PJRIp4fitg3Bp/iI4X9Cn2JotDe24iTrSVBan7/9Rg4+D+DvSoLJusyoO+0+TvGHl7c5+R9f1mgzp7wFrUeKnxctVxDUezHqLqJs3JXqHFJE2LDPCht2g52LSPPvetiw+80bdsqGjYXYsM+JdrcXOptS7YZB0Nf7/w826l8luW3UMTls1Iu0jYKtK3L2iMOl0h7hDPcXhFwiLJeQtpyavD3KK1e0wS+F2KMvK3t0NbdBHUf733PZo8Mog9G7a8qyesfv8eawR98gOOPksEffIrjU59XKHn0V9ugaYY+uk7IA7e8qe3Q9whnfBh12+za2Bc1b2JbiIvOBNvL6AfK6Rtw/1eGPn9wdtmJ9Ij06FjhLEKODt3I/wUh8QMTPw9mVJWiXP2L9s2eh6TaXDFcah8SdbfcTTw/ZT63jwbfcr/xRw+9Py9xncKU/erOoz1rxyT0WtxCOppUGnqR1m6RVyF9AN26XY2PQkp8e397JNh74SifuVnkyDZHnL3POdUO61C6dsDlo28Y5gbnnZMK3N3dZH6qrS4YjpB3+7yavw+GyrznSINectqH+/fe97hP1P+htH6Hp55HARSMClNf2TDKt3Y8uxlT3qnkH6Bd/Byn+AH2yXn4NXfsN0mLvnUlrd2biN8mp2ckC4SIvznGl5q0gj+8rNX1bInhHib1wMZ4UOPXi3JfhqcFz1WfPlFC4yckgRjeyj8n7QlbjrNVK2PzfCpm3mTTbh2iN0ay9QW4CNKHMJ5HWyOoQZBVox2VOvrId/85vb8AJx5vm/YHbkomnD7gG7wFRZxRn6+xPfl8CfGmTH4FNPiRs8p/VnNJjSFODNH9RfD6Ug88nOMx5QQZIA76zvNKeUtHuDUzfV/w3jtd5Yv2Py5qlTX9t/s9QnBxzXqjGoNtU+HsqfGGBCNvsVHiqCEME/px2xlSWvSt6L7//mLF9CPwihGe7dUa+/2pquRj7C7sVtfdGWK3TwNzn/5DeXpOApBzOdWfWYeTp35F1lOV5jO/9KaRwxLN4XM4GL2NWYcX7h7Q8gQx8WBP1r6PR4d6RfVm8V8AONPpvJAr5rM5v123dkJ3mulw1kYzMEt8wU5I=
*/