/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // appropriately qualified target function in const context
    template <typename T> struct qf_c          { typedef T const  type; };
    template <typename T> struct qf_c<T const> { typedef T const  type; };
    template <typename T> struct qf_c<T &>     { typedef T        type; };

    // appropriately qualified target function in non-const context
    template <typename T> struct qf            { typedef T        type; };
    template <typename T> struct qf<T const>   { typedef T const  type; };
    template <typename T> struct qf<T &>       { typedef T        type; };
}}}

#endif


/* access.hpp
CqBPF/7Hj/2MaBTCM4qVA/6fC/8Xwv958D9eepNauWOdRaOhW6IN6q3DzXiMbvJKg/dG7k+HzWcm7DIttPlEzy0fGmqUfSxikpUYhu7WMJeRX98HZu6rvbpIuHqJBfVuyhk6yiSOv5SB7a00Ec1CO2HpZw2oo5wk88CpkxsQSY+ksDCvX1C85LhFawrN/hIdINRDymnUotSqmvBajU3KD5SEHsf+6uhNndofHfEY2F/fF5H+Pv4yfhaTKfRefoA1kKbuBDapplMpmQZWi6dQpBYezA2swV+kt31vFQ7MV4zGLR77S+lamo1ejgIXOwEEWBya9k9X4Uadrpydls1cBrYSmRX16OSn6IyEHz/UY3ixPdkGj9Gnlks0mRpN5acaTThMF9cXwi56vj0j9Pcarbh7BGmZhrWYH2Ux+AV+KZrB8sppg85FEa+ArqEPKPBOaP71BOyjWaYRiJ3spkumXzzFFyY/X6vKTMJpX/kWwtRq1LCNpGdq8cyS75y23Og7J3kTd9JNxLqUPTU1b+PxGr+KNoX4YYNAXutqPJ5a+VeqQiy1GZ+9BUxBJVrrXllT/5vr1Zc1m6fa1Oe0zVjuvUVU3IAfYNTUR9/XbN6I7Wi4msdDkT58Kw0jyq5MvyBXPYDCPNeA/L0xVlU2/h8QVIXme5hNEzMGvCSrswZ08InjilwiZr8RaxV7QpnvAdNTa+m0s5ePCYqGn1hibsPBXiQvNAyU203pHasQfhiE18sz+M7BqvY4njE8p5P9uA1mr9BnxjvxPnil3F749R9ZzWMWolkhq6+y0NzmspoaXjaf1T9rEV8bw4vFMNSyfiK+zEReYDQLtK/iwQ2X+KQX/xNGA9+PAR9NxKuBvNehZ+A3YwP+CnRqrjAyBds59weUKsTcRjpxxY0L5VVcqYuBy+e6lDe5dP+yG9nSCPrXW8aR49uJLA/q+Dyu4BvRuvMIq1whUZwLCpx3UhJKija/k/yzVGWppogL8NQerSgK3UitYLvjLgmdOaa2KtsvXr8MNQGmq/t1cBGNHSIg3sLYnmUgC0FlF0n2o4EMvZrR62jzoLs1pctNlood/k8K7TtAW2cH6DaoYfHgMSu6Px2POL4bWncEOIpTGPYEuyp24Ukgzle7KlE8tJOhJ28J20jHgD6vAD6y/FYnuDdQ6RiHOIq+u/ib6Lsl41Tm27XmuXHYL5/3W6YKkjxdzyReEthM3fBmjw/RrOJpbHNJTBZACbxoi7baYB+n4mVXxckoEIF7DfEiNO9pFCHq4++4VT6MX6yHyo7RaVtcYrdfUDFSsaOHn4t6VMM/y3bl8xfFgLn2TPzSShN6HRBI9t5qaEeE4L1zcmTbk1xLte7QjP1DUmGpFsgw4jAOyreBW+iI7Mt/AP2Jkk2YWKr1sMOhA12RWV4VmaWSlxHIy+fVgD/0sfyhL7sG7zFzI6V/oE70P/GGNKrue9gwwmsAM3r9xgvqSh9RnvBzxwV0D0dK+PcR16EQ8kOK6+5Gmybcyerwid2KMuZur665W8jre/QZRW428PWNTHNTOIxhjpEyBfVYw3wSzE54H6AmfLNH3VGufjq45YZO+KFJrJkGPf0DSb2NpP5asHigZXumkbzK1CIvUE2CT3sLaK40otAXKC+QvBeFHj6iyp5ctYEmQkL/Ggl9WVIEbLwvEYNQP8N4Jvlb3J4SsKv29hKq8H1kS0jKga/T6SGtpgCGuToyjPc2/mqpRqzqjs8iq/oVovYnhyMK4ZB49a+fCYUQ37jnU2i8Otsf9t7E5MoPCafnRpZZRKs3sG+BWr6h4s6FCkwQgddry3i99ihf7w141+aNZWN8TZvvRsCNCPh5AXgkQvAO0Dm05ctw+Ey23aD1XuU/472C4ZVy3oRi2huLayii51fpAxu8cAjYvEDebimVxtH+0FoqTcCAkb1Uur40cC2+cY4rdV4PxaWB+3T0ewL9Hge/9aVMU+rUljoTSqVEvFaiNJCVwHKh57Umlr3WxpLl5pvlZh2T5a1vS2d8QVOpb4rmERP7wHm488LZLhyhua1HL+3q7JW336crDeg2YywTCqFBqb/roauiVWH0mLp6GEq3eSQPsZsGb6CXm7t6RijW5M4LUEHUTZK3ZyXwl4flrd2l/paHZOfXnX1nPygNPJggN5+BIeAno2l8MLqNSvkZrTkA2HqL3HwHk6d1fio3j5L2SSC3ALgF/prkrfuD56BrWW6eCXOd4jwHDwn0r146h1FxeWtfMAw1JsvNDydgLecBeNLjv1OkA9CPbdA+YKoe6AdDo9L5SB/I3ffiAWp7yqHSAF25w/9YFy3kD6YF8Bfq0PlZ/EoF+soEchTIzfctLpKbn0ezoFhufgn3I85vQMUaldTlUE7bNq8dQH0Jd5/Ofc5vSmCiNme71IXpRaAWW2a3OrulI1LY2Sf1Kkm/lM44v5HOOi8o1kV4xY+StByNm9LAQl0pmw98FViox/vlSgOrElDfONud+xTrvdD8gtTrDCrGPHhjhMbEfIGFhtJAzpWlgdtKA7NHcY5KAo7KkJtHMgseUtfwSJFN6lJy9JjihC47V2PKiAx5+5KLpf5TcvOph8bJW0+wOfhllZn1ODEuHzR1Xjrb3XMFfyH1UIHc/O5IpNL2vL7SADbe8xCgYA+egrBBO6ypNvyB3HxC3roMyge2hqkv6fu+jfNACBzfrzEMq/O1GPAgiew/jxZgOeBJrroDbUBCYarcnDNKbh4HTeXmVbrOj+Xm5QZ5K8jOBXlrDwqSsxeqGLGo+coAnXzYBwVXQgEecYFH4MXfJMBPJ7382okuJTA9FCtuC+3waFOsC/GTI+e7yvxbNU4shMlKR3BHiQwgdQHb/M3Zp6T+Fv2bwCR26QzwD3APcJZzt9QCXZvwYw9luU0KBi8Brz+PXKgssfEfyJ3Yp+Jdbgv2QckkNIqU7BW2YC/8yrJhyN/ZpqzAt84DpQHib+UB/KlkzwWefAkZHyor+Q/ZFi0EgQNBycrEQyGlgZmL8QRsW0rLopQ9C6Fch69KA2uwD/jTwk8PYEUbVi4N0H2v8AenNU/cGeQ7mRSNx+PB9mTgyFTugstD/ZrHrkfPD8MLo4FKbLLzSwpAgtCxO6EEDxbYFGMa63V+ARKyD/fiUg9i2omoN4HQ7ZIuSPvxkjyongxdFiKNvWtBF07gupcBXYPSGf8eJj90NV1vuAubIsv0nj3ckyjtoke2T976Lmpe/6mHZPYFMJus8tpVMAAe7JAB3SaV1Ubj8aPk0sBSHesB8RHd4w2/XzjVatA2UfoirkWqvPUINNJT/R/Aq1ilu7/nSiiRPui8AJoZfu8bHaSzaP20LihEUrwzdRIqzgT6V0+a08w1JyrOh0FxjiLNmuCMVrDFVBhU91oH64Gr3gMSP5O1dT/nlsAoPALhSHkn9GIBuruT2hg/KGVt16rqZ9HCdp1G3HwdKU1eMC/lHV4eKhNNuX82LcovqdAkg4Iwtch0BewJZLoi9jyGvIrZS+jai2hr9jzmByJJeqmCXpSwhzNB+zr3ITMpqXfTuWuds13JwLNCZuCmc6BmoQP4IZ1GIcVzKyCUHzjPKhmroFUyypNzPwglsJZDyXgAtyh4zgiEKhU7sTrPwt40iLXL7amgu8kz4AUWXIVB+zSW3wSrYhNp67uBNewpp/B+7ZQWCZ0NKNxmX5u+54qexKi+NrFlf7EDC45HlXzA+S5enchmOxieMorV1rMd0pdxjGUuDfzyIlu2zgGNr0PNaBqiucxfDtpBH3SQ9N/owAntk79HexhaRwfF3taPDvraDISaSwZ53eegv1P2oNJND8pV14vgY341qPDJvFur3LwAlHmZrvMzuXkGqPG/yVvPylvbnV9jrAheGrGoeRZe8gXSAdy8APT431CTwCMw9q9Aj//NSS+/pCUZJqdk/C5QTleEmZy7lfJHNKSOzVKQPmMCToLf7dIuJWOl8xtgMpiuFaePrgjnPumU80sJ4AUVDzNQHrGBoRJ4DblSOqL8jv9CbsXeoW8qmIKSp5Tztw9noi3l7FUW2YIXEpz7A09Qcq578ZeSnYv6PfAESgFXx3ikUskHvX4uoWdiYFRgZmaAJCZQi80CtVSztoL+baGDLPCXc1sGCmLo73NQBNPa3llCGYtGHL401tSyUG9qH/FXeKp4GJ+ehqf6xfi0A55W/A6f3oCn07Pw6Rg8HZ+NTx1Yrxyf3sK28/DpWXhKno9Pf4GnzAX41AJPpjJ82oJPv8GnV3BcenoHn36LTy9iLyvxaTc+PaQ3hYrLVN9cBp/Di+nqHFxT1TmcnqrOYUWmOgfXNHUOtul6E7n+QiMjna3knR2/We2swql2ZkuKAHSb2tni29XOku9QAaqfpALkSlUBOp2qAvT0XSpAi9NUgDKn4EQ0Jk2owttvIppr1YmsGB+Barw6EdMEdSLHJ6gTedqmTuT4DepEVkxUJ6KxqxM5fZM6kRf/QZ1IvUNvasOV+UhJSlhJeoqOJNZ/gf/O0TahE7LzUzpl6F+RVKaXm2b21czsC36qjysL18wMx5ZJctOomlH9a2lrZmrZzL6RNRjogdX7PV9YKn+cnxp8PRE2dSlh6ZRSfx5N7sOK8eqmqwYfXTozYPCYIj62YrzTn5dEhXxsCcQ6bnw+Ou4i2t5hOY6iEtYb/DIxGEo4+/7ZDt9nOt9xvW+35DugpZsSWagsV26evUpurq6lT//gR7nUnv42FGA6w/GHnMHaOjrw0SJl+XoTx7dkju5IaZlSV0Ef5bWM7oB/Tih4+SnF8mqrsXLKoSl1m+lQY2vKnikUGJEfC/oPen8G/Tbgr+aGf8XxOsD2XCW9n/4eFOAExu/Bomq0vaT3p6W/N/5Q1ui98A6PfDtb4aGGT0XMZDc0L3d2+Fol3/lEXndjS4/uRe3ZnCRMybZoAUeVJG/bXUOBNHiBGXViiy/x4gpDfHEfL9YAtbwW+jCypjpMjg7sZyQF99rkbS2DlEbycXwX/Ff1x/+aCP6rh4f/RsJ/9TDx/2R//FdF8f/EkPhfMzz8n8lJMsYjH6ObUNoSW/aVQLExHvN/F8UtMZj/mnB8uh/mB5T2/77NVFDEljtK2CWkwSmkwXtIg0/0SIB3JaCBTSP78TLuOClACozfg8AJlgOsbGskMWiVphGsKS0cM4i1GtgY1TYiltPm43aqsY4TBz9OhIXZgniqrqcy2m7VreH5PMzOVhrpUBYG5GB1NQpat0m+Cyqp0+p+HyF1c/Eq3KVgNzcgOYqJV6DIOL7L2Qp0mY6EobkdFSzSXFcrmuM3BWZ5YysyWR0CJdpaxoedQWibi233cAGeNvpcyp60aj5ycPQ5ZLJZOmSydcRklGmgSwzxWBvwW7XgN/9R78+hf85k1f+qMvUqwdS1gqmhCgl5exbAj4DCO2Ky3ULz+IKS7xzMZ9rogygTNEOV/wmNPSN2wb/aWkIPzqU6IgQ0o7S65yMz+pXgd+h7C/2h0y7E0PUCEeNbnJ1Qzjk/k3M+vsfNCr1Zw6kvGB1f1dGr2DKkC83rBm0tSR1MgwQSBbFFlckWfwfiqIHjqI4EcS/SVjqQ/i4UkCC2YFEDTedAZvq7iAhEGuHooGChuOkUlzv3RpEWxLkYaS5GraqUOUE59Ug1pFU/H1ENvxTkglG3CNVA1BLaoT6qHf7UXzs8rSKzrr92qObCM1BB1ML+KaKk53HpHyFvA6t7ED2tvhigqenFmDhdHf+CVDN1OLIuxDWQMaJq9g6ilfYOSyslklbqkaJKqIGUEJ31iJ6HYhrfSXNBSlcxexHdCGmb8bCE93ow9FPyHGeDGKUtG6H8RNtzZcoeVEU6kDWMjQY2YzLXwGY8RJm+T65ieM4mz8GKQZOdq/wMzeDKj8gYhu1r+oWyUemd3oTKLzClq9zUiOcwiuSmLfhXme/UwuMN8Hjwgu/DRPQ/wPA1m6/jdW+I1rFTnZrNNv7GLt5Ao4MXRkOzms0TtRRY3Tv6ACb/qPww3NfXVxnUw39vUlSxhma9BXFwAnOgsrwktjzJ96Gu8hONDWV09LsAYA1VU9/p4R3YreLNmJg3BnhTEXlzTcwbE7wB6PmbfPvVNTVjtfgxRfoF/IgCdj7KspFa/Fm7GTuEQsWoSNyzaKki3Mr+f49aIXLzZhRF51HBylJ3+hEoe4xz/FHQxtNQHRP3bqOMr6BuKB2K3OxaJW9sG71PVbPNc8tR8BzOg9J76ehb4MsHdjNNaHXRTYXoZh2pWOiiFj/x2dg6Cn0S1vTzUDZqXw2yPTAy+iFqNyMOqubbr5b9W/msn4wR16NCV4nJPzHI5GvrG8Wgz/OGfElCH6ADQdhcxdW98yh0Mh8nv2UN15Z1XGv3ZPnelnyXEsd3TR/dWbuZLI2WKY2R9Ym86wNBuAb+H8s42Y+MBvoQu0j7OMNwu9Uflv1IC/8hueoJElrMMQzMh6zntXCuWrBoYXsFCoUE/82jRCPbFgvGOAfrOvtPEAvgtNHvwyxqMPfEQd9HetYHIpMZLb0ZSw1UWiFKkac+JZ7ajzxVaL8FpuzE7BWVrVr4L1BvibD2AjryaBb+wGKWXNGEJ6EwrRiekPLewOY4Umar4p1IZ2+EgKepAp7SEqjWU/YqA/1rpH/xeLV/j1w1A7/VnO0oSDlUxH7tYMHKD1HWfccTWXflxxpe6bFW8hHm09mdJKXwB1rUBSmH6BUMla1RzBtFijKrXDUPxbHY7vtIqyzV/eIUagq2y/l2yik8UELfy2FqMtiy9OgxOsreTt/nzfHv8d5E31n5PpKVDB0+SrDkBsP6X4SxB9h72H3H5Z7r2CXfZ1rWGi09e9h33CS9TV+aQWtJapWbGlAfBXt16DKSm9aSdso2aQ/21lRbSeVsuoH+VJNOKtRpD56vabieitba6U+DPabNjQhCicP3UeLoQnuqd+yuqtsQo/p2MgQR6SdmYJW3gyGdYvRjAX390nkchCkTFALGal/Hkok5SZ0fTzo0cVHS6DZg45ps0Ci8s6oW2f8B90hkHuxl7wZPSIrxHrn5L2TeKMY6ZX7mD+Vm6x+cPeggUcyZ6eTAeY5UR5di3gTozZSbf48c7fx8Opce2BlmojweTTmEXrXaAGqUKQrKppKdeYPcbFwLA6YBW44+SgpGKJVMJ374aZG3VaDuSEe6Nm9cE69dGDADyTpYZP5q7lFPxp72woKbSV8RbmwZ1QGLCv6pBVB7MGDowHZyU4vcdGh0h9QqwIcCblYj5X0tuhnEJPjca5PX/fVSOLxg3qKF6OwE4iE9fZ8kYhI7uekFom7hLbCuvEBrD5AyhsjijV284UTeZBdvsOhG/qEG2Hpe64J57SQsuNAsipKXBmY5SawkyXdc5/vINLoV6AX0o8qsOInlJvk+st2EldFkbK1pGEH+NmxxE3qGQFmY4F0rNUqINOI65CZSBx21DYSJjZiGCjMxaYg9qhORO6g/2b+ddORaoYxpJekgQjW/8FiEUJue4Ebd55lChZLRtq2BLMLm5Xj6Kg22apvIfAVTEK1usPfWVoldQybvU3S2ZvDOaE2BTqqF2R6szSaiIy+NakWiwx8AwAz/j0HiVxHYERC2xO7MBQhPR0H40+Cj8oXwhRq+wBIUYn2pVecBfdcPCkjd4F2uE4D8PhYQmv3k+QhNcFQQQLgG/h/LOLk7QAuYF0itXK9ythXMGd0P0ud9xezV41fy7ydNxaw9VHIGD3PQOd88A3PP92DhjXhM4y7Yv/veMm5J9N61A1ecQPVJOhJL6derKT07HdQN0N4/UI2cFsugC9p8j2i0BWUJL0tbFpdJtQsxwd4w+qi4oC0bzWZoXKH0L8LhngkVF3TwexaeT/8Sfl9ZcUEqM7IijSc0/iv8plBf8WONd7LctA8T+LCqkU+2m03SHlK+r0lES1a5Gco8VEQn8Jy72a5Q90lqDWha0CbOIyITR7833My/FqQTI24HJgQa6TuuLZCbH8cdcxH7C505xEiE3FzpoDBGmVXeuqtEKbf/1vdZi9Tm25lMpiFmlsGFfIQ0w9gjSTOwUfLZVoTWq5POkB6evCDJOxJPo55ptdF5NAclfmraQF/3tFwkX/UMu9T6EKb7GuXrTVk1YkcKWhJFDig6BEXnoei1FPqgV5brzmO78/DwFXKIeeOSP5lNytzTLOkpCzwFP9ZXtqX92Wyq3KlqF9yvv9ayWm/yJrAxxy+NNdVW6rmVbQbVUkVb3wAKfdUe708rz3e8qjeV/VBu2sMK2cUSD8WSmlpYvu8iurDdnqJiV2jncgk2BNaecmhye+X5089+e5OEhbzJPXLTbqyGO340AEs8rqJid7jQnoQi7XvLUltJc2nxTsRAi9wE9tejF7HLEpe7SNG/VOzCylARA1e1lQl8Rav6DwRjA2mwQ967KsvtZgLkVrlpL80qOiErTRBm5WsxwMRO/YomdgL1A4y6LNJJKnZCoN3yrZ04FnDoFkMPtwwCoaJ/lXy15mnFnlhYA4kc7/hFPMAaxN5L8Ht4m0c0KYI2UgdvpX7aLPvxdgDErdxUM4EvKkksyy4FgWO6eoyvc2ZJwQykLMtBxXG85bsA/GPTCY4aq+OfsjO9H5kJOOnwH80mX9vp1/SUeRTDscBXmOBeowWonUHOYum7ZaWLj27B1Br4UT8eQnus9gtykCCHoT1Xm9WHFAoghWaGOQ8On9dmLeOofXj4vPbEPN4kFymRDZQARipx0Xt4HT7EmcdcOy1chcfI4tjMSmyW/VIvVKSZqpW1CAOug7X3aCMw/EzAcMsQE7LzCQV+yXkMZW0YYIhWnfdxMO6NAwO5wx5hKP20OIC0yH8D5SbCS8YsaTdIWwQwoBAlotWCFtJixKwjzA9Ym2X/DMy+mU9HJpJBX+HeGlaaJNGX8zBpLXQE9ucu9iuH9N6guuvvqu46EaO7lpxm+n8n3fWJvvJtrrvMMboLbbPXWh7h+usi6S8z11/WqP4aM5j+UmIx6yexdXtcxQWhc78YSn8N2STn3lj9pajSbQbpdhcXgHSmRvTXmP76ayPSwQx08CjT9aS/UiP66xqhv54n/TU2qr+sMfpriFn52gwFoVs5LCd+z/XXzyKdoP6yxuivy3WyZC6HzoXzHgRCpcBAKigK5FgVSFJcao/mEt6lsSAGSKGzZutw3Qt8b311paqvRqC+Ero=
*/