
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
OT6mh/Wx1N3R5z9/WyQxQdGi94/feBdyn2jsI3E1kESpo+Pxr7od/5z53sKAj0lqH7fgI89aU/31LcFxXrtlWupGqew7SRq9z30lvmet/7iKSl9IXci+WOI1SDkvkHy0hMtHhM924euCsVxTRON7cs3/GZmAP9nZ4fzxv4mVuryR3YcCPiWITzfwXBXUZB7/J/EmJWajxNg8I7+L2BGalwOx5nv5lVr7fo1VXjr27KjKiw9pU2U853Pj1H7VW/oV+bOd6ZyLT6LG4M8x8edK8WeCvO81WfrTuec9xbuecZxjX3P5TMKftOXW/vibxy7wqdLCp7N9zeOvJ+NThqVPHXsujcSnOpzRtiTxKUFLj0954XxyV3qI7Wqrf6i9uiSqjHG348334Glau2zpU+TPz6r7Rj8ktG3dH68un/qwvngqO3uf9SGixnC+kvqbx5KfwkqTlT/+bil/70p5pbt9n/TjII+LrZ3Sjt+PzEjlnxWt4z7LfU5/J6ffd38jbu95sTv8Rzx5lpeIhEAd7Sb7uO3p+w35R3u3CMb8rkT4zVFt7XsMaek6M4yr3J/AP5rfErN7O7wa/xvV/ksD0Dq+OtbmsycdvIZztr6iqO3ZSPG8FG98Xgo+P7vxv7DCvcmfbzRfkoOP/P9b/VvPyRWSp+GJ5njcj/CXxpX+PLVmpXC9rWeoQD6+Tvr8wHUgvwugvixrE839R83sa1kZGKM6a8XS8VoE43lzcrSXB4bhlpW1P0ZVX9/OJJrH3X4hgX9WKWxEGD/3oQTzuNuaJPO42y8mkFJpz13h9ncI2rfJswg22+r3JKxqGoorWZQhJO/dBph9eZvyyFD7UuktidyPPvp+b5/HYL9GYf/LlEWeyn6EcYQpe9X4Y0Nc5zEDzXGd52htftD+sux5S1esyHKuyFm+cOkCnmVcbqd2xdgvh1mpxvMxh1SaBjkfwfeuXrGm8xSsM3sGmuvo9/qz38LP9vuQjT4+KudKXzbdk83X3lytHbOwGbz8bNjV521zsjlv87HTZGWHSzCSceiUvylvvVLM9e5j1JcWK5tchh0tUznvYc9vncKfD/gRe62VP1yKHfAlcC24u8m1qCuTpFSzD5nsSw/6YL7N+6OtR9A2Jaa2H2t9j8KPRezLDuNHMesKRFInQv2YIm2T/pwkDTLXyyzSucP4wSXQrg+BZ5H9KC7kYyvfcw12tynsZmO3LoxdLol27QbnTOquh/liM22wucyXc1x9GJtySUQ0JyQxpC30mu9NwXqwb7C6HjSF84nLoiP+KOpB0I/0NLMfOaRrsfbDf6eKpK3gnFjeq8aJHzvSzO8Es9Eem9vqh8/jvzHZfv7yP99CvY0zChsXcVx6mw1Ol/35eLQz2DA+S7qHmO+5q7Tru9WG/80h0mfJaYZnSX4rniXjh7YmHCvvFZci96HdHWLXOXvFvFnL52Q65yzJds5fartPODEWH5zig/wucLa9K4hPwf5h8dl47YuP58uY7hjo4S/1rT62Du7gw0nxJnl9uNnlqbBRTlbfrk7Dpi6ch/V0krb/+rUPvhz7xZVvbf7r6jN3Dsp9LvL5WW/4j3/2J7nvfr0s+eSH9++Z+4thT9Ch91xvbX/9b68b8mDewz3vvOjoxxLe+9pBq/lB0Xle53qeF/Oa2f+7e1wDXqv9ZY9Xm3wJ02Z870WreV5dO58rzSFjjOT/uSHj8Eef1zbvpFqOmy/H6eed5Eu8/gLYCxbCRFgE06ALDodr4TRYAq+GpXAuvAlqduqQZrHzsNi5GNYE5rfgT294FUyAk+AoOBmOh1PglXAqnASnwSVwOlwBZ8ASOBP64NVwK5wNH4Jz4BfhXPhVOA8G5zk=
*/