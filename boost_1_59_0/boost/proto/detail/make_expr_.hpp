#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_.hpp
    /// Contains definition of make_expr_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    template<
        typename Tag
      , typename Domain
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PROTO_MAX_ARITY
          , typename A
          , = void BOOST_PP_INTERCEPT
        )
      , typename _ = void
    >
    struct make_expr_
    {};

    template<typename Domain, typename A>
    struct make_expr_<tag::terminal, Domain, A
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
    {
        typedef typename proto::detail::protoify<A, Domain>::result_type result_type;

        BOOST_FORCEINLINE
        result_type operator()(typename add_reference<A>::type a) const
        {
            return proto::detail::protoify<A, Domain>()(a);
        }
    };

    template<typename A>
    struct make_expr_<tag::terminal, deduce_domain, A
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
      : make_expr_<tag::terminal, default_domain, A>
    {};

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()
    #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)

    template<typename Tag, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make_expr_<Tag, Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
    {
        typedef
            BOOST_PP_CAT(list, N)<
                BOOST_PP_ENUM(N, BOOST_PROTO_AS_CHILD_TYPE, (A, ~, Domain))
            >
        proto_args;

        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, typename add_reference<A, >::type a)) const
        {
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_AS_CHILD, (A, a, Domain))
            };
            return proto_generator()(that);
        }
    };

    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make_expr_<Tag, deduce_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
      : make_expr_<
            Tag
          , typename BOOST_PP_CAT(deduce_domain, N)<BOOST_PP_ENUM_PARAMS(N, A)>::type
            BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        >
    {};

    #undef N
    #undef M

#endif

