// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP

#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/range/value_type.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffer_box.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_inserter.hpp>

#include <boost/geometry/strategies/buffer/cartesian.hpp>
#include <boost/geometry/strategies/buffer/geographic.hpp>
#include <boost/geometry/strategies/buffer/spherical.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Input,
    typename Output,
    typename TagIn = typename tag<Input>::type,
    typename TagOut = typename tag<Output>::type
>
struct buffer: not_implemented<TagIn, TagOut>
{};


template <typename BoxIn, typename BoxOut>
struct buffer<BoxIn, BoxOut, box_tag, box_tag>
{
    template <typename Distance>
    static inline void apply(BoxIn const& box_in, Distance const& distance,
                Distance const& , BoxOut& box_out)
    {
        detail::buffer::buffer_box(box_in, distance, box_out);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct buffer
{
    template <typename Distance, typename GeometryOut>
    static inline void apply(Geometry const& geometry,
                             Distance const& distance,
                             Distance const& chord_length,
                             GeometryOut& out)
    {
        dispatch::buffer<Geometry, GeometryOut>::apply(geometry, distance, chord_length, out);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct buffer<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Distance, typename GeometryOut>
    struct visitor: boost::static_visitor<void>
    {
        Distance const& m_distance;
        Distance const& m_chord_length;
        GeometryOut& m_out;

        visitor(Distance const& distance,
                Distance const& chord_length,
                GeometryOut& out)
        : m_distance(distance),
          m_chord_length(chord_length),
          m_out(out)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            buffer<Geometry>::apply(geometry, m_distance, m_chord_length, m_out);
        }
    };

    template <typename Distance, typename GeometryOut>
    static inline void apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        Distance const& distance,
        Distance const& chord_length,
        GeometryOut& out
    )
    {
        boost::apply_visitor(visitor<Distance, GeometryOut>(distance, chord_length, out), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{buffer, \det_buffer}.
\tparam Input \tparam_geometry
\tparam Output \tparam_geometry
\tparam Distance \tparam_numeric
\param geometry_in \param_geometry
\param geometry_out \param_geometry
\param distance The distance to be used for the buffer
\param chord_length (optional) The length of the chord's in the generated arcs around points or bends

\qbk{[include reference/algorithms/buffer.qbk]}
 */
template <typename Input, typename Output, typename Distance>
inline void buffer(Input const& geometry_in, Output& geometry_out,
            Distance const& distance, Distance const& chord_length = -1)
{
    concepts::check<Input const>();
    concepts::check<Output>();

    resolve_variant::buffer<Input>::apply(geometry_in, distance, chord_length, geometry_out);
}

/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{return_buffer, \det_buffer}. \details_return{buffer}.
\tparam Input \tparam_geometry
\tparam Output \tparam_geometry
\tparam Distance \tparam_numeric
\param geometry \param_geometry
\param distance The distance to be used for the buffer
\param chord_length (optional) The length of the chord's in the generated arcs
    around points or bends (RESERVED, NOT YET USED)
\return \return_calc{buffer}
 */
template <typename Output, typename Input, typename Distance>
Output return_buffer(Input const& geometry, Distance const& distance, Distance const& chord_length = -1)
{
    concepts::check<Input const>();
    concepts::check<Output>();

    Output geometry_out;

    resolve_variant::buffer<Input>::apply(geometry, distance, chord_length, geometry_out);

    return geometry_out;
}

/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{buffer, \det_buffer}.
\tparam GeometryIn \tparam_geometry
\tparam MultiPolygon \tparam_geometry{MultiPolygon}
\tparam DistanceStrategy A strategy defining distance (or radius)
\tparam SideStrategy A strategy defining creation along sides
\tparam JoinStrategy A strategy defining creation around convex corners
\tparam EndStrategy A strategy defining creation at linestring ends
\tparam PointStrategy A strategy defining creation around points
\param geometry_in \param_geometry
\param geometry_out output multi polygon (or std:: collection of polygons),
    will contain a buffered version of the input geometry
\param distance_strategy The distance strategy to be used
\param side_strategy The side strategy to be used
\param join_strategy The join strategy to be used
\param end_strategy The end strategy to be used
\param point_strategy The point strategy to be used

\qbk{distinguish,with strategies}
\qbk{[include reference/algorithms/buffer_with_strategies.qbk]}
 */
template
<
    typename GeometryIn,
    typename MultiPolygon,
    typename DistanceStrategy,
    typename SideStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy
>
inline void buffer(GeometryIn const& geometry_in,
                MultiPolygon& geometry_out,
                DistanceStrategy const& distance_strategy,
                SideStrategy const& side_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                PointStrategy const& point_strategy)
{
    typedef typename boost::range_value<MultiPolygon>::type polygon_type;
    concepts::check<GeometryIn const>();
    concepts::check<polygon_type>();

    typedef typename point_type<GeometryIn>::type point_type;
    typedef typename rescale_policy_type
        <
            point_type,
            typename geometry::cs_tag<point_type>::type
        >::type rescale_policy_type;

    geometry_out.clear();

    if (geometry::is_empty(geometry_in))
    {
        // Then output geometry is kept empty as well
        return;
    }

    model::box<point_type> box;
    geometry::envelope(geometry_in, box);
    geometry::buffer(box, box, distance_strategy.max_distance(join_strategy, end_strategy));

    typename strategies::buffer::services::default_strategy
        <
            GeometryIn
        >::type strategies;

    rescale_policy_type rescale_policy
            = boost::geometry::get_rescale_policy<rescale_policy_type>(
                box, strategies);

    detail::buffer::buffer_inserter<polygon_type>(geometry_in,
                range::back_inserter(geometry_out),
                distance_strategy,
                side_strategy,
                join_strategy,
                end_strategy,
                point_strategy,
                strategies,
                rescale_policy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP

/* buffer.hpp
E+Hn+z8ARYC6f2K+AIIrKhGC3ZytUZ7miHRIaKoyE41FAr9JmiifjamMkc/GC1vKMP5sinQ90HzB5zFj7kNqZ8YJ+ZPonHc/U/3IrwSYWThgsQHVwIU8I+DrUWnFEJpmmsdAPZYCl/GZtBPluZRJcrsp+AUe87bJbKPQtBKrg9KadFjT8vKEpqXhiNyzZGZRBMSlRmdGC74/WA2GEf+c85HlT/AloAhnyBw3rnjB81Hfh6S3DJZWmArRUiy8cPZDV3dhV3z90uwKdIrEmuaQeUuKBEiW4mkSGf8mDrWPEqGgrVzP7fOUUoEJntuwyNy4lOCvMN3TyPgEHyc2AucufMSJu7Ec9g/3CHsEb+macucH4jo1QF+6N5m0KGHPEbVb8TtobI5uulINoKWAVmHP3xXiO9Q3Afh/Nh77VG0DyNsS03N0P8ZLnwt7KBcUxhPwzxnHtAlqJ0T9xXjsM7UbI6elI8dWyjm2n6GWvXwDDMrmqMjaTAPI2Yngw0i/kHa0Sekct6R4WLBjOAdhvIBoBO/HzvaUKHydTefr7BHjBZh46H4iaD3ezWU8ZbnzW/F272pMLt7aQcQCQZ25C1sizgnjeEKoBVbOLXXQmn4/XrPcNVoFTZICNpEMDHrT1wRdF1afgy7eeZGjjYWd0h+wcBNnRYy1oUoUakMQz2vklxDChlu8UX4fvhV52J83hW8CpwIxEGOQEPjuHo7IsQTRY5Y5xAgjcIMrkCnrMAWXDo8nXbewn6IGaolzRGg6PXbqXIfzmIgUMUKXj84k0aH6B6ku4FKCgplsVyJ3BwAxmg1hlnks0yPFhBgezfZ/H9WJ9/Hh4oCS9xv4NL7DiC3hjKhvJgQOIlGW9yO8NouV/GWjeLfvY8F3mtYMYNWv+hmtF9zNFE9yv3SZdyFhypY3iN9AplolBlt4sc8c+NysUJRWhtf8OvHcOn1mP8Pjij7lafp8A1YkhytazisSpQvKsxQEPrfwAtm+b5DNDWMAX6SEPUCO0p81902gUkN4wvl90caBJc4fB59vN4zF+uDZkfEjW8Ae+YYOcfbP5qypg+ijkXgGC7F5WNNAj3zUMPCBQlEKRQU/NERAHMrmQ/dKB8YC+vowoK/2fRRmMKH/b6zj/a8LAzmeA7nq3sAXZu3Ke/RYbbbvI2ktJZ72U544vyDwhYX9ru/7YInMlzZ/TXT3jwDiy3vGAeI2/UJA1PWNAYRoGviYNy4XeOWXaLmOcFtBQ2QKSAs5+nPqFEI/cSKHnWLl46vkWjRHw/6r6JtFWayZy5XFfJcxQrtimHOcpGnXIxWOwX2qZEZx27E9uPwezmWUqwJmoPWGZ8NMS0MHB5yPSgLCOVvKUUlXvlzebLpPulYdBOJajofeT/bhdo7fZP/xN2FAeDR7qD7OqaAZQlzDaXFZI8FHXHTYChnV8+hYwIiRyH2w6zByXAuuVAkw6OVnIXUSOtQJC+J76L5CnK36uxFgqCo+JRwZq/ooksyZElRDMgbHn43IGOTjyQ/pebaKJmWhDzaV7PHfRI4hrvkNaUxsNXILYSL6rTfVfAjP1Pr3yb1Kkde2RthzXUERwJB9kRQ6LvhnuTwyT7LK7kSTZoX3NMkKidCVNYqvzCtirz/AsTCmw4W3nAZtMW1PN4ux8uBqMUopdWhz4ZODmyZzSDOLWDPPIiWGUkZBSila2FNtQlED8l4mOZTCQXSiefsD3EmcdIV3CcyE9mpsxG1VMf7c35bLg1Oqrw69CHvaq80yS5Fbu5wux6ap0GBbZulw5ZVSlNM1WDULwhYU0pFmozDG16YdNmkOhkUzqorjNedPAajCn9wOc6cCL9THIBojxaPL+h0W6eIdRilL7jWJMY21pNBeHQN9SMuUhqvmsNnPo1hDopH7eBGteMerCRBj4ldc5nY6kbOXreHDg19E80ApxA2v/QGZ1ytGxjtmT0edbb+7m91QTZ7O1FJ7RpczAEUlOz+Q5rCXnouMdN5zKPV0kuSGerjcUMax4Go0Cu1OxHFPNNW8A8/U+q4iYU9GMbovdA/7H4Lx5b322orYFxPDx0Xh8U++YPwBjDBjmk+RQXWj0HSCXlKFx4/hlssB/UTseP7+CHYkEnZkhcY8AbEDY9FSqnaZUpqYWZqIyHHP/f8DckClz97i8epeXXH1KoWn2KTXYaq7mVJ6WnH1KYVnilja/Wj8pgRNE/0IytxyAcr4V3c5SxM3OfGeyZ1sw1umldU21TXodPVVLlVdfZmuQWkiREsJGa1O1+nK9OooZymrugJSW2gaXK+6kjlOOdFvpgORCu/CYMyDSNvz6boDjXmxO5tRVsLcNvEofi8MI9rSMKLhGVcDYNtlgG23IrbFAxZXT6m0oj+96gkAmMWAcZWZ1RihV13NXv4VYl5yGPNiZfegTtg3CWIBWdF9klI6rEXjB0Ua5jK1hILweSJ0E/odXsZciArjkAe/Fw5rU8PZkr+HWqN3Axl4CBzC4Myo3haLQ4quuB32UJrRwzLOj3XupBbaiorHGrA69WxYaq/5WRJEy+CWlyzNJu1T9V9pfS22ZrsVhdjNq6RvIcuEdpOB/fHZUYtL7dzNc9hfsroi1TIQQFvKYmqLUQ6g0YiVPEL6GrVCDCHDPqEf1fiaPjJSZ+6W+/SMQ3LA8nuD0dgoMnXJMOS8pumUmPp74OlgDUNTFbpo0v7qX6JjLWmBNv+Skcjb+cjbcOjNa6hA+/Co37wVnVJ1wcR5OrC9B9UPA236gh46+89Di/uz8d0QBqfqtjntb1ScNjvE2GxgVSu/omN3yxsbTptHHSOh1NB4V+a24iK2j9sCOVGi7LcAMXGeE5o24Mw0s5/tImPFMGejeUT+LhJ0kOLlrPloeERo+gqFJkaG6dT1WrQqkfxPs6MiEYB3sBdSFLPXd4Y3/T7UzK+woGmdi+otjqKC8u1TG7E/j241O14/ZyLXPjMrDn9EgupyOJ9oDwuN5/4b2iX9+190PRtatajqyiL2Vwj4LS6yzNeZ9rbXfHSoovuk2ZH2QYGHffbnkACztL/iMEQewGYVFbO//CV80/cSMJojuPNnv43EPVHhSDEaKnogQzEr/BO/pCgrwH9BNGbmPaMn3U4a47CryZVHdHFJRmuLfVnzo1G2Edy+Tlsm2rKzzkA/K1mB34cVePw+/OZpLj3H/CgeEo4o0pMqsKywRPlPfkEGPczsi79w0ItJEMAuI9hnhsAuTapAiLPZUAQ3rHkxHeK39S8hL0cP2gCV9eWWzXHqhGaTbkTzJ3bhAHoBKX+SOBIyQG1t063/q7ujxWF3R+moOoLejtQ32VPI+rls8mJdSkBXR4L65qs3kKsj8nT0tx/ydNRgusArl51bkI14OnpxjEetU3SnspOeffTspCej51v0/G96on8tVrARHm8+jeGnztNWP43999ORhW7t03iO8Or5EIf0yvlRN0fXxRkM6NJSKitinyfDgvIaOitDpdyL5UH0aAa765lqX2AkKvCJ1WzfRR7NTOqR/iWp9dKvMd0UTJcI6XpnBoaixngTNqmH+rNTGwTfAzrXGhGa7kLtv4khR2J+ciTm3wvP5qe/hmfTMaHpMVj7cjL6lefRYVjmLkwoPPogelK6sXcR+lE6cOh7fpQCET9KJYrvUbxZCkT8KD1zyOSQ/Qg2gG0zQZjgtovguYsguYsgvAshGQzi6fuBQxd4UcrLC3lROkLuiDC9LXgg8m4J/jnybgz+O3lRwnfyovRvkU+moArvDWfDXpTIwRm6t8G2wMbYv2G0xAHynxa8jVwedfL7HuHAEe7yiD7dEIN3UNiz4PxQsXPGF8tCxSZRsQSDYAwVyC4okEr5Cs8Rzy4XCxvOVohLG85uEJMbzlYLvuO2cH/IgVIHJnNukCblhCLRfRINV/AVW7j9juALkfeU4FPw3mJedK00o+EhI/pOajOF8jZE8m6ENIsyKMU1PMVLmII8J/EUKzHFeqEpF3/vFpoW4+/9QHbxV+J+lBZtFprm4O9qoWmGDQGE+HAJja3fhzPMI+w+5GHRmcQ7tfgQ70rES2EvQee0iG9s9znAUnMOrxZdCb1Kx6ljUqCHl+CBaI4q6GtpN/nMWR32tYRKduIK8rUEqJMKf7a8PMH3Mp7YHUrp8DWHToA43geLyG0Sdpe7TfqNYRzEHzeM/SzFjn5SaVRRiDtqX8h5Ek+Ih7VjMKGXtuQjYf9J3JFIL91n9NJJ0+FQg4JvhV0hXQprBbS7Pi0gNGHvsP0aygVRqT9QkZiOflu4LTW/D736AZHvoVP0e34aPkaa2UFkiyx2TWxZNtzs4+7/ekKRPCNvW7Bm1OPRKX7s7uQej+bzuiMejzC1mPhs2qGjg2O6ch1k5yMfnGuJuDzqpRbZ8HA5mGQJuTzKIldZs00hl0dmS8jl0R4D+egSa9Dl0VXk8ugLcnlEs5uDgjeeHB9tCI0MahOvk3341aLSj7pxmLkXcLt4P0OzclQC93508nzE+xHRResojIKLoyIQp6KzeW3cBxJGhH0g9Y71gUTSxWNz+Z9HsIb8d5EvR98LRF8RfdA3Dv6ikR3NK01oOHuXdAePonEqzqR3dJGDv41EV8htUpZKBYTdJs0FStBCGA10eO/5sPMkqm8X1sedJ4Wzj3Oe1HA+5DypaXSm6kSwYYrpVA3HAoh9gZJgjvGOk/rOX+A4iZ0POU6i4sY5TmrYj+2M+E0KJ/ie3yQaT+43CftREAzQkLPQkCt+XKO1K8lv0n3D/GR/9Vi/SWEkwXTcexLhDh9H7j3pGkjfQgks+e0+dKyZ3uz7G+XC9QmFToIJY5wnJY5znoTF/6/Ok8KJpvqO1U8i50mOgZ6Jx9F3UriHoTk1xnfSePQIu04irAu5ThqLFyHXSbSk+qVv+SKjE4Ea6zcJu839JjW9gu4D0pXnOWpE/CYhILjfJNe35DQpPKcUyqzsoun+M3Ka9HZDZrpYrBMFUOnZbkzP1m5YXg7x5A2pS/o2jVDw6KB2+RjvcaPUT4te3rDQIEZlk7Fdjq5Uk7z/v/np715jeLohDBfAOKCDlxg+VvO0qWgkMhRK0+xoH3ICD6XwEaR7FVq106jgtBAH9wKVaJdmq4Pa9LELzKspq1g6+TnCkE4egT7WCbTq/qfopp8SUyVAZmlRuua7MF1BJ0pX8VcLFL4f69Gm8KKBU01fxd49M77wz+T9h+kYltonSr7WugfUXRwUz9CxsVX344vHayXRVt9WDMjtJvbYmhBxl67NpFjxKn3X1gtbSnmomSpV/Qy/vZT+XZslEzuow86ZMsAE76W+UerSkCMlDBhqrgl1Srwi1KnvQe3stxdATd6/93zIjxK+sO770I8SxZWotMK3mJuJDYDN60TV/yi1HOdLS3ew8rsfZJw5oY5sWn7uI09J17xmcly91+T4KfwdhL+4fSbHJPi7Hf4ehW/FajuZzBV8aGpHPSp/Uh/4Mlq8U7P6f83t5t5vhb+VDngUpcCjDO3mRsPfKjSlW4ymdNdC1P3l2fC4zwOPqnXwqNsIH+5C87r3o3ndajSvW7/RvxupoJ8Mst0kbYdVc7l6NPClxXdMnDy2vvpof5XDX++4Sfpa/kQQU9VAIGgS49VJymR/lcVfb1kOcxk2AWYxpsXaHJ27bLk0sLpsbWnba0i80rrTjuSrh8IJJjVPpgQBNq6IPOnbkmDcGOvW2+0+cujBzx9+wBQ+2srm+3NPhl4M//L9rpMkD6u4ezNOMKGMjOsortM7LGL860Qd0M0B09L9rlOUkD3tBGrrOm0CLItCl/RRryMsIMaIYZNkbXwT57HqOpnm6oXBPDqo5FpU1ykl16G6mJKbuFaZobbTCD8jj54e8yNqlPizZLR2te3FMjC4yYGSeGr8jgct8GZZok1H+W+vEQWGvUY9aQP3TGy+xDWM9n+EPW77rMAYPU2uZRid0cov49A81VQ28EhkE/creN2LTF7wc5RqRQ2Jfkjxt9EUmyMp2lDQ/SC+Oj+uSmL/NZrm1kdCl7a47Ln72JSf4Slpn5qNbbtJLbSlHYfGXyMPLqmMlwdvq7bJrSnCnk7YzHWSA9QllXEYbaXoVpj/N4uxaN87qtzZKb4h7OkW9gTSDmnXFRThOWyF0YHyitvuIMcpUMM0NvsRrmrK2zOqcNqhOeTWkZAaJ7cAO0aJMwvPyAxFgu8JQwQ2J7ZEelW3JdzzJlJ2tEOLPqZTwkzJUZXIXh1NWrCFDs3WAm6hWXdLwgVd7YauQieM3+tqwKS7HdjZY9jZbrENwCLsOZQW0CaOPY+ey8+jyyIGHtCK5Gq05nlCKR1WrWi60aNmsa1mR0GBF5iOAv19lNhvE5d4TR42L5okR13DEJGuS4Mer65fW0B+HcQrAaEKgJsOmR7fnCS3W1Srs03aHVJ4Rf9T/Zmlw2I/mij//G50gKWhLYgFc/EsKgMPBqbirv95A+lUZ4nGZUVM2YYuPcRcEwxwOYzR5wVey7Jitt1Kx8MlyvR16BDihER+xu7kZWkLilj+NrwXWpxV4t9sFC/1morZRis1Ho1cLikq9rCD28KHSsvlNot/fh0kN0hv6FQEy4X2ybPx1SDPMnREWSKWQUvWrC1r0xdgvSyFUq2jVFD/qfBhWGYTWVAo0pNEOozK6HJ+gzOyrK08M0F0oNn5TJs0GPrtK0hr9682AdfxSFRI/EWKh7wbMW/H2jVlbSiR/WcvP+36nA8d+b/CSRwa2sr1KB6BHeqXkjNdw+JEVtxEXG4sW9lEC4JiA4rRxRVE+w86gMrJi747WYVnVtP9lu96kPVYWPGCAPMvXe5I1pM2czlme648klrzLklPt8mplBAAoX2j6gXqdA8gS9EBjCtWF/t0caJcZzGK8cX6u8XMUAFtnmMokdttjSOD1RZHzUlKuZZUlGIwpWT26O+Ofv+8bE1Ey1Of/0YPie5wr01ee0U2SlrHkB3xZUBSM05kTseTVimZlZ/Wde8M9uqX4UO3Z35JdkElm38+NThzhmiBeXyvN5ldYkFTlYPOc5LAMmScfHYaWc3jjWWr0YMdTIbMGVIawaI4DAdpcjH7yV2oozbycDiTUnpKi1MWa9HFLPGuMZb/wnbuf4eqmFDqFXrEqxbKKPt5zxDhJnrYLO4rT7J5J7Ay1FbTrx3vRwtvI+xVF6luW7mcCbxdNsx3p8te+U1pW0X3EZNjvb6Azr6XpjqUDakOP/yl9QLO0KJ1tWs44w2PcieDCau6hkMthFkN69B63OoY2lR333olHl9L1sJcVf9Rmh8+gI+Yq6MjwU22jAVYZrFqRT2dDtcZ2hc/5MBjtnh1pcX8ToZ9IbPWkhs2NdfGw/01ZNumP9tSLvimGEnj21/IlIJhdY1dgeXMfVo+NyKu9S83+C1r1BVbEv1LtzgUoPwGaCeQy0T1ffbUdIMBVTqAtmTXL8MLjR6oVXob9TOAM7COb4Jcw5tQRE24nm2iJpzhvWuDhmNvtS4AaUih9Qo5q/MzdIeVUoG/7C9X4rKAyq0CLDxe4y16EsbLh22oulpoY/Onk8WbzNV28aIKDpR31U527fSQIZxBJc9+Yav++dD4Vn34EF/g8mzQwSPTDIbXcGwyC+xC0yp4CRX7JvsEPgWnhHmUImZ/hZvchO0Z
*/