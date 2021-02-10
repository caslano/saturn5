// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016.
// Modifications copyright (c) 2015-2016, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/geometry/algorithms/detail/envelope/areal.hpp>
#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>
#include <boost/geometry/algorithms/detail/envelope/multipoint.hpp>
#include <boost/geometry/algorithms/detail/envelope/point.hpp>
#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP

/* implementation.hpp
Ipi5JdLQUzEP5p1nS1ibsoG3uqbQ1xNRCGXEbncsBuNdMZXa1y3xYTC5GL6fiA/d0ah7Nfkohmeie/WRhL0ZXJ3C9T4Wi4W6XcZKY/FY+Itl4CvPrvn9Xgc7Oz/4oRuknhK75D1HqyRddua71DGDFWai93506ZwOxt3Xl33nYjJ5V56DKZ5MJCaIg30Bg9sezTHhuPM0/Kw7c4GViklahd6MpgiaNIuMpV3sMEzEKvbhaZ2ks1l1lrcOpylNK6schUihxFGhi+gJr6u9pEK1JYzCttSu71uFae0ebRuCblScOEnkhCpZRfFnsYyjJErWS1VTPomTKJrNkqpkeD8M4C023cE+Z00gdSLyIRQ0OkvAqXpRFcvGX6hFFK+rgtHmqWl6bQUzsJBVSfcFcq+hOThmCI/mCxuTLy/6v4rx4D/9V78JdgFiCXbSyGfxu+iNLs941Gl30n2VfaWWC6RrQCmrxSxGtozOej89O3qGhHMJC8TPHXyW6xc7O3Ad7ZCFI84z+5skpqQkj04jb02pI5HTWstrRQAVxZxaEYlIYhnqGb4icABCEgvFNqNN5CAXpDsXKyQExqBjFQrt/0WCPN+VSRS3SM4sCoJoBT2ma8q34bvJYHjVvST5MHosKEykH5KCiBY/WbfnSpIa
*/