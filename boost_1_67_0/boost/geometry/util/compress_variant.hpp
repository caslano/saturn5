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

#ifndef BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP


#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


namespace detail
{

template <typename Variant>
struct unique_types:
    boost::mpl::fold<
        typename boost::mpl::reverse_fold<
            typename Variant::types,
            boost::mpl::set<>,
            boost::mpl::insert<
                boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2
            >
        >::type,
        boost::mpl::vector<>,
        boost::mpl::push_back
            <
                boost::mpl::placeholders::_1, boost::mpl::placeholders::_2
            >
    >
{};

template <typename Types>
struct variant_or_single:
    boost::mpl::if_<
        boost::mpl::equal_to<
            boost::mpl::size<Types>,
            boost::mpl::int_<1>
        >,
        typename boost::mpl::front<Types>::type,
        typename make_variant_over<Types>::type
    >
{};

} // namespace detail


/*!
    \brief Meta-function that takes a boost::variant type and tries to minimize
        it by doing the following:
        - if there's any duplicate types, remove them
        - if the result is a variant of one type, turn it into just that type
    \ingroup utility
    \par Example
    \code
        typedef variant<int, float, int, long> variant_type;
        typedef compress_variant<variant_type>::type compressed;
        typedef boost::mpl::vector<int, float, long> result_types;
        BOOST_MPL_ASSERT(( boost::mpl::equal<compressed::types, result_types> ));

        typedef variant<int, int, int> one_type_variant_type;
        typedef compress_variant<one_type_variant_type>::type single_type;
        BOOST_MPL_ASSERT(( boost::equals<single_type, int> ));
    \endcode
*/

template <typename Variant>
struct compress_variant:
    detail::variant_or_single<
        typename detail::unique_types<Variant>::type
    >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP

/* compress_variant.hpp
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
*/