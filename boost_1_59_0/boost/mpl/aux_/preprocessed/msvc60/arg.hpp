
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
nRPw98ZAVrCGM0QCD4+LoleDbhpETQG9Mx5EHItCQGvDYk8GhQchNY8M4f9A/iMFQH0UtriTcpMSn0PbWz23g7r2UnIq5xni4rPrnjHcw+dqURgFtwvIRI1X6TV2jMVx4Z1bXOTMWluk6H38xPFrve5Ouf5WzvR1De71GPeOy8D1WzHVfW4hI58844En8yUDd0DTkDe2Gry0XdoWvoLbuD3/2gYtDr2l4LnK9WZZ8vIcePZoC97mBxeQGyequ8g+ecx0gtV4TL1M9Jfi5qwyvmXqrW0m8E5cWT3PgWtPJFedrIGDvprUrz5PoMDwFZg3N+vyPP/nC5Fv53uQYDx10iGdCAExmQx6hm1Ny9oq+2/MRzoRwWErJ2UnAk0wB8oE0zGvwQJX6sUAdElN/EiD/34ET6ryFFTx3tqZuZ8HcHutuEl2Ts+yR/IGpc3NWc6IjzTuHNb78JYYp9e7/rs9cyiSUduhvagbq1zJr5I+raUF/VCBZUsVgsSoTwxojgD/VvTU4ShAHJJUJwJuk1kij8hJ3hcRocRVyezfvSYQULkDNP+Wh9E8E6EHWKB5+XYnC2iOX487OihqCt6qkmB8y2yT32G+2He+vCn99bIMkiBRRfxWZEfII1W5r07e8mbHLBen/mFX3vzqh0b1yCavuVtKq/fDndPfbXGLaPWeqNuzzuXMOrJeHdzhntlA8zRucwa+0ajNOlvpDzXFmnijg2UbLJNKDekJXUiV4RGNg/npYyzzbbQQ/jXh/y0RsfmUSvsC9eJ/TQSu0MD9ezxR7T7vGNCmghl4IHx3A3rF9mohfvB8aSbwFm3IkAdU8LzLyuWsKJEyqwwWFaI2doyQM1PCpSeHS1C7IIJtSukk1ly+YuyD3NJy0QkHvvaGj8kqd6Y/vDN+Mrza3IYOtOrZZalnUCKj36789LtgDOwpsYA2hw4EDbylTYcbjA3U48/UaDn1iM8NFMFgAEKIWY3DpTkM7inrx0lYqxEzVyKkberNSSxrv19a452rjFz3Cv0TWarvQbc9yrUgu69gfMLo2KUtD0s6DosVyD827kByoqKHBk93cTVQfop11uMV+zvv+aJMb5FrLXBk0PRUiwwypSlb1wPxC5T5xxYfGMbl1QiSUTbo13mGEuYNlTb6yJzGeE2OA9ql7rKMZbLX8x+z+tw6hsFm5VVyLGgln7ums85NxDpOVauIB7Wy9t8xqWaZU409fpI5ok1C5x+RqMZZ0E89ckyP3U8auGfhPyQfPiMfUZvVvuHDBBxqGLlUzr19Y3cltU4MUndUsYvcXE4aqLtrEyaO0nA5PHQhk9XNaXXKX9PjV8grWyVnPqDe094+8wpAmOEXI7H1KmBd3vkGzhMJtj/fTUJfZzOzH2hzbDihOTpjCafweNBa0L+YL7xJa7oqQPqGRyYAZVIYyPrGHVQaBKl1+ieghxsET0D2KAxIVOrXJiZSI4wlIUcQJYdgeek4FdTFO9SyZiaYhhpgTqZQcNOrQPiXxiYchxu0TqaQcd3b3Fjeq4xQ+f+jcg03pj2ZQsJVrwLRYwxNrg0qRphUUUHAQJCg9Dfm38vDn1XwC0fYm9ODGLsrp5goag+GU4TGLUTjFl3gjWgUriM3/UYOydQ8vHSejUshp9cs5015j1yNI7wvYcF65Vs2dugkXJGWdbPQ6tRpTU6u0gezB2s0eBIyQR6S8FdnCCBpxBySAG4sIXywkkZPLdoowz4EAOUhWbith7G3ByPc3BdWtCX/T2caS6XxpaNQY1KsmfWnDGlZvto4gD19vanMwxB1iASo8XxIArcRa4gEzERRNFgIiUoxWV4dSDhHjWmIhL1iqOwvnOXmMmZiWux4ZE/oUKz4uNAjytqhUb1OhUTDvh5NhjhmQryQkiEsEtYOjYSMVim4Q054IJm8sigaK5YLS1OMCoH8J7f3UxDjJ7JG8svwn9NLsJrH2hJV8kt4jkp9vVATQKqXjMB88fbZfkDPKknemUjD03qWwjOHh+XC1xkQZ57FSuE/I30mLUdq8vxHwC406ydY/aVm9Bvfj+K9IiWVDetTD8rh8wIiQwjYf9q2UVSg3xTFe8yYoT5+xTG6HhwlScWa8+7+m3352AP0vDU19sUDPFh7VXA0Awq4DDwzBXiLLbl9m7+41Fn0QQy5WqcGUDKDxRD7gQReZfbP0djeblrtdg+hc8jpVAiKUP/2bTo91kLnQsaL03E1wVZ5goD/PV0wRlEBd4scBO8n1zjmitT2b7uYhWWj9Hp2CYLWC2+MqtLqdxFhlFm+6aiqSC02amHumhOkLpnb/BNY9Hyqak5Qdgb4p9da7P0CBQD5PhAJAtdD9Qs7zVIt8TRVr+gK19xJfHGzqdGQpzYWoZoeYNLrWeDKLH7biS/uscTM/vVjM3xuu3vr6qhD0p73U3AK+O+wSYMNfJq+GkwojNBUqlqoEZDUk9dVohj8sxJ+I9k/LJpseIS2vIPqIMqbPDlnSOYowrcbbWiuh9Mx8xRUZVviJm4VnXNoAbDeSY5ahMGMHpbOEMMLq5JzHKvT7+Ifq7NDJle9eGiU7RodOOdhXI+tY0WyjamdYRLk+vDGVTl/wRSjNhKbhUgfGAknb5+Es9Y4cxHfbS8aCrppeDLHPzphmVx3DfVOLcmWq48TvkIRn0P96B6O+CzqslF0yyJ62VBtWo+Y3GVH4WGXYKi9JdBjsWVx9p2xGKkm8WVchUOO3uLArWTj6z3nTEHn5Mft4i2BFBV2WissPS+uHQBl2z5YOUA2IL/gY1hyV6S3Ndr39+sy9lxajZhBhSnjnMEq0bvni1aeyGofPoEfmVk9BMMCzZjIjdQyBWVVUPywL1ukmL7HJk69nkv2taS5WEA7QACgP8B/QP6A/gH7A/4H4g/kH6g/0H9g/sD+gfsD/wfhD+IfpD/If1D+oP5B+4P+B+MP5h+sP9h/cP7g/sH7g//nvz8Efwj/EP0h/kPyh/QP2R/yPxR/KP9Q/aH+Q/OH9g/dH/o/DH8Y/zD9Yf7D8of1D9sf9j8cfzj/cP3h/sPzh/cP3x/+PwJ/BP8I/RH+I/JH9I/Yn39/xP9I/JH8I/VH+o/MH9k/cn/k/yj8Ufyj9Ef5j8of1T9qf9T/aPzR/KP1R/uPzh/dP3p/9P8Y/DH8Y/TH+I/JH9M/Zn/M/1j8sfxj9cf6j80f2z92f+z/OPxx/OP0x/mPyx/XP25/3P94/PH84/XH+4/PH98//n80QeEIMw4YeK61OSKcjYKQncE1Kx0bPPpdywlQ3yr3Osp3PpSmSzJCjGy7BRp39qtnF60a9mu1pj2oGrHSaRZX1+MgjWdrOnk2U3g3MwQQqWY8msrcKTccRCx37nBMpidaSpg0Z6ywZ2+DvIi1qtsLaOA9MmW791mgKiFpSG0pH7O1f0GOihRnnEymjVu6ihaZeJH2LRqL4dDLjXtFuk/rK9ef268Grprn8B6CevY8qikg5FTpwiyd109NcyOw0lngwU6r2SxYt2Mex5eqRnkT7JLcmazO2MWaMNOdUenTmbpVE7YWu7IFlktjzFjg6AwtmdJYQtcX1L1Vit8HSmD2hGZtl1DVomHhbTPk5HLbCdAVErFBHt+dNfa46cLklkxQ8jc2pB4xDzTpgHc9DNjjtdFWDQplB4q1NA1bsNi2lwHY3DvWU9oZcPOmrKS3jfxQKvVasFhJF0vwmJopfxJufpkndp1wEokj9Q55tdglK3A6QVJ0TCFKaPhA5XgoWQvYEoT/uz7N302Q8I2YuzP490yY5rIHTGg6hCTgdACKG2WA70/8GQFObySXp8Kvevcvqd6B5oOsNXLZXy/jBaXchVQAuwwv7EKACLVlblE/wy5Cy0bOZRnCgT2Yv4Gwh0LwB4wde8/WIiWChWqNOuVfDHOnX2snQxOVhUn9ccEujuGzYenpVde9ByEgIkLlMYIOpvw5mEpwjhs1EauWEPss4zbg7fURebEqMiEuyjczefFBqp8g3x0XH0KPj7gYrdcpvO+ssnCrSlsYHr5+cYPTMetXiwNfKDSGngjqBVCgNwxflRzwPpLrIdU17j+YtbDcx2ZWaZM5yu+8/8SUORnst56O+Hgma/vfx84BCueKDMVO37sLBV6NVEzSVFMi6p9hqN0d6leY5nOjsI7PPB6GuhbJ3yQNh8FUUiY6Tp/deqE6EhtjZ3h5tHAs9CUWpjCl7dYxhkqW9sWSC7QfZ9xqwbYf181eCF1MWoBnfIbM+TKv0TPtkk3ERGb6uajUCX25KHNgtoCOIOrByu2/UblbqClzXp/3g3G8dmCMwCCNclRt8tOFrQ96/lVG2e8bq8PQU+dlC/+n6PJgNXid2XQ0RdqUS85tR429Iblg2TfwVYpSgkSULxucZXAoh4uGOCMGbOYB4mfxjYap6gDBsqt964Wi7YAW7ReoX7ZHTb32LW+VuK8TLDf+K6hB/wqWfSlIEqs/nsxwWfCIbqpA66HrsBw726xww5TWSUb6ir3vj276rnH5vDOvLN0xWBl3SD2D5fJfywQWrWs3kiJd9En8ypSxQdg8jsigek1NmgGTNjqFMbGUM9DNJD44psOgi88G7Q8b53EHIHthazA7Btxzb6reVx5Q5V5OmeiFQQu1o3HK6aydQCaVI/fvOb22wwdnJh4z6HwnphzwM/S0ZfCIl0qZ9EMmHfMPqmaBNCdNqncMvGRO+pzRPRrfO1bnnF2Hir0N4n6YZDH9mzuHJ7dGDoeOjrwgIB/wCet3jHYRBitjVsAdfFFkrWLvNWoEQnnqyyMVablTEdxNusDTyVakz4G2pYIdxyC6zi7ZRPBrXKDznchLsyDgN/Qo4aodvQVspicPRxmQIqFVfdTeFd4wgfNZq+1/1bn2Pi4G8v+m3xBYdqQxM0iPP2qc6qIDypddy8tXnFid8JNAp62jHwEHrE5eRooTWPpX1W0Zci28UJZfVKUkWG6zg26hM/Fs0oD4YO+QV/WIBo5wyuy5UB5ZpTQL76eotxySXIq6903PNAQwxf6FoQX30sLtqPnWyv/noyUZcBKw8VWC44SqHVWRh/34vCB4ZCzxkHaTV8Rj5rNLA2AP8+pYV4nRgD2jvxKIu1VlWEDzhogXtMFd7+KvljlrUUsGSAApMi7hOx4B981bBJ3gruxBTV4/0oVPXJdQYA+/TOL+k7A1Ld+c/P1sI7H6JqkAL5jzCahoK2AtuphdImmWq5JDS+PNjzllYOtZ0s5auC/r9VZFnM12sF20/Kb4UpYcXMI1bOFvvUTqDvJu6gsF1qoGovUxfKKRL6BCmWp5rcSRg+SFIfz2CfwxZhLZONYaopYwnHIUdsxxUrvV2i/gOPGw2y+tKU68hGQdLH1TFrh7GQnFitZ++kbbj5UXz0tJJkoX3lYfVt2KZtVEWZyQrhzJWTmhEdKUx6axnmDMz5xKR7WWtutEhvNNpoeOTTMFif1F9V8IaEofDMZhmMsrspqxuSEtWAgs9FGSnFEYivO/RrURKLRTtvUQsodwhb71D7rpyEdsPlPJvHWasxAZ9CsgNPGmqA+Py1miUCU3JPYiRppKrGAog4tYtfIahFx1z6nYEzYcAXWZY4X59iSalnAS1hZiSepZg2SOAqbQd2U2MpyezIEXYE3Rnbb+zzvUl3ridbmrp0zBLy93CgLghGfdhCLjtBNIyTCvybPrWIs1cWxtj/UIY5/o3Ifz6i8oXXqBwgVPJVanYCq+M7RVkytFx2RN/ZAmT0weN16uMglOLczDSUiFdnszPup2Kluvkhz4TdpkUzj3+qkFN+OkmAnFUIv6qYh7Y0bMXBp0DET/st14+OBhpGs5WhULDF1z2sNsMWWJAQkKIUNxt9mRyzB40ooZc5hbOUKY93qFS5qYG5KKJKYnbpWLSFWKmbMeyWQroWU18ydRy2aXsSBjGNehlPlPOLIDFbrIrQvj/eqZIqxJCsBgXjGk9omI3VagBAS+zoYyCI8dMW6MFNhwutoAZlVa4063FxAWrnVZ+Icy1KOJUkJL93iU5rC91/wM4BxZVQLU8lMRUkrDdBQsaN7HQv1cyRl+/zUTciZ1azDyahOnxusGA+zizf/MIzI4lm3XcwLSWSe2IMU9WBb3Wrv8bCNrjpPCKxAXl6bOfSZ3wr+evUIsSVDXak1KIpbBtWglvEB9SsoxmYYvVLVtJtgh+EzLMf8CsRPra+tXf0AZ4YUWrC1Orn0muc58VpoTLVoEF6xYmAZtOXiDIQQmrvyKuJamOHwmx8vT3qGMC9RMajLSz1uzhIRoVvUnhMensi1OtH0k8bEE2mQUTgCIpxWZon0m95ymrkqkjnBuVZh6Aa0emHsYX9Nog7+hWX6NOUYFJgn9n1z+iakpzPYIUM/bn1G96GTOz+1vvKdpK7IVysS5GH5DGXA0aDoyD9Ku7rH7vWzl49Wy7ZCRfjM0G6/a1VhaeUVzLStWLdH/O7YskqMiFnskcAClrmhqwr5UXWMHS3a13g+6+VS1RxOhxDJBWmEEza41XdbnbtTb2JEVLHeGpo/R3Rl9q0kDGGTIXUvK3bZpXndvOWp82IF9QpGJHui6VdbJJKaC/yqZm+2lhQnxEBXD+xfcwXjaxz0ZRfAxn6gzl7TLLGQ1YTrsjjgrL+1ucUgAiTvNELBQNBxBunYYdnbyTSqGPCr+yv7zaLY4fQiO5NiPXx2Pbq1kwxC+E4BkNRbHCjdQbCHGenhT+jb9LFcQ4kgCNclRoFdXxQHVihQAb5tIu840GfOis3ttSIYaz9VJOpsDednyn8w9CrXN/rC1xT0MbkF02kFjfttMItpmhxbc5LEGaumdEjXOdgs3HyYP+AjKjN8AZE56PQ3XkaNfrxbdUFLOaITzzjzx0t6cQfEZHs4DWXgY8oETA4UOugsw49h88XMPzVZgjqCBmY5slSbIZjGQxzbQ27AoKjmdah432Sa8nAyQmxElhxcykDhUuQdMWRwsUXyhWEP8KyaYqqrqFPGBlMuPkgFMHJMIA57gdC7bHZNnQNoif1g5Vjj0HiUf1N3nw95j/L3m4UXrf34h/+jMsuBbkolGhWFwLzGVCDZED+ouBMrlQy3/43rry+A73pFobSoEIj2vXTI387ZtanuliqSK0tSyNrMH7VmYcLp+ygmqDBL4Yk/JzZvQAl0hfgv4sB4bFsCHcz+DY2wMllgIkI/a7sMePk1zaA71H8P7SKKTR07+XR9U/d3Rk4ufJq0o8B9rDSDP978RZSd/secfZnsVvlFV2foeIAiKlypvYENJXfbP4vQIT6qw80QCdOkYHrFx/319p81HL4njI+CEgnqIRz1i4u+jCJXtmuSXdQmk1MkJmxgAv78edbbX0idULIRKhTqg6zTXUw5E1dKXAK/coJE9JnqwziPBheDB6Z9xY9d7pvJ7tgoIIEM9ixqqRma34QGnyUnEAj+aee6aOZQzNeU+yuBg+7jzznXR6gcfv78TuKpu9bPhGV9ABW3wzkI4AlguPgD2mgsiuWsxDnr4YO9DIh3LxCZIPQg8VwEn8sruz4rCkmIj43APJSMCW5wGT8SbuISDB5su/Ic1gu7wyNnDFVo7LMTWpLtNsHeoa4R6VQt/e3+zqvvDoNBLOvMoYc6fzBwsF2dJUp2lR7ZggYkj0yJH
*/