/* make_expr_.hpp
82Jo6fsgwp/59LOHkHvr5omXluYWnI6kAHiuEHRg2KsfHImZBsb6NCV1Y7gMKTJK3qV8/sKhiFGpiXj56+2O9hrYhKQpA91SRzcrvB5AtRe5SOntsDBs5R0fsTXksRTZIsOHEb5qUeCnCwTJo+6wBh8Y82Jgfham7cKRPcRE4MoLbAmPcWgQgZFafreGrGQ/wQtON6zxoSheY2YhNFjnsFKl37puybCoEzbhP4XQpKHVyz0j37OxOLIlxxdktObmAAAs/9O2JXikSeFg2xW4UkXsBT8tCA1AbEl2Hz/Db41vduIcwXKPJI2lcrxnXJLwHtvjiH6+iaNa8FGIT5kLjSN75OymzrGdOj8YscDKPVlgxre/ztOAT0gxzp27ugg0v7EeCjH9QLRJz7R9rvrAeoxUvloxqwjZI0877zbvi1LQDe1tz/gv6KCJ0Fln4dp4U2LgbbmjlaLpgdbBQK9gnG8zkzG+lwZMRiRxTEl8aT6urhVX6ZUQgTxIq4KnmjsQaCj+AyL5L1xYRKdiSf1y1siBWLWFdclbJbnNsD1ckK3l8X7It99+y0a9Gv2RB3dXIC4vj0ZfCCXuM+vHUC4UhHgyW8Q/Z1HH6gO3ITP44J3PlbRbR47NuFgntZbb0zmOLMtSmank4uBXluSVCaum+42UyWlqQphhk1Pf1EmN9FKgmxnG3MiDhld/prc3lr+2yXZUtJMsk3oBp6eAyuUw71GkBTsunUOJtYzphPVFrdOKjxgV8D90UD4ZNu/BiCIBB2TUFgfiNX/MF5qunlgRbv1ZyktY9lvHHOfByfqTC6W7KbmmgfuKwoRe3BTLMY8upQm2+h/nlHOalyKCB0oZMm1h5ArbGoayxhYHwLkWxhgXTacMwuW6Pn0uqGGpGcwUqupMGczhgtr7cQ1zubJB1yAHzWYsYV67UKVFb2m939i6K7UNn2S5+1Kn27oSaYfhRt/hPdk5E3xBrl++RxE/umWiqmXXi2r57AdIcfzqvpskFvnY2CwO0lYjTzblHKb0NAyuZ1V3cr2wL6sPX58M3bGrvzQiQz/QSm/kDHk+tHFPa74q17IqKbNfzC5h2/mC9W5mMZpPpgYo+U4k0uELINz9T4gkU0tluK2WnWNjQCwLOcs4lQ9ewqeWLAGbUMHYNS5NDhfDyVE4GWT2VkLPPru44q18uUWkeNCExOeFuxCfssTHFqeD2ZvCTH0NwIQMCQv77mFGa5zPmHAy0GDvwmIcO3rkvJ4hWF2U+hdoqDeiGOLJQx4ZvsaL6nS9Lg7jmSNl4JBEn5mRbMa4zHyUOgkqvE7on0I7YRcFBrHbZ7FPbDdc0U9si9JRmOgGUpBWUohOehXwKFEf/V+XuRdJDi3YLjHCC7k16WyWmCQRxdhTx9SYxZzLNyirN11qth3ucb8atjbSuG3wFmhqKasTOrv6h7dspJDR/3EFvzIL6vpYr+/iAdwn6Ppm0WOIswjpIUqg/+FALvU05SS8aqHnUohpArP+c5CTeFihbsf5Kmml9sKpfFQxpy7saQd7/Y/hsp+Gpk6ZD0GwpngWXkni9b666mVmihCeevEA148dNvSrWisWnoVe96Tf0CjLNl6WaB38iDstGdMIpevN5FQgS5nOgt6oQYFFuXZNjOUYL8kD8XGD0VX9i0cKBqFJyrrAyPK5mvon7CgdX53tpqO6ap2DWgq7MxXji7NbBtnuNbwQtQJGeFp36gKmYn/aM/2ck44lIYFRWM/4HW/ewq191k+PanTEyq15EE9BePOjbsiQgrinc0CKyFWLsbCwZcmADYf/jfJYpPQYo+NxwlZHd+2KgrbwE1heHdUGd734jCUcbdUeRwpOHG0rq0bmOEu9MPv2qvO+0LbTysVZzfjSLav7j+Ei/7eAOqp0Ga2k3CH0BHhu7bSDuVNDMwe8WUTBQmHJ/Ae5rEduJUp0RuU0hsDUrXUjYv1etStG5fUt3n5eXeEhoAql7pq1cXocbjHQI8lZE8YzzJqkVsogrb99WB1I0je26cWAGcHLIFHu30fmTulRSxJS+O3BMUqsHtX9KcexlkzoTNpBP72bVT0O+oiLSJ2+GXIjGEKdkWSbbxibKFIQLCAPPaZpPVg8+VLT2qid3db7sPcelBQ1bnHjNF0criDT9h51WjU27uKO0bIOeWAoQeH8DIFdthOx0yvE1PnW5nw2TIOiSsIfKppV8jEM7PtOjS2Yxl079hkRBucv52ck3Y7GHEioQYcp6NJs9bmlVRlYi0Pp3KdVhm4xxOUferxlMp0/64kM246mSbZRYPizLA/K6jtR1JIvpUjyb+IY4dLQHADe8UK+cq1CbAf48k7UTUzeFe/bWxaEzk/hFmgDw6obwZZclnbu45Jt9hOwzLlLABsFqVz1Yj9uPByuy+E8ElKPwr1b4RRNW0mmxR9AWWnO29kLOmDlSD1i5JP9qidBPu+0sllzk5JZ8B9xmjXMS9qvyagcD3zcHmcRAXAnLzClP71JSRB4Ww/dyQwCs3NX4vr70xlcYo2NuUbNOIU2GPMugrLPNNGlrym6N2vJB3oXUnIO9M3UyPSTA4kJeAeb42TAIoeG5lrWkhSqPG9FzIg6W/ypW3e+9kDdD/56Z6Cc5sMStnkUMRW8YgNKzV+lvrfl762bP3A6Vd0/aK53vF9HtN9VanavG7kPFzi+13SPFyy2Hxy1OzWNCm6bPwasrtSvwY0Ok4Ol2vROgsaaOMXkJNWwCNgTaYlMl9BUAwIihLgX93GbigtXYQ65dfVKhKOwbPKuIwZcf3LY7exLrlPMXe0yr1Pg9Nqy9G10v6i/tj863Uph6WSHXcOs/N37s7pcqFj0JxudsEOVU1+MS3fvPr1K7R6KnN9PtJS4uh8PlZwzlAAtYpL6gMm2PHEEwBpiIyBeGKAlcf90+fd9URq65ovcYjSBLA5NZ04bwhK2Wa7H6T+suBql1s3/LBn04+D1xEyIQ4slrgYWn8qzCrK/Tzl3v2SUROoAAgShvllbsjJEAlPdbAuGbZ31aogoIuX6VMOBKWk6gjROZqzkysibsTMH6mdm4Hug8HUJMK+nkFzlyufPuR1PO4v6ZUGGqRkOzn4ZkuzpxcNhIod54Xvc4AUJpzUGLyHhyXEjS+sI26GOMkc2hjTGgHNQZ0Aw1TEp0xX+AKKccxtu359vkgpGfKkpJj5WiPWd9QbT5rd7wzXdt6njlfcho9niY97gz8MMRaiYQffT11o0bw7EUmOYVCCn+s5ZAHtOwwThacB+djQO0g/EWmObWBLtEgGm6jJcVDfiDbpQ1YDhHZ6unzq23xyweKDtOIy3Yyf9i7c6OoS+lrax7WBdzZ92icCr5bMFFpuGNr9ElQfZ6Aj+xBP2a6mB/kmNPvkxepVYaU9TNLdudjk819wl2mKgr9OIt4K0CFr8oRAjP8ozB/QUR7GJWV9/sCEr1xRILZOpbzRpFaGj3E9MEnpUXewhbv5Li6LI51h7mTebJCW4owpk0dpvX5/LOgtkWME7D0DV14KMUdDZpPI1llUWz527EgT+cxuLRbHYEv+ODxWAlvCqOBR7kOhhBZFin35835JJzCiMkCpBfZAoIw9MNQe1+1q9bXqi11uQwT5gy6zU2fEXFWuTLdrwI+WHFXzOelRTKoQfQOV1DjXKah2+p2b/MryuekOXhC9DpKmjnofQjnY7SbS4oJD+KXiDsWVihpyhZTUmYWb8frK6wf5zmFnrzD1zG9rf1dOUrQPkWI5vDyUMbrNHCxVnI/x1RVlSC0xXUSt0isZw4sHi87igZ9taOIZubmX/yOLSkR1GyPId9kvJwUYmgPrnPgVYw8fUMqHbh748iWJzyj7FqynLI0NaCZhmEv4cVc3DstGSozB3gRc5V41so/MDFcMVhSJ2ShjGQYPPU1W3/9n1wan5fiXIKhNakHTnheTzMYwIrpIeyuy2CxNDmKviFmnkp4lsWgNvZ3X4k7PUqsKZOaAvJ7oEI67z42zSQI1dGxTgCWyg1oa/iIyVz3emaQXaNdBYjbSsC3bCKyYsIkz+n1E+VkZhcmaRwBrRvw+GREzblklu7pqIH4PDEu2xy5zgaYdMuZHOVP95T9B4ttvy3ANReitTgXb5hQAh03dpouOvFBDGKpCllYZOS1HTcL3NTZhe6BQ3Dw1DilJ+q+1UlCyk8wZt3RiUhxZHbjB2T0ncmab7a5rDnSjRG0dKOA18Jt3Zx0QFPbJxBRTnNtWs0fVZaaiX+NtiaQcHfl8gbhhD26oEAKgKh+p63uV8PVKAiWy2UQ1yXijBZI01fccBVJA8q+PBkHNGoj+6Po0owEIcXI/6tI42t0idjX+5153forqIh8TZQgkGp/jlARtVW0ud9iOXQic8q86ADTdhJEBaL/QzK82rkFEbk0e+mkbPoxAv34NZ9u4hPvOkcr+56QyWN9ma2NFC5lwM8d2Ep/vBIadrsVB7rEzBHYgfRFwc2APNmEffC74OdeHGbiqEQWF6PXn6eisPiFh7vX2dOlEQHR65MUpbMSD7ew3YbMYNgvOgF0ENUGYNYraSlC2HXSdjnoakO8ORu764jstn57unD2a2rZPOmhAFyBdyiQ/j0q8IwLwaWnC5a7Y+5JuHciQbN2p0Q9Su0toYJxWB00BeIt3K9a2TPHnocQpkobwTEHMqxmDRrjTXxODIebnVg+1O1edHdmpaXDP44nyHbldjx1+/VcXHA3gm3El46++KXS2WeYJmy5IZkp5H8mGzYrJ3c1DfQ71ZFeDgDHyWb0BsIrwNF8reP5eKHQBlxXtFX6tu46juyYNMufzodVAIsMQkdLHJEdyaBPh8/PY2tkv9DMq/u8f7kuwN+fpocRmbJCpjUwoQLIxc/1xvPtn0fVQM1rTkVI4YYbg2X2sn6+zox4z5K8s6i/l6yaHxpSK1ZKTvgG9Wr28YYAd6dGPDQY+ao+a+xVRn1g3qL/qnuVc3bsTf0sFpWzNlEURgu2PwBm2SI/xsY7BNRV2VMlOcurkciBAH/g0FC7liBD/Cnszj5HCBFGKv1aeLRsZXI+zKxgfLjAc+AEvjhurgvAVLR2dw2bP6WTDZa9fhqZvACYtWIJQI9VtzbQoEXQuCL3ibT8Fb920aSsCdH7PwTYKdvwzryTorLEeczOhzBX/jQEgT5FgxOJvE9IvvLtBvECJg7NaYKjYULrScpBfXLfmQTd/cCA/8p8e0CcNU8FnoXD5rXsia7N90fc899DG6GLep8TDSjKGRQUbGKv5ieuzuFHeb/hqqOn1ZxIgpaXzqrhVYetp9SXVy/If6HQFaUBZXXZCjeN19qWzKU4XQ55VgRsOwB9QFlIxj8seIrYR+FJIHzFfjK47bNKW/DhpzSyNKt9YiWGSqRslEmKHYRq3x71UrxUG9Zw3YP7tmAXvsDgpZX5wgcE7T9EST9WUuDbGkR2AlMKQ8H5Ua1gLy7i4p2hb4YuqED1J2Hkcy891svT7PMYhMSLnkYWyed8CFyr9sYaG+Yg/cqElMC01LH/yvnoTnjLlujKB0YIoy0VtWXtL6tb5+19tvS8HL5m1duEH+nU2Q47MVsn9D+0pnCSqcia9sIEtmH1EejkFjpqhQX2PS9lPZwirL5Qg/QSLjA4UIrRgiVHJfBAT/5JGZJADnZrL7TSOv3rcaFIBLx0WkAhruuZTc5VJh7PmrWU984bX+ASLC9whEX5f9eI4y9UMX7O+/SXuI9Tp4Pt2EqWFmHcCDv51lubw4H2TzHWF7Qbw+FJunyklFIF+KdWlmYM1S+wtda89fdQInd/YH5UsatkVgaZQLuv7AaeUl7ME31TnNeQCKDtjvaJYvgJ7ac8nnZrUPrLx7qH22GYsmLDWud1Xm32SzBxkOFOBrN0TV7pOcfrG65qvA8Bdmj9o7wnkJU66SL3rpFobUYpjt8cQbEU6d7IPrgTsZz7lIMuLu29JVW3nO3r8nGFuWmiKUkSslV/1TVdwuX0BBHFpMic3IkpKcxFKOde7xxXw6i7gB7V51iE3xjXlhbOuUZYPzAaboI5h5kGBttZ6qSsBFth0606l9dzZkTVSxqfEn3LoLnNyyVZX9wJcvgW6wUo1+0LRMzMvBS/kGaQ+VF9fXoYZCvxSKeg1p3dL7sa/tYajeaCyQFw7UZ1jMfcJOOW4oSk/EIyknltOUJG7HJv58sGnq1lTHCcO7ghVb0/bs2zmoxcHUqiiYI+xWWRYk0DqfeplDat2vgUjsdxHG0epkmdKx/dUXCx7hXlWIyd7zC76W2ie+j1iVTQIMm/bf8N3PJtstAG4NrLqcV9/zJPsM6Fmy8hjI9aP3DkCocWAlAzm7ZoxPYcDyxKnnXY8vcXZdY24wg/y2lx0hUap31WHCa0Y1+zCl9eeAc3ty88com48slTH6wzcQ3A8J7Qx2/lZLXA9nRSvUwa3jlZ7FdU8ikn4ZnYxWVxD8c8dZUKrwbUJC7fQfCiMx7H6ldcfFqBqH8/Ee1UDvwauhdnRBJbvOcI1Z44WIlMZnsUmdmlN222AXnSQcGsddnjNFFNrbNnPP1Mgxcc9U/zGJFwdwKtqCifkseRz76ZzJ6jIqnU+m9mk0Wk7djA7hcwbGg3MvE/zURGVuyQcOcD/TA2/aCRUtEksW4x5cqMEMxO/Wa8kE0hPkQ3Wyq/iWRFCcr+00VNbhneG9PK862yTcAGIDzxZe3u4LeXPljpRc+p6Fwujt3JE0GzMzrN89VKV1BhU0MR5gU5pdpwSr3zxZ5mBt8qjgGeua2QWKSSSYSPvCmI0Kpm4sKrjLbOt3ONvh6ncOYHuXGbLDxaYX004t3hfn8a7l+MlNrEd952RvFNJbNITX4AT5jbi1l7b/MY8uQNs1jrwIj+AkKfUx0Guj7E5oq//+9MjogTkYMlolPk1Tjnww5WHL4vywafWSLw4Md8vHaEp4H0pIy2eljuEXw8BpbQhjWklnqRa6oiVBCzKQBJyrmW41M+yCAgNOY8kRlkPrRv/q0qY83NvxPbOqUx0PlpIIntpN24XZt3ryD84QYWZS2quYLkJk2CCw4vWmCw6jEnEBGsgKw9MDdBR1m0/3sjrlx5D5aTHOh35x3cdNSRXDRraf/ejHeG7H4k20rX5MxS7RPemY6utIyUVs18DuKWswajQpuVF/IZY/FQmtPsg1YzkpAvOsupDU8rG8xx5Q6xCtNGsFDIYC7iU8xM45JttRs88kPSeG8T6gtkRm7ykCEgycXkk1cfQ9yU7LxjePlLqzoRB1b5kaLbsoch+h0vFisU1YR64DXCZ8sE/Mk7LXIBk8oRZVAvAJ/7kOQaD/0uCOT3lYC7JAOnXfqnJvyUB4KrZhExMm5JWpDq6s8uAHUiJxP9D8q97ZfR3ieRWwEa9xMUwYq4l2il+yK1zqQ7FB53kA+bfU+55aMmznby7Bbmo1wy51lUgHtWXzinwrcfk6thF17/43Egikbvsx4QYYaCtp7qIbPcY6YU5UIFYk8pWDSt8azubnLvujkRvSBFxl9f49JUWLYuiZJbfcdoFvHJuRlU/TnufqBnmAfp75VPwPgUy31VPnm1hEGPxEzWfc88NMF/zR1KDpnJeIEe2Vh09e+WMepXLP+sgTW4GPiR83sqlfxSvY6L0rIn5ereuC62kbljsL
*/