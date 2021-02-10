// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>

#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/policies/is_valid/default_policy.hpp>

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Range, closure_selector Closure, typename CSTag>
struct has_duplicates
{
    template <typename VisitPolicy>
    static inline bool apply(Range const& range, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_const_iterator
            <
                view_type const
            >::type const_iterator;

        view_type view(range);

        if ( boost::size(view) < 2 )
        {
            return ! visitor.template apply<no_failure>();
        }

        geometry::equal_to
            <
                typename boost::range_value<Range>::type,
                -1,
                CSTag
            > equal;

        const_iterator it = boost::const_begin(view);
        const_iterator next = it;
        ++next;
        for (; next != boost::const_end(view); ++it, ++next)
        {
            if ( equal(*it, *next) )
            {
                return ! visitor.template apply<failure_duplicate_points>(*it);
            }
        }
        return ! visitor.template apply<no_failure>();
    }
};



}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
35miD3GUsAyySwFcr9hwJ3JvFotideevOJdCYfBFquydQVxt3ppHVUSXsvGQrdwj2gHOeH9P+KNRMAa9p48i5Y2N49ECQ2tapXI7TA8+AzXSNx51xCDGMP2rlESMFDFtLWA/CMUUbNju1og1ufL2CabqhECKaefKpboQX+vmp6lzNq4i9S6RdI0h8kfuEGriOJGEOmVqzQnZxtk+4a4pXXFBy9NEaWxhV3iLn3J4LaG0ZC2RS5ByWhnaS7dbs9edRA4XHVGeWubN3DqaVYEfhLWmddJWcfiV7wJRlwm+x6sRhT5DCkJvHdBGpb31Kf5H4BJ2QMXeND91Cs/pNOd/48nR2jv5iieL6XpIL4jFHvw/Nzn82ByegC+ll3o3e09/KRbgkAnlpcdzvgVrT38pls389B5aMpfMVb+n/1qn5bWyyOsRU9hVkCXrqhG7WjXyAcM6c7ynOA7OXN2jH/Ddel93mPQ5h/93/ved0k3B1xtNmzWHcPHSLNsoH+e2duXRXOI5zYIeAJ+mfeJjN4htX8NNQEPjgtpkhJswkhsR51d2qAZMdszG3cX8jAFwB5U1wBTcJiiJ1Dqg/BmTicUyr0drBgoazEM7gK+bQcxnc0zHTjHaasUi7OgpsRo9VJfmTJ5CcWTTCnw1wZWy
*/