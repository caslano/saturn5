// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class vincenty
    : public side::geographic<strategy::vincenty, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::vincenty, Spheroid, CalculationType> base_t;

public:
    vincenty()
    {}

    explicit vincenty(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP

/* side_vincenty.hpp
Yej1CnGQikX3tDpW1Ed1oimNjDYyhaa35Rp0LaashVrxkSnymfDERgAwuyk4nUKGlZLqB/EkuaBe68Jxck5WJaiM1a2/dHyEY5E3mdk2xdRBHzvIpCHd32bcYsTIbyLdNxM/MyYknrKoQUexei2uMXhVhS5L4Qw8SYpwAEPMh2oZGB0u4mt0qUcwP9fRMbwuXjwXA50ZRF/3WHglK6yfKRc+nAyZgkxyeeqg9FOvfmZNPiJLk1LTcbwujyea/ozr41j5GZxW3k7PR11Z5vv/gcXOItK8irxAXnJnNnS8keH4Ta9Cz9xKbhiY+ZSwybaZqnGru8aNs/BPchJRt5kJDitaO83oqWWJ7ElUqC4vuin+FK+Ly94TrxpQbMDw0YSUMCVRry4IDNduf8BCOTrTk2/b+/yPoOPXarGJ6gfpCpuYvjVlhwfzUM+Y7NYJe/XIhYcX1GR3UfaMjWgsT2nazcMw+uJ5O/mAXgCSDQxLh79PXlgV675sO6Tc0M8d/tK5C6F7T96amaQykX+2q88IJlpdeV2BTy1b/rbw78W0ebZdgXFvz7rGmTtYdZin9ugmU185dHFT1sULPhO2euSov4ASSZjuZdr2JLG/M+SjneKknZR66PWFEFi6qswmYNb009Uld+FUlr+yyxaD
*/