// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP


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
class thomas
    : public side::geographic<strategy::thomas, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::thomas, Spheroid, CalculationType> base_t;

public:
    thomas()
    {}

    explicit thomas(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP

/* side_thomas.hpp
kx8zW/DqbEVBkBV3xYr5Ude7cx0QLpeAlc/3wEt1IS13M71TKncbtm4wexFQcYaHDJYVc/emqi5Q54LWvkty4gRflWel4Jgr8gfMnIg239Pk/EJOZzB8lOJFZ5VJI5IjO67HGscj8dI6J7IsScWyYynWUQk7RJRR7VOEjWKX47Mm9PLXTrPX6L9rn3xaaVcsE6gaZgJVV4JhEWH7pRGVlMahWpHshft7tMFTEq6jKVAQwmrGnH8G4haEJmrE0ipF6eTt6KUKLUEBXqJZteBmssyXbSxnQ5l097OTQjlqVkt7ItJrofIxxtmhS2L81EGxOPRFhiSYdDQTCqgRsuJCqvT3MGV76xKkCO//wR9VivYN/TToOLfZxx0+EGo3DkoXJ+goomZyMmwhzdtGMVt9LrgJadW9Y5wnRobsEpLncqCWfGy2fH7rqO0Fve90/paLN9HJkflFJlZh0W6lGqsLP3MoY714zPRKsTSM2DSmuLAyp5JZcgcBsdwK05xlHDx9rDAKtRxrfV1nGUkuiyQjkLx8QEDQE0YPpZrz5SU5REpteisoYsuIilDXC6ujn3+Cha6PezLvbxWoJ+zDXtOHehRqWu1TP9OoaH1vpuaqot18RZ4DvKkTasJ/C44D4uynGzlVE/qCzmw7Gc1l
*/