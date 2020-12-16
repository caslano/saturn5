// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP

// the implementation details
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/multipoint_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_to_linear.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_or_areal_to_areal.hpp>
#include <boost/geometry/algorithms/detail/distance/linear_to_box.hpp>
#include <boost/geometry/algorithms/detail/distance/geometry_to_segment_or_box.hpp>
#include <boost/geometry/algorithms/detail/distance/segment_to_segment.hpp>
#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>
#include <boost/geometry/algorithms/detail/distance/box_to_box.hpp>

#include <boost/geometry/algorithms/detail/distance/backward_compatibility.hpp>

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_IMPLEMENTATION_HPP

/* implementation.hpp
tQBONY8uD8IvODmDeb+YfKVS+0H8g2b0UyRMxgdtUtERfeF4As8/8FeaTovxFtUZrMm1kvYQn9RFcaNzpOpteRPNeYVi8LYqPu9JG+YzWxQWn5MBz9E6xwl4PjWOfuhFV/3Bf5XzZFf1Dey7BGcTpQ74PVx8q/48lYs0ZRUx6wiTnbHFD8jTUznLqSdWue5N8baW5JV5w2bWg23p8qny9CHtdAGWNDFL81aq0nh31cEXsOFKN7PDKrhXyv71fK2PxbOQWdj73lwMwFa4fAIX8lz7tHWf/vIHA5vijYqXcGUiGth63u+gcfnSa73vHjyZ9VxtiF9+eB4d33xFG4bQgU9yyccGPOn1r3mGe8upw9P0dzWcvZfugZcLZvF12ptBfX0Pzn26kAdhrSXUZNs8aoNuyQEzJh9W73/Lq/W9GO7cfoc6Pen92cUA/tbERbH2WQPsvZlS76Tl3WfUfxvkzDWS2eueq/AgIa+M9z4O5qafoRbtuUgHeLkE9/9H7na4hjOmZ3zYsKVy+Ds/J7P+dN8NjegCcWkEj36y/uWraTD4NfoI3bnW9Q7DerVWZjd/kLYr5msFdvteKloH/1/IiR/6B5s57SMTD+O6OOYKeL7b9ceYkd7BffU5kC8WNZBmsIe2nXgaeL7DGV6R2Wqs/q3SnKegJ38+4Zopgj0Xrj/+Nm/5PC9M1Mv+HkfAnOY5bLlfrQcj+8KyBnD8kjlRHfQSu1FiUHcEjTPcM0HwqRLuyL9fjtuptx5B9CmuPwnvRplji3v/O/URT4/+ys/k32eo7Tklz0uFqIExYlgDNn/nGtn1Qrq6nv9vG7AZ+WsqN3Tm955VTR4Fg2nhUrytkjC58VPvC9DM/TyL0tV9frGHpmZon+/DqRn5TJXU9CZzQlZxHPUBnqoIM+FjkDoaYRYL3WmOC+Y5T6Rb4Vahn8RlJD87I/69jyuT8Vho/mGj+Swb9LU8pZhPB2cSo7382xpqLYG6nqWv6KTk+jAsgmeWDB5Xt4adZlBz1E+p9WVH2EZ79U3DF44587mAk16Z/11rUcFgvUFffkojVDVjVuE107bXInEbfr5fR3/UUMd1zCBr+WydYcrbAD+IP1XO/lyzcWm1qIb7luZnDsN99EWaAmZR3Ft6PI8R1qSDc79/LMdwYlRqejgKH/NJzWeBzmX0zON/n/0+KxbL/lCfaqgcPJnle7+oqUBb/JnCHvo4v3c+cBJWfbk7SJ84i+IX1ZWrXF47x3t5S4Hz9FRLcdnFr+/Y27MfD/H5TDMxHdA5nl7Dac3b02p4Mk4d1/mYB65eMgXsaYBaP4tbWtGpaWipBXD3nfrGcXjc38rgH1XhG+3yOjzSH9b/1/Vn+xm0YY3oild8okh7cP8Gp73vOK+vqtp5L2/ikeWmujG/TDqNJ67S8v5/l5fUiT9+ZYat4pulF3FCfHHPZt9qOjfc3h8ZoCGD8JbrLoM7M2i8Qvb4hK5cCtetI6V6COlCK+SDq32sY6f8T6JfzfhVB+qj6TgXFwxLDIPbinG4s8cYXh9tPilpvv1KzyYR27LOifHArIM+HwjbLpldYdTUEt7red3Kpflbr/iM4tbkANyhz37EiY1h7akg3Po5PeO+I+Ffosv8HP3eW2+VHERPwreiDWHoMXMhbrx+A7/wAc+p+5zj1Ic5pMEheR4II1wvTI4G/Jf2UR917vFr2vHknplrssp5eq//L/6Wr+Z6r/p0a6c3ZpTn7dH+3XBUdnPOWDEJGgBL6fvccrgwxqu5bG0r9Foj5xzmval0afo+rvNOD9DknZylXMMrV9bxLOPBXPG/TF91yojvrO81TRSL9/ftH/q5Ac+J95C1oPnI/POYlk0=
*/