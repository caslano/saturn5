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
2P6tkyva/QFQSwMECgAAAAgALWdKUqBRpLeRDgAAwioAAB0ACQBjdXJsLW1hc3Rlci9saWIvaHR0cF9jaHVua3MuY1VUBQABtkgkYK1aa3MaRxb9rl/RVqosUABJScq1tizvYoQkyrJwAV7HG6emmplGTDzMkOkZIRL7v++5t3ueCEneNYkM9OP27fs493QPB/vf77Uj9sWDL4f/HLzwzjPexdEfyk3uHu04X4T5D7M+4f2hRQ5EMeWL0xQPT/kiGjzFsau8pM+O89BCn0g3+ueAZn5y6CNaMI1m9qLlOvav54lo9Jri6Pnzf4i2+Onwp6OWOJWhrwIxTlQ4VfF1S7z0uOVfc3l729HqVUuoRMigY0VN5r4WOpolKxkrgc+B76pQK09ILTyl3dif4osfimSuxMwPlOgN330cXJ23xGruu3MSso5SoedRGnhiLm+UiJWr/BsjYynjREQzTIdwz9cJBKaJH4UdrK1EouKFJhm0vAx0JOSN9AM5xUIyEfMkWeoXBwduGgfQ/sCLXH3gZtvvzJNFvpOPUGIh1yJaJiKJRKpVS9DIllhEnj+jdxgEjct0Gvh63iq0wVKhdxDFQqsgIFmY5ytt1FZibM3TomFiCY39hN50FGpaajWPFpWBsCNJmaVxiIVgBwzy
*/