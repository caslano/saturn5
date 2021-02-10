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
PrDtGQf20WCJW7gmE4WsJd2SzC59QMjAllQ9emELktfxnZrejxa3XKkRG0SXjqNIvlvcTojVwjb48q0wSEn1W7t4kRkWNrpAgHWOAkaHUOsa5XOoeZsUwIzbnh7Q/ljSFkKU6jNPobfBT/EVW+Z1To1d/AjFti7sUBNWWemjx6/7omaccEBcOYK65P6+0iZM8yUz+6IL1sI+fNU9678vx0TJz+aXdauCha7PalvhtjX70CzBC/3LqidWxNXDKh4HLSPoPQpYy3otleNWAlqp0+J9VTUOQal/NcSLb2AyTtgtqoYfsNFzoAjt1dTRZnU1SukQ1Or01HXNa1/wMnVsVMIDq0NQH38csdpWRwtCsdJuT/0Ux9PO4Tj5GNOrSQf4G6/UidOdvispo/VPEcwnoNmSF+Y3FBmkoWED2U6h300WVZ3XFpMMU2Ytsljh25CNR2izHaEeEkRpHG+TLcPaqGVNXbnDl9YLejJXa395U3dt1J6aaV5IW+/+AXaRmauyvx0Vln1KXnUX/UGvd2oxZlmi0keZd1qOhkOCvshcpObT2xngnuhcmEsPJQhlDx3OFI1mTY0WZJuAdYdz3LCWXieykbmEn3f09RXIrsJ0VhX5YVFK54OpEwEWSBDAmQY9Wh7RnZU5A/+CS/G/
*/