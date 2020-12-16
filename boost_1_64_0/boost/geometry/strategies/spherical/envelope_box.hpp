// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP


#include <boost/geometry/strategies/spherical/expand_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{


struct spherical_box
    : geometry::detail::envelope::envelope_box_on_spheroid
{
    typedef spherical_tag cs_tag;

    typedef strategy::expand::spherical_box box_expand_strategy_type;

    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP

/* envelope_box.hpp
YB2f8r3sRynDcR+ryob36c9eY1KS022mdXiVJ00svG6psY4sU9stc5x9mX810wZr57Tkn9k429yGUca8tRiDUdZzhfW0ZgVcQyre4aodWXRiQqq9feRKSYtMI0H2fRjO8pcJ7/DdY07ryME0+zp4wJCxwNQ6EphHyiVd9lFPNS2aaXpaTekNJt/9mOmSJ8k4vKpNb3TaRFush8s2RrJMb6YNfdlIXy7a7M+eCWNc5l/J/NFMkzxY3Q/vUm0u7fHmGfHGJaeMj5LnAfOYuzKG//usqJq4+HbSlMu61X0j8xqeYcoBv1+tMd9DNqwx7iHz17hfh/Fr3K/DDmvM16GP+hyqf/4t1/G5jf75pPrcWv/8kfrcSv+8Tn1uKe+mpvEni/y85VwWGyQV84fdyrkpZjFvzuvm/Si7rwhjRdv3V+YW8/47v9nYf+9udr8nLdvsfk/K2ux+T7rLmKby9983qWnqeOw0pql8e6ya1lKtb/1bapq6N8w0pqm8d6QxTcURZkxTcfiraSFq277b6H6P22RMU2l5cqP7PS5+o/s9rvVG93vctxvc73H7N7jf4xZucL/HxWxwv8fdvV7dz1S8dY1pKt7SxjQV79dvWtwLjWkq3o3GNBXv+DfUdaTiHWhMU/FOWed+vY2QaY7rral8dlxvJdaar59si+tnkcX1k2NxL1xpvhfqedxl8qSZXDtNiETiknzf/b4XZnXfk3Xsud1+35NtlPzb/b4XbnXfk3UEcl33ZWHZn8zvPGY8DehTefaXdxS2zdwfQATfG+2wTe9i0yW/KGVHb/PyBOndl6fyCzWmpdaIl1bohbbFdn4fOCfr/1DeO3ZiEus/Zqy/CL+FWL53mPK94TK2fxuCF6E1YQ7xBG4z4hkTmyYvlIW3J5fxduUem266V3lVss84WfZ1KuFh4rJZxhUxmvEq+U21KHkt57DRb4ba3rH2c1rdI9Jd+syobzzP2PivKa3vSVpPkLDKeBRHsa983jOnNSX2AfuomtqDQTHG+naue9RTnY82p3FBze/VQZhuvC9L+p2njTOdny21RGvxyL6uSfiFOPPmGemn7lQMv1qPi42YwBissdd0HjWV+PZIfJmOYyvx2d434uNHsyLsH2/f4/oy0seKeX+p/fOH/XOIo17ZQfsyHgn+5vt6/Sru1+kszjmfHU7pSh/v+CG90PPb+RrdIOtuTwiQa+cB7dpxWrctNnbctVyj5t+tRqfHuT33kzG5nLN977CvMItQWa6zR7Xryzk96a7XV1GeBdnnxrUiv72rc1bGd1b3BtM+ypc0hco+CpF95LNTpYlrKCrmRu8jx+/ee2Ts/qpEXhMrYoT2e7NLevjNMU3riyWxGOMQO6druEW6Ip3T5TYOsXamWLxLyvn9sD19HmFSx/CMfI6U+nrdd6nPpvM/VMbw7yfnfl9HPrDLeXuTYsckpyVEpcUWev5L/u7YVtP5lydxXZJz4QeJK3C3ZVycfbHR464hz3TPI811R20yhv9u+U13OyHgdtI310gHY5w75X/xHHHubkV6L7rab7vx2l1AHcNaxrGWa0RdM6YykDIyTn++XCMHCaO1c/IDU3rN95piXC8yNrv8fmruXyrM9BuA+dxZKekKl2eQPsjxpGG2U7ri09NikickFWe8btl3BZ7rHT4016ed8aE6t015y3AZlz9e9ls0IU37bfYjlT79zlacfeWat+z3uUreIunt/5H52syWz9Eu6R1SQ/JnvgzAyRjLPHkqvRGchQkZsUXal96+vvvUfdJt31aSPEierVkrz7Lq9ww1PX20Ux9SwepcsI1PledeP1Nez3T+73L9ZYDaX3EV5XeSTPO5dEi2fbDkDf0=
*/