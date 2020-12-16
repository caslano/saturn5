/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/norm_inf.hpp

 [begin_description]
 Default reduce implementation.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

#include <cmath>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< typename Value , class Iterator1 >
inline Value norm_inf( Iterator1 first1 , Iterator1 last1 , Value init )
{
    using std::max;
    using std::abs;
    for( ; first1 != last1 ; )
        init = max( init , abs( *first1++ ) );
    return init;
}


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

/* norm_inf.hpp
3e3JJb0iC9v2d3oQ58/qPw9xT+FfkfmdxcNK/yOcrv8Np+0Tj/B4H07zX8VjOG0/UuIzOP3+FK/grP0ueNSTs9j67Y+hfMruL3wysr9d/IRy/fBR7Pt/Ev3XrPwCnwd/rDPo+xl3noH9g6pnPdmxLTL/wPlh/50Br1/wxGmR+aEveZKx9+dlj4/PhI/CHysOOr9Z5h4Y31+9wcefNYqbN/F8/xk7P8T385bSPghfh6zfHdQe318Y/k6vyOaW/qviQ95/UMJ72fsLZ+tvNXD2fkcfIf0j7b8lPGTl9489eZ7s7+1/wuMT+ALES/g9bPzcpxj/x/pXP0P5hzy/Ar4L25/8c/58Yzh7P6r+eNL+BF9h9PgZGap+/KXS/g0/npx/3GB8Ztu+/0/wDfrH4CsOG9rr7zx5FecXDcO/hxw/68nL4+D4lvxPhnclacNt78/YXZmTeDVuVyZo2/s/EqeL+qN9/YTc7UpPL45vW39jwq5siz/mt+3/NHlX5h7TPn+oGtGVCVn7P/yPln1/tWSmrjzVQ8rPs3dlBdY+DWfpXwln+8NWc3RlxtlEdrV4tm1X9hF7+hVs15UpWPlO8Qx+K1s/cfuuhC1Sf9qx27/+ilj2V8vgP5DxRVWC62Prb+3UlcNI/cbfuSsrs/oZnK1faXbp0vahAH4mOb8GvjTxaNcuX18QTse/KvGF4hX8D1J+j/boyii2vwn8hLZ9/xB/n66sRdzs35U3yPpuwQFdOZ14A7+3P30Z8O9nH/h+g4O6sjx7/vDX2P6mB3dlEdb+cwjSB5b/HtqV1YmnijfwD9pkfYIju7LvwPo0/7v+4hgcn60/cCx/v0I4HZ+oxCdKfKrE50p8AfeIV8rxG+X4chw/vg+n/U+Kp4oXitdw2v90PPdQ8UTxHO6x8jF88V68n9b52Tx9SuGLEa/ge7Hy62ldmZ2kXwV8BFt/U3FzOvdQ8QQ+advefuCf1aX7w0bwhsz/S8/uytfEi3O6tP5hzu3Kcqz9Cb7IGCh/2PoHLkH5kLXvww9r2esP0WVd2r6cw8dh+R98BPt+lOMHl3dlcla/gNPxbXB2fhl8KlI/KeE3tEj+eyXSBzb+7aqunML6D+GjWPvx1Xg+JN5c05Xx2PgIOF1fGd5l6Q98J9a+c21X+ki8D9+H9K+V8BNI+pAWXZmLpW9wur45fGzitRLfKC7XcTeK+4oHioeKR4rHiieKp4pniudwNj8xuh75G3s/4duSeLmBx/uKh4rHiqeK54qXiteKy43cfcVDxWPFU3jM5qff1JV1Wf4Mn4Z4rnj1J2F3GYe9GEYB/NLN1LZHTjfTzXQz3Uw30810M91MN9PNdDPdTDfTHeen6z7HF+/r79r2LO4O4XYd9xjO0o9EeAqn40Ph5/66PuT/z0/Ob0D7A6m/1/AThjTE///8hf7msej6DvEtY9kV+MMt5lif4k6eP8TwcVn6Ah+deAEfm40/gQ+IN/Bz8ZcpXfsv3zeWXYc/zOPw5JGx7LahyPyix8eyC/GHWRzePjuWnfNr+5ljfdBXcP0s/3h1LJudeAqn7w98E9I+3cHHZ+WHbiy7nO2PAL+E9F+2r6H9iIy/9t5APBmfFL+F+j88cnj5Dn//anhA2//5+2nvjsX3X4GPTteP4O9vDqfjQ+A5Kf9E741lX7H1g98fy7Ym8T38gSHd9z//eCx7+F/rO2wz7d/aL/qxrCfzq6LP8V/J+hDZF3g/yPzU6sux7O6hyfiU78eyB4dyr0+Q4e4PNwTp/x1ibDt6CJjLhxrblmb196HHtnVJ/3kJ3514PMzYNH/J4Cv8/vvC/13/gcc38G/wly0d7fPNqGPb6EMgfXMcP/LGtpk=
*/