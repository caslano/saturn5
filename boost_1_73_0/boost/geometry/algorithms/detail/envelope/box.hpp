// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP


#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box>
struct envelope<Box, box_tag>
{
    template<typename BoxIn, typename BoxOut, typename Strategy>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr, Strategy const& )
    {
        Strategy::apply(box_in, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_BOX_HPP

/* box.hpp
T36eHjLr7X8ddmQ3vMvS0hAX+PaUxeUQpzPmX0bmyAB8d67BVu/Oh4/8VcwTTiRixTz65/8yXygL+THVvXueNAAprI69qiMdOzlobPP8uvbSIs+BgfbG1rQNOwK7ARzE14Q+/5qWsrWGkR2XTX6DMUS1o4Ek6vVZzg+EkkTDR9VBdLNzoPORP+F85OOoo/RJl44BICh9yqUrQT9N9GAyRH7Uvwl/Tkz8z+5y6zHYdgK9HCp9
*/