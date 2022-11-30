
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
d7zxocDupEKVGod2MnFrfiZ4MUoO5Sa38nlYad0+5Y+rQOybRM27lGrVslyKMCBs6r2qotUrfArm7ULcvX0uoABFRXoSKkWWXBeyOildoSo2y1qk6lOlzitz36emKf/sM+xVFW8QoOCXcyn5ZjWnSkkA+dcDywzpkJfx62LOSRVNJuiuiXRV9gOT9sUHhp2GBAdyTnL90Dr9kBNVDjxDVhvpIAw7TfQF0sRH+oIKCUnNgsl0Bj1T6yz3/bJh871nw0cAIbbH0/RnJmG9p3OJSeWNDVmD6/gweO3MgbwY0WEPmDLQUTI+f/ZBO4t+yZWRe88ZXxKVpycCJKysm8ygVPSzBei/hjstgvWT6i2MA8qVv6PJdgx1oQsDw8Iv2td+mtXFM72a4NxkKFLY/7dHkJfiQdjNvCDjMIQslfl5/PyEAuGAUCC0Q+uIkuvdSXTwGnSkwsqU2P0aDMdUpzQ+qKFa8c61BKb+7BqDROHmnJoK5pnn5fsy1sucMwAWRxcqaivJRWDfgOpicQfKUerqmOXQ2sBcFizjQrxLMZdNI87/Um4kVVtJTfYyry56XpAO/SA+oHe2oMmvLBon86yxhFM2E0oN9OWCrC8GYf1xNmMQ15rMlDWAoRznYeQ+8XSaD3YY4F3djYl4jgQirmTqxfk6vRw2k9tDwsFqHbtJx33F9m4Qj1RzBAw43DTD92FqPAa/cdb7rfdANlOHQYk/vlgSB9d8jqeOu21yjXC/g/rzsM82sVsMbnTqJ4JqmdlqHZJNsVDmCi1BO1wLZCND3FSErZzjYYK1bSxldoB3hk/ZEYg5O/Ik5badebPE4EqUTtdXPn0q7Uh6WcJqiNSVq0Q3lW8dXkzKyLZ4YQm0Zx+GnUqDDSbHGmC+qj+mpU1FxvYelKZIaZ72gA2kvu7WUDBloXj8cnzAI+Mu9zjbYDMnHPZW2NbkYSYzfxmfNfEBR68xWiM04g2w0y8x4U6zwVaKSvjwbxn8KyPDBMi/VovG0VCfBXDHgraiZK1rdbBHtrFaHT7nAwRllF058pAGlZ3LI88KX9K38rjjA2PnXhTKJo3yzzR0NlAKDcjW9wlUqxf24dZUxXP4KqzbwlZQ3QVYm9tH4K+H+tGAeRjYzXxIL8OTtX3jeGCBwYok2V9SJygUcBa6YGlTVWgBv7ufdgpC78dfDIQpry6O9y+F7gfnYrzmCtS1J2wm0AHfSoOr7Gfgb1kYXXqUyob3xKC7HEFbWesE9qEueRw9fjFZ3yTHAd8qyBanmgwD3Oo+Z+leFI+DFyB0C/jLyk9RaqW0pXtR6Alex+/G3Vkz3jaJq+vQl/jdg8Ip4SX8nhHiQv38Z6/RpkdXJ7rVPC9e+Br1usrY/nsyUNTh4l1ZrfZbVTV3CzmxGIXUaqDB3F64Vfn7G5nEm3O9ObN0s9vYnqclJbi71Y3F8ZSeM/lws/B7SPJnB22ahK3CqWdQLtu5m5xAreGPPkjWM7iFkPfS9rv+EPdiAGqDj4cO+ercyn1vYFaT8OVLgjFqZsm3nYbFbXxezHlSnKKcjBxZRhP7HtybePg9xeIPMmdPnTtoiPQBKSuHfq2Rxr/kkX+G2xzUAj2cisGggSx0b/LOrzSSKrrQHUwl6fFOqnq8KHq+QO7/J/Ho9ohG+MqNOScIEn3gcaAkN9eIbWSkbUIKfS2Nq6jWTIhh5ZcsT7SAEeSN7fdo0rQffySaiDkVVT/ThEAodYFn06rXodgPyWN1aBWzohihu7NQeKRXoMw/Jaob3x1pG5NC8yk/9xSRwCTXD9YxZzfFnUQre/TJB5V1q/EJ6LV5LuZqnuuFtLJ4v1LwazoGvpBf9pogwFeV07/CpOAHMAhixMVFkofdnRp3dXSCX4gcoXUyaOHbH6QboAcl1Q7uZ7SdzKOd5t10rERDyalAqkuZ12OIuIwkKUssBLLM1KaP5doSZY/OfBwdQ0ee9BlqzCGHJP2zgNRj7166wmrc253zvCdyshum3OZTaS4glKTL+2dZu+1RvABIM3hpt+GxR/LokK8zwG4YuE6Zj7Xa3MCpG4CNryed1vYITs8qYOQt6M/wvMOLhW8EqBV3WXwBes/mhRTuptoW5Aso2M0aWwsvpFg3wHbh3wb4F4B/t0KeVrbLhhuyjfC+CdjKeo2Uh3Y0GyoOSPg3YPoNvd+qk0xYfhkwB2gd17mAp6+deLVG6XpuiSRvxytD/NDikf3o+KNC+eQ4kfnqmaNRjqMR3g6jIUDHhWZZ+nkNlA96Yu02PL6k284Vz6JbzVPbkdm41tuHAagqI3FTOhGvwgqG8a9JmLGgyjspgNs7HhTYgQzphqPQj6A7vYU3e6kFW57Ii4so5D8f5s8aW3ld4LXkJBUg50GGCvVZyyGzX261VSnf0dJWlkRq0W8etFVT34U48tQK7PuPosm+50FrFRk0L9I1uFzmSE/haraeFIqefJNOeQA5a5a6rMYd6M4FMTU+P+Uf8j1Ugn4YQ7xADnk3dv0OizZoq8JzFuOOvRJRgVsSxlINvNVWrUKhgy5XeGCY1kRieuXnx8UGfoEI8m6PR7vDN8DiHjd2rMLap4yyI4/kBTev1dm73Wjwt74O3te68XeT9kVlr0nUsUHUUalecUy1PpXEMoCScXcOXQOw1kagVyXl2FEHTMzOK9H1/98Kt0/1LFHlzU4xcdPYRCdNbvtx5aknEpaauUlgFZLAlkiSBFI9SxxX/q3A/3M3kcb1uNMN643yP0Oh78QR0dqwjl+fBq4/Ce1KhPaVH+WANrP1/31oqwW0P/k0EV4i5/4j0PeT/w+2/pWcmz8AgENLrX0NXBzVtfguuyRjMslsdDFYUalSS0vU2I0anFhJYIEIC7ss7NKaBPuqPkTaouwaNAsYl7WZd5lo1fi0arVV/8+2trU+9SVtTCHELPkw3zXEJJoq1UH4+yeaRqLU/Z9z7swACCz3036QJYn9vdosuzP349xzzz3n3HvPxynsWzB18yhasuGpTi2IP7Mu+EWQh6Owk/52+tOHkxMHW03oTGMBNb3J5PFirM7I8eBGfqQBG2RiEPrTF9k1n71z/vFEyys/+OIvsc6Uwd6f3sjm5PHtvy8pf0qOefL8Ke0iDvJtJUJ5PZ+qpIQ5GNQC12EO7OXlFTDl52DCHFDM9/e+Zy3YHw7tEkzqvF3Kq/lQUFr90hTMiYkNsFlEim6/qmKWT/SHFN8Hlb1HidRSyOJxJVLCs2yY2Y03yQOdFrVeYmvysC4lBtUjaryOrdW4vcAoPKqvVqUUpMrrmJ9Uu2EHFxEklam55GVg4I86PMXRkO4gvehlvuzQ50GhXB9kD0lxShghhZSOp7A1t/o65RNZR2nnAhWke1DJCeqHmVFLJyklOrBSlz9Gd51cx7sBf3yp/fAjGtbNPGEqK7op0tOZuRblFVMJP2sIP4QD0GVZBBGl+urdqorNao43OS+8NQ45e6qEQ01BVyw8WV6klN7PpxbxBShalFkV+KeizqH5x5wkijpOn5QPVaVkqJS7U1HRi1julVbvxGxgFD+I0bPIFmnVR1agmH5JfQ9zsCyzWp7ir7FZ5hVZr6VHeQojDcmPvIHNd14cEplXgF/YZat94cq/mY2L9y8XcnB6/2ZlXTOwNHtkBhZT18/gAGIKUblY7Lw1lCl7hdYG9VWMQaXdg33b0GhguzIL75M9VuaGhSwqHgE6UxaKrAIDuno4rdUwyonrZlP1DKvsyUzEh/adKLRDJK4nfF1DI/fBerBgF6VWS4SG9+QMwp/bxidKmQ0bbmic1pLfyufNmDC3h68Ubd4UPl3taAO5BnFSuKhZ6qrnCSTUhbHCCHYnqaWUmRe/F0mr/gPjS/VK6n2UuMDKCAC1y0xbqRvsCg1ALhelBzDFGSC3xia7BSlsxhBLJvXVeqLfvUhT8zhtW7Vr38KTvPWm4EUs0kajDWHiG+d6PKFWIi006ZRli8Bki5pZucCzagFf44m1WLlNURvpiZ1FiFyJA+ijNrCxBnN0qZRJuCaOiW9jFiJOImuoiQiW0klBma2UWVPogU+GPpSOv8ZhX9NCdQNJsK9po2BhIapFsC9sRlJ4lch8DY2gXFTUm5OnTycLhcNSZNfnj62hERBsaqQ+aSotx9mT/0AKqNEakC4i1FP3P4hki5rV9f+gHD/lYmd9aCqT5HKhtVp9FfPrajvNk5Mq0mkCaBFjIKTSa5kVaVZjmxB9BCxHL2FGkYD0KEHUE3sSZFzE1/lKIhukmYX6cu6Xuq8Zx4GZaJCVlPkI65AZe9s4Kx+T2+2dS2GluWytPpYdORhw64OYdopBsDobjsNlN7jaWOqq87u1bX0mPUl0uMcWU/PjAAR/+q8y2CRb4cmkAeljQx+dwHeEgVKhfe5tPaTVlFrZXH3/4WOvuilTs67XfBv1mhN3Z5iGYifSKxjUcFfmc5hA7Dtn0d9fYpIjNqMIP7NK4PPZR/BpOXxTZjyGWciynoTPZ5+BD0qI1IjvtftuNzIalWv/53FotCcwi9407hOfNmnP7o3Fhi+HDdxM2sBJT5h+aYUPZQYWYTME/J6FrT+LjSszsHWWRT0/RiXo8bksC1+gBX2VoPjEielF4vZKIvlPoY7vh02gGKj3abv3Y2AwNoDxsAs7hI5cjEuN8RjdXr8Hj2zf0n78GaG9sAw0x9ARID1Q8i9kPmv4HsHUmUXloVwtVvGwHdpFmPATERj34YobL6beD7fd93C6YBCp/rafU3+d503iUSmacM8sgJjCwzo3dw8BIL7/NmkszhHUAO+6SR4FJaVFwqD+dYOgLHlqfKCVqN5aTJ+kvf4GxZZYwJaOqMF92pdoRTTpWhBpLdjQ/rMGVXu2X3uzJ9kH+pT6Cr/L0v2lhk5zn5dQYUW32iGorlHtO38hBaM0aWutU3UBUvUlyzNMZ3ypZjfRbY6d1Y2iVxiMyFYD43P7NNGSFFHiVPqx0VBa/fzG5PPH3GTlNWWQlLfQCU1nrd1GgYAG+N3WhISsh4wcVQNJCVntM9Aw/ZCRP1WKoCHr/KfRuiV4aeEFZNwyS/tdCPN0/xQ3mLfKfcEKnqB780+xmJmCC+VCO9q5u5DOg3Mwlx3G/UQK2KQIzDWolFuBdDDblGvEp5SL/FTmOeSZWZUznjDxkjaW5cbjFreVZdXSF4Fl1cMXNlMB3r9wno+OHLuazcYRwbpLyZjMy09HtFuCGSlxi9LH6qxAkyeeiTY+cEwPagyjeifXEf9BlyOnH8oQip3GJV//RUqD7vkXmAsAe1O1K7aYTMOZz5jg17V9UtfvKUHpEXdjC3b23g7eGR4CsbojBiLqBhELdRqioG5k6AsQMY2vTJirrh58Wr47td9LaSA92Pb9vO2uawgBhC+0wBrahnGX2sUMKItwiDOh7Pf1sm0Tyj5NYTgmR2nKsjD2E588PyHgEqfno1oSPedPEs/k8/CKm83BJWpwu/baiVPwEa+ddNhGVgyspEKsAaUWFqHNAytQcIc3Cmynduvr6Qz97SYy526y4um8BNtZPEr205FXhSHwkMvrbCGfzj9bk9iCdgY+/HYMfMHDRmg88kVjCEQUnYNB9WVpOvomdvTsncZB60g6CU59d5+2b1Z8M+hl25VbBr36jWC7QGqES6Mkc099QQKp9DQ9SV0XJm3RJu/NAmQ3FZE6OHy+nqZYcQ7Cw2k8SfGXT78fY8FBfnA9gu0V+SguQ6CVna+fnAQFtzfOii9BVDx2R4ae2w+9G/WUtKcG9ydfngm4xXNYRX6kJ9TYibcr/wbri12Lof3RJQja9vg42zyjHv/5zzPoESjawlZks9YcVpzLKvKU4ADbL0Ve4qGMaZPbcVZ4zNwxHQS1SLvdYe6Q+3gNSKjGex99zKQN/ddl6L4p1Li1d+Ar68dgrXVHIns6zwsJK0+gx+tyaR3+gRdR5xFaTnUD8F4MWSOx1imOHsee4QwWZa35BUdZxZzzXUfk3Z0Xhazy5tbzmGsgsiVeco/j+PAMtp8dHZ7K3sKIVwOW9kPnACuMRo5L3Xj01SlE9kj3PUFXUFL3w/xJj3SfwuO5sOtBGI64fTXMn+c51UxfjDP9+5985ZmOjJ/JTLfamdeG+9xiASPLAdqDGvtujQdmO4dkyWRg4SGvNtsAi1xqJ4I14aSFg0WRUk8LlssOSFv9Bt1qZWOSqD+hMeGKm0xS1yoe1QbbuIlsf7DVJ7BkWji/jnD+5MdfGX2lZwSnt77A65Z3Sw9Q5p2KJQUVtbBHesCAEWOisEU3cZn8mWkyGHMRxm0/+sq4/NXnZwKjgauMUzIUwlPZj74yni48MxhAXms8GpJ4KqpCxV7rbf7KmHjsxBlA8ZVGdmoF226K229c9vNH0onslKCIdOtWFNvT+JIpOdoabGtANeWXQdPc2uJN6CSJ1lSgqxph+BhdfOVwfRUf4k5brbqpyQzbq3y11O7Fa3toKl/1BdTSfLw3yVcC8K+WrDXm49Wa9os2s6lwmRCcXbgsJ3i2T/t4cyyWMDAf7mQNNtip27zaX+GFN2E8tNyGVy4HgfteAW3ZIwfbVsgD7ctZh9USyrP7vT7t5nMwDKF2wXl0sxKGIZE32V8dB6GrjksdMf0+CKoWycty2mVWmm2JurVum8lUHI7OhWeh99ECYkLcwQlRB2lTk7yP5uZQYiSGJk8XbU42edKNpcMdNsy1VmqLlmI2K9i7ikk+5PH5G30naYtYlDp/biOavsDqbRjJ52t4cNMiAn7noHHbdPzZUV+4oj5wIUAiwDSXW/2x3ay4PiXK8op6VrVEqVjCHkXOoDxM/IF8Igv/jJ+BvJTa4e4JjqAKlWLkXVn45wcTNSTmsWKgovBEJ1GFSjHypy788yNp+njkpD4eIQtvOiIkCBRG3x99kmB+MtUAF0301pG1/68uNwPrE+g6MAfZdgQvB/cA/eUOz0rcB6LRETzCW8HLM3SvpW/gmWUrGvLMsXwiL8QbBHxyt5WVzC6xfA4N5hWWlgQuhX5FgtMa2wUN5bGqErT6oGsED3+klJawsnJeo1yvgSl9+V0e1CinGmYPKxdg+FSjnPkrFV8lK8MINKy6FjMS+etZBzysB2QtRnOV7frV8wJur+IHMl1CRlkHbzeb1Ip8j1/7wZ1mtJ2ZB6/qk2wHqipV39wa7Zw7AD0d7ontlSe1R/GcWby9Wby9oontuam9vhZ0FRPCm5d4tf+8nCMWll1uG95S5iBaux9EJQ9IlBU3uzXvRvhh0AdsBwIwgcqqAZ7e27ElEuvId+zBM3m6Et0pqUQ4pdZwyFZrklQk1YXhjW3yztDbwKthxS+yUADwUF72nykUwpK8elbqprvs7CSrlw180rPlqNT1MvKs2jx7DdZKMXpBczA83pGjQeMsze/XhQFZvbxya4Zp2KPboVP/ey6ETRce30KLc2rgIx9axX9z4N9c+DePC5oFRBh2skqpzZtbo//hpimrEGrqN4n96/jmUA9/cyI8ZOeRdytZLcQLppxbVALHmMTPJ8lDhBthog+JFO+6tJYWCRVKeurm14zxeB/5l5zaP+yEYSZdZoPNxS2/RD8kdsFLtO8NXHBreL4pMDu2N9lc4gYcVPUtGabY3nU4nW7jTZNJm39LRpJlanqxKpgwbFLw
*/