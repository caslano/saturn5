// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_BIND_HELPERS_H
#define BOOST_MSM_BACK_BIND_HELPERS_H

#include <functional>

namespace boost { namespace msm { namespace back
{
    // helper to replace std::plus as the lack of implicit conversion makes it not usable in one of our bind
    template<class _Ty,class _Tz>
    struct plus2
    {
        typedef _Ty first_argument_type;
        typedef _Tz second_argument_type;
        typedef _Ty result_type;

        // functor for operator+
        _Ty operator()( _Ty _Left, _Tz _Right) const
        {
            // apply operator+ to operands
            return (_Left + _Right);
        }
    };
    // helper to dereference a pointer to a function pointer
    template <class T>
    struct deref 
    {
        typedef T& result_type;
        T& operator()(T*  f) const
        {
            return *f;
        }
    };
} } }//boost::msm::back
#endif //BOOST_MSM_BACK_BIND_HELPERS_H

/* bind_helpers.hpp
PuNcgT0NZn+EOB6JDGU9IUTodfLMMGhvEPfDck2CzH7N/GVb5ucy9PIWsr8Y/oi3hQXEEOqjyO7wSV4QJ6AndJq7CZlwHhMml1fkGaTcC7uOWIYvBBrGELP5vB67aUFef5Dnu+iJvJ0eQ3wjB5WZe342ur95NHGXOYKJ3YxeTwP3P+bOvAUxszKE/PIU9UGGOncCuqK/wJ8Yh3ELrLWqrHFFGBlczTjsi1cZI/Yy1+Gzypl36ZvEZJ6rFb+k7wdYg2wtv4MC/4zA/xvUAGfIPXL0+lP4vg3ds/cY+zXjViagD3KA3Ou5lzXpc+Q4fgpPIzf2FKrooihz5n7wRcxI7z6Q9Tr3Ho0fnCv3t1nLnch4n5LbRlNbI9cKMSV9JXZzMb4kn38Zja7YLwkzbl7WcJzRhR+Fn8eZL3MvrOOHWr70oWAdug2/49Nr4OdU/Iqx0uSW0JXIH91E9qYGwg5Lz7F+vGhb+mBO0hZnoL9ygHU0cruZ+qAL3ZEzBDVQnrGK1G2Rkdwj93b4bvz0/swLP4hdQYxvZq0g93bfQr74f6F7FDGEGIz95ug7dw+1GuuJKv4jklz7mHiLPZaQV5U+yoOxl6e3w/fwZ8YLdhMv8J3ijxgLnPgYe4OXMvu3wf3Ihy9xH34hUvxcQTzm90ojfaxGX7I2YY1WicA3dhVpZ3zGzqOvvTaSB1l759bhO+gixP5e4F1svIE+sY0yYwRu3BZbQFfYaIh+qtQn4TvoZy4xZAA2vxV6OI+4tZJ64q/47Lb8jWdyf+lpZLQentFdifVd4Fl0OIBYBg/589CflAfrlurT0NkHiHyCTbAWzD0Gz+w/5rHR3Ev4EfoM9owhbwbYq8UPNhM/w8Opy4aR86mLiI+ROHGZ9Xz1EPhAnoWTA6w/kcNGYv8TxIIF8NiBDILc8z8+nwyv7F0I7slzT/V35HfiUOl9fqd2qixC5sgphk+GyN25c8CDLR7CzwHkJmSRx6dzxE7Bd0EH30DeFxEzeY6kxDos1EmcYf+1+G3yY4x4w/q1yP2Fc/H724hd8C4+IE9v4PPPR5PTsat9sBn6jx3Nuvww+MR+QswrdhB2xL1laHnGDn3InMmRlfXIXvJEnA7sgt4eJKehkwq4CtfEk8wFe8pzf24UvivH3w99jyHm8XvlD+gG3widMo61Dno7Hj+9irlOxpZY1xeIz9UN2PdB+NsnY+GdGnHgYPYgkDH48kncN4ox4Sd31nhyCtfu5NwamcQuJy+9zN5YBfu8Ex6uQ45/x+8Opk7HjwT3h/eEnyuH4wvEcOwifDFx50Jix+HYOP4Yg16U57+PEptlrX0M9jiN+d0NP/hloEpOPRAb5PsTQuNZW129HTpD35vAEwfEoeT0P9CXYL2RIL68PRbbJDYzfpH8XJ2B32GDJeQVuZYY8Ed0OpO9GvxNYI/Fnclpm/CZBLVSD3FTyvPf5O9X4H0X6lPWd0H4FCXsl/HE5/ycil2yXqaW5lll4v3H2FWENQz+lnsEnPy+3H8wt4H45sH4yevbYXfEzHOYx+nUY+Tu9Hj0xZoriBzDq9H5jeOxe/wiPRZ/R+edrN/ZVw8cjq2Qh8Um7J89isC25I3n4b2MTe4xEj03wCf2KPMcNWAgQr5NMsedqA1GUxscTJyLM89Tsd2NxDhsNZZHZv/Fv6g3ytORWTLAfhdx7QHWPxOxsR3h7YJx7PFQu38PWxGc+XxI7P029VZ+jIjBS+V5ZCTPLLdCljeivznoHXuNTCGWP4b/7on97owdf4rPPwO/v2Uv4Fh+/jMY/eK3begHeeY+HUw8I39vRU6HHjqOmMffjRQ8O10p4j/vouvl2N6/oK3EzpBHiXOwIv4=
*/