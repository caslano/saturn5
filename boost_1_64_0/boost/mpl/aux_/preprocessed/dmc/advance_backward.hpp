
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
ulX3z1I5zVY5zVE53aZyul3pxRtB435DpRcJWyq9MqXnPpv8LdN9Ubqvic19r+q+7ZL7mqkdFUv/LJt21Fz5PgM2h3GwEzwT9odnwavg2RrHW8IM+AelT8Ja3zLGLlf6xvixX+n/Rf3qVhgDZ8v293bYEs6FF8A7ZAM8Dw6ChTAJ3gWHwYXQkHs3nAUXwTnwHjgPFsGVcDEshkvgU3ApfAYug8/D++ArcEWEbEzhV3Al/EY2ygfgg/AQXK0zkx+GreEj8GL4KLwEPqbxIOUErUFpbSqBcJ7rOe78XaZyGASj4WB4IRwCO8DLYX+YBNPhUJgFr4A3wBFwpmxBl8Kr4KPwavgcHCWb6GvgLzAFnojsVNgUjoFnwjTpnQ77wHFwBBwPR8MMmAYzYS68Fs6HE+C9MAs+BCfC9TAb7oA58EPZiv4Mc2ENyiAP1oT5sDmcDDvD6+GlcKohH06DKXA6vB7eBG+Ff4Zz4Ax3OUdoTQpcqfZ8Ihym9hal9txAz/tojQsxek43hG1hI9gHNoZJMBYOh01M/c1RST9dov62VP10mem+xEr66SLdd4/6aZHZhnOWxXY0sA2n4jUMEq84xHhlpniFPvGGmp7XFYo3zeZ5vVnt+1nYEJbKp8RzsAd8Hg6AL8BkuAVeC1+EufAlPc9fljz6s97/iSt5UXCue7yTvO0aV17Tc/t12Bu+AQfDMjgCvgkL4FsaN96GhXAHnA/fgYvge/ARuBP+Db4PN8EPYCn8UPphx633eupN457xHDok/T6Vfp9Jv8817u3W/OgLeB7cA+PhXo1/X6l8vlG57FO5fKd5ToX0/V7znX/CJ+B+6fsv+Jp8fZTDg/Az+DOsgIegofthWA+SAWy7AWwGa8CzYE14CawDL4N14VB4IsyE9WAWPBlOMdmoLm0faWunWsK/y1aVM2mrdsZx9fnGv4496s72kUFtUo/1GcfH6nzjoz3beG/7yJBtVf3PNw7fVrWSs42xU60+0/hobVV3rq/cXjW+xP5M45obwrNdPUS7adkBm1JCPmEpoZSwm3ByR86FJyQSHIRCwjrCTsJBQvNO2OcTUggFhFWE7YQKwsmdIyPOJfQipBAKCCsIpYS9hJMvxg6WMJIw5eJq+9PjeP7fmMz8vPxjcf6fcd7eV8Z3gUFOG4A8wyO4a8dZcn7qmKx0knfG+Zo4vCgQZ0L6DcmT8lLHp1tiGfYAb0ZFePa/rNa7xjX6jnIVYR9pJE7R+RSTXY6ie/Qbljx0WFK/wZeF/q3H7HO8gclXNYXi8R0eBRc79w559w3sa0wcNo35fpeKrWH/jbJsyrH9Rok8nf1n/12wYsqv+13QXTf56qoT9W0oE35r7FOd7Po21C7Tt25C3w8dij94u/0G2ttsU1faJ+Pd7+z5tuOs87yIkL7jHCvfsuF+xwnXp+qx+r5zrHzR2n8nCvQ9KPzvO/bfcX47X7F0Sv593fLsVs0P3Thi5cWLK66au//e4+MrNjFC4yO8xmbdsa3e4y6C58P2MAF2gMNhR71fdoJXWX1KMpaF9j5fMSX4ezrZ01jhHEPQ07XtYqPi/Ul69tB7Zk8YD3vBTvJheY3Woa6DfeGdsL/WxQbAD+BA+J3Wp37W+tQRrU+dgNyhsDYcBk+Dw2FLOEK+v0ZqHelKmAqvhuPgKJgJR8M1xl6wg8zPCFMSIplHR4bk48jundHef9Hv23fRb/GOGHUcfBb9Fv6KjsZXUbjvfuG89/2afol+Vz6JYiKPuV+iUsaj3YSa3XkX6179jlX9q/79N/+O1/s/e3mPyfn/57jP0u9inFnco/vQfj2Nt09e+7pzhtNQy5n5b5vs/RNP8D+n+TvjHONJznc=
*/