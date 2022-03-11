// Boost.Geometry

// Copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/thomas_direct.hpp>
#include <boost/geometry/formulas/thomas_inverse.hpp>
#include <boost/geometry/formulas/vincenty_direct.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>
//#include <boost/geometry/formulas/karney_direct.hpp>
//#include <boost/geometry/formulas/karney_inverse.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/integral_c.hpp>


namespace boost { namespace geometry { namespace strategy
{

struct andoyer
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::thomas_direct
              <
                  CT, false,
                  EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::andoyer_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};

struct thomas
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::thomas_direct
              <
                  CT, true,
                  EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::thomas_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};

struct vincenty
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::vincenty_direct
              <
                  CT, EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::vincenty_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};
/*
struct karney
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false,
        size_t SeriesOrder = 8
    >
    struct direct
            : formula::karney_direct
              <
                  CT, EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale,
                  SeriesOrder
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false,
        size_t SeriesOrder = 8
    >
    struct inverse
        : formula::karney_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale,
                SeriesOrder
            >
    {};
};
*/
template <typename FormulaPolicy>
struct default_order
{
    BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THIS_TYPE
        , (types<FormulaPolicy>)
    );
};

template<>
struct default_order<andoyer>
    : boost::mpl::integral_c<unsigned int, 1>
{};

template<>
struct default_order<thomas>
    : boost::mpl::integral_c<unsigned int, 2>
{};

template<>
struct default_order<vincenty>
    : boost::mpl::integral_c<unsigned int, 4>
{};
/*
template<>
struct default_order<karney>
    : boost::mpl::integral_c<unsigned int, 8>
{};
*/

}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

