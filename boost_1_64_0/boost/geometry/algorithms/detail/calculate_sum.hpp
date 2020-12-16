// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP

#include <boost/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


class calculate_polygon_sum
{
    template <typename ReturnType, typename Policy, typename Rings, typename Strategy>
    static inline ReturnType sum_interior_rings(Rings const& rings, Strategy const& strategy)
    {
        ReturnType sum = ReturnType(0);
        for (typename boost::range_iterator<Rings const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }

public :
    template <typename ReturnType, typename Policy, typename Polygon, typename Strategy>
    static inline ReturnType apply(Polygon const& poly, Strategy const& strategy)
    {
        return Policy::apply(exterior_ring(poly), strategy)
            + sum_interior_rings<ReturnType, Policy>(interior_rings(poly), strategy)
            ;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP

/* calculate_sum.hpp
Za7FRD3b4vpjm7OEhTldkq2vZyQ50m20zus2AcyskvA58JKYkNPZqNwgKwEoCzkPkOzVeuI9K7z+lIln5doT3pVYgjHTeJF+TKRvcs4zMxrM81xYN3R0rSu7V9CCHNYMGWb+Otg4htG5RKzbjce63U4xn0tb2zEr23FO16zbaahbtzuX0vbrpqfrJtsI9RdwqruB+hKyrtTquoIzk7O57sq3AZ1/lLBDPJ7qeMV/13qS0OVCZ3PosPiKlLAC56CKqJORbfcOtP1NY95JXV9X38yna6IiuE5PiRV1707QTFuWEXC03bsW5GfaY3NOgvZs1hENL0tFwMFv91hR91mpU+UQMjqS814WK9ynDq40zviCaiDzqijEawd8mN2rAV63o/+xs7VNg+lemfPbr60RfZBtEX2Q6yL6ILsQz+0ezErcd3GzgaV6soNuPZjh37fwPj/GwnMEv5Pg6JYw7G4D25DL9KyPez7sXgPbBCDx9eE/NfCRjMkctw8PeRnXF0Lf6Feib/Qekvsp3Hnc3ddDl2s6+G4Ef8H0e6jX5PuDv3o0JB8J7r8uJZw3vZE+zpfRa0l6oG/+oYce1k1nlOF/Kgk+OYBnKG3uE5WWhPtE1YQ7u4QKUN5DXuL6P+ascLW5P1L6lhJb7NIE4EtcWbs9/lRUXCZRZze5HeP1hhqRRukOjAfnhO/ETGaXxAeS6bg4h0mwuoHQPOp0mdYYfbMO5p9vPcWsGMCGgYd3HPl9yph6n3IZ2r/3CjlqiaYvs7DbrMZ0E3VoBBQdhXFQ9F3rt5T59dbjO+jlGMCuf0JOOs9u5Jm4V6y48+y8HhALrwfUWnrc+Qpd7y117fyI6zhIEwJIn5ucr96KnBlzYYLrt+EIt/Cc8r5Ea89ZlgVryS3uN/OYHQvOS7yPfh9UEeYxJ+bWUC4uD8ZaB8DXQWameX/MyXxgDHNQkHEiz33ne4twkjcXss5X75rMc/JRWOphvDc/hrk/pKHn/j5A8eE7CXsTWRpByTt0qI5aTyPu1LHhJtTPQ2VfjfZndPnPA9JPeZ3E6JgCbf674GP3vkDner14EcH1evHhQjeUL8IJ6+ZICoMP8eA5QuAFfI6Oyf0bDu/Z8qjyox1khCtk43k8LVs94R1VeH0rk9rQ0+frREFZH42x8HnnJltWFsnT82Jy7Tcm2lrfDy+VPikkRyJKjIT2w3u4t25zvVjjFvPJgz1DZhElzvfWtEjfsAN5HltnhWU1OjsmNnrfdquyjeWo7zNMTcZ9Vm2xYA2pwH7qrtZ6XwQOc3kdi7SxB5zO9QT1eqvwDyn6OqRMpMXOwLaIDvZHH9GFbGsl4Z0k3wp0cwBecO9OOp4NtdEp00iLNjpF3j4IU5s2at9fpTfYnyYquX9otfQTY+gCuudzTVL3a+EDj+NyonZAxZ0QE2dewEe+D5oioD6ncCJou0Frfq8KfHjpbPEeeS/gst5TGlxGfTH1Jh14x0F3TYFzWDPUOazjY9iLMWwuOnI4HyRYzMLcLkgfVutg5iF5HiuuM/04wOclHH0PweY6WGJen4MNEGyhg9F/I1nbH8E89XpRdotd2bV3tCxv6WpZ1RjehhcZx/bdJfWGcqE2ifWm/eVJ0NuGaH3zOQCt72HQjRShb6PfyW7/U3yTu0uKdVzKcKNmqXvAoWoDTxj9Mzy4b2rI6J/hwb1TSVsGgEPlTbh/LhUas2NbYxfdAaKUPTpC7gWT/kOfqaBaDp2RvfF5y3lEN8XDeVX0QVL4wKeAD5ri5USfZktZQJMqcEbzFKKJnA9/13ZWUro5FtTVLbABrtsTuN8UyKf2iZ0Wy7N29i7KwsjzYSHPViFPF+SRfgoy0TutSsc=
*/