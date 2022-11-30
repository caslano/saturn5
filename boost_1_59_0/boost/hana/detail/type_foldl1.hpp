/*!
@file
Defines `boost::hana::detail::type_foldl1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana { namespace detail {
    template <unsigned n>
    struct type_foldl1_t;

    template <>
    struct type_foldl1_t<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct type_foldl1_t<1> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1
        >
        using result = typename f<state, x1>::type;
    };

    template <>
    struct type_foldl1_t<2> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2
        >
        using result = typename f<typename f<state, x1>::type, x2>::type;
    };

    template <>
    struct type_foldl1_t<3> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3
        >
        using result = typename f<
            typename f<
                typename f<state, x1>::type,
                x2
            >::type,
            x3
        >::type;
    };

    template <>
    struct type_foldl1_t<4> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<state, x1>::type,
                    x2
                >::type,
                x3
            >::type,
            x4
        >::type;
    };

    template <>
    struct type_foldl1_t<5> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<
                        typename f<state, x1>::type,
                        x2
                    >::type,
                    x3
                >::type,
                x4
            >::type,
            x5
        >::type;
    };

    template <>
    struct type_foldl1_t<6> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
            typename type_foldl1_t<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
            template result<
                f,
                typename f<
                    typename f<
                        typename f<
                            typename f<
                                typename f<
                                    typename f<state, x1>::type,
                                    x2
                                >::type,
                                x3
                            >::type,
                            x4
                        >::type,
                        x5
                    >::type,
                    x6
                >::type,
                xs...
            >;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldl1 {
        using type = typename type_foldl1_t<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

/* type_foldl1.hpp
5dufo4ay8pmCUeWbyWlAOPZmO/lrWmmdt7TW2yy8N+G1+ZZNcMdPYd+dz3Kv5XjRiGQHvUfOMPYcjaQ41uJeO9dMfPn8CzRo6Jn+xy/QVEZhwlwr/dTzMZcwBLQ4QikRJev3q+Rho3VNUS8xyN1fR21fkhL1Vv7H54NEff0XGfr/i0xFBMw2MzV0fMGZyr2sh2JXRyh2dSRD4hcwqd0rHfFTvdHRGv211EzJV5C8jsjgo/fyfPYSVpaclhL44z61BD4x3I8bLhhdI9FFOOJe03IqTZkf2skfEfRxr7kfRMCD2ktU0UtEnUNFB3zE8vKj2oygmRcSxuyIFafSCls+ZclVlKUeVhqkdIGtImWhafkYvLXUciOL74OrqcBa4vv6rciCpTW3lgbBhNgujGcMdvuWgsT/ECk+Y6Z6DljhPaI+ibqj7l+Ro+ndM/WVs+cEndG4fsMmghDUaW+lk3awu37Xk+6u5p7B3RWcCWpZ245NNZ0dHYdK48pzKBfleyltzeqyiaYMDWa5f0VWlVesbU6Yy0fZLoKjJERzr2BK/F+SFBNscplKUsMWCwprLZ6I3R90r/5aBqrjBqOacsdwKapd2JpKQgu1wWCnhYzpfv/ZP9PUDipOjwNjDrnuhpF2vMhThvmWTXY3YABapWCLoYrIh0pulSHiTpbwPkyEn2myffxvaeSe/VtapRLzTV5NybsJ4vOUp8i2i4+VpSp53gaTEspojYJK2naKfAizgX7l6eqyPJt8tbHdRfxsbBdBGSzNizqQdJMpxDXXfE0vLnQQWBMoARKgAxrV7hfssKaItBnQ4CsqeP8EiqDJl8H/cYcZvzmYZcZv9qBWOciLTqC93NWEtgkJN80cvXMyJEcSQ745QjYjEUv+J03Eyf9zKTP631OCejAPBgY7ZQ4kpjTZe/zkT8by4GlqPNlpPImasbRYkyytF1gkF/qpY5QKNZHHeizWoSaRRBLuySTRJzBcN8a8pBJQMERsZ9vDmXxNxUhAmNxtxIVzNieDuceTHktV0Cl4lXtDnYzQZ1K3VzopQjAa6Vr7KWZ6J6SLyQwCJW5vFQpP0weHojTwKd53r/6y25JTbv1UN2JBUo1Emp67Lmu4kItWkUPdqFjX3epsIaOTbP1foKsxI/iQiC2iW4QLCHzLStzx5+HCzOYS5BH2nhlMfFJYQ2hhPt2d7slId3o4BMVwwOQuEQZCSkTAyCHBQpnYFlmnkJgXgp+wF1aZFfmpf4HpzlTdiov6p0cY63Dt1/E6OgJkqHiczNEdU+FOK5V9yxzyeH1pjb5sgQi1VQtNG9RKl/DphQ5bOiew+JJk3qJEFXJfqKMsHJmE27xYppYxtqYFsKZpLjPR14yQmo9CrRmpt7YIjLYqEaDXpDb+WMyKz/MxRWdATbVjgrMWm6YFPL4YDK/XycCG4UXT75JLi3Zr0Z4WqZfcD6kfl/V1l5WjxRz0xRzuBobDUGpX+w35Kl8gWO9kUq/KPcl72awgk9q0ULu/NTb1uwk7daa/dfkwMcuaJU8sM36DufnmVPiQ5RcMBJToYbPCmtTrlbrtB/zNy/UuXMTq241F3XFcVFrWhZEJX2yCfB+TTnqlDkBJ5cNxFwPJVUZIAoICc3Tnnw6KKkR1fAPQoOsYzS0fAwxZyFUiygIALdSfvDuzjWbThkHT3M9T7E465gvMBP8gFlx+N7Y14RHIstBJb6jD31yfELgqT1QjzQa18UaoOvkwWMXZyhigsjIyYnUOP1gP5tolmH4RBZIEwvZAkEV7vdHusNl1kW+cM7RiFgiCwQkCVTqmRo/Z3WtvR0ZW2gbV+CsEERrQYh6RlfVPPfZ0KmqZWPDBzllTK8/jH145otdgqzYihZ7bSJxFUxfP0VKAQBgzhwNztOlzWMChTXewQK42PZcF8rTpeSwwueiENn2y71VEITYxfqLuHj9dY6bTNGzZ5Jf156mJTzn5aECuVLyvP4buhFPkiMceTzr5QJJWhlOar0gJ7zZTwl0rWZYGitbDWvm6L8CBUQZYu0jPaEW+h1u6oTmP53Gqqhxr24QUloA/nWZq+GuUouCwRRY07cWpoDsLzOk5xnCCh1IRNGkbfw3q0KQmzLhuUsaKly3STvIuV9rETmrSThznwnjJ9IqkzkYxr4Q7rxhofGrRI5RWjr6z8aH+Fk4qVaZDOpiK6duBi2XkBb7oTqXKF21SZosFT2x1qwvXczdpTXjB3/xln1FlTvYxj7WNwltYVMA1cAsbsbZzsgkCPiYoooCpIIzQSRhJJZh3QEtgg5jhbuhL69OJ5PUmUnMQqYevjM+NfwefpfV/D5ml9cI6bzQoETxIC3cwMRRwwvQiUfc8qFuec+W6G7dYddOq38uqr/k71RcZWnRri7Rl4l1jPKhwteiAMbY+gXvqhLbwZ/5wBobQNloLccPHuJ0cMoCvCbfdi91v3CXvGe/RV2/Eif6PrjtrCP7ApO6XrWwTelJl1DpWNmMxYxLGIvnQfQPoTUk7hWZZfgNUUsV3HT+T+dS9FifMkt9m0k5/S0ZCeDrqJpJIDvELfztjJukcAmbl3XCLrOPwt8hXQdvFtAAG0Q1pJ0ITyu2NpMZf4DjSEP4lCfWD4P94MPw1Jvxr/S3KeBN+yypkHrFe8rKafoLMn2KnQt77C0xXqcrsJOVIRicFcbh0Zn6x5wpfdA7+gv2Y+mYH9Y2bdgxg1DPtWwbMdVlbzI7mQ989Y/Dm/EE5K1GQhqe4swI67XmcctNoOa1YacsenqjNmkix460UPJ3l4T/O6TUWZ2wsiUuryjEp5BR/arHYc3AVSc0CbyCvSnmQBQq9gXzl3uqmJ3M9+gxHS2neOBS55QCH/YZqCTn10kJ1fw3rh3aFG3ldO+jpb+fbqmf+YbQnefvKGfk4LKq7cxBALgC4FwGMRgAUyCrBrQPVGfnO6uqFVIT3DcHtQ0qs9VOOpn6UdieuoVQsyYkLEZUhTQgeFAxpgH3wRVVkuHm3/5VekH89wB+Pl4BB6rRKXfwp1Gmm37BRVTRsZufiRk1AaMw1+PL0aRDOPbrUY32y7FXM2qJra0MG7gAooR7rmwPwDeY3/IZILBYyrcpHsZ+l7d5IZo3ntQnPjPcYV+GvVXvYmO1i14lNVmrCxgcUr80V+6LogQVhjRbMaruRa9DciQW12MyWAC5ytbUEUEfAY4cWc2oxFyhLsaxSi+VpsUItNkGL5WuxAuMDPVAPkJDF4HqVSAf4QNu9icrO1WLFWmyyFpuixUr4nGsyzbvgoAyb48hoemkNUKw1LfnvoTydoj40PthhTenWlB5N6dWUfiNMm3vhF7rUEcbt/ZRO3NFMAXNQbhXLZTA/w3jGaYzdDIILl1u9RWu+in1vIb7KJK6+0WeYAnJBhoAUmyQA07ZSqgiROtqaHPJaAuXa0gWVmpRIDcI7EY9KRMKqWL6B3/YGjsuMpBMBqUBAMpQEZR+FJ1kJ5m3knrZlhGHCGa+opVJbIzW1MVXNKABrrZcR0oWFADZmcoUnpZLO1b/YKTGoqE80G/cDbgUv8ep+MMwP+ZYWyI/4SHLIl6jUfdpWUiOLXu8zKv++Gmm9TI3sM9UILuuyXM5F6P7Zadc/92rcdNLyUuI0GZOZBN8GJsPOr2r3g9TMBDUTk0uYspPFaqz5iRKan6CULpsytCVQQ8IXmpyS9lqsxpD2AR6Wg/gdQKwrgRGKf/us12izcoDaxg3KAQKVGFugxZZosUe1WDUA0WK1WkzWYnVarF7bvYIGUwP90k4au9fQLy3O3b2eftGZ4/9+JjXg+acwtCvNIR0d4EU7wMcdbpq0pZ9fNFpWoWFIMxG70VbUdofpdyb9opXYsgpH6iYqMZeePkq/S+gX24c544dAAO+XBhx8FE4m7ecHxtFQtFr62dj/X1ra1Jtuae8Xg1r60H9ltHRe9/83La2qYoeolV6c/JSc2iqyO/bzj8eSSqtOwG1TPbZ43lhh2CouTdp4SdgeVCwIJGPsuv1CCv1+uGWwiFTcTX9B9TPXpjbWYKjM3IAVt9vUpM3LxzJp9ZBN5Bqua4nXmJ49VFEa1krn+OiJPFLA863EvDrZmcrMnVGsNuKcs41VrNaVBnMdnRavozBFA9tFgdY+LV6PAYCKLf5D8pBbo2uS9qxlsvrYVpu2vZYCFrjLlaas0JQN/kP6snoh0BrdDS9gfG2HSOkNrdN3rBEjGOugKIqmV2MwwL32JZx9kbbiSJ2XMXEeykolJoW20kSVaQtpyma+5s8pc4j189ifz1BWr53SMd3xC1DVdB95VbJT24UYJnM0yh4wlI2ZaU20aUCw6EBZUSLMcsp0ihdRrlAtuDeTDvSKxYk5lBwK/qj4II+g6KH1IquIlcreUnA/jmjSenU31mqT72ahBtrR00x3wB1MX8Z8muas0BY97BBzNiIyqlWs1sjcTk5mysuM6MIqGryHcH5jp+64A3SAPnUAN9ILNenKNkE56HON4Tig4EZ0M62aNK34rUBPS+K8BsKm6w7k/Qmf9hpmj5jhfKR63V9Ms/MPl1DbTEK98b8FcVHNWtboVeazdSTvBlG0yJj+94l6ouUfI6r0siqtz/FJKzBjegUU0ilKa8IJbfA7l+fS00fTT3H/4MGtvxrDadENNqVUjW62KffxCz8dtBQWzKP1YXsf31WIedpiNTLOFW6IH5A9GNheH+bfmiqWHyPHQQeAAIBDSwEAgP9/HW9Atk8R8Pe2FNv++8V0GOxHFwfNyltUPPEnQTE9g4ot9EyJmpyqmATYJAigRjfZlALC+hqRpzZ4vg97OjmVSRtYaAWr2MKiDVrAZEUttJmFVuOWiS0409lkD63Qotso92ynAAQs+9MWStDWqo2N9orNMKwHk8tLg3+LYEdWWicYFKeGUjO6pcVKDgtt0WbUadJWS9+GslPEeCkjqUpLJ1VdMoa3Iwvzdz9LezU098bf+uwMbROn3Oqj3A/lGz4aUbK7JS5bocvf4V5blP0j5pgpkafhJoqFNfhIYMWGmQNP2uKLbo3ZDWmL8bRDD23mdw9Hf2szaAYt2qlFT2pRrkW7fXW9yg3mvHScdqlmmcn+WdKWZIwR0oP4XXQZzRuYbOtkYQeT1mih9SABvM0gAyhrAYlKcV4B15xgq3jZfgQs65co8JmOlMIQNpcYvAwVq41zSEzvqhahYbPv1WXFNugJqVsrrcM9qUObaXmAOUe9REhxsOmFAOd/+8tpowsVJqYIrrGEnzV9HzR5b2eqFdvxK2gLNMR+yB9aE/NAe/yn5GFZFdASeukUKLE97CW8R1ZrB87AVdIVRzDrEeSflehI2NoBVXvF+kwcNfp0MBO+hVwzo7joff97ykhgQr+0rh5suXXwNS6xDji9OTg5+1ItdbsXdcZ77jhupQeFhaLBGhMO3P9TE7uKVWz1vShY9XR63P41I4np0/MZrMomr7YG7tc6xcB9I2PgjjSf4eyaGLwicvS/DmDQEDhNnSZLsvwfGMA0SYVjmILlOIyJpTSRUDmjTnDOVw1pjzWk0U5KXmXlUY9Fb00l3WhThlOOtXiUKeNok0JBq90ZmUe/Pjd4WBtCzPHcP5wx5s0DywQ9ootoihzQVqNRrK2upV+ZfnFfKTK9t5Ersi0zp6qVeqfJLiVYaBvu3zUmYjvarzZfDJfhNi+54d1YUyX/+adnDFB6uE9difZcTZb11bxX5rHQzvR32dZ3lfxp+MQsX0vlt9mlnfOgeBPVA3VEbGVH+8NW+UC6vDyofMIsnz24/Diz/LySedpz2MbB/bDtopi3JqNsdKZR5m74FK9JvoFeZCh7p4L3ElrtIyEnm1vjBeFZaZ23OZIbDBvbyU4DbiGDrYwx1M/hIqOKT8o6Y0TyF4GfuK8qzJ/71G5jL6Id7X2RhLq0juk48rzSavt76j6XpuxrkVqHkrHc5m+N3Qs8ivtt7AtroSMCbCSbvzcCQ294U2WuCJmEc5vidRavsZ0xktf6dmHjlDGiYMSeUZJ/OFy4AeGmbWgUTxtubjQEDoCSMGd3hhYluv6A2cu0mZT/sDyWZVWKEzZwdVFRoqQrMZTw1KL71IuFzzwk+9SLw9wNdfC1evEq+Qb1YoF8jXrxJuVh37J8d8M1DpqlvLYFTKARDox67CMFkk1TwlDgHNieXX9FA3S/ym92N/wLvA66GzDzBP6MF3fXZJulD0LBSj72hn7EGW2YSv4i3kiJotR88Rt2skFX4+S9XzzTafJeFYtqE7qjyUqtn2YuCr0JRSBqpyb+sr0XTx+5Ba6tEM27z6HBVDcZGJWV9X7Lvyc6saSu1j+1d/l3H2eOqY9rUmtRAn7f06VWGMQuGMTut6VWv5SQb4RvrNDO//zxtDHdxGjNI+iGDmRb6Ve4o91wTWkz6ZPxVRN81fUBFKyusg1dwd/5yWmDd37QS7PIQBHDltFb4YxdyKaJp+g4g5es3JW6FTvhid3ASkpQGSnoTkUKxZZ4teaWeF2LLaLTUpWLNwtpq1Io2mbG9QgmGGqjEO6jgkuGgAGazC4yRHQgY7eru247Y4SrH31svIfXfCzkVGvcUErAJK259zyapIAk7czWvvUi3o73vbwVuE1xR7KMrVuQLVv5Pz+LEzqtERtf9PB5oyuCmoqJnegwB13HmbEdYjFxNvo/FyfIw9SLt7jjvdTqLab+/TOO97oCd8Mn9HiT+fiw9RjzqsuETE0cR1zx7Zs2U2weMXezwkVg/7IF7dvEBKCw0uFXut1r/iUF0hx+1ftTAzUbnKVdN5wx/P3Rx73KsWQBU475lZPL5132QTwRm+ZVOth+IIRfLCTLe9cwqWqtIQt1lqUXj82YawLJKstYM1bU1yJtIkda2ayB66Js1ZQturQJAGrKAB/dilmgreHKSrHDnKa0psM/UKwxDCOmkdufumCo+yZgBEaT2uRrgaPGY6vZQWUov2MPuHdD+N170dprE2HmTVxfcsFIXqde/Lo80uyFYe54j1gLZzRTUeDhaJu74dlsiyH9Etw+AbdFff79ctBXWyOP1mprLN6tNFfzUVlfbS2+rM14SdmXKT6n5X7UKN9dA3vHe+R6s//3y9/3Lc2X/y9T2jKTBDq10E4WOon2OZhhRMDiVhzKFQn328pOwZssq/kzz4gPZxvrwtkWQw3aiK9N7NGXXxKODFRWDwG5b4ytp40doLkCHZZDHprYA9FcTOWsBLLUtGBOJ1qFFIa5UoOsGt0NJVmDRtdHt+DoWuEHjh35kRhdbVgM54rVpp6RNCQwEYQRDpQogw0vSjQOMoukI+GMkTsFAxVSt1/qWF7KpJN+6Zhbxzny5DKTHCuPuWy2kjAvKjoP47INxuWCeXA1uI5GASJWBSWwIZ1i6enO5KJMKMEw//xOC8q4K0JBBKKjTCgdFpS8QYMiYksPCamNrcbt9UBE5Zo7KGaJUKaxDne4BlGlRvcBYXhKJiLNPkZNLvZv3PN7ULs9QE3QN33uhoTNlNiWmJXYj6lDTsh2Nr8gvdUoPHCXW7svuhv2YDJ2AMOVMcDwElGbjKSVwGJTBP7+P/AYiH0Y+TWl4LBIFsi//34K5V+CZdFeHcJVUU4aSqexLoE9Da2Rr2WhfXzBvbRPthuvw3AN337Yj2pj
*/