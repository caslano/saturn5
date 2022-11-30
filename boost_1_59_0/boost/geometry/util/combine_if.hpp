// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP
#define BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP

#include <boost/config/pragma_message.hpp>
#if !defined(BOOST_ALLOW_DEPRECATED_HEADERS)
BOOST_PRAGMA_MESSAGE("This header is deprecated.")
#endif

#include <boost/mpl/bind.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/set.hpp>

namespace boost { namespace geometry
{

namespace util
{


/*!
    \brief Meta-function to generate all the combination of pairs of types
        from a given sequence Sequence except those that does not satisfy the
        predicate Pred
    \ingroup utility
    \par Example
    \code
        typedef boost::mpl::vector<boost::mpl::int_<0>, boost::mpl::int_<1> > types;
        typedef combine_if<types, types, always<true_> >::type combinations;
        typedef boost::mpl::vector<
            pair<boost::mpl::int_<1>, boost::mpl::int_<1> >,
            pair<boost::mpl::int_<1>, boost::mpl::int_<0> >,
            pair<boost::mpl::int_<0>, boost::mpl::int_<1> >,
            pair<boost::mpl::int_<0>, boost::mpl::int_<0> >        
        > result_types;
        
        BOOST_MPL_ASSERT(( boost::mpl::equal<combinations, result_types> ));
    \endcode
*/
template <typename Sequence1, typename Sequence2, typename Pred>
struct combine_if
{
    struct combine
    {
        template <typename Result, typename T>
        struct apply
        {
            typedef typename boost::mpl::fold<Sequence2, Result,
                boost::mpl::if_
                <
                    boost::mpl::bind
                        <
                            typename boost::mpl::lambda<Pred>::type,
                            T,
                            boost::mpl::_2
                        >,
                    boost::mpl::insert
                        <
                            boost::mpl::_1, boost::mpl::pair<T, boost::mpl::_2>
                        >,
                    boost::mpl::_1
                >
            >::type type;
        };
    };

    typedef typename boost::mpl::fold
        <
            Sequence1, boost::mpl::set0<>, combine
        >::type type;
};


} // namespace util

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP

/* combine_if.hpp
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
*/