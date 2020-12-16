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
8FMfoXAxd8oF9zhEwFEfz4rJd3aFbmT5Kd2cg7aPaDlP56q+7nlSZoKfT2HeJ0W/5Zu/F/j9MMStVv5+G8HCY0h9ZtVtwIC/I3p+69fz78i9MNT20K5/M1q0usFv6GODsg/ixf5J6uBi+JdVwEd9E/ij+3SXEC7KmfLp8LKqXZfl/DnCibyTq4D8l6v+73ixBv6B0vA7jFciD5+P9slkf9E++Qso/8tF+X8JPKA3yp+jW63O6V0tyvo84MhzXtdyfLBvWLbvX6F4pMHtrT7L/zXRB6CykX0JylOY3zdjHIYtwk61v6S4bwmblukcx+lQnOJLeuDx6ILos+Ow4QRtdA7u3+pzbT5dOxzMg9wkbZh944oueWxcQ+X9b+9TY+bvibz2qbbgVoSJJny3BPgQXkiPt4sxkD5rqNvmOykszzhSuQCXz9vpPpTV0A9lm076Rjuj+17goekneT8SfTB93lDv3b9X5Ufy1fm5n8LynoAqdfYS+SPbG037QKzgfuwMGYBftAyQY5UHld99SPndh5HnR+ivuIvO6srDWQHxJjiHTfmWqrsAKu3c5SZ5Z2M8lR3EvIB454ffBh/gcNbj/ibf2Wv0shB+2oQfjdmzPbQghTsE0F9rDvprvFb4c1EX2ovQFWwVOgnOmsnwDBVPOgqFSUd+mPX9KOJI7zbuceG/CEbyh+vJk4I2O1HdxwheBEed43th5B5Tilf3EPLcj6Qf7z2Lss+oc6fPKXyKt/jPC9/aVQkcdYfNi37+IL+eT/qTiO+N2Gv2ZxFPPEfF/4X1o+9VpEuikZ9XY2PuF6prWNLdVbekleeMFJT7ia+LNuxv4Ouv4c2Qb34iPMEL34Xxmhs79PeSyfqwN6zvzvYOiTF0zITdFdOob+4Ox4Ge3FC2Oyvqod1nRO+OGGDw3uffhb3P5Tzq3Ll8hc6YiHXXI0Ud9+dZ3pLrvDugO9EGo58g6wjt/44VPFMeLTvK5F+iTP6NMkG5y74Z+1XdNyupcXbynDrzBXslutFzIhOIBnhirmA03sQa1Nkanm+wYaJBux/Yd0sZfcq+dwF9M3xLO975n1gqZMV8s5F31xrwEP223QQPvceVYDyPrM+LltVANuDdUK7OVkNvFBfyF1U17AtEurQ+BPy3FH5M4b8F/BqVvq7700X8WxHx70W+X+B8B76iQ+aFZKkFLsEZd1+5p1qddaG1icT6eMbUDV4Lmlkj5iDHPOODO3DVHs59alxfeYvYg7VfjXjTSOludo1ZX6DPtzP/jDaFgUNpuDIZKAvjHAAaipftBYXDaRzE5SPwiX6u0D/BRul/HsXz21Kq33wI0ib4qLJpVbiHApfgUk6iDcu5SMlJ8VbOw2F3rQr/SMaX/Mmn+vmC3Dpfi0V8a0T8EqT3ttqv20Bwma9GhAku80XhsJzNLKfAJzlbhBwEGyXHMQQ7rsTf20LbE9pb69aamxlblnZ31tetoKc+GrvbOhoa7dLIyhWd7Y31LU0tjQ04E18yJk17R9vSDnozgCZUQDNuTBrzLlRHa109JfPajtN0r2xvb+wgIVsbmlo6Ort8HuN3hEdr2+ooHt7Wd8Zi0tTWQTfqriRe8+d5q2jfz0Ts+1leM6aG3TagMZDINdB9LnLucSDRy/sX3F76EVo6zsaD95jbQn6nJ7OZbtCyVL7rkSD0b/19a3tbqkymeyB42+C4UmM93d0EpQdADrawCpO2g9Hc/3reD3E84ZYy7jzvKKxHHytkor0ZtAfA7Cmg1JPpHjz9r4EF9hgP9NPVYckNuZSfIwbIsU1nTXjtqqvG0fr73mbaPNBiJaVK8jOs1MD640ME47HzSiF/DDo9pSeR7RaDBgXNv54=
*/