// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP


#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box>
struct envelope<Box, box_tag>
{
    template<typename BoxIn, typename BoxOut, typename Strategy>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr, Strategy const& )
    {
        Strategy::apply(box_in, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP

/* box.hpp
afEx2/Bb5dNL7g3y92hoBvnmGbDhWMRq/j4UHhbBLyKi5Np4emkmnq5PxzPxLmwTcEbz4LXJrIv6CByxi8JVdUVj2URPPAScGXjwmui6RGd3J3354ND3RDsSLSHkMnjUZshFzL2W+USWNoYbIqXlTVXLqppWROobwo3h2vKwkMl+s/IgEcuH13rraKqPlJdWV5eVli+BoqquQZAuqlq4iLmxHju+tq6hprTaXZedprpuP2cddnxV7bLS6qqKPmnK65bWNgmbV6atu16s20YuV21FiTXf7qyZm9J1ZZG6ssXh8qZIbbgp0lDaFGao2qaGuupIuLa0rDrMmHJtfdLWlC6PlJXWVuxXVdEk+TWoT/qKxvL6SFPpQrnmwX3S5pgTqawuXdgIn1ey/kHO+htYfx8tZRvJi02SCb78ysaXqjorWyRP+qBrbIIfpdV1teHIsrrqpTVhR77+NvmXCt9ZKy3kWptYq69lf5YKlXWl9L3rQHet5XU1VTWlC8MSG6liytUr5PqCuJklZVVNDeF9l1Y1hB19HWS2j1RXlTWUNsg+hgTxjcykdmFtaU24sWphLd1I/RoapKstZbeGI2FmvqK+rgrtl+MdHjLn3NSAileEy5YurChtKg05dHnmz+6vDDewAG+NDZFl4YbGqrpa9Hix+KuEsew42lCz9sOrMALuWoFXhKvDTeGKiFhipDpcu5AdwRo9/LImoUALS+t9FFIWzqKbVtSHc3uqvMzdfxtFW5hbE25aVFcRaRTibcT0yL0nlt1YtTLs2l65aFowu0UR2aZhWalrpwL48CKFGxLAldFveVl1XfkSt2+1BslPj1cKPmeWBx+kwysb6moiS2trSmsZokLyLD8+0hBuKq2qjZTW11fU1fAvlxdD9TZYOHhQ19gE4xtgnqOXk7R1hEubFkeaFi2tXRLJMQk8bizH3+rSRlQNOYi+FbwefaK1xHzYwD4c5+zDZUOxO/GUCKcy5cn0opZ0bXdnPJ2IVcRbE13xjNyDfVHI/Sf86eSQP3Zc7saO5DwpJ1fFBX+o/53i72VO/DJMxqqZSGu0M9HRGxKwlfRRRHwCNBVtKQ65cfMQCcN5tnn5yI+hHerRloTKiHWEbV2lxTqHhzLJ2OpoS0uaCDiZjrbFI+tSMiw24SytzBavFdjHrp5PrikvbWzCQZZXL62Qcjt1evGA8fN240l+zgv3WX31yO/fU3PXnRc9/cslv9oGfvKcU6JrdZWI3XbvinYij90z6dju7fEokW9zB8NhgeEqv/RAlMwPP3ASCfDr4Phhl/PDzwv7zhzwXf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7/Xf7//8z/t0JPh4cGj96cwD/LZEugcmFDgP1jEDwaoGBjHLqfaHRTHNgyDVYJ7Apge2qwWoeuXoPVO7A2DdbktN2gwc506KY4MOLo0SF+pk9fxX/JVLwrk+mYVjy9ePqM1lWxdG8qm1wVzXQVr4pGWhJt8Ux2ekzE8KM3Iw5EJPweyO8gfsna6Y84jf64m8k4pY21xU6r0EQHfqsLT2TjnS5yQ2Hz6E4xCdr459Flncft7ni0km2A83Onbx4gC+NFG1FjJ7MIzCHtm8NUZ6y73bEWhmvDDaXV7PWKpipsbLTlQObk0d2Xjy7WHqdA5NE9kI8ulSauV3R/zENHngrP8bUO3cN90LED6LQt5PLzT9AKWEe8a2axtsY/Axe8EZyJp9nOB8VbRPIVySYjZP+F8DZR0hJpTRl6drDGWyXHxz050qo5kWRdnuyf1HD06OngU7rs3Yb06eL/EsTTuEAdRQ42HT1CrUEb72lnPIIK4jEiI3w=
*/