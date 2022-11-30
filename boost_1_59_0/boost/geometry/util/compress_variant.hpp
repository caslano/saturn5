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

#ifndef BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP

#include <boost/config/pragma_message.hpp>
#if !defined(BOOST_ALLOW_DEPRECATED_HEADERS)
BOOST_PRAGMA_MESSAGE("This header is deprecated.")
#endif

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