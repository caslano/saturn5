// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010 Alfredo Correa
// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP


#ifdef BOOST_GEOMETRY_ADAPTED_BOOST_ARRAY_TAG_DEFINED
#error Include either "boost_array_as_point" or \
    "boost_array_as_linestring" or "boost_array_as_ring" \
    or "boost_array_as_multi_point" to adapt a boost_array
#endif

#define BOOST_GEOMETRY_ADAPTED_BOOST_ARRAY_TAG_DEFINED


#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/array.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// Create class and specialization to indicate the tag
// for normal cases and the case that the type of the c-array is arithmetic
template <bool>
struct boost_array_tag
{
    typedef geometry_not_recognized_tag type;
};


template <>
struct boost_array_tag<true>
{
    typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<boost::array<CoordinateType, DimensionCount> >
    : detail::boost_array_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<boost::array<CoordinateType, DimensionCount> >
{
    typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<boost::array<CoordinateType, DimensionCount> >: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<boost::array<CoordinateType, DimensionCount>, Dimension>
{
    static inline CoordinateType get(boost::array<CoordinateType, DimensionCount> const& a)
    {
        return a[Dimension];
    }

    static inline void set(boost::array<CoordinateType, DimensionCount>& a,
        CoordinateType const& value)
    {
        a[Dimension] = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#define BOOST_GEOMETRY_REGISTER_BOOST_ARRAY_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <class T, std::size_t N> \
    struct coordinate_system<boost::array<T, N> > \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_ARRAY_HPP


/* boost_array.hpp
j3wPDz0nU/tJPVssWN9StJ+kPmGu9UnPyCTvMZP6IGb1ln8xk/IOOetY8lfP0rTPNHbm7YnJvSWN0ueL/onq9PWuc83SEwMJOT4AOQv+d7S7xq9C2928kkU0PK/+kHJU90mmH94ueuoR++GAv+OddcvUhSfFrnvEfvTpr9z96M9F9x+xP7L7UNJBvkk6tA89fB91SPNqaAByz99IGE1heVWyiGLUdheWV+p+qDvNeobmJ2LXL2KaPwzks+r8deCIaXbdN9abNLvPEZ2ovrvpWr2WcJ91fzgQmjYrPtIJR0offjQN2odkif6Hw9UD/GhZ69nOp4r++8M+R5wubn6n9cUOo89hnyNOEzd/1D7X9tPziGNB3Jk+NbsZY0Gn+5xmjAWd7hmrOcq/uoy+xdSPt8XdFNU5NfQPlt4xvL5oWXwl7oerzt1F3HeQM4p9rWVNmYx7oqvioqKTOWs5sYVnvbxVwhnc7OveKe57qx507zyT+LH2gb41/Qj1NgOuD2mroyOMc8dFGOdmRRjnZkcY5+ZEGOfmeY9zTR+R1E7P/EDa6Xznr2hH9X8IbUfi32sco277iD4d/QnRnzzcGEb99PSlaft5TPQ1vlH0FQXEbwUibQvTT8SuVcT2WGzikC76AvRG0bf59Fxe9VOYX80bjDRt5w+Lmx/7zrbuzHJ1v7YzO7yuOhaw/eu56Y52hjtnOwgb9zjbmNNtcfg4x/SZD4q7AfjV+4Tonbk3JUs7yCI9OSnaDk5KOMFqBfSVnu3gNfF7bcR6v0vs681YPiNC3fY621Pqafi4Qeupd33PMWOCYHloPdVxgTOfed5zjit0rLDgj8RZ67uzLse31/UzWpdzkQ3kb+MfQ+oyz2zlFUsd94PCKtKgeWK772rGlK+JPpleye8YT1RVFljlq++ifiJuzmI0H6d5b4eTZsZmu9sdbf9BvIJjKb3/y3Vdz0pbOwQCKEJikdma7nF/8kx37rzS/PlUt/D0a1rOEX9TNT/scJJD067pVHs0u/1PFX0W8XbWOfWj974scfOdsDp7LnZni91sqeuJlGlpB63rvRNOSBjDcfFRiZ51fZ7lj1JK0T4/T/TTyanIz7Yl4maotjXbz0TWXQw9qufb0PJKCi8vU09npAbHsK2Rrjou2x5eXlbnH2ncou6TTP26OSlQv/o1u34Fx1Wy10H0t3d2qfcZrkd/dq/3GcCRz471Pus38tnD3mf0fntnAHufTRv5DFrvs4EjnwH8ruTbx9u2R+V37li/69XXFnzywj03RjpL+Ns7M9j7bODIZ/16n7Uc6eznoz9j+GjP6I1wlrDsH6MNXvqcRt37R9Zt2u/P9VtGY8i6zY91vefv4Ei4H44RvzqPHvJ38F0q7K3hONfP/lXP+zoEj4N/h91Vt9fPblf/49W/WT+r54JZfA+O0/WfEn/7HRgcHB5/WY/ZB3aGfeFxsB/sCAepboXjs9/96HuvxpD9UqZpfLPhGfBceCY8D+aqPhfmwBo4G14ML4SrYD78LiyEt8F58GVYDN+AC+DbsAz+DZbD1sShAvaBF8EhsBKOhVVwPKyF8+FyWAYvg0tgHf9fC8+D62EZ3AhXwPvhFXAzXAlfgSXmPEB9H6B9eWPIvOsUPbevA0yCqbCj6r1gZ9gHpjnCa9LwhnqEl67l2hNGw16wrerpsDfMgISp6/z0OU2fkxtD1vk9rvX1KTgfvgir4EvwFrgTPg1fgc/D1+EL8A34E7gL/gK+Cd+HP4d74S/gF3APbGGt94At4Vsarw32WFifOxpDzg0YoOeqDoQnwcHwfDgUXggnwRKYCcvgKI33aLgcngjrxJ3ukwTXwlPg7fBUeKfaPwgnwKc=
*/