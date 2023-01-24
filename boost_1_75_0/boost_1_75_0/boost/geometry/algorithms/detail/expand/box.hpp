// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + box -> new box containing two input boxes
template
<
    typename BoxOut, typename BoxIn
>
struct expand
    <
        BoxOut, BoxIn,
        box_tag, box_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box_out,
                             BoxIn const& box_in,
                             Strategy const& )
    {
        Strategy::apply(box_out, box_in);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* box.hpp
13C4gmMSnYDIxxVsn+sk/ArDtcP/C8Kia6sHbcWYfO9vEBXX4efREsztRkYiN8gbbpiD3SAn63Yj7mlcNqbnHyCRN42ffyC/Se3qNg+SXscnbagIHyJ+yEakoBFtI9CIBi8akeehNrMEJ4jhHqWiocTX1eYhLWk+8xkdzXJGh5RlHZAPb4XLTvIdzsfJB2zIhx9Ap3AbGTNJTrI/oiJnVSqsHQrZI2lJGiGjEWeZb60R8L0RcH/EZmcF8wGmIXfVUCijavgAo2cFVJTWarVv1yo5LzoSIlkQbq1MYN5UUMybnEp6Eun724gvB/UgegKPtQlu3IQasL+vvWY9PP0dvR7vhsSySn7+wyBzAMsPgSA0FbVgak+RNDwZDW/zouFQj8OhHolf2SR6FkiheBxpFGvLAWNaQzD/JLC2SP0dr+T1dxIi0Meh3jYm6m24BHSZ7zFqD7ZZq0jymM6MQH164L5nc3oP0xeloWFQR8M2G/NG9A5uIzoBIuUQ7ryD2q4wJ7vUmSCz/7+DFm89FG9lsrcLPYX3C2EcE8O4BkKpSCqsGYrrGS1DXhxoeKvVSx0d/0CjgOwd7oXI03eQs0xsoNPGYJ7N1bcE/FoqmokfETJEtxClesRBaF4007wGQZ0m4JMKEHgqQcDchjp+F/MfKEE/FhN+d2NVUNclcIlX6X21RXgNQ0ft//k5+vPzIQiwMm2B54aRelagnoeg
*/