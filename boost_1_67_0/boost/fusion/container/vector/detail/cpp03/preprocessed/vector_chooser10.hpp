/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector_n_chooser
    {
        typedef vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
    };
    template <>
    struct vector_n_chooser<void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector0<> type;
    };
    template <typename T0>
    struct vector_n_chooser<
        T0
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector1<T0> type;
    };
    template <typename T0 , typename T1>
    struct vector_n_chooser<
        T0 , T1
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector2<T0 , T1> type;
    };
    template <typename T0 , typename T1 , typename T2>
    struct vector_n_chooser<
        T0 , T1 , T2
        , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector3<T0 , T1 , T2> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3
        , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector4<T0 , T1 , T2 , T3> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4
        , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector5<T0 , T1 , T2 , T3 , T4> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5
        , void_ , void_ , void_ , void_>
    {
        typedef vector6<T0 , T1 , T2 , T3 , T4 , T5> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6
        , void_ , void_ , void_>
    {
        typedef vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7
        , void_ , void_>
    {
        typedef vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
        , void_>
    {
        typedef vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
    };
}}}

/* vector_chooser10.hpp
ikZLoVH6aIwQBQmmoIEUlBkFs08KeUwKLSqFgkhh+HOQajlomRyUUQ6G2xmp4oyWdEbpOWMEx5CaY+ijYyjYGOaAPlJJHy2uj4LqYw43IDUa0LINKJMGDO9t5PHbaOnbKIPbGOE1pNYaWn4NZb5G5RIiKQhRRITI2kJUvlQSKJVyJJVsmEo9eJakfJYicZase5YqMEQ6MUSRGyKbDlH3g0mKYIoYmKwDph6qJqlXUwDVZONqKo8/SdWfIuVP1venCtFIYBoFSCOb0aj7gKRjQIookAwBUvmLSGpFFJkislERlduDpOJBkfQg63lQBadImlOUo1Nk2BT1gBlJyYwibkaGmlEPt5M02imy7WSTdipvFOl4FEU6imwQRRXeJmltUxCcLlxk+s5eULSbQRGBsBcT/beYaOcA8PoXE9d/3w2c+DIidISPi6sG9R8XA34/1sC5q8+KP/5PrLo6OH1crBnuB8s7O3u10y7VTuacQZwAvXMPYHcBPu4B7C5A/x7A7gJ83QPYXYDuPYDdBRjdA9hdAOIewP8D2EbYM5MP8nBxcVW5/OcrIr+WKzpk/l//m5O1/DbZnCeUhtuLNnYp2vg/gF97ALsLMLcHsLsA5D2A3QVY3APYXYCZPYDdBVjYA9hdAOoewH8B2ObVs1dqc3D499+DNqzhxekfnW3Zrx6q5cNFnZDqgvGblpnWkk8GRM70Zvncsg22u/YYLmgHfeoY7wd6/xAS3PuApy/Lbaq+8WKH/HAjFVtNfTPFCttZP4qInFjwYAFoIYS2pbZho83NQyt6qrJQUSh/Zje8F/4W3gPviohhS0GPQg+sHKWEE+F/H718iXJEYXwzHotn47nxsXgrvDwkCWKvbQ8Z1B6EaGhrQMw9nT2dvceujnmNeY55R/X6dvp2c6K/3f+WzJZckaXcIcrjNfFyRGeiPvE2UYh4lliMv4KfxMPwbfhI/Bb+AD4G36EdHyWfK5jioqXv1uDfBbAv7fl+qXt/iOAq1MXmBs3UayIYLEorHKpuOBiVkq5MUw5OKHMJTHB1Fjz/6npZq+BOUTdc/qm8f6Vk1PmC8HXCdDeZpK0nELhvwSB+/QEudMthcWuBObzWtRjOHZBEKkG0uAEAgI6FEQI/zrAk/jd3zLSlqOXWr634lc0omUqD6LhI65/lQiEwL0uTnbAtP86O6fx01PoHZ9/p+Q96ieU3Yw9GJ5876W4txMywD5NjN1Fezl1eLlJjbvDJChfxHRKKEh6Z3dAjma8tDcqc2XZqHdXJ0CldJ/XZApK95ljpt+StfjlFrPopj6d6bY6nCwCsYpw4U6YZ4zaBPaA1vRRSqVOdTM+ZUjwLpTyc/Pu1kxw08VmK0pxJIk9pv0linqASNkrig7UTWkLWPA25CgLK9aBKQZDEEKYS21ci0iawC6Se6uUyaYtO9foKosn2ZJeCDBJh9Up5BolOpbMmiZdtAqdAiSm/WfnpRLmeltJZg0T9Uh/txKBS22RKR8cRiNMZaYuIxU9HyKyLAreysloDteXs2uEXwecvWvY1Xoh9XchSsAr8/qjS2Q0WrZb/5Ni6BD4J4Wcq+vSZjfJS07H6VSOSzGXpVL2PI0pVoUN+P1vvq7TojWlN3P+TCWUWElqjK272VpnVnEakVTqFzBSkH8zW7LnaZHs67arkUSGNM3HD1h5RI94y/VN2NdqGku/XNYRFbjiGn3Bh1S5MWfxJcYu78+ahHAOF03Ux1m19AVb/dnfDwENLTaRwXyNW9rCbvphPxIToeMr06Y0Jvct/UBZp/eIQk8ls/obaJkTkjydJ31uKviwWC4J1qDhA3WNGvxHQ9NnGvnJ68eqqE55g41PXlNVLjvbseEdyd7tgvuEIvYMEnhC95dNada9XNouJ/D4UYdhS4PAQX14eL7YaJZ+9nw/YhCP9PK826qHZUt3Mde7pVs9BvY8cl1b9gtsEkVS2VVtAZBfBBh9fltoIjk5+ZNU35vpkG6947/Nn+V8RDz6+bJ9tDrO8sS4715rm2NS2NHG6/DXwU+2lwM8ML/zE7QZM6iYcFt2Rge8G3SNtqU5KBn33Mb3z80Iw/yN/g7qlyETKi8ANuKejmm++Uldj7WF23/U/cFo2qqab4a67eRiwA359vuSlADJvUZx8dvj0dmWooYi70JNGh0txugnzohXKQojL5/ZJ2mlZYAwupZ1572mE0Li6lZIpCcZkOe4QkmbAF089HxkooSMU+800LUKnjoOKarpbvRqELi1dovFaFV8NsHvxfeOc5mhR7l9v29Wv3nzD8b72TotH9CVN92QZwM7k1mmYOdF6pgO4THPSM0TxJfHN2T9hhsnPmZTyDH3heRmSD7uSVon0l7xNuKf8wPqHDPvG9oSWbD8AZOp2JGijBwnzqg/7anDv0rqOB6Kn3R2eBkrUGtV/GVv3brby2kmQBy0Zx9Spk7o9+SZ4YiJKarniRWSIt6apYc7PlfcRicC3Z9VTxipjTpu4NNGFFMJ7w/O0h40NA7xpHouC/eYjnLCL/cbrQBcf2A5RIUbEvaI2gQC8dcmPmO/vyAhXSax/AxQLAQoe1HnKfPAnzoFoz6RPmNJuWCksxw9I9C08ZT7WEkflZd4bSzP8lGfChK4/O3RcomXZaWVw8vUM1HRIQmPj631OSaX3yK1N6NeNEN4pRDxliaQHIcxBQcSRfvvUkyu44NMDbvX7popp3/UiBeY7MJcGrCp4+ILzcndWHQVjfnrU9Kx7HlhdrFkw9llJPwk/F/Hzx2euM4PvualpJxe3grffPdGR44w7ktsy7s+YsLr5IDiq/ikiDRsXfTKzpVpg2ygjuX4laDNY5FeGgq5Gk+WoI09lbNRLDRwmej3bVFfXICSX83KZfyl+m6TImeBwRrXeahpyNm+yM1j4aSYzr0tGkjeNfqfr5ACeON0sxhgfD5jqsgPmsWpyBKB5wrkYYaoBMQlfYE2BDQh2sQUPU2EDRfgkCHf8QDfWYfkoEdaFfNvfGs/mpxqkxQ8YRyesAMvlcgKnusKSVgquwqmEJhz8jLvw382edSG5Z0wxwuCdQla/d7M0FRLbBd8uZD2SUx0EZELUl+bkhhB4wyVPs94ACSz207+7fg2jnHOvfrBS+Aof0sU+rIHCEwtc195iUz5oZ+KosETX4ZgFnMwQwnUpELjigx/oWAGyPHX+etXKdR6QG5xCxGVAIcVCmVhuKjQ+oFkyJ1c486n+32PID7n8M0ZbX5DAkHf0qz8xTKHS5SKr0mXgsX9mScx3wjqcAPf9vTa1E0s9E6nX7j+LWRjwwpr6V8hSVZj45i5kOxC9DDuB6A2Th0sTNV079o8XJ6G4q6R75N6x+9I8dTSu1xQHYE3/2YTWf/aD4gF/xKoZ827pcR3r3JjGpvXjclmcKEnXO0JFd2nVr1EHPGcjbORGH30KlVRXJvrGeqplaF2pzQsST6RKZvu21fEMvBZ1JyxFX+6JjvwR4xQ5NnZ0eNxs/73fxG57M430qg/Gm3oAQPlQc8Rf1zWf46bLmdvBrq+xT4xtJI4SEopCWv54vDvftDRNsxn4UfctU7xzc/yrfLszCHFVNVe5rIMnWMUkptxw1PzF67FJGH/D1GfnJkLqdwepNU2jXIFWby+racCTiGNu4b9i30u4tg2zfxkdvlDMvsD+WaX7IM/fIHTlmHGHyKZzwSLugL+0PyiuooRxmftrtW3U4RaKG1AzLGnIxtnjkUmEzMcRkB+D2W08HzGFebVxNLQ62Q3R9EWkfsencY7NUvjslYO7DjAu/kIEvEgv4L8tPaDud+XWdk2YYrVKlqD5/FBvzfHqU0GBgQQnocrKSfjkanR+8fc8Vp+ZxaZyCaf4uf3DrS8bKn/cP+p9M6plsYOUh8VBy+9jIFJenCt+sxwpum8v76sIn9D6W+/qZvo7XjKLZuTJXYulEzNW1SUc1TcKCp9ruBok9QywExZhM519BeqHLMyZye8cCj2yOjzO6kyf57tYyORhZ/QjPuXYc0KTOrGPcV8+yA46RkHm0J+Yig+IwFoXg/jlXJ9Jqfq0Grud0YM/vA9/4kQuLgyk1bD7XdpeAq1tp8LZsxteod4dARtEqA/MyjA3ayHR82Snk2dPCKhDcbnNnpVlEWtfQhmBQlf5DCT7ai3V/mgNmkoPxyzLvLBdiaXal4SlbZSX3AjyaRXyZJ8f7DRrW6jdvlEHVDwj3GiZfZIBXQgcd3AKykHdu20ksTkMXtG2WfBkbnMelQUZ5lyRfjyXQCmoIPg2Ptlfhew66NxusSLOEDPLd9kX1Hxq5NwzDrybnJ1tpcJZHniTfyRpzGHmt9vAd7vKgtYU6tqMkS1BQdp3h78Jll8N2MHfH7tjW0nbPB4aQOnzrTC+0BFCm7kZ/vzx2ns2YN8ZMKlYJXa45fljh1Pn/AaDVfOn27ULY74o3HlF7PsQm9gX7Hk25ovIfMCpyGeR8jE+sIBVs1GLwW8hiO6GUk5IecKOmbPgheTNn/WzE4okgrv3QBbgwYTChl+MxCVh52QxcxdNvDS9EIuTZTdeI1f4ojXLJOQK3YsSqg2c/4z8ePs8tof3xnoZ3Glb7NZUz90q7vP2wIqSSZB5Wmh7CtT1cLhdc6qLzON1sfTwxiQnXl6li2CauOVWrb4NSK4qpkVsWLfdmmC9kmeiuXrKqBniM/mmeGJQLGF243ir+OCZsWaM5L3T9mL8Kf3QYkJuujkv84GY9C/LU9VhI/vZOp9ly1WXisrSVicw5dNaKmnZG9T3r1LEEkjMsiRrNWw2Jjbpc8vTBMu7BsPv1sWCntEy6LSh5gTL7ru0yR6Vso9lY/QhGaJlNPunfYAz5JndxGYTduy3peJN7xGHTK/los33wZY888VuoYGVG0pY8kWLX5fELRax13lNopQnO1o/w3M8HtqK9DXE3pFMHyyqUg+g4dP+CJJfpkqm5/PWVV++P1rDX/4x72C64rnslmuq3qxuy/mdWeyJuoe6M2chWavWiy1ts3mGLQ9HW5WvnKcqZtnWeZCK157fHX3zgtp9x0r6g9bvwBanfc20+STEfo/n/WadCW45DtdVpke03OIo0m3VAdWnzbB9w4jjkW2m8/JSh1ap6elx+7tLbWodN8lU4jA53eBF29iHIW3LtUJquT01PUm2e7rZRPuh+Zpc5NU8+3LfUI1G3BPgcnFR5ydx+X7SvZLUluqVj5xCnIz5+2PcJHDrWq3V4qvVguhDtQPcS+DIIfZApu2ob/qU8UOrIZyngtzPimSS95aonRvyUYxvMD0nu3JrvABXNaiMGvFzBY9/DHWzn88BYh1SByD10xBBtrlXbOfM5pLtyIfFBsLZf1FxT9GRBmu4gINJMpnYtm3btm3btie2bdvGxLZt20mf7H32uTgXT69/ddfbVf/qWtXf1xddK3qQ6St2bQRejjaW22rMlgG3l32fwBVkTcHqZEojfDHojWFYnC0rK8VByVIog3WGE4Z74y5VItM7WTrRC/5vJM7uMJnN2Cwt012f8G/s72QMuoWF0epDlZ1TEFDmnsAt3e7yooEulPLSZTpJ4qrn6DN5KZKnFozS5dpZ/gMtY8dpzpDJ3Pd7VwduTLp858o9S8Y1k+oSeOXmP2dTLTFwBBJMmaNtRpxlfKYTxROfEoeQN7GgpTJz3r8fQtV0re81x8fq550Uuhg636d9/URoEb7f6aWy7muD5hqvIA/vE3bNfMbNfTQQIkEj98UXILYuc1KaR3lvgY2upBiV9Eyt+0FligCaddw8KVFarSqP0XtsyHKttDOM7rKyFa165swoU2HtHCtBOEK6XKik35e/MeEqG8gsDZg5Fg4tGrtI/7Ith0w/0MZKPLd8XWBQkvNG6JBI1MCJ/0sYROEqVbg4y2Q8dYldXH9t+oqqgZ3PlFV76RE6Zu+F0Tb1349moZsffSFttzRqLp5VRq4N1p7YLM8/zHhWb2bXoMyBtcRlaBMFF43VWRKlFmsIl++PiSRerN1Inw1+Zprr0HR9lnC0G/zlhEO0iLd39Cnal6hsPc3g1Rx0f7NTC5cmNLgCPKn306yC/jStPj/NK89PE6uTxsfAxcBFv8GwQa/FwPHT6PLR9xr5Dn7+XYtaC34Da0RoBH5gMuUxxTGlMYUxZTFFOSablJz8M+k4yTipOIk4aTgZ+9NSh7x2VAIx4THBMaE9gJrCmrKaopqS/jTgbmkYaWdpdgw7+iUGJYYluxe88XtPcjn+tUgM6Wm/TBvol40YGSAnjQmqRowNEdPGAtVjx4aI6RNHjHhIkRL7pHHDntKkpUGYNIAu/htg5PtfgPd/ga7/BTzqcBMjJPRJnf5fMPL/Bj2g/xeg/V+g9wb0c/sGcPDB6Hw1SDl8r29ZPUeCjy+3RVeeXlwNOp+tyXKyDHWqoBayJwHUEfmLrX6n0Du8rqMaqx1ZllulhdQUXfG9iiWmMk+dJYrGSkhHz1y8B44RXOV7pLEXT/iNmsCQ6/hWVFzTZUe43RNlyfcbXIrpldbA6cqZajz2d+tVLTT1rrTCTu10saSylyBUUkugm9nTWFUzFLnPFASwVJlv16Ko1Ybh+fu+lmEqijRS5EebEvBRrbCM3istlnopCn7zgCTWGEL+9xFXn+yFZtYTHaWfDQ1n/TpsU4L3GANW2UVmXqZZouvAPu0VxXcKOZ5oJXJBPVRLXawFx2q+d1I4blTnEZDKAvMWkXvZnWhWbYr9L75lm1641qWyu38R2c4gzyfbl0pa8rxyhzjqOxfQ7wyMYWxTpcNu5wcwYmriS2gbD2cYLj7Ki7MH++AQR21ZcJAKXzdeBYxOcOHsM9/tdyuI43hS1ZYvff8mxC6NRxS/KTvwHLdwCGOwddoaozp4mb6Vmx3o4t6W8JKnla5OVKggr4LWJKtXfKjKvwuNnotvgsA7P1ebT9KVv6Jvunj0O7HazrULauRed8bpVuFoCjIzrkFZcMFz5T5801wECfTbwVhyUJQw8TwHcHmFls+Yx78X6Yy46GbhsWqVHSCPSoM9rP9OArtzHf/LfBsSJpaiP07FBfIoTw97dFTF17i2vPwXdDvu+uy4hgxq+Vn+oIoTGDj7XCsFVvZMV0rqgAc+Q3yllKFX9vq3u4HzjD6OZ0NkcqnsCc5w0R0XONoC2OB+hAIgNoQzy/0nrLTXY7035y+ZSM/YTsxAJezIAtdb2d3blGTHAQyBYq11TLriHZq9hBkslPKXmoYpg3L5mw7d9khgbNfat+5B+Sv88t8xs4BSkZq1qH+NcdzwXrpbEF3GZldLMsWfXHr9T1VwRasojoJuio4XezAyvHV/zexUPi0kWSWyexfRBB+FiRHfyz4ygXHuW733JuVQvq2WTt9jyFERcO/BQkwGislCytwZMhnbjtDdV3SpGJFvBFesoETY70b66leiFtZkok9MvL6E+U6tUs/fzAXeasmKB7bgiJ/j9JyTyi8gngr/tfvaP2RG6faJ6ljyJEWa4kFsqfEoHCP8EV+WoOT0wYZmosLpLVX0xAqaHz64LfmaU7RgG8cDr1cJJeN/y09ZMRbjIY6NN//LDrx2lyltJ52/b+bcE+fD8HDn66ii/Z4SnknuRyiYclKzI7dOkeNynil5hMVyAuXrGecBMfCXFrqK/57jo0Af7v62/TVqg2n2CdiBo1d8JkjaE9zII7W64D7xcmDd51D0aJQH5N5R2Sfy8+BDvH7pAU4sXOG5JYeD8mMUgu15R3638F6JrNiNw0sCr+bj3SxG4U1+djqJx0vio3ALo2PEjLBdmc1gX/d+c8mDu5Wn7G6665u5P/txtZZWqdOZNeHlbWftWJa1hjezZccMJ2GtQED7+vDKbUVquFNGwDFxPn2Up4jAwft909eSN3sNIvo5rkbvD5/PXuk5WvTW12D0YUzGLN6S7FhYI6uOcMNsJ9mYU9lnvajBmDab49bs4CbHetImp8cHk5rigNos+RlkspwWpMVze9wmYmvKELriwUHutMmuYM5zGrdtJzfJic27/Xr652JmUUlKocDUjYR8D9JZK+uzVidW8g0GlYaMKyGdS6OwUpCa4oGMYpMr8Q0fn4udTRN5wokXi+gVaa4NwjGq4kLhIUx8NexhAJNcDG9c/ueHbfOTN4TjREiDGESqwpt+zhfyMu18/JzCaJZc9cjfDQ+M50OELaOj1J6ZvGE2Z+tAnjNrvaLyx7jxlwghzkzXhF5BPcwIOMW3S+LyDnque/GBDq7aAlSlL5QcqyYSLurWhpm3mvzhD2WxrZQkaS9cFhPcZt3JMBNcrtFdymvbalNKXM95OJL1uCc6aUU2Ekz5bwym5JHQKoXey20H4YTxk9Z/1S2kTsfVHljH03nDWobea3+tJzSScCmk1zqX/MIbiW9u0L7H9csVPBdqTDbGYrPr1WZo895jj7OVu5KluSecuD5Qu3n5mq9a4kp5u3tOyuCUeavrGhYCk+T3T8qVC4fNvH0fGJzm39TKpx2Izj0Dy63IWiKyUtpt6feXsSt4zrbYZMaw6kX7ZYOUvYAjcZilxXNlvIb5bvOGkRwmQjf5feO5Lzeb4u7NGBesrzwRYenkZBqKlxckXxYrXQ4/V+E4i3EWPetcM1JrSO1wuNUs86Sq7YLrnFMRzkqYfIbXdCm/q4+RI+nIoNC+sVNbIix3zrcYpkgOs37hOvh5SM5QZ9bbMqTH1bX59DtLzkg+UBrF4Vbonci0ThkprW15QOo4VqEB7meWHr1z3msXiHNDqjLTO8VzK+jeZQTTuXn9BkvnJxa9w0USySTje5VnLG2okt5LL0CP7yO2+HeGcUmdxughBw0aUI3SI0x8tOXgNmgG7gWpZ0aenOu3uKkv9DWwJjJWZUE3yo00YCYa7XlUrEsDTUyoqfY8/67KAk/cq6cMNkC3JA67LtRxg00kOvBQWJNFmEBSRxppIG9E6HdCqqMONODXsMFuQOqnw010teHCtWBFHjGok9ZxEzNYs7FLHwOlfNRtckkXmKVV0VIDhhwhalZirjTrJ/vv4aj9Rlx36nSYUjLrNsMvWPQ7PalXDNrBVyqHXVXUa4YcwVIm6nQoWqiG78Wo0fY9wVZp8Sba1b/9L0yMOqmpe0fuuahLjTpbV69hUpTqswIv4ldpISesqXuHn3QNOt2pRwzewFKM6reYrNGCjkrVfQMveIZd4eo/gSY=
*/