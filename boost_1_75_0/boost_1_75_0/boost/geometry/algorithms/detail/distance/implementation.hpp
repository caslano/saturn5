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
dwos82vZiXNUD17sbvIUe2O+8f6SwCmXP+bbB8fDNDmuFKqLtJn6eGOKS49oH1LZAB4s4dPNrQcCVDfC8fh7obMlfxR0djRUvg+l5Y8mvqjIT1MnLBPW4dechqmHxl1/tEhvyRUvmiJ7XsSziF9KKAuw1KYWKCXyQlKlcJtEL/c+at77FFT+BuVa93s3CxJs3buJ3/t/ut17Ykbq3iOwWqiU4GLbvZkOztsDdy/RKfboKKjMpo1OG9a/pfvpFGH5/FAwfbWxqi3otPbyE/CCBsl5T+NHmYGmWFmiFmrj1aUwCTETaY95FTEXPAv7uJtP1plO4Z/6ClTSzsK+PpvCh04ols6s02Zd4Oi9XXxMmWet/U8x3TersdP4NCkH+f6I1oyjWqFaoiTYmBJaOk0EH+MOmLKu5ap8vtjYjB5jm3lW7IEFUHkEyq+/eGxt9rHtto2t39wcdLlf9DTuYiNb0nNkC9nISsXIAs58n1ehq8gncBl0DtaMNoQaMuve8aL8Jnp5mho3K3w5tsSf+Ihmt00XwM/qhsMFZ+LU+uzm7zThnN0+AY27z3F6M/uck95kYqAg08Q6C8I68znWWds5was/DpXLUP51LhUjbkIQ92VbEBaEK0zF/uY5Jy3ekRncjaUZckRaptSpEWWRNgk2frOyEdVwjbZmw3XpQ///J1P/D5UlUFr/lNL/OzX/1XbNvx2Cr07o//9kvdxp
*/