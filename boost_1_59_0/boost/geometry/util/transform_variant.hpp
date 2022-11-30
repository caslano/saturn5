// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP


#include <boost/config/pragma_message.hpp>
#if !defined(BOOST_ALLOW_DEPRECATED_HEADERS)
BOOST_PRAGMA_MESSAGE("This header is deprecated.")
#endif


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
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
*/