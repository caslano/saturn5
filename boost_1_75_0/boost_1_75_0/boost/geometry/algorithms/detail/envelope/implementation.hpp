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
12x4A6oQ9oiaVIC4P0Fvv/4EHwUq9Az4MxD5K4TPIaiSTA5S1edaESEMIOMkPI6e7njfyENLdxg4S1m7XZLDyllUgV0irHNyMdLPoH8b+kW27hc50S8i6ZyvvQ0izRD2Q3BZ8XkZh0+wXg9H5e2tSeS0/XiKW1O/l/2k2URV1ZbDq7Lm2AA/2OF8kPywztMSXZZAcW3/H4ivT9WX6t/e50Gvqf638bNiofyS0qCesGu7MQVIqSPg5XJYbdVcvC/NNvpSD1AfU/nTIMVs7er7P3Lx/2WIdEFfWzI4Xmuey8QHlUDixy62Fk5xWfvTu1gM2NBUei5AH6smnnOpmc4aSOzidDb1ovOVeBtGxbgmkScXwWxLYGBR/Y+L9/GTEEkZnolGQWD+uLoYX6D74DKjE5vhvujR2AD1xpU23FCcLAd+LnVI6Dl8SozJMTWqteFSx6tazNGt5Sl+KUdshs7rArEph/O0o4Cn9QNP6+rD0zYP5/zYYojsgfDM8EzDDxdDOqL8ve5xnf7DkBuYv7r9RsaS8BnoDlNCxW/ifVicCRlZLk+wKYux/IxNzSEoQuzeWJuyAMtbyb0zEDwYLm+jBtpf/Ioie/lvPtQt8cN40MCcdbtB1h8Nl3IIs926XELO+LNffoa/lZ31506up1HhpMptzO/fa/egMZJzO64VHhSbIFfL5DeVHHkjfHlA35nb4X2KrbIXIu9C+Myt
*/