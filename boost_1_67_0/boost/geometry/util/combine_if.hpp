// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP
#define BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP

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