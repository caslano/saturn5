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
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
*/