// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP

#include <boost/core/ignore_unused.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Check whether (each element of) an iterator range satisfies a given
// predicate.
// The predicate must be implemented as having a static apply unary
// method that returns a bool.
// By default an empty range is accepted
template <typename Predicate, bool AllowEmptyRange = true>
struct check_iterator_range
{
    template <typename InputIterator>
    static inline bool apply(InputIterator first, InputIterator beyond)
    {
        for (InputIterator it = first; it != beyond; ++it)
        {
            if (! Predicate::apply(*it))
            {
                return false;
            }
        }
        return AllowEmptyRange || first != beyond;
    }


    // version where we can pass a predicate object
    template <typename InputIterator>
    static inline bool apply(InputIterator first,
                             InputIterator beyond,
                             Predicate const& predicate)
    {
        // in case predicate's apply method is static, MSVC will
        // complain that predicate is not used
        boost::ignore_unused(predicate);

        for (InputIterator it = first; it != beyond; ++it)
        {
            if (! predicate.apply(*it))
            {
                return false;
            }
        }
        return AllowEmptyRange || first != beyond;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP

/* check_iterator_range.hpp
o1Ou9nLnW+cu6pQ5KcTvCh5CQsJeWH+FT0P51qtQl3R4nDSyrlwfVcO5NWcjyMaFNffa4QLkS1tDo0j6AC1kvj3cysOisI7sjfJrFw6HkPHaa2NRk1cXNvwPDHjiCRneBhEBXc3UTPQ82v1S/n++kvTGNXJ3PDPSnukPgjsPmhW09ijgVj9FX7apHy/up8CPyZTR9FFWAbqkBiFY15liGLin82uv+EdSWmHedXybGpA1/kj1IhQPf7kNQPOeU59MVnLp1T9WXie3bCr+6zYRcXPPjhcg2c7F4wjBPzdF4BC/OKx+6J55MXcPXEo1vCgzvu25Cs44rN8nFGtn1AQaM1FshrQjkBu6Zw/UpjOKszz/BMMXNtTlSpvPIgyc1QWfIwESf41hNB20kaSx9mSabpZ+4l6Gg2P840ClvAfheVCXthv+ZBl1wsbtmSYKZkCNSVo1Nwg6oWUwhJYR0Fsg9zvpq+tAvcFj33WkJxIyRIwVgF9OH7Dk9chWTUGmaRn/+jNvze2plNKgkCLWuTzVL0Gqm6yWMn0PjZE/uLKsUX89qkU/ud2t0L40cw==
*/