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
avDYuJcmZJKTESHxBErxxff9Pk4M9Bw2npexopMe4dHiYQU9xFhsXIpYMniv4DnhOCeqetJNm7fgXPcjqn18mLlslFsEcJVGJqkFgyjQLHG8f0uqtWR1a8ZKezAtzTp9i2dx/GUbrz35iVP3ckK+RN+cWjHZKd3rx93P7Eez1J+y5mgyp/1lEL/TdmiB46OKFzt1RuON6c1rgCT43fwz2fvRKJc3CVO1M2H1M7mlcbMOMyOQ1rosOI4vpvci5VxZPY1vKCIYQSYIBNcV+aB5D/XOn6y8QyQhonpktpmJsZwROxniiAurgisMv+kHVPC7uMRxGrb4yE2RYtM9JUjbPbaq56BODu7p0oPodzBqt0AvX811eBOQhu3YZ58px8FHD0zKjvn3aPjlGkyNYjf2ZNO1RS2r1aVGZZKpq+NLahufBBj/cHbE0OD5lnBQ3lM2pX68bfa7RRUPD1FWzO3eWzv8RT5vmhsJEBXunFvTbZSkKe/Zl+FRhtSiIU4copxhU8lOlRC8Y5R94X23zF+XTzAS/eGQRAe5ReDMUzQS8rD/jDRyBB8ALV5qtV9yT/gg/GcVzpEiQu99Pt2cdiG8+82Ekf5W6D1fcvx1OdvaG0u4iLNJkQIg1a47D3IDduS6zBmKPYLSqvPTxZoQAnUQ2bvb3GOE88xPeUfwMO1+qKH9GjHZaovzrCtT7Tzkr7+zXsAespW9j7TPVkVF
*/