// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP

#include <boost/mpl/assert.hpp>
#include <boost/range/algorithm/reverse.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Tag>
struct convert_ring
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TAG
            , (types<Tag>)
        );
};

template<>
struct convert_ring<ring_tag>
{
    template<typename Destination, typename Source>
    static inline void apply(Destination& destination, Source const& source,
                bool append, bool reverse)
    {
        if (! append)
        {
            geometry::convert(source, destination);
            if (reverse)
            {
                boost::reverse(destination);
            }
        }
    }
};


template<>
struct convert_ring<polygon_tag>
{
    template<typename Destination, typename Source>
    static inline void apply(Destination& destination, Source const& source,
                bool append, bool reverse)
    {
        if (! append)
        {
            geometry::convert(source, exterior_ring(destination));
            if (reverse)
            {
                boost::reverse(exterior_ring(destination));
            }
        }
        else
        {
            // Avoid adding interior rings which are invalid
            // because of its number of points:
            std::size_t const min_num_points
                    = core_detail::closure::minimum_ring_size
                            <
                                geometry::closure<Destination>::value
                            >::value;

            if (geometry::num_points(source) >= min_num_points)
            {
                interior_rings(destination).resize(
                            interior_rings(destination).size() + 1);
                geometry::convert(source, interior_rings(destination).back());
                if (reverse)
                {
                    boost::reverse(interior_rings(destination).back());
                }
            }
        }
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP

/* convert_ring.hpp
dGy5XyqEft2W5x273bESlx1bk/KOTZcd2+iYkg/dv3Ts1ZT3br3s2GtXeN6bKTq+9zL5fXCFd3x0heftuby//+L8SO6TdAX9qnZFm/Flin71SA7fdlHFfme/nPy37NfA5OE9fz9Xa11xru5PedfgISOSBw8a/i+9Z/AV7WSdK/b54IX3/MpO/mux/Khh3Yf8vl9xV5zD36S8b+Sg8F1/NRe/O3fhzAV7e9jx9JKlaQEflqITXbKeP7Y24tKxrinH1gSO/bN6MnxQhYTuhnzE8BHDdOLXfWjyqz4UTmlnYlbtbNO8QmLdRqKntq0bNW+Q2LNvUs/+l13T/QrX9GEnveii/ex5hWvY0uDCM5KudP43z0h2Tc+KyYm/ue7i+QFZXVOx5+/Oh+U11Lla5FUiILd/TV69vLL3kN/Jq+0Vx3z0hX64S+MHG9eLen77Zec88WK777xwPHlE0sCLN17S24m/Pe/my/33vc5r6/nnDkvq3it8/wW76NwI/W4UaGnKsRcce9qxfZcd25ly3YDLjh1IuS7psmM/plxX6LJjkdnOH6vh2C3q8p3Voksz9p8sExNwEEUK+u71CZ6uvpqFdd5nHrT2uso6g30OhxPYO3uP8kwP2ZPie37WineEa58b1EvVpr8aZ9+Ie1raD9uhmJhOrW2LdfGnxtvrVtm6ov1M0Y86rjbymDWXctepn6t/TNqkHjVGXS7KOoy1wulq8I+r47RRr+raW93L2lT69epdJdWGvrNu860avLWBx9Qoqz9gfcRaQcuBakc/WzN41NpYa7XWj9U061jvfF39K43arnVif18yGG0dIW0p61Bv0r+PPdd6zANqqTfdqpa+hAytR7TurKY7Vs11jrqONY6cja3TJFuXS6vSof711vPWAdTcGrvnlZb2GGfQt2TrRfutd+VX5/zSGuRJ66XqVcvPmfMx1ruXqEU+bmw7ksd29R97mXo8rF43zlqj2lJ0bbXJkma2NZ1O6oibSltz6heu9dh3rU4b8xnfneA7GNPIxHrJlGrqQ+Mi1MSMSRWyMFmesO9lEHkdLKB2VzWwF55fa6QGedh6dXlr0/p+8kV1d7W3W5d6j3rsDV/ah7Lbe9QOZ85Tm1pGHs3FE4KHsu5tS36Lwt+D/FqsXjHgtBHw5z4LCBaDbND2ntkDf89PjJHDTPPe93JaW5mnvp+bvqnR5s9D5/ZYG8zrfKD+KviMUVR6Mr/fa9OtAj5vtoZ7rVdMUBsraK/APOsj3lGVfm29zvv3qKEVCdzvu34xPq0jdS0aeL/15GKB+yMDRsP77cEly0B/qqijl1F/fYI8gz1qemUC91ufsw6UIZqcy3lfbWsIFfTnZvW+itplnbZmZe+bpyZ+vevUu9dVCbzfPg1yjfOEmGqB+6OCE9Udrx0VTKwZeH9U0KyW3ydEBdt9ZpgXFbS6yfENrq+tP3v0PGCREHEJ/7xbO/vmDa7+u/rv6r+r/67+u/rv6r+r/67+u/rv6r+r//4n/+7CtSPsi+tvD8c2excG+t7xUXnhM/bZ2K+fQc78cRO50lYpVn1/e11+9XM6+6Yj/O27xWq/ct6e8rK+6I0H8BAex5OYi6cwH0vwIKbCNfanRfrv6fubPoPtxfrMO7bYw/GqnNUeqYGj5fr2lxZVMZlwiz2TT9tnKcc+4nuIjXznp9hKef1Mf3ctv1zXd5d3fGDflX3YW3LYnx/+O84d/JxefcN+taER1lMPyANr2ifX176yDCpA0/xd17fkY8n2/tawR8P+0XHf2JvYyD6Wzb4DXsKeq5b2A66Wq9uf9mwufbVvZkFh+4XUOHrIhSt5b/tC9mb/EvgbUL6ban9l4kn7ZabIfX0=
*/