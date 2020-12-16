
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
8QbOwZZMw1xsi/NwGC7AUbgQIzEbM3ExZuESXIvLcCPej9fwAWxC3azCpvgwBuAjaMRHcSA+hmG4BkfgOpyA6zEeN2Aa/h0zcJPtuRO5robzSf6a5052yP5kN3bGpzAQc3AqPoNz8Flre/RK1mtlLIsyXzsqy6nM1zoyXz3RG+vKfPWS+VpP5mt9HIANcAo2xHhsggvRB1djU1yPLXAX+mIOtsQj6CfzrQ1+h23xFmJphzWxAzbEjtgOO+FA7IxDsSumYQD+BQPxQeyGWzEID2F3fBP74AfYF7/HflhTafKNnhiKPXAg3oqDcCwOxlk4BFfhUPwrDsc1GIFbcCQ+g6NwL462zsdKck1PrvVR7+zLiUPq/Q2Zj0fQG99EH3wL/fAotsdjGIDvYAi+i4PwOEbgexiF7+NkPIHReBJj8QOcjqdwAX6Ei/FjvBc/xbX4Ga7HM/gUnsUX8HM8gl/gO1iI+fglvodf4Sd4Dm/gN6hM9HfojufRCy9gY/wR/fAidsFL2Asv42C8grfiTxiFP6Ns/+W6IXWppMqO30XSFq+jtc/1jTLcChlO3ef6ONmvjkcPnIANcSL64iTsg5OxP07BKXg7JuJUzMZoXIqxeB9K3/JUhlzTw4dJ2uOyIDnO6IkdMRiDsBcGY28MwT44GPviSOyHt+IAnIkDcTkOwpU4BB/Eobb9v1yvwxiSdv+/X5bHAzgYD+IUPISFTvb1+kc+U1KAnTBUnieJGf3f/UxJ1n/AcyUeocTwX/ZcSdF/wbMluU4+X9LoNP3DkiaSFpBWk/aS8kmXSd6f8twWKYG0nLSbdIx0nlT9M54tIUWS0kmrSbmkU6RrJN8zPK9CSiAtJe0m5ZOqF9D/LCmClEXaTsonFRe4nlFxfVwf5fNvav/PPdt/vf1/E/r1q8MJQSOGdzNwaz7TREP3WanxJtos8DdP/ra9tepvGYmxmWmpmQbp76+fN+Vb24JWKt0+M6S+8j45y33/MWOiU9JiE6ItYyKMzPLvm8p9Pc4LHN1H+/e9u7mi9+/07xs6vn+3Nkn5PexKnzfv2dnm5FudO+/b9OqHbg7v08k7jqW+ZT4UkdTng43lukdTbI7NsDM2x77YEgegH/ozkkae7oYgkhyfybGZHI+pjsXUx2AeqmOtzXiIpO1b3yDHTZs1x0JHSJ3UfeWTpE98W3/4MSRrP/hN5ThknaaPezm20B5T2Pq0Tyfp92Mvxweq/X6Og/7p06Uv+ijqx/VxfVwf18f1cX1cH9fH9XF9XJ//38+fcP4fP9v0r5//K+fw/b0N0s645P5torTdjSXVDVTewWhtuz90zOhxkcqThvKY4dAhxpnlPxtmacMvz4jIdw/5HivfPeV7nM4zlta29Xe0Mz+XKO3LVc+qa58DkOf675bpmC/T4enmeDrSDf8503EZ/StXvG2y/rWBircFrmjbXv22un/8tRn9a0KO2ghXvK2uftthR9dyKn5NyNG1n6NJyu9Xrg56/K/rmm+q0zDkvdkvfT7BcRtq5dpPkkHWU0yU90HWwCkkdVvbMVgfo7A1jsMOOB674EQchZNwMk7GqXg7xuJU271SWZ/wbp33UzdT9V3XDHtjO+yLXbE/hmAohuEADMdBmIRhaMLBmIXhOB+HYVRl5+4xut4j6XqPpDPvkcziGt5G13U818f1cX1cH9fH9XF9/oXPn/D+P/Np6+/x/j+lDUA9zo2Xt1Du2/O+D5Nl3JmM14+/NeRvGwcp7wZUbt2PGjY2KjpyzLCRg6MDexkNkqcJeSaG6eQxGoOseZqRx3+wTp5uwbY8vuRJH6KTp7uRv5TE4xtuzTOxV3QPY0lA4422PKcc5ulmztOKPKs=
*/