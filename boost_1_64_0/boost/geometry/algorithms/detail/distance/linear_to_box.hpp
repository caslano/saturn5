// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/intersects.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{

template <typename Linear, typename Box, typename Strategy>
struct linear_to_box
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear>::type,
            typename point_type<Box>::type
        >::type return_type;

    template <typename Iterator>
    static inline return_type apply(Box const& box,
                                    Iterator begin,
                                    Iterator end,
                                    Strategy const& strategy)
    {
        bool first = true;
        return_type d_min(0);
        for (Iterator it = begin; it != end; ++it, first = false)
        {
            typedef typename std::iterator_traits<Iterator>::value_type
                    Segment;

            return_type d = dispatch::distance<Segment, Box, Strategy>
                                    ::apply(*it, box, strategy);

            if ( first || d < d_min )
            {
                d_min = d;
            }
        }
        return d_min;
    }

    static inline return_type apply(Linear const& linear,
                                    Box const& box,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(linear, box) )
        {
            return 0;
        }

        return apply(box,
                     geometry::segments_begin(linear),
                     geometry::segments_end(linear),
                     strategy);
    }


    static inline return_type apply(Box const& box,
                                    Linear const& linear,
                                    Strategy const& strategy)
    {
        return apply(linear, box, strategy);
    }
};

}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear, typename Box, typename Strategy>
struct distance
    <
        Linear, Box, Strategy,
        linear_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
    : detail::distance::linear_to_box
        <
            Linear, Box, Strategy
        >
{};


template <typename Areal, typename Box, typename Strategy>
struct distance
    <
        Areal, Box, Strategy,
        areal_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
    : detail::distance::linear_to_box
        <
            Areal, Box, Strategy
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP

/* linear_to_box.hpp
5vT9au/sSP4Kb+Lz/bAAti45j1Oq0+a7eaVVxdE6B8v9vl54y3PDIbHVYiF5S4Oztugb7w+NFscLYuosJnijWvqRrrgNn+XnEVz+dblYTbQu137n9WfKwjtr2tAf18WcIdG27+Dfn7HNhva8s4hrqMuyBcXSXLGVtk861D3U8G/y/uwbeLXUNWBBiHO6Xdf5jm3kvSIsryDek/gqdFB8+jONXpwZ3zwcz/ouw3je+fe8tHfeczEq5vebilFOcVMbj73vn0/1aHqay/e/TCL2qfg6v8AZc+q5xer+jL6GcVVv4C21VbmutSwwu9fi+9BN+Z279LmkbnlCC/HXxg78OmsLheWHWqrTg16/xzro2nDey7NF8L8e/PqN91ICP7vmHfo3ksbIgNvu6+muVfl3tOgsvkBi8+gQWB+nMy2E70rQUBdKwj1acPEYWtf8tDCeGD9R7/r15HTnkaH83r78O73xvK2aFcOhR3HRct7wYX4EfykJTZ2/M8/rjRpJaHbuKs786zXuPeea9wbBU7N+kftq8VN5ku8f06p7XHJ/A60PJ9v+ShNVtj7+YN8f3bcqryABXXbP2vRBkmJ0UczzJOv1MK0wPaMe6GD+x5sBc3qsp86AeuIV2qJ8gM6ngT8LMy/Dl9ZtcL65bddgHHPKbFUc35zS31/j3FxeK/fFM/i9bPCxVAPzmp+/Wgq3F8x2ttIFhnvdnQW0GU0+ehN/0NfvzjZj8LV6iPsXS8xxh+DMVdz51b9nUi+aOdtWj687844G6OWmtAnMKJA5ABOCebd8wJ6+TtuOvMmDiaOXjuPDX3HUYz5LLN6DWN8bjhda0nu0WHV8/1Nr/vgu8Srq9cnVjlz9PMm5BH90W3dcd0+98DCWqcWQZfRKQ5yjn37KLo76bnpvcfrBeyJpHOsM0OzJu/lZLudQa3iWh+m0xHp20UQf+POleXxwjn9/xmi5uHcoCSub0SPD+bXN6aUYzQnzP+nD963Hn8QnyVvhcd+bXEit6NmUceFNHr4eTVovmfowP+egpZKJy4JHMHGWupjrWYGYa22yj47//m3Dgfz22WrtlFw7xw+EyHfStDD1hhjBqio4ujA8Dcuhh9Vx/L/5h1/CvtG0Muy60NzcZ1bNOQgH86pKjrP2m+p/PDz29c9T03HlgulavfhATEJ48nT1D7P12/sQf0/WLICLsuuNdZPg8C697n4NrsDgy+opJ3/TfNawG9xbbbaH033U94JD+rwvj9rr711Tfwl5h3TEaP1f5SK/543+UTdvYXOp6+5No2aQv5KLYF4cvwd0Ho3+KZwMExfzcO8VfIvrtI3v7W4hbq/1YswzXfyy9HzUcfC1kfr4uKw+cDb4Wx5e2wRaLgq2X+KHjtHvZr+h4j+osPqE383piXA4N2mDcx777/LKveDPdliRO50+KfnvDJ0HH5SOoLWsfW9/9ZSJ5p8J++T6Dv3QzDXKn4THi2FRC7U2R3/sheXB/Cb7yNVVfYv1BVqxRSE6dYf/l/f15bTPQ5pjtnVF4rKAHs0N+6x1Mv806SX4JCYd2usjs2uXtDRSI1opBK6+85zodVptOv4S32Mwox8d4GdL/Myqudu165ylh26KMf+vXSL4ndyZ+CM86yMtPdr9kJxu9MxnYnjh87H83cht1kqTr76HG8vR0jXoL9ds3UO9R9MqdfAMjH2irn89oNfMKqRfIFK/HqZhy771+UD/2sfKibgts/oSmwbylEO/vQzi/6nJI9H2GGFGDIYpauWCmNSDl1v0YDPrb39Ez6uNfi/o3Oe4tgrcyEgffexcszRNtgdXwc7T9n1qhbjUoz//4N01oZ2KwLLX8J4309V7MiaAG9ZXrZM=
*/