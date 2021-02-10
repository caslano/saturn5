// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP


#include <boost/mpl/transform.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function that takes a Sequence type, an MPL lambda
        expression and an optional Inserter and returns a variant type over
        the same types as the initial variant type, each transformed using
        the lambda expression.
    \ingroup utility
    \par Example
    \code
        typedef boost::mpl::vector<int, float, long> types;
        typedef transform_variant<types, add_pointer<_> > transformed;
        typedef variant<int*, float*, long*> result;
        BOOST_MPL_ASSERT(( equal<result, transformed> ));
    \endcode
*/
template <typename Sequence, typename Op, typename In = boost::mpl::na>
struct transform_variant:
    make_variant_over<
        typename boost::mpl::transform<
            Sequence,
            Op,
            In
        >::type
    >
{};


/*!
    \brief Meta-function that takes a boost::variant type and an MPL lambda
        expression and returns a variant type over the same types as the
        initial variant type, each transformed using the lambda expression.
    \ingroup utility
    \par Example
    \code
        typedef variant<int, float, long> variant_type;
        typedef transform_variant<variant_type, add_pointer<_> > transformed;
        typedef variant<int*, float*, long*> result;
        BOOST_MPL_ASSERT(( equal<result, transformed> ));
    \endcode
*/
template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Op>
struct transform_variant<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Op, boost::mpl::na> :
    make_variant_over<
        typename boost::mpl::transform<
            typename variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            Op
        >::type
    >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP

/* transform_variant.hpp
oyHks6dPHfYC/np6Sg/qL3FairsP8xYOKbrvYstkHonAzadA0Nu4JA0fFpKaNmRPpAvW7ETCHQceTWa+y/k0j8eRX/nd+emZqa6JL0Mlx/P5XZTcJZdoiOKskuDtTXdYaTHJZqiwqz335RwPL6IX/wZYopl+TqN353/uds+jXn/Yvfi5c1rpFRgnMX/AJlIaocXCcef4TZeXqekUR2td+DKB+CohiwU8pme/t6sEFunpHyIhCirgg8VarnLk0sH91/jgP98ymAj/jH7uXgyA5Y+eAw2MztJF0lDhWfTMXkKlrA6KFCNGUkiWhknpSjf1FSbZJseswIYI/Dstse35X/JVJ2EvvoWx9hYT8x3XHMgWoVIbjU9x4fxg6VgLLB4jeej/OjJWFDvWGeTQVGrscXA6LNwMhJZrLHHgaH9GPr0gMgVqAr+1t5y/UKwzpZeeWrcVbhzKmIkG/FeyyNEkKhvrvSOAEFOdEbXeedYmhj6fVGbcaonxCpkBOeYf2p4hViQ+gGNK82UhHoVit0Gub692JuyxucMSz7ba7mKlFzI4ShHsgicxkPbjv2fbLUHivjj73TA6exW97b49u/jVKIp8Ewiq2Rn8Gr3tvO4dw/17+1P3grbQf16Mzg63SxRSnhq4ordzXxTZiDUr
*/