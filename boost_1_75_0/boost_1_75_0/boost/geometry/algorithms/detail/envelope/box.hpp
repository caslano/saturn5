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
0jalEdbSbVqjI6xtczbC2rrN3QirbAD7wv4AzggHAzgUzgrgcDh7T6QxJxzZFm3MDUe35TXmh/O2xRoLwrFthY1F4cJtxY2l4eJtExsnhyduizeWhePbyhunhsu3VTRWhitaqgpqCuqiM4tr/dWRquyZk7Gvaj2uD89Oxw3hxrKGs3PCTUm4OTxvT0tja7hlW1vjwnDb54vCS3YkEx/3Al/VnZqbruwhLaxFtKiWp8W0QuIGUItr5VqFNjNS723wz9GatRatTVuk8TPvHob5A+uV+cx71JHJcAwmQKQZwnIIFszbJB3mkzUig/SgcH4M8fY1euK9zWEMm+8uhTHpibzOEW/bpXy5AKr4mqw9pK6QurRUG56E0XLmcpvi3VYxvNt+MAi7HZmGz5F3IXHOweaalzMCSD4P63EVKiaYnnRNHgFrshfWZKdlTXYOyzTwZQOQ+AkEAhx7K/lV1Enwg1VtGvnhwLGboQjnUnTg2NvvtQLHdgzxf4FfEqrFXfI5rByXKylybJ0QE0Nyg1JAfSH2wtDcAsTp+d1dECEYmqs5hiY5u9HKzm48rT/zAkS6hIeFFzCvE6fFB/pZ+JuenX9tYhBdgkSyk6wDgnhtmLHOUF82gvosflxYIeYITWiyQPh2Ir8MaxiGhgFvNOwgqyVq/+PksuckiNRCaIEg6z6FGHNHZ+BOckh/ttOYgQlwz4mhzqO4W3hLFJdJ
*/