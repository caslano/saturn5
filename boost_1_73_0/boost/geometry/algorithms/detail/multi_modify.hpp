// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename MultiGeometry, typename Policy>
struct multi_modify
{
    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    template <typename Strategy>
    static inline void apply(MultiGeometry& multi, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP

/* multi_modify.hpp
p6oWjPPAwg90Aetri006zEawI5sRg0853OQD2+66AdYOn0bchDdfKDHqXnAGff1R2bsRZ9HxeL32ON5m5wTTmMphex0GbNtQvA6bEd9jdkVovxZ7jMPOVNBK5oGN9aXoaG4ZR2P2PKrbrUhjo0AugqzF671PlJ8q3h63OQwnCTaM8VJo5PaDbV9U1u2fD9lc+iSlOxs7TN9N6Wba8TyHGC/4cXmeR+nK5YG3tU8F7P1GdjGb
*/