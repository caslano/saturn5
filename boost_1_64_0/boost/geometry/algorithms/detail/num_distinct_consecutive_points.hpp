// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP

#include <cstddef>

#include <algorithm>

#include <boost/range.hpp>



namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// returns the number of distinct values in the range;
// return values are 0u through MaximumNumber, where MaximumNumber
// corresponds to MaximumNumber or more distinct values
//
// FUTURE: take into account topologically closed ranges;
//         add appropriate template parameter(s) to control whether
//         the closing point for topologically closed ranges is to be
//         accounted for separately or not
template
<
    typename Range,
    std::size_t MaximumNumber,
    bool AllowDuplicates /* true */,
    typename NotEqualTo
>
struct num_distinct_consecutive_points
{
    static inline std::size_t apply(Range const& range)
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        std::size_t const size = boost::size(range);

        if ( size < 2u )
        {
            return (size < MaximumNumber) ? size : MaximumNumber;
        }

        iterator current = boost::begin(range);
        std::size_t counter(0);
        do
        {
            ++counter;
            iterator next = std::find_if(current,
                                         boost::end(range),
                                         NotEqualTo(*current));
            current = next;
        }
        while ( current != boost::end(range) && counter <= MaximumNumber );

        return counter;
    }
};


template <typename Range, std::size_t MaximumNumber, typename NotEqualTo>
struct num_distinct_consecutive_points<Range, MaximumNumber, false, NotEqualTo>
{
    static inline std::size_t apply(Range const& range)
    {
        std::size_t const size = boost::size(range);
        return (size < MaximumNumber) ? size : MaximumNumber;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP

/* num_distinct_consecutive_points.hpp
+AHRx9jXHOx7eCNIwma794E6HcjxurUSdyAJ2CNVgXrU1tsPEWyu196Vok3eadDdTbAFXkfXumQ648OuqLLnIv1DfzzuupbgzQ5uDl8C6XDnV9m7yolLf98mATvJ3cfF4U51H9fNBEt52bvYb6DwoL0jPIGOSha+BXDbqYGM2wm+1cGpliaf7kqa0/jJfsh8lPDb0J6v7c3eX7Fd3WdxlUeaD7RnEjTclGs3Ozw6penAfC5wpzoXaHz6TnMec4PH4fu83uRgxp0TPIAKx2NVcm0ZJRAuxSF7r2nu8pzq6narEkEQ7ih1vubeCGhvM+kw9UORORMl5I98n/UDj4lFn+Xnoqx/XdQXv1D1xZNV9FP1xS9R3p8SPO4X399UdeEziP+rKqfDs4j/nKIzeKnrb0D3W9FOsI3fRzvh2/l3Vg8XYRHs/IK0M/FuTZvqRzKyVg5DWN7zcrWxIHcsFAxt0R+CfT9+u+GV/YJ9vz8RnW+vPyp7vYgwwTEHK9sg4JGvhsbAZb6+jPgkF3c3g170PyT9qzye5T6N7J/o8ax5uFz1gdxPtydvCj1NPaDfm/mHwg8ovf4pbPSomlP8F8aCpp6f4EC2fIwHflQZ9tLvpu+U6NhEjQCdZlneuDxBFRSyVoOtb0xzfkd2gU9kiMD8QRvy3yr35kOPZUS+hPHde3KcImRqeQBxP43qOnkHF8l1v6JJsg8J30HeDCMcfM/aReaL05vujyAaez5kkugbgNfQOFg7QJyRk/R7I4oe/r0P6D8A+nrYroTCntdjrkk3ibV1+t4EG0nzjAxE/T+K4DFvbX8ySUCsQ5vx+AcJzmeXCsxD8ieyq7i/dJK0sbNtjH6ULm1j9v9SwofWE3nnbVGsbFJWh32lTUWZ2o/gss7YHzYdA/qlueuqFc2NTS0tyxItq+jI9pFQJhSHuuuAScF3Rd0bG7729OiHfy+M9fMN7i4mwMptXplb9NF8AZ6yb1osPJYGIEsaEsuW1NsBCrfv5k0Ten/RcfLp4377TN217Dy03VNAA9yEPWws+3Fzmf+iGRK+IAuvlX2KxeYNCPGGzVjSvdnA6J6jerwBc6DwsTUiX22/g96uGeTMVfAFC3Zf1+TBw94fi/yw84STuN0P1OUED76FBh85GHEl7XhFOwFhwqmzVpovjQ8pDJy1l2yv4ggTXPIx/sQ+PsXpwzxqFP+pk5Au8C9Xd05/VOFT6szcDB8P3gYu3z+YSTC5N+MkehNK2ka3PXOIXuJ12zWX8Efn01dINCxrrGta3ZxYsqpxOTI8moDr/nki703bh7GnDd+swudzGDpj3KrX7o6QNgc9+gkclml+VPUXG5RNblb4RoU/X+GPJDzXcRFrh0vYz1zfQ/rZUYY/+p8IM7/D6NvA9fxyE+IYvD7jaWDPc98L94NyGsBTpaFFlhn0rWRYl897FP9jUD6/hHG5bYMwf2H8cwDtNjW5PJc8gJ3E+CbUJnc2YxLv4+I3FU4Q9dbI4v72WfJCFAT9MfMXAvw7p6OOhIzOGSJMcjprRZj07ZwpwzGvc5YM7+s1dctwudfEY877aU51nNOb8Se4dUdeozpRpOMkr2Vxne1n+QkR4cg1qtxpH4+077S+nx3PnmTbsfVubhT9t1bZ3yhe1Uj7D1c2zOLZdgng8vup0uC+p/ZJ0W/xdEzKzqlPwFqJKZMfi4FW3pUK/1kn+wyCv34bp0uUp8tUH3o94eR7JTGsXd9YGhx33KDqm9sR1vXFDaqsnKLqg9sVPk34qD2Kf7R9jPR6+IyNH3NzAV72XaiBVKavw/a/52FNYEDkVUWe43Y/jzI8nhL9auTRRqNrmJ+9jzGmP37dZHU1aqS9eRg=
*/