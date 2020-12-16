// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP


#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2,
    typename Strategy = typename detail::distance::default_strategy
        <
            Geometry1, Geometry2
        >::type,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >::type,
    typename StrategyTag = typename strategy::distance::services::tag
        <
            Strategy
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct distance: not_implemented<Tag1, Tag2>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP

/* distance.hpp
xnZ3VeCqezY69IDf44oK6DOaHbyqIZh2CsPvWeqMWNHnd40OGlcUxlqccb+HNnbug/3+IpyNycSaCvU3PZFslNwyiyS3SeZ/8gI/3d/aF/pr/Iyl3zAQIbsc3ZMXTFHEoj9T5EAun5/HPEF6AKXmZTg+G4e+nuBNOUT7R/pW2hM2XFWk2GeoR1h+qXfOuDT504ulY9xior0Kw/W6QIU30lu6phGT0ZZZr3Xk+I2gJx70hJKrQzKKP+Wdhb0FSn5Xn7Pa/10/jYke5Bds4/7rl9qrXXslxlpa+gJZ/1V6X36PsLHF16fnSFspfT2nlbFhwzMylBJXaAlDphsms8HMbgoXgxvrGcmDpzcKJopnpJ/yBnGXHjgTvai1AJMlf94diao9P+ybas/WzPaE6IrzYmkQXHH6qduAr3zgSbQkVrNpZ8MwC6UoiltSTStg02AiIxQfq7AYivf9h1qm+7chqf4WQJB+Dlf6YLyPWi3ifu+at/P/20frE/ql83skBzw+wU2tA6yjdzUZTeJe8F3p+5Y+Kf3U1UJafu+sEUGjD6+0fkxRCmeFwvpZ3/CmKBcQnjwZY33ISCJuONwIy/T/ny8tYQMiOdo7IsAyBz5AXQoAdWf3QOnyKlbPJubo67l4NSbZdyDrYOwmyFENQrMCID5JF4hDnN8ZTIa83bh3Fpz0Q3KLAsNOZ/gsf9ekXek//x3pv7I7+i8+kf7/aeq36d+Xas/Obuh/Yhr9e2UMCP2/6M1D09a/Q9Pc/0TT7P5wzSpmf7BqVBmI5/KNjZCSq/Ka2EMxJz5+73Ei/h3prUm6rDS4PDWwmubQl5YPyxeUq0VEg6rU6IheYXB9zqr02s6930EeiyzKAv9lauiEe+sJcZ+Y4nkD0+LE9daxNGj0Nkf9QglBZWNFCBmf9XINOx3au1gyhjMhJaJoqcX8BaZPJOPSgnqGpa0SRkTb0OBA85/kAZD4VO7EgURgVMqL565Jp2c1WFIkjciu/q97afBWS3prSOqpYXGLvuaRwG76ExbfrTqUbps/ni/PQdWleRv8cWtu6268+bqZFe3msu+6zWzPB2veZr77Tk8NFQ+kyqIQ+u32ZnKOfebcnykjq+ihBRKUp0wMmRVLdY/I/Ir+lCn2pGY/4LNM9L9VzWRLECpzHPBL75In5tebsTANBiyZoU+Z11csIbtg/rX0LtDU5gm7WzmNZPsNlz/u5JYMK/xYjz8uJ6eiIOMQ4I07+V7Cd56Rxvasl4AyO6AXfXrGWKGxcKbzZPzbn2gfR+G2Ii+dnVVtbKk2diivUZT7RGujXuX09co1dVvn+t1bK5Y0ugDSq2zQVMAVdrdIu2mbUjVzitVMPwLk7jlEe5AbzKKvpklzLmQxwS0my34PJizexoeEb8XeYd0WFjCcRi70BWZ7wFsFuvDo+w6Q1h29nZmr19cdvGI2mqqMLThTPo1eBQn6hi3U+hGeftiXjR0d6JOMFoRgjjva4W92ZGduFkPGepDqwc1OB9LnoZ2jA7lIDp06T3QPkkcyk6OafqiG+g1MD+4Eyu8h5R/OlvJB2V298/4V1iHiObSbxbfEA3w7+YX+belD8SNO7WFxsz/3lOJmk18M1FCRZ0CpkjwlW3YxCInH4ivXhGJlQyJ/jR3pt6CNc++M4DSM2y04A+D+l7cNFDeIJfvPnifv6wIXFgLlgMGgIfhClaiP9Z6v3h/5lXqHWSPDXbpeTjPBxDhvOa/ohIfjCWEt3js2/umY3rEn3UEDtdsN/GuubiAP7K+YFzmP/jMmrrhnOesS75oUvi5vmCLX4TkWws77s42wytJnsd6QsY7PSKIOU3M7ubihmjLyxyN7ia8OLliTgtM=
*/