/* parameters.hpp
Pd3s1a1sDb/sj1E+7fM/l48wZBukNtvA0hY/+aJ82ud/zrcAf9cBw8Ox+hf2G+Xjr9eyNpB7jzziVCJdwigNbHSqZDlVLO2RQqYp8tMF/ctgtlbFxj0azwg3h/lSTy9L5CLxnwE19J+ppONpDShJ+s2M3xyUS5zWsdwNytglYxPteibNJvy9g+HPwt9ZN63g7vwtVz9rBVeP/+tNCdlp7CzKDUWzzDYzl7gwI8uUnAiPvILR0F8TxpJsLo2lC8G/CFCyYDNyEtl8Jws4yXjmYBvlzJLLYCOEP52+kb+Rq08oLDRXVxs2lrDzFSrKDTMN5RWGxdnZ89kJTNeys5ESKzZUlpktZsPCNaXmQoshvaKwwFLBDlgyJLJjM9NKzFUFVYXFmw1J5urCqpJKBVxvmFdQbVaQEuhoa+T65g2hGwoshumcIXtzpXkYk3vXAop4dXlF+UwL4DM9h0XNrCyoKtgAyaqoLMJdPQJodQEIN2+osFYbypFVXVlQaCZcz5kSRJtqtpiqKkgXuSXlRRWbsixMHRzy0wuqLQmFlpKNZlNFpbWSI1w5LaNyS6DnZNgFzSZmYcaRjv9Ix/S2wu3K/DU4mKvH//V0UJa1vMRiLppJ51aZq5GnpNeXlK8rqtjA1VuqSspLijBBvsFgqVhTsK4CONUVVkvxzPUVVWb0bvZcsLaqpLCAZGdpgw/M4AMrq9hYsJ6rr7SaqywVM5ENn1s1s7C4pLxAPsvL4H0uv4erLzdvmnmPuaCsoLyIK64oX4ciy9cBWFxRxvLWoRCLYU1ViaWghObt5vJ1LL/wHnNhMdmhwsyDAX0zUazVFFB3yFK9qaSa6l29yVxUUl08c21JOeOBhimn9EZzufkeq7mM+HjyrFXWddaCzV4cuT4GVh9vnrnKyursScMCGJFfHkwAjD3pcgjHsHzK2lBRZK4qH8LZYLYBq9xbDvRSZK0qqPblCw6wvAI/mc1lhuqCso0FRRVVXlpzodUvjQYvIRnKDVVm+Yy1oXILK2AiBrklh/LKKjasKSnwLRs6Z0bsSa+pKCvZCBRPuqBqnbncIrdLZUWVBZo0V5tnrqkquKekrKSgnLW99/eUcuX3FN+8NRXrUTc/PCTQwkQ+09OeJVWshrAIxEivM1dt8AF70mVWm3nDmgpr1bohHNS72GIur7aYYTNKXoG1Gj0BJa2tMpcXFg/xUdJ+fJQ8KLKgyIdmjblMFlaRaibZ4dCzT/76oWdv/9s81P88sOH9y5NPfcfzXAoLI7AnXVJl9j7D2krWrDEXlPvwJNvyPEPgknvMQ7ygBC9M6UusvYqsFt/qsX5HjWqpQv3Jc6G5PHnVcCwFaHizD151CdxkydoScxHnzaP+rnR3Tx7xQCjmvIoFzFMqa6AC2YI8svk0vzfPMEKeMuzWy7sC3Xcq2wPxYTOTsi9dO1aJJSXfEC/H18QfvzZ625ZPA+LtnQc3RK0646FrcbtnHyi+9pl/6g6679wW4Hm+Q6Hjat3u+vpV5WabpWAtGy1WlVWsWwMhVm0u51ZtvhkhimzGVkm2BAdA8q0q3lxZYQFuYcEaMryyIgUuJ+ur766ysDpZCspvwQOiYvn8aLmu0DuLa+56uSq98o55v+vbuqHo7Td+O/W9v4jr99Yn7l6dVf9GyfEZHZmOre9/tCy+6ZUXLh78+kRI+/jnN3euWjz/2fCJhQ1n85uXHw/7zY/LNyc9tOPNt4veee8DU2yDLWxFwy/2VqaXNdleTW2wVY4CNwG+BfD6UeC1gJ8FfP8o8L0bmmz18xtsXYC/3/iKX/DF2wK8FcDrG4VP591NtvhMwOJGhu8GXAt47CjwYsCPZjTYlo4CjwF8F+C2UeD9lU221YDvGgXeCfh0wJtHgdcD3pMOPYwCXw14M+B9o8BjAa8FPOz2keEhgKcBHjsK/FRFk00P+NJR4M8C3rUA9R8FXgz4HsB3jQI3AF4MePMo8N7yJlsU4F2jwJsB77sL9R8FvgPwFsDDjKPYKeA7AI8dBR4KuAnwpaPAz8L+wgCvzCosNhdZy6i/Pwjcjfc32O5BuPGBBttnfIN/m1Q12WywucrEinIL3AT12y7QBDzcYBuLsOiVRttExIMP+dv+9ci74mF/Xl3glb0QvLKLMVsqwrzSxuYg0+c02BpqG2zP7kGM0ISw/skGW+fvG2zn/9hga3yqwXbpdw02V7U/v+LcJlt62D4b+csd4LHpGcgAfH1Rg+3qxxpsb4JGAo//wrP9Dw226wG7AN5ZT0PuNQ22PIQihDKETWsavP1VM4w/pvXrDQVlJDNGvoL1Znjp9Wx9W852AOX5bRFbRdCcthuy3PZ+gy0R4X2E1vf95d5d3WQLNTXYQuc22KJ+bLA5fmiw8QhPIDzzQ8OIvqMPNLWgqQWNfrDBduBSg+0ggmNMo+0ZhDhtoy0HIXssQkijzYzwEeD/RPhMCcSzG3HwpEamy4eAMxfPw8vaZ0FZixpsLSir9NIvfdpIwc+OQd8M+owCmwlTrsLNyWXmDZhpLTBv5pI2Y55ZUoi2x4y5ujrFbC5aU1C4nlNMEiMyQJYKTOe4esXkTFUlFZg1b+aUNJYgheuz2Gygvp6WXGUKILEATBRANk3uLAs3mquqrWvkRRMG/5QCOgeX6DJKykFVaK2i+RCsELL6pb1dZAHWMiA4dEeDbcYNjbbbEe59pNHWjtg0vdF2d2SjzTij0bYA6VdvbrR9P63RTxdaK8YO6KKyMkc+BVhZTVVULa6osFRzhRXWcupUdMSKHoHOSjKwdSmHVT36Hw3+9BsvW9dy3FLyo2SbCJUIVBh9/UTXetKkgW523UNjEgK9BdhMkwDy3Qj0XVQXzSroTR8E+vGvj4RUoWwEA0IUQjyCCWE1QiUC3W5Tj7AHYT9CC8JRhG4EdkpUAGgR4hFWI9C1PnsQWhC66VVxNeAI8QirEWoR9iC0IHSr5Q4Xj1CL0EKdLxBphFqEFgQ6xSoeoRahBYFOz45HqEVoGUNKxjMpcCxi+m41GDFtYYxDPI4GDsS06ByPmH6gmYB4Ah3whFgnK74rvsH294LG/3G/2rsV/XpNo81S2Gjbhpj61SJzo209wltmuV/FrPG3hTkbYQtZ8M0JI/s7B8r/NX+3B/7o7OX7bGmg/+faRr/+9/u1v+zHu1DenGyMdwr+M4802O4A34GdjbbodY22+b/z51+5ucmWlIu6JYzc55+t9K9PLPD1wD+UIPuZ0+D5/DZ/nDRbk23pkgabdl6D7ZHHG21/3tpomwMcK0IF8DchbEPYifDYukY//+uhnQ7aTwD7mwLXDoMnzWv4pb+EbIcgW9E8ua2G63L3PU22oqUNtgcB/xD6OIJwCYF044t3Ani7gbdX4eMrnwcmzvvleNjvbLSdtDfa7qxrtNU4Gm2ahxpts+/zl99Dr0lssIU85F9u0r2YKwCWlOjvd448MuR3PqlvtE19RPY71zzkz9tDXwn60Arg/a7RdiPCTIT7f+dflg24ZXmY3yb+0i5fegz8Hx2yy6/x/Nyj/vT7Qf8s6Gkc1if9chx+GPh68PGMw+l/aPSOw83IdyP0ItyB/AeAa3/U3w48/GOSZDuLePyXth4KW3gbtlCZJNuZr93+Ozvz0NYnyXY03M68cFqXJTfYpj3xP/MTC3Y3+o2//aA7iLyvEcb8GfCnGm2VTzba/vqEvz7Por5bljXY5qCsOU/DbhBKnmm0nWlotN2G2ITwAPI0iN9r8KeN2IKxd5nH1nuUdWBPgrc/cv/5P/pkez9kWkxjyCz43osc90ycltt3u5Zb9pqWy+sJ5nYhdCFEnQvm/ogw5YdgrgjhVYRehKTzwEHoQ0jvDeb2IPQipP2IfAQRIfZCMLcD4RRC1EU8I5xCmNUXzP0eoQch/qdgrh6hG+GWn4GD0IUQdimYK0P4CiG2P5j7A4KIMGcgmHsC4XuE0sFgrhMh3B3MWRDeRzBgsLAgvIqgUY3jshFeRQgKGMetQNiH0I8wRz2OexDhEEKEZhzGrHHcUYQZgXhGOIFwa9A4bgdCN0LUmHHcFoSjCEnacVw9QjdCzFjgjB3n1S0Nk1qsMUNpHdr/go3mKPROgEqB02utnDIXoPcE/ObVwEtKHcojXtlIr0YIOfgi49U1Cq/hdA8ivctHBlobj0S3ZRjd+0gf9aGbPgrdq8Po+pHWpg3R1Y5CdzbVv86vAi82bSiPphFpSC9F6EWwYJ1N/AgvYAR+vrT07wzwdgzjtwvpvcP4nRmF345h/EKx1upK86+rOIwX4YxU165hvNKAFzHfn1cM0vHzh3iljcLLl47gZT40tB/BjUCzYr6/HvYgvR+hf/5QO9Gex0h6qJ/vL/sh4HUPk71nGK9Do8g+nG461q4xdw3RnR2Fjta4vnSrkS7zoaN18kh0pmF0u5B+1ofONArdjmF0R5E+5UO3YxS6lmF02gXo/wt8+v8odH3D6OJBk+5D1zsKHe1N+NLZkK7zoaP9jZHoiofR7Uf6bR+64lHo9gyjE5Hu9aF7dhS6rmF0hnTMgdKH6E6NQkd7P750S5Eu8qGj/aOR6NKG0dUjvduHLnYUutphdJ1In/ChWz0KXfMwOi4DfjpjiK5+FLqeYXSxoEnyoeschY727HzpKpHe4kPXPwrd6mF0e5F+1YeO9hNHots1jK4b6bM+dMWj0B0dRheWible5hDd7lHoaE/Ul86E9Aofus5R6OKH0e1A+lGE/Zmyf6S9r5HoaD9MWzWy7zyU6e9vT/nw89Bof4WG/pUBL3ThUB7NUyOQjkWwIOxbOMSTcNUjyOFLT/CiEWhpP24kH057dB6YdgTY3lH00rnQX59dw8rz0Gl/hY6tk7HOfTBsnx+vCFODLQoh3STzoj20kWSgfbXK6pHbptjk3zY2H35+/R95RxF2K7Cjo/BrHsav04embxT5ak3+dZ1hAe9F/nrTIx2OULRI5kU4I/HypaN/K4CXvshfphU+fAg+Uj3Sh5Vfj/RRhN0K3Y5R6JqHldXpQ7NvFJlrh5XVj7R2MeYyi5U+Yh1l/kd41pHth2CnRpFxxeJh8x+fsjw02l+hoX8PotxnF/v3p1eRfh+hGyEsS+ZHeCP1J6ItGqVe/Yv99RGS5c9zjnXkesVk+dcrKWuIxm/+BfrVWf6yVyJdm+Vv44dGkd2Xlv3biDXgMH4txGsYP8Ibid9w2n6kQ7L97W3OKLRnh8lSCTxLtr/+0pF+EGFptsyLcEbSny8d6a/Oh4b2zUZqqznZ/uV30v7aEv+8WluTrTdn2Px9U5PtTLZ/vXuR1oDWQPtbucocftPI9SbaztFkWjKs/sN4eupH26bFyK9D2IMQCxnDSU6EM0uU8iF74Ahl0B4b7YFoRoC9rZSvkrdtuUO/wr9u08j9rT8PPltpJ80I7dS8Sa77cFjSMvDeNHL7Zuf4t29RjiwTW8NtGrms7GHt1o86787xb7d9SL+N0JUzpGPCG6ndiJbsYaR287URotXk+vP0ld2QO5RPe64j1Zf2YX3lzKa9z9xhfWHzyHIm5frX+33gPZrrL9+zSO9HOKPIQTgj1cuXjs1/fGj6RpH90LDyV9yD+c9S//pEIB2DULt0qB0Jb6T6+NKytT3aO3uYvi3DeNF+8Ej1KVo6ZN/Uh/Yh3blU1mkZaOsxdzlDQZnj0J7uSH1o9zCZQu+FTHlDvMkWtUiHI8QiRGAMsCjjFO3ljjTHo/1d4jOi/ecNs3+F7/C5zhbk7aD+R/MtwGgveCQ9lOX59/NXkT6EEAU6oi27bJ/NdJnMg/ZrR/IVz+b564D8Qf8wOUPQp0OX+fsLbgR/4fe7OvCSlg3b/0J69bIh2/f4EG4EH+JrZw8ivXuZ/3hE+7Ej2dmWYWV2In0CIewP8p4b7cWOuP4DjuBeIpzNElZqc5wvH2VH3+BP/vKVBzSc4M7KyRXmlmEGKZyLPimkaCPbrONzhcN8vlZ8iI5MOptmuSnNcnmaJTDNOt51tQKqBuiWFtdv3Zka65iOFC1V5+8qd07IzjbXlPP17gnW8UKKhm5atbeo+RTtftWq/OVtgjvXuVUr2vT0nfmTuRzntNNvhXYDJ2Rq+Cv4FE0H/cTGrZIKgeIuCHHPJsnsBVqO3RbTxmoiJGsdLdaxHQlaanjXOF4V3RLPJ2j4BK1cJeDQBVjCOTG6aMDdEZQWCx205xOw3vOOjq+e6Oe608sVPeWArKGQLo7RqixjcsTE5/rdeQq1XHyC1n42xNFiWbh9c8jjKxps1ql2Wwi3VS90is//AO0u/kLN1bVYAvar6lro0tnxpSrxwx857kLXlS2DLYBcRnfM5d6AQbJ5XBO7cE9c9NtB98G20vDmOeomm3i4eMAtHnqebqi2BDqX9rsC0DTJWiFeK5i0wnnnAs3F01ddmHaOTz7LJ0TxCTHOFJPJeU8Sv1Lkl5wRX6RL7pPP2s39XHtKgspuC+WozC5x7o0o8wQrs8skfnYjO1TO5DZp7Bl08MsNQrIopBU5Dm7VCfHF0LFWyDgrPvYDXRDU726es7LB1iasFB0nLVOdiRpXOEGfC1BxFFf4YUW3CDVnnJUme0eSmE7S0KFtHYl076abTyziE4v5xBg+MRZNBkHFteehtvaCAXebb+NtXEONVzzUeJ73p4a33RMosph+iG5O0kJ7X59Vc0KNln+HihMdz/mrcZMWRs47ikiS6hi+OrZ220TOmRLGP1nGTuBl5/A66A5Uy0TnguxFQl97YjIn5tJHeolOm0Y4Il6fjvJTZsi2au/Q2DvdPbrWMcI7xNSZmM2qfQMIBFYM6FX2lqX2g4SlpVYp5XKcDgu7hPSpXvQC9swnVrYn9wcIKdlCfBSUHymkxEBwPSJ7n8qiZXGgNVSQry9Fq+UpZ3C5ljmd2VTXlb/xtK8jm3H/+TdoYgdVTG7XMLldJwrs8El35VIhPlucO8hxCqdmwypqY6YEgSmklPNI+mAfnbBOzxCTExedlxvclS+ji2+BjXvjUsgvugaGc/x3MrwxoJjP08MFkKtrL6zEdHciJ7xDLWO1QevCEf4dQhD/cBemwvcmc5Y7lRaozqYGOEGHTcmMGJ5rliLopCFB5/kX+1ix3IDip2Rhmb9oYdcE8Bbv9TJWLLojsYjw0Cc6EuldCU68PpiOvCdgdIvX0mMT9JYgQVWqcuuFdnELGl6s+0atOLUc5yaNcFj8YD67KhBGRqV0BLHy25XygxQnlOVcpRE+FP9MuCkaYQKvFYLIgaZphDHGHut4Y7zGqolucQUIHD+mg43m9jaFhxpeOE2TI0TxNwtaoVJDB1gF5xtbQTWfqA6Caiwf3CZMdBy3juHjNTznukxYrOFNGmEirxcm0nMAHudpeBVEX3QxcIW8ZVFr0btnz+CbbO4pM+SzRQLFD57muLw28cunWR8MEuAj3ddBkDbxuJw1hmWt0bC8d/3ytJSHAsQ/UhNS1uJQ8OI9qTVhYo33OVzcLhNfKaTFOA5aJgsJmta+8L0qncPyHcdJs/tpvGLs6GLiPFnp4hxqPjgbxt2wsk3gpJ4kODQap4pzxVY8owGDMDDxKWl8SjqfsnpHygo+JZtPieFTkoSOVVIL4SeEYAAKaRMS9G72qMdjSJonaz496tvsm/XcRk1pwFK4R2NCyFUtF7tkMexn+hbRsDP4PQYJZdg59Gd52BG+lNs8R+gRUgx2m1ZlDc91ZmrE77GyEe6vI0ONX7EKOfnSt5T1GstKWZHfVso1R1181Sb+NYuOiNXSl+op4TuT9dEnd6TEl45ZFX2wVLNM6Lj4r46gQ4UNNj4/hM/X8/mhfL6Bz4/oSJnOzifIn8HnR/H5MXx+LJ+fxOen6epb+fx0Pn9pR8oK5s/zV/P5RXx+8cVPx3Xy+WWL+K2VfL5F/F6kGmRWtn4RsCjLxKfYRE3bJXbU48p+ISU82h34KvinwiZjU4XMcH6rVlDBqcVefTNsyDKldm4UYk1VSK4J4+d29ES65LldfGr5gPtACNu63mF+0fY65oH0Ozr9/v/v3hsb7T08++YwDv51fhgEWM1MsVTbvOtHqK5s8YDbmZcktGGktbdohE4+uUf8PhmywIuzk8fKBZvGtd6ZGyoEwOJzhdRujHXGVguM0KpHT2umk9qndRo7LUaXQYjXCPM1rd2a1i9gnZrWnzTG1q3T7H1uyzX2n9yWKzCPeYDuGUrdL+YGsdtRFu4XydEYjZZAYZsGA5jb4bY+IiT3KKOJWL8M6iADwcRMNGGMhCoFlbBVC1XWziVVcv66DBBnBzFdrmornVFcubbBJs55tp8ZSMpS6kB28yE476NHnm+0OTPeF68dS14GEOs5+1YLt3UM2iAFs3L71iTOeplzazp9e741UCyBVsTbwAnStCd/xdXWfMVZv2tP/lrlzEwTf0iSdUZpISUJ5WihOL6m2zWGznwQarodbsvi2pqvOUu6cWsSoKkaPvmUS0Pnkdg79vM1J4RVUfa2MH5lF6Y/4j/Br67FauxIYS8ZOFPSFYWgAA4ell3tCa7RLQ435mA7kr/y3MeQSydHrSKvLQ9QzlQT3ZmckySe+RlDW2oC/G83vOuln+lSJAx0E9mhhXRttbSE/A0UtbKrI1Eju1Wt4lbbkM/En/gLkdoGlbnKq0rsSS9ZOzSnn7vWO/+0anOFVqHvOfxbxTw+zX87EkKoRWgKLfTZtxk4eNcmyJ8jbDLA92NOI1ymPmr8oGaCkBMyrTWBD7+Pz9S4grLED+nttW3xXL5lnPBALfMXWpfWmdovPn8J1UkNF2rpLnc04jhhYbh7E/UC0/RVKClnqCg6+ZyVlC6kmOztaUphU4Sc8GmtKMuZoKILzjeGqM+5tFkivWIo9FCpvyj05l8rFA4Pw5NBWIQR6m7tXbnC5pBpP/CLMJg5Y15/IGhVPsxQMw8ZJJ1wtyEyJZuE6cQwmGbstI4Rf4/KgkWKxthZc7kQZOzcMlHIwdxz2jH0C2fIIw+o6A4E+EZN846xmCsKmQNulC7yWOvwqQa5C4fZW/Qm95Q0+XYvTfQFl9pZeZbfZHBcsF5fWiZ+/SbdnJDcc621nwzZJG68S8Whb7bQVAJcXIHimz+hlpvC3JsM9na9uJj6ZaqBtyWJ3TmeWS68fqm7ONz9qq3oaTazXbQo52l67SX6fZMzKUJf9BfK/XVpYkn2j5we2edAuLs=
*/