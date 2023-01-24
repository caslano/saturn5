// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry>
struct value_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename geometry::point_type<Geometry>::type,
            typename geometry::point_type<Geometry>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

/* value_type.hpp
RF/+vDBlmkAfnTEhVQZAZ9hvzCnXl/4w2MWnCw9L0XQcwZQ1GevnLI/XyZBRJrZqPRed7P1LpqpE1eobTQ3lEHzUMutGVX0Aud0XrZAnh/eEqqzBq0n9PSEYAneR/fBXZqRS6JMnN3CvOlXfDDLM5abwDTOmDlejVjCkiG98anx5ffETO4yB7xhNrOsHGZ4P/tqQCe15gzFyjO8o2jRluYG12QhLviSrWi8IZns77fFrowPkCsmjjGcqmJPv4nETrsbjyYB+7auiumPYpwqLxEyQSrxGJ4+13Z33SzdiEIo9exuhfhuv/ga6uNH/OsYLbNu1x6MtH4ynn+XVumfDMEPphpSRW7ynzxtqeezEcuPHEXxJvELs7icFwRYbbLT+WMUGN2NCV5+XO16BcyM61PvqQt4k1m7jmYIbsnH75FpF+xyVEOL8yWlRSFry9IeNAb+0nJWbk/HSGrt/gqj13NcQ3fGyG2hzmyu4bAmU11KcK3INHuTZOk8GRsd3Hi5qVpVVsc9kuUYIzOsxBrZzOqxdyAgX3d12nOrOqHE/eveK162FeI2NFxS2pmnMmPU6akrJF8LVTyTW6HJf4o7SBBesuy/zO0w7+36U0YvdY4Y2SJff6u/cwPsPzcLPPfqrn+Y6Dznm7u2mWVt4LKcDJRbcD9K0OTvC9QBUNvpa/C+VLGgnJ+/+WfVf/qS2AVS8X/eJJPLzMnm0ugrh
*/