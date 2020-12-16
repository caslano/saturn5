// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

/*!
\brief Within detection using cross counting,
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation
\see http://tog.acm.org/resources/GraphicsGems/gemsiv/ptpoly_haines/ptinpoly.c
\note Does NOT work correctly for point ON border
\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */

template
<
    typename Point_,                   // for backward compatibility
    typename PointOfSegment_ = Point_, // for backward compatibility
    typename CalculationType = void
>
class crossings_multiply
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};

    class flags
    {
        bool inside_flag;
        bool first;
        bool yflag0;

    public :

        friend class crossings_multiply;

        inline flags()
            : inside_flag(false)
            , first(true)
            , yflag0(false)
        {}
    };

public :

    typedef flags state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            flags& state)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const tx = get<0>(point);
        calc_t const ty = get<1>(point);
        calc_t const x0 = get<0>(seg1);
        calc_t const y0 = get<1>(seg1);
        calc_t const x1 = get<0>(seg2);
        calc_t const y1 = get<1>(seg2);

        if (state.first)
        {
            state.first = false;
            state.yflag0 = y0 >= ty;
        }


        bool yflag1 = y1 >= ty;
        if (state.yflag0 != yflag1)
        {
            if ( ((y1-ty) * (x0-x1) >= (x1-tx) * (y0-y1)) == yflag1 )
            {
                state.inside_flag = ! state.inside_flag;
            }
        }
        state.yflag0 = yflag1;
        return true;
    }

    static inline int result(flags const& state)
    {
        return state.inside_flag ? 1 : -1;
    }
};



}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP

/* point_in_poly_crossings_multiply.hpp
lZwUynUK7+FUTuU0LuczfJfTuZl/YLXI2EE8jzN5IWexK2ezO5/nzZzLyZzHuVzAhXyJb3IhNzKN4TwrXI/TpuZwnjUyfN66i2dyDC/mfezF8RzIB0J7OYGT+FBoNx/mU3yEz3ISN/AxvsMnuYtTuJ9PsWQu5cIyfIa1OJ2N+Adewhnsw2d5A2fzLj7HiZzDpziX67mEb3Mpd/BV7uMyfs3lGWN3x4XreeE6X1r4vmF3KI+VoTzWshbX8QKu57V8nV25gcP4Fh/k25zPd7iY7/JjbuJnfI+Rer2ZDfg+r+MH7M6tTOU2TuenYfn9bXq7uJ0ncwcb83Pew518ml9yJndzOffwTe7lRu7LfEZOuCbI1eE4nPUZOf3t9+U4gOcziRdzEJsxmS2Zwj5M5XIO5vC8f7tPd1cTmjizL/a05Zl9sfXD/n9/6//3t/739bf+f1/rf39f6zeWKw8psMI6SCvpLWNlhmySw1LlNfOSVJkiK2WXFFqprCVBRsts2SR5V9kOq+L+/9////v/f//j/+WVAf+G/v+RbzkjNwCYzT90D0Ckj//0otE2P09c9z6p/bul3NDFTJJ1GuvWb7BH4GdO0zVmGl1XwhQZ9wHo529Zisb0zY+Mt3AmT2DDYl5/JP3cL7L4dbp0H9yzZ2JyRueBv9VXslnkTQt6h3hekSvXMf1OS8X0ne/jG/8eKVn7d/dI/267Z3K3Xkf7Sk4PfXAG1Tuve2KYtj5rmdZ7KObY/v/9Qh/10pExO1mEkXWa+/uj65T1BoDI+kz6he+5pzDr9/AzjqP/f+iTFZ7TPjglMTyxPvJ618zXdZTvktLnpsTsz9Tv3m9gjxsiv0h/vXPm6z0GJ9sUqYOj80zNOs/kYenTto9OG8qxy8CePaPTts18PbIY0T64m3JFx5KMPD+p/lPKJ5Tv0Mz3HRqZOHs/msztOKFs+jqk9OrSOyFrH+dS07L1oQn9D6qGPvKtpJy0kIe8R9E/ZNk2PfsMzdaL5lf3Icvo91g5phxCP9PY1zO3SeTNHo5Zn9j+P2lh2cfmCn2cOMn0SVmWPYceQL/YjyL0NwllG7nnJvQH/oXlic8X+hbKiVJSHjN912ezLc+gwYmDE/VJ6TNQjY/2u4r7heUpwEpxYb8LdbnoMftt7PIsC8vzkBSX8fK45RmRdXl69+8SKfX+eiL6R2Ji3C/3Mwnlk6VtiK1Tk/JnPE8rWhZ1Odl8G8/8K/MdkDjkePpYRta5bQ51pWzYrzP2u24pKYn9u/cb9lfbsZjtG9rlMG3VzNc1sqE8Lw3rVT3cD3BRKM8GkdfKaJtnZVkv3ZKPdv3LrHmW83j64lrWbH1I4zLX1xt7m8w+2GGZ8haIvsGqsA8s4xRlXXF2lmVyQ03oAJVZ5n/PPQqhjcm+D2TuG2fksA/Xznjd9OHlcBzxekxbEFvWd4Z+77O0hTU5gVMj+9LzWdcrrJQbs7xDF3tGzDFxaK6/fUzsmiscE/X1emtetK+Xnl7Rfl65Ytd7dK5sbWuoL+NzZfQBHKgK/bX2LByPcqiHHXM4np4c02esTw7H1+ixokAB5aGcbomMZTnn6P0aXVmieHrblXjjgMH9+mU5DrSYG9tHsPa8jJ9j+9QVCH37H5ZS8oA4ZvtiPUv5J2tPu/Ts5oQo4dfcP5W9n2u4V2VgQmJs3a4d+rwnKN+abMVIHVgWuwxhd088pm7P+IXtPz7L9t+1KHb7z822/dP+yvZf9iu2f/0ctv+Iv3I+FR+zvY/pWxravKztvzPTfompieE8wtgVnnfherifx714tG6Mz7luZP7NbH8zMo4vHT33aB4xOp8+iJn+Q9OXMmHdhUenb/s3pi9km34=
*/