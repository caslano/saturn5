// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

namespace boost { namespace geometry
{

/*!
\brief Assign a range of points to a linestring, ring or polygon
\note The point-type of the range might be different from the point-type of the geometry
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Range \tparam_range_point
\param geometry \param_geometry
\param range \param_range_point

\qbk{
[heading Notes]
[note Assign automatically clears the geometry before assigning (use append if you don't want that)]
[heading Example]
[assign_points] [assign_points_output]

[heading See also]
\* [link geometry.reference.algorithms.append append]
}
 */
template <typename Geometry, typename Range>
inline void assign_points(Geometry& geometry, Range const& range)
{
    concepts::check<Geometry>();

    clear(geometry);
    geometry::append(geometry, range, -1, 0);
}


/*!
\brief assign to a box inverse infinite
\details The assign_inverse function initialize a 2D or 3D box with large coordinates, the
min corner is very large, the max corner is very small. This is a convenient starting point to
collect the minimum bounding box of a geometry.
\ingroup assign
\tparam Geometry \tparam_geometry
\param geometry \param_geometry

\qbk{
[heading Example]
[assign_inverse] [assign_inverse_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_inverse make_inverse]
}
 */
template <typename Geometry>
inline void assign_inverse(Geometry& geometry)
{
    concepts::check<Geometry>();

    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

/*!
\brief assign zero values to a box, point
\ingroup assign
\details The assign_zero function initializes a 2D or 3D point or box with coordinates of zero
\tparam Geometry \tparam_geometry
\param geometry \param_geometry

 */
template <typename Geometry>
inline void assign_zero(Geometry& geometry)
{
    concepts::check<Geometry>();

    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

/*!
\brief Assign two coordinates to a geometry (usually a 2D point)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 \param_x
\param c2 \param_y

\qbk{distinguish, 2 coordinate values}
\qbk{
[heading Example]
[assign_2d_point] [assign_2d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_2_2_coordinate_values make]
}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry, Type const& c1, Type const& c2)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
}

/*!
\brief Assign three values to a geometry (usually a 3D point)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 \param_x
\param c2 \param_y
\param c3 \param_z

\qbk{distinguish, 3 coordinate values}
\qbk{
[heading Example]
[assign_3d_point] [assign_3d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_3_3_coordinate_values make]
}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
            Type const& c1, Type const& c2, Type const& c3)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
}

/*!
\brief Assign four values to a geometry (usually a box or segment)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 First coordinate (usually x1)
\param c2 Second coordinate (usually y1)
\param c3 Third coordinate (usually x2)
\param c4 Fourth coordinate (usually y2)

\qbk{distinguish, 4 coordinate values}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
                Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
}



namespace resolve_variant
{

template <typename Geometry1, typename Geometry2>
struct assign
{
    static inline void
    apply(Geometry1& geometry1, const Geometry2& geometry2)
    {
        concepts::check<Geometry1>();
        concepts::check<Geometry2 const>();
        concepts::check_concepts_and_equal_dimensions<Geometry1, Geometry2 const>();
            
        static bool const same_point_order
            = point_order<Geometry1>::value == point_order<Geometry2>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(
            same_point_order,
            "Assign is not supported for different point orders.",
            Geometry1, Geometry2);
        static bool const same_closure
            = closure<Geometry1>::value == closure<Geometry2>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(
            same_closure,
            "Assign is not supported for different closures.",
            Geometry1, Geometry2);
            
        dispatch::convert<Geometry2, Geometry1>::apply(geometry2, geometry1);
    }
};
    
    
template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct assign<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    struct visitor: static_visitor<void>
    {
        Geometry2 const& m_geometry2;
            
        visitor(Geometry2 const& geometry2)
        : m_geometry2(geometry2)
        {}
            
        template <typename Geometry1>
        result_type operator()(Geometry1& geometry1) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (geometry1, m_geometry2);
        }
    };
        
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry1,
          Geometry2 const& geometry2)
    {
        return boost::apply_visitor(visitor(geometry2), geometry1);
    }
};
    
    
template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct assign<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: static_visitor<void>
    {
        Geometry1& m_geometry1;
            
        visitor(Geometry1 const& geometry1)
        : m_geometry1(geometry1)
        {}
            
        template <typename Geometry2>
        result_type operator()(Geometry2 const& geometry2) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (m_geometry1, geometry2);
        }
    };
        
    static inline void
    apply(Geometry1& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2)
    {
        return boost::apply_visitor(visitor(geometry1), geometry2);
    }
};
    
    
template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct assign<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    struct visitor: static_visitor<void>
    {
        template <typename Geometry1, typename Geometry2>
        result_type operator()(
                                Geometry1& geometry1,
                                Geometry2 const& geometry2) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (geometry1, geometry2);
        }
    };
        
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)>& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2)
    {
        return boost::apply_visitor(visitor(), geometry1, geometry2);
    }
};
    
} // namespace resolve_variant
    

/*!
\brief Assigns one geometry to another geometry
\details The assign algorithm assigns one geometry, e.g. a BOX, to another
geometry, e.g. a RING. This only works if it is possible and applicable.
\ingroup assign
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry (target)
\param geometry2 \param_geometry (source)

\qbk{
[heading Example]
[assign] [assign_output]

[heading See also]
\* [link geometry.reference.algorithms.convert convert]
}
 */
template <typename Geometry1, typename Geometry2>
inline void assign(Geometry1& geometry1, Geometry2 const& geometry2)
{
    resolve_variant::assign<Geometry1, Geometry2>::apply(geometry1, geometry2);
}


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP

/* assign.hpp
vGNrZqy14WfAXax61uU4ZzxF77D3AzV0B3yhwXApy/Ochpr7+eE4ldIOd8pyQPDg/ENfopypLnDnGqqr0dNkszp7D4nRerm1Um9f7lQ1rr82Tq6p10UJl8Pc2XjxuYRq4SGmmFMCPC5glKYm8kFjUReXrULS0PxiZbnwN8WX3DfnDG5brNT25HXOBuTwLPcxO7IyYJqj8v3E8xDkZzGCvemDkDqGoPRSazpMDpa/vdH2xwZqgrvM5oNVqhRt3QR1HTx6+jySK3/QUMocW1b+bnGE/AjFfjJWae7xTm0ERp7cYFEbi5elpU6GGJjYJVEqXp31uW9Lq90fVumWq4rw+Z44MZ3CQHeY8OPnRpdw2OO69+Uje/jEHplX1y6+3GztdNa40QIom7Uc0gxXkQ8K27vEqIabh3KlBULDFKFEaZeO65F5BSvqKN4AQblfJytkRVw2HRcVzLXWelUrk68FDVXV6GfhUI+NP+MZLn/vUN81sTRg+lkaiCOB/myrV4hLjLInrgFJ3vufdZqrHWh33VJe+qUO8N8pYn3q8jBXRUodESR7TABA/tuV8FnuGbOp6ch1qRRx8q4G3JtxDa3oHYL3/bOsXSFdkncgLiTP9YfTkSW8okbs0L9B3b3BgR+tnKWL3SWJQNo3cT3NvR0PWkdTViQwLiaNr7IQ1Ms1A1aTkPISjd+0dPAF/SJGydmJ+YzaPAZAyYrrVa3upUpNjZoebQNOlJi+i2oelKjerNIABnlYgr7/surNclxa3elKQLochCDdxZAfFYBkLBTMBOwwCqk4S1dGQQHYv+Wnh15XvTcv8v/4wRrs9K2yJqsjdscC5WKdHbJRQ4T79+oAf9DAhwyi19DkflCq5MCvtcEN+YWu4uKtr/APbWDfzgXGHM8xeS6+h+n+JK3JJ57Vhfq/T/F8OTcE8v7LvEoquTmrz9hqZjTVU0TxJn3CX+UXnS6zi+2wi7XtpKqff4mNFtP6mjKIXz9mSSoEHZTcmwHzuaU9qjX/S84KAmlHFCYJjuXK5Su9GQxfJVfTre2VkkTo/c62rlSRXNM8JoVQE5em3Eks2xm6hRJZyfdj1Ht0zeVrvR4Mbz0PeHnK6mlWB15bsXELSBSe+3IbTFWtoxRxzgIlPTIXnlKhGg52PgujNxWYxLc+UJyyUFW6j5U8szaodopIa4x2ZuC0xDn0lV1vhTsoGbGkfIHq4jJS/3RaAG14XH5XAZgZ/lGI5cPVmUqResarziXilAPiWz7UQiVJtuq48vdK6HlTpLQDZzipUA6T6en8CdRd3zaMFbTKFSj6ALUEdvgr5gJR4HTj1QQQKHjDSFl7a7z+CbPqMoOLCD2jRHEkxytBsLyrFCMViPWNUOtQFvuwsqo1kJyWdEmF3T3u+WpzvMsaWvrQigPaXDcIlBf19ObgbVzdvj72CwRp+ADV1HcaxWpE8PGFYVNyr4Rwb+B383G2v4EkkFvCo8NVeYuRGK45cOg9S22GS3qY/tBORI407sPGCur61pz/mTbOoZ0Grf/HwSqaue+SM/myPnfhtxJ6jK8pYtljOUs+xNyOCyYULjCxGmxt157qGhSixaQVzjZklu023mwqqAvyPVQsWXJW0O37HmBXeDaDunpLxNgRxyN1Q/bZHMJ0vpMLkMUc9nXtsOoeh6VJy0lsCZ8vbGBnUlbljrSB9OZM8hPcMoCpnVYUbU8i4MpZS7xgXRGtb8mwVrT+4fqBjhEXQlvlLeSFjRQGue1Ggkn2xzrap8g8VwyXcC8dfxZlsm9oXN2i4pO8ANUHaQKVqkG+rhBNTMLAUAmSLIFSn7kcyTk1UyhJN54cOa39yOUwrM5XQKGy5kmAKrZAjQaKLvIODnR9NBggQaypC+lv97CLf+YtOyNJhyMiXdXUCp2ow4od8prQD0SAASmWue0KrxL03I5F5g2GhNOu3xZkU9Y0bqV9hXmSIxjYNzT3WFaiM4R2DIUzOHo4eo0aiVdRkeB2xEJ7EI8zsot4sG5lhfDDVDyYdZhgmGuGLLon9l8AAOj+Zg+eo/H5JKKKAEuIPyrPa2Xyf76YK/+CfwI5Rb6cYzyW/5OqiY56Pi9S3NOh4RvyAOUo5SKt0nTimj3Hgu8qwetnJa74kfgAC+GvI+5t3TP5YLycLjpnM//xn1b7OZnmfv2a3gTJUpfNYqj7a8h5EOU4bIxdcJ92XI+LO4ndAE+Nh1tE/Nwy0//ldst0CQ95G+M8AFXg3KnVjTdyKucaOR99/z0Y/G4Y/G3UKGgXgtB9bxpHav7zNpBUHaFkgVm1KDLJovJW544zsqYSbcUCLl0Y/lIbnsig/OmS2vDoZJ1NAJ927tvDLBm2MW/OUYhPkg2Ose0QrILxpLi+lyj6OMuhTgnXgJKZx49mjGGmkPOgubcnShxBZH7yOTEL4Fmk1Pv9Rm49mqwukcmTcf+8j8jZmbrI6pDRUKXAHwB6GcEleE6R8MkBF6otVScmVLcvC9Q+dpDToyor6N6RRZliZYEW/PiiH7BgQzG/syMTZbcWyxmktBbRiWYLNdEeIAmHGjUmG6ZvIuqWoF9AOMOw6wz07O3VWrzTgsbpQ5PtF1QYFuJjJLQBBLmhNu+iL+SQ6gxPzB/CCMxD4lZQOfyMLsYB79UXYXjTAWpQcpYIyC5czahL67mVruubDzf6sTxA/dbI25s/dNH/vRHoTvRJY7dLBIp/9jo6HAKOf3FbN1ez++acvQjb8MC5asig5zjazXL8Qudy+PfrvsSfXZon0Y7wtuhvI4Xi5wQN298A+xr1RlZZ9XiyLO2GdukrTHaCFo757SmzLhEv1W+UHsyUTeIsWLNUcIn6TWrYbTTqQehnNb1AxHGw/eCN/mfSlGLS4SaJlAIkiM4NPyMfZIXPV9ErxQ2wZSHPkvXonuOCdUbXnixqt1WGqbndOWSxHu515BWSLMxXlSshY0TxOuYlhtu2NzNjf+R55Q1KULLCqnD1NDB82m4WFoYDkM613Sne2xc/vLcbsKfQ9+p3wGVF51H91BdCq/RBSWPfcaO0oYhn7rhNK3U97K3mF0L3/EK9jW1INAOy2Rf+oLlQmBw+F426kK46eMiY2hJFWHIntKLp4sU14Bz2faBvzpEJup7OGvhnpd5Kwf3GFniD4WRhwwYijyTm3R1GXDc+4KG1PzZFzLXN1J6GfDQWmY5/63ZGpve9RJNEZO0B/sFjRX4mm6aiuGdk5CPQNWThJplqeOpmDWEzRIqbW6AufM34eKHdnHAGbZmYmj4VNvI3j/wocXu/FG/2S32E5tiMMYxbFxernLFTmys799hidGWqqnPLsZGSjLBWvsknllD7uoaSmMrszQzFlvly/C2yMifvu10FQS0E9w8jlc9XCtwooK0s5tNDQcZSUSvh0sCL6jdognSNTwqUp8AABWXhsxDxNZ+bmpmDfn7KdYYGNwy5QUF50NQCba/OdXky93zPQLptaNvw0Qz3tJFwshoIDzyD8/EOR6PLyVKwHtEL5+tpWctL24ANJpl2odwYEKRmwP+jCYzSVwdD3n9l6UuIQ0a1sTHaPV0fte/Y5g0sIaCqmpulm8vk4iPJeSSlFQBuenfZtdF/0riEGu443uYb+agFLextIT9omTrL7q/mz3k2A/bnh1WqkLpCjoLFKKCQa9b5QU19ZUTpDEXptiK+TgMAlJ7R7PSUzw+IYsFlt9jeSDh9DrGJqPFtPsHKlwtaMkQk5Rwv0af9rrNZHI+DTpuZNQw33ozsME7f8XK1xERTlM8ihMG28RyrsODymeGYbDhMMC5Vl2HgSBV38lTVwnoakULA2rAGNoEtx5r8hyZr3GxqM6Me0mVAVm+qWtHe0l0Fv1zeZ6604cH1hCTfogmv8AWqk3FrAXADA3pOOq8MguarDSP9zSEwvzqAPD3vO9NcBI/Vg03J9VIUpd59NN+q3hSNUR96Oi14vSZ31OWuXvC9nSSvTNLMYkSzeauNXrHdv4ctkuq4QNvVxAcqvK2ESjvO/esnaXpEVNJyjKWfuENwtUttdasccNRdE6u4T2xD4cSRfKp1kkPtqUjDMmFDGjYCVoENJvP6PGnDuha0gR8ySaAJeH05zpAIMKDjbri//HBVH/eRqkxu1vrofOlIgvMfYu34DrFXgffE9khGd5YvLCzV5ALN2jS/Mh+absiK7ClMXw6T4Q6E87zJhA4tbBkHGitgTYL9pYSfNBNVhhVB+tDfJSHx8safUS3fA+pXG9w8Eb7+HezoBWHxSvGRMLlarKJWD6dl4yOPtQSYov7FJlT640tAFGWHtUwOtLwyjBAg7c26KUs59shnhTaENvgtroFEfnDae2ohQEwsQejU2v7n/LFG/ftod4Wa8tDJeEgLGxG0HDK8515AragJSqhF6kzM94+vNmxp/xvJTrao/jVzFE/8fX0h7gk6ONk+nInnrlaP8TrrH9v3Jltbkpso8lAuDOULclXVw16wwWt30PwGFlHdegRIiwNNFWJZSxtnbl98/09ghV2NP2pj4vrpGQlUdxsnnFPr4g1k81bRzJ433lavjpEBPLquogc0oclwUV4NCCUNrNgx14pYM3daoJf6k0P3fBANxumgVawAxXXsp9oZmUe9DhRnhDduKoGeEmIoov8SROK81oACUSxaUIFLnkcrNjMq1wL8ugyBuUbANMSAv5uy4VJgQeWw8LGkQDAiGA59oXrG4GEPSFSjSXBsHE5tMkBAc7v1FmU4PdllOkAs4FiBl7iN7JELaPn1vn6WK+tZLEbW55sZ0KU15cJJD4TrGqQ7+SYe/iSq59n0FQsIq5vUO2a0G9PBSwfPCsN/gARZOBvSPocKVh4nZx0gNUaTsu9I7Y921HE3GzJ/v63YAZVqargNF8UyaG7ZYwg+/KP0UIMllmvpBL0BjyuRvLit7aAo50LREArS9z52y0rkX6RZnas0ApkYSpvRy6hlMcGX29h6DdMWbXq/IOSvPOHPzBUtyHE0A9GrgkQ2rsZFo1NIURctaFq5TS4L0FuXH5Qx+LeJUVAcm5ABm6ZbWMwFPjgRkRQ0GaGIu9wbEbGq6grUuirnH6EXMIjeJx3abyGGaXdXyLMv0O6QD5CuadZPZNQNcGIDMl0Fh7ZrbsUgaruJoBHEt/BK+akMWN3v3Fz/pxKtFYDmdOwKO1wtbHpsqszO4RagUMcZep7yTAkb73TfJk9alrFXdhUI5v4cmlLunsgcw1yWbT14LTgcYhQ/+kt4eINuGd1R1NVr0y8QCSbe/K32k0p1Hbdk1BfMrVStEyjtcA7dMeaNfCTheKA5fPYFRA1lJvckypWSJzU5hqwKFRvxX08AnLLVN7VnJjzEdpyHB9m4ePKGb4x28SIJpRP2RksuhrrMB1pjRs5CnKbfILj4fKBmf6+QAXcyvHokyPL0+/3bELbG1vgWAPFMM2wezI37EphKSMu74czrqgV5LWx5kDP/Hb7raxL2xXNgNWR42zDjypUc+JqP3rKN/9F4LeloVxAi7NmFjxQ0MWaWbd5Ddy0WhLmMZlMqofOUTujUqdhBb6w7DX4woUqNA53bLD34h3RsBrhgU4YpQqTl/ZhrWo2uGRYxxbNSdeJ3DE8q/SFDcNeM0INbaUQI2t3sBXfilJDPbl4R96Mm3vhBHpnr6TM1DmmkWS8EQMolZI2JE2rpnjp3cMTim738JNRzpJ8bA35RBrfRlWXqodQ5K/+2+pAV0b9RkmlqRqq01dIFkMaCT3qU+5kGQ6g0P7DVtbatVhgeYJI9rdy9jPZwUdjtK2r9JXI6LIXjtjQpDW00QXcnQGkMbplMDLzG8FgI1FsYY7Oz0w+hsMk+k8VQyAP3SHTZenChF+MhQ3nsKKKhWmcDxpXmvn5B02YuvoKlIgPwbxs+KbF01Bn53ATw7HyAJXet6X4UMCfA5Vpcsiz2v9PnhdDDrhwXNO59F6OL1qu4lAbY013R5JMYqtb25It+V579hFereBYdsyi5H7iTQqZVgsg0wPh53hNAk9PwiXd6oAuBWBOASBbUZCB5wwq4lxuojTjbeSYEo5QGeMwcrubvH+4vz/Sw6ljZPHxtJIwe8yMz2S/mx1qRTODW69E5HGbf9Omvio04CCafCWNY4Rl1oHQDlxRNbw6Rg5jK0OURZbBZRmGD9RoJiQqaucsmQs48ldqACSWUjr0O8hETxywsHWAZkiHr2qZ3WKwFFW2OtVssRmpAJG5R78PCXgWgUaTHBfZR+AfcVrXJ1DT7T7uCK5ib6Y97y8QFypIoz63Bpm2XsKXMOFXtH/86mNr1yzBdyGLnlEE2UFSZEOo2DYaalnQ3KlrxlQtNUV5khrqE7HpKW3XlNmcorlVRXxTTrpXMGaE7kTlINX/grC3RCMS0TuWgdM0ZaCQQryIMhDfy1ebqyXUYd0rNQX3+2jJskcMPQcbkxunwLN0kSMP5bHPBCjVbVKxo2Sc8153LKBsqBUV+jGjZJuZ3ypNopPzLVTYx33/s5OYXSESt7MMOa2lS7SJNLYjZ52l8zvc8KQCDsOwJRkI1B0fReLoPGlLvRLuSjZgflESfQjbV2iHt7iYXc4Vp8kdrOzc4qdY1QsFrA4Fl0WQ5IrXNXB7EJrNSl0yHPxhHSr9Ve31nzTNH9qb2JDnN1d6Csz7Pn3wvs7+apsgwcFqZptpIL0gxN9l6onT8fm9el+1RhdMwDmDlAbO2gNwWAjNwMRAIf8xnFms4t8lWvFyJzzvskR+z24sf0LWUNa/RXQNTRxuCiNkMGZFL3p0w+/woRhz6koAYndtO3aUTk1NK3E0DunVE4Jafm7SEzi+xXfuKvI6ihTw+uBN3rIVjwS5EZ2ayHZjdrEBfK3/eLpzaE1H52ntnvcrVyjBASLlT+GI7k8tzxRjfLsNLsnQBKOhW7sPWZQJgdXMqtjRNKshz/lM+zL2PpQb6T16Lq26kPxmeIEhlP4qm7S9eOKrnza7AKGApd4FkBhCP7G9eUWGfPdG1c3I5iCWb0yuN2dP+kYpYT8kJpVyaMbeLYAwaufuO9XknTY0BA97kystWhmXDGGTyXtGPob0iBhbls+1TnDxhjO4bZm24TdNY4I9Ze7Iw2YOOX7uUmKb2lGcsaSs21tfuP0jhv6jXWZI7M8DrvL4AHVaDq1bUqmGHh5Qe5V8ahn+8nPCGEJnV8aNLCwqLR40Z0Q5hgtZFTN/mt4snX9pKtJNy6kIq9RqiBrdJ8ihAdUFOvsXx7C5Zus4x2YyA0M42r5aS63laufY6K0pxfLH8nu+y2NtofQLy7SppdUdZ+asvK1O5nkLQ1QVftTDJyUk1+8pxzBMq0IPLeqoZxKN9NP0CivmSdzQNJ5ANQwc+gz84y9VPxIDA+e8WDKZLGzemyEXQIeCONNGO0gUvxYQW81+XCJpvAmORTOcIB/WQfMk2nLf5oOfVPIkkmL1Voon9MWmEo7xJcGKuuC2FQgkhLhxesfldZE9zyUBTwIUBXwHaNX0LZdDMW/TS1r4ulpOaXdfpTB1FNbrSq+5rfu0JoX6MQDdy7L5syOK+/o9nwoNuEprpTvEp3IoM43GMYqG7GnPKxVz9hUiC5w006dZXptZHZt63U9tAYUf23BYXwsd5CyuYVC0F+YvTknbJcvbjWcaCUpmY
*/