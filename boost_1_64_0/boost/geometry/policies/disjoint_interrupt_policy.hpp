// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP

#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


struct disjoint_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections;

    inline disjoint_interrupt_policy()
        : has_intersections(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // If there is any IP in the range, it is NOT disjoint
        if (boost::size(range) > 0)
        {
            has_intersections = true;
            return true;
        }
        return false;
    }
};



}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP

/* disjoint_interrupt_policy.hpp
dpLwu30l2+/StmOZyoNmuNGOxcBYy9/YI2BEpeAtVHyiMXjf3cTv4gmkXye63zN3F23qxYKzY2NNqck0zFPuIWCg63sY9IhDnLxhe9qLDI0a5heTMKONUXsWaZgv3BMw7CxF5DwsLkuLROvyvSZgVpH5cntkzMn5vTYMNIkrI3lm0ZgG+yQcvptGzBjze6t2HD+6lXh51X0m29sAd7QdU++KB5p3Uwm/ljhpUMb/0B396NDB2X0w5on/xL/yHXG9dL/P4c/uNv15P/4cri/QDwfNehwXH2b5gJR5ESCUHxIbKkKGUBkerSMtmQ4q7R/5MMtfRkTXhpHH8ALUNX5wcVTiRlqWMXH3I8IH3xXkzuMRHiRBB7WWZTgsHATgwu06j0d5rAnYwcMZrAue4rp0Ho+EdxpWybFXN2FnQ5RBLWN4uKteHdXntU24e0PsipFgELxCUSdhif6NGCxUKJGfpYAVoKEFeyvGaywKxKcQjwE6+V135LBeCB8zRA48vjmST8DOmLD3aaACiRGz0Y6tBCc9gGPCHkwQq1MjOlHyC2h73hrWd+wnOXLiYHwNaJKDGM9V0ZoFU+fxCF2e0BUsmrAHiihNUO2tdh4vknjb76xV1m9SeLgYkO1qntYOwW5xWDh0uYkL2ODIEQ2r1sNTTNh9cAfyEhH5JUHpu05zXoMSfqzIrjBfPbgobF7PsPWQofBVIzICzGN8JbcEe5bx6sPbORJVkedpGgj2HJsHPCLCogzQrxivmb2c3wsMNg/g4lJGHejeWYuHj7JvQ8xFGQp7wXzfPHyS8YvAYOx9ZBWep/mlsf0CH1tU7YlFxWG1hTXcZQ6XhfDJQuSb3Dz0TV9hfKJod+ZGWFu0JQ0+v81gUZ5O1OcALG1J4vNHfL2kXixUjTSzCu43jM9ClI9uYEZDQSLO5x8Y7aosYNxG5JBLfBLtf7A+4xT61wzeK2r6NdzgESacyO3gJ3A7UsNONhTAGesJNUBDTKazLwgn1/61WZ9JHGbY2qFz2N/Pae9icD48fEDdB9ys9U5ktFHiv8CzEvqFIHQnaN+KwaY1XJ9FMqQwDHifdzThDvhIS9hGMC/17bu7m7D3RpW/MoFTo1jFcwdt2P0Mtkr9OvbDDHN0ZO/snLU/7s9goV9N4OZRCtjZA/eWsOq7AjZWCLcOo9pNBCz/roT1mYlSEAgwE3DIj23RbxisV8eBGAYB60/APsyEvY+X1yL4zZWwc5YuH7CmD0WAkFMcKo4PSauALyuNxOCo1uVzHCgDAtwfnsbBiGgcrZ83ceaKImlcLAmNouAdrZ9n8JBMAr9VISUu/pqd0fBqzC+wMYcDfOr7GVRgicvH/INsHIsYRkOc4+0COSiXvObhogl7sM6Fj0TtycVUun4HTvLCF1jfIlN8mSRgwRgQV59jDBZqwFxYJAXwvjnJh4b9NoOF5ST0xeFknuOutreyuc+8DAppWNtEVXpoLybH7UaPZPp0yBel0DMW9UP5uN0McMa3Qb5BUHWO8K8gfXBpyU27Tdj9+LIEwlAkSjmoo49g93DYKELxJdzpUdros4r87ADL6rVDxEOJsbC9TQ7iusY/QvwDZtF9hw7qqR8r/MbCz33k7A2LpsOHFDEFX+mlZt8tdEqyuDqeBq34DtVVa6KHWkbZ/6PzNhzc8KDiVO1F2+4ffnhztIaf9lpbeQXtSq+1552iHdVyh+P1Nh3b8cGmantYhwtBW3h5d1oH1fYY1tYpy24i2xap7UlwD9E4j+t0aA9pRDRu9/QaKB3aSLed0Im4jp1qu11XY/IUDdMILdz8eH2vUCa1Xg9oPqLgntkDh15nhiI7N+AUzeZeVwAc3kZi0Fj2r8E=
*/