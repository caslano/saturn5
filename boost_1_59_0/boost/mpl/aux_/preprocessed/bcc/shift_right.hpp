
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
AWK5678Ak9s3o/oxCW5orS03gql2NW0vbXK9mI9tGxxdMki6qGc8PkUjZEjdgPiaJQbfgyNYH3fYPuENOsbj3hs9QdNmTptwjwcolXuujh+nb9cRieOUVhyAv6H5euHsAbxnBwcEELhgihckBhxR/WiAVcaOrUs4SWokoW8toDyGUjitoUXD2mNKnfeYe/x9CpzxDZ8FjTqKh4g31x/srwrfbLwS1+Nn/6eUjE4rduAUyTprdStpTI1ebzFK8J7IqOervdfYe0lPKVe2nnGsADxd+nhtfOCCUu4WwhHw74S+lsDvwl4HtOo0FF+NRYktAdfPR+jlpy5wtV6to/R7aelLXUbu7UPNBwbDOKQ3XvT1LiBdLXbRbvN5J8KBeJpav/TP9YFsw3gAcPolZNQ3qsBaTSZga5yEHrsEi46kArMe/RHJs67SaOq1dNcsOXDmBc6syheb1CKT9tYRfHX3ZL0t2oO0fGx5DFiKMlPKRjqEQ0/6Y77DNUZLw5XmVvhhlCFTEbK6vjR4rqe+caZQOfESHSAZ5YHIQ/85zGdkNiMzKx48lI4iEHrl0OIFVSoR9MXGCgA32kbAY6ttTxNAOd6/+8dcIMGZDgMKFX0kWEQfkuy0sRi5+GBTmPtFEcOsAD4EveYSRALT8EYrCj9jd1sSQ/Zuka0jIQobJZPUMmPKlGSZj77elrEM/O7m7y1uvsfr1JykRS6f8m9lrNT4Aaej//oh43WiVCqiXs4MkaTU7bfcGfRwaDTmk3ynzR/Ev0WX6abfJSudKbn3C4TvIcVbDf/dEMw7PPixwWESQEi/IVqBV4DecCheAisoX8I89s6rOtMk6gEHB4u+BhSZd6kr5fKgmi7Af76nOQiSJpRo/rZngdCk1Bpo3JPYcggj9S+9/YKzolqTCpxwLpLr7Sl0Cv4IFqV8VH4SqbQjgr6CisYusfqVs1UfS8+eq9FJunuABKksn+gGp9aN5umQCOu4DHU0KVrrwLuYSPrrLzqDkft4fHT0paj3uA/8hhKIoq3SixKAy3avkP7KGKh2fZXq75wuLLzU7WtqQCLXrYk2cPqaxnp4BREVqfve5P7yUtTa5PuH4tDQ3IuOMsC0F4oB0CenX/lcrJPmgbwCbSAP6/61suvGBHl4P2H1dzOwoCtLKR9d9yEZdpruKortGETut6mtkkKdq43yUGChCto1idB6EdLRlOnjMW+V5Ri/Prv+f/kXeJqKr2o1s5tKEeRcbItvfgAoJi1hC/5oR7ryBtAm0Ug3MZBM45GxnP6ol7APvTwXCC6tKZM2MCP6MzxfRihDEzKH+3jP2Ulk9+azgwzNo138OZvXbztz1pDKvqknl6uwwfaUIA540YJh9L86DrltmbUbF8yYxrnUo6M8eNYJaaxdkH0FpiOTdAa3u5pQJynOKYECXvUlHuz+igAETQ+uz60iHqRPDGOZpRIuoW1ln0zrnakmnHx90mDay7fCy0nIJeQmOI8i5RZCa3MSqG9ghMVhUqPJjlfwAECuUsTfKTBWM54oWhQyoZxnUm5QR5VVvxepneLZuSZE+snN+3MMlCWHS67I2WUWYQ6BzvWahmVgjIkcwiIfGQPfP3opg/cZLSOqw0ffVwEb6YxqYpi0jxt/3/G2Eg3DazK/te9UbezvAYgENSV99tY1xv49EU45ofPVPfRTgki6kmWk5z4lPGi1mGx2VZIanr8Z+RZlzr+K2vtXdaeDEB+xVFxzLIxw5Hffne4w1IRsn+DyqMTczKSgn2FLxOuQ6NKy/+mV6pTRxg9wcTOjTEMgGQIwjCMM/RxwPcY8bLTEGgqmkuL6DwbGhnrAD+cdeQdPMHpBjB2ppPZYHq/vCJcSMnkXukwSlBaJQz4TfU4uV2SOyakbbgMAGzJx/rGGfg9kNxRZNQRc2exXzMP35Ej1VbQjUSrbEItCJZYYIo0j2+90GLvgUxqrXZCNKe7RzHdLsLh+8VlunZ65Dl2iiSEO00CwIvM/oQEBn3lpsQyRvcpeJdWh5HFzBaBbk/OK0fUHyqayMO4MTzwgyLcBMnLpuqg8auQEsOZi3blUW3PimcoMSFv3pKld9+Le75nl0cbcuBwbel6ePZhwsH5BQ6v1FFBUS7TUdm86mUTvhp9JnfIXPwsalS5n0QQ3Z6tleXbLW0VXpNzuvRZ3inBBt2rIxuwJDdLeRPXM3r3P9zeKPupOT+yNfXAYXysrj0N84Z4kUawWaODkkVrAiidiB4u2PpwLeLC9N0qCdWScE12wm3EPhseCVARx7McBS+dmgyIdYWaxFzmU2PLD8t9r1Oaxfvhg1pelPMAzFnACS7689ppmbci8OZX5ozN89BFkSu+rsW2+JJNQR4JH7OzrXIAdYJHX86hrfuWKjFcopizzGSAvtDgv0buk9+77C4oKIPZ6aqAoBYgU+9Ar+1x+kiQoCPwXdJdFgAJW2vDOa374FOtBUrQ90/lrojPCryKG2AmeEQ8p059UyykYp7J7NEu0qihgRLJ1gobfVkmvCAiilGh/zv88fxaSM52/1lsYJbyp1mL4l/aIUjh/5qq69y+X39Zu9bdNkSYv+r4jRKEna+xBTWH0nKlyFM1ZfQyV0BXrH3tEsTVLZB66KIXPsrluZ1bZQD9W9u8DAhaFc9+dJjNGHfDet8nunE47RN2n8TV7Rbj9PzKnLPEPtx5/y2R8dwcJwYW3VEqIXK3f9N9GH+Hs9T/E+31ay8bBJDKGR0/FfSwLE9Z3G3JjNNFoMHZPkO4jJT1hGvIBQ8jh/hc3p5RrOQ6eGJ/81t/pRSQC2q1guSNXFeKwnOdPzVfvXPuQDfG1JxeKJU6K0flnDpbVNZfZY7zKahFY4D6CiumksKwYo3feUe8+kUXHCGigwxGazNFB0jEk3Kk0zaxkmo/LSXLSlAS13Eo8oJcK0YTESu0GtPYR4OecWjY7uRwuxhaipHOJLK1tpEppTa97hMgxcQPtXCh6Z96OxyuVXnLDUnWhtgqoIZ8RDPJ/b16NeXxHbn0GrEDmaE1MLzZI3zTXOb191zKkAguVhD0UM5s6fh5GQtYpockZDj2bZfhxs5FPxmpTjlAA2crGBfym9MW8idaQJN0AUyDrgQXaPJRgF/BQn0JIWx8eYuTVkivMGSsdk7Hld5+2L1FuDREJIki6rsdSSR9p5dp7QSfAfDxVgAMipArDZbEwXQZniUPDkZBEhB2U7OfQdpWX+JwyKkl7ZjkgD5KVM9C5VE1a7O82Akgd4apWGWlGw8HP8GcNdzzXSceRlgp9flqWBFfFTbeMx89TECHvA3yjohZmmS2El+rhFatuBfe71UkfK6xk4CL5zDBfdC2w4SsdMtjvkr9OGGFyqrzYYHIJsR4SjagamGDNUaVoBkUd9frbtRHzyALfAJr7BvRnlPn1sBs8bPfEBDl/QILLJGHFRY0r8KHjcWLhlJSc+qt70G23WRb9y4PnGSrfYUxhbyGudnooxBVX/IvMkDVIlMTwb+BBgQ2hSw7tjljR5d8iI80ZzuQqZBzRD+2TbzF78G2Co0+96KduwN6wqB2V1GOeOWQOtSPLkHitmj2m9FVjvHtC5UV8n5WgVOfzuCsvvY/1dfxevqjKroBLoa4cU8oaMU5tmlmrqs9Cr5N9JyUhJy8dkqbIhIcINApZahJ9hvk9ARnwUUuglu5/5TCOVvjQOZLX8PMqhGlBCklWS9IUwHtvdH56qeSbkM2ELgie8XWb4WJ6WJkp0WCWqXFyQ3MAQAn5DkCOC30AqAiO3axZElLLKTPnMd7hEIBmb1AHxORNCtGlq0KbNyAhQmH1IBDhVz6eURPUeCKJbHgclwYID2nwBm0KGzZpL3Zlexwfs5H5mC90OokoQIoKVUMbTvdfCzmdEYnSDTPaex3u578Jn7X5XP1+NVvBf/rondpHbpHywXF4y4eiHIC6KwmRtFboANYUluZzDKIK8/PQSTHO2wrWajBbwg/TzBQ86UTgb/RA4lien0iqDNAu47QE7NfwborqEQqmSO9Wnu4QP3jpBkTasR7j/sepvGDSStaBghcVWKJTwVLO+reRiqo59FQKAorynVf6+HP5zOWM/MiRvCI3GhHp5M0If5fAYXpxGNojTBhJNTx6EnakJjgPEHn1WwbMcnmZpow+yAoQ36z9oquXfgVs6ec3asDLmnM2r8rwpXJl7/SC7HSLp6ArCJF5yM/vW7bZgl2NpDYFJk6dRyBzOQMBquJuwkQn4IFguvO2h2aoL1mUL6OzKcUc5iNLNXNwRlFj4Y4Iw3ZbRC74gFqerBEiEIlCcuTJhanuVPHfpBRf8QtySNLVXKngNImMYF3vBSdJdvgXhSWVrSQrTPlQQGJmpYNLvocxqZbRmwj9jUguAd17fH/Rg1TQq82YRpQQ/KlXMhBhE7STCRuf/yrQ1CPyTdTPyX1jx32cYgwdcQV6Vv4IxYVlf0W6K/tzsmHwaVbS5MSeAGFR7QoJSlRKVLZgMtKPZ2rZw64Mwa37F4JcPOusEX4R8REk2UCB2nCgO/0Re0COb1z2+t0myb3bDezQaOuSI9x8Ct1DHNESQAvAKL+0iE4guavmvplvYAALPF9nItUhDxByncSTbN4B4Gue19dLivd0SZMdydOBEgWZQ2A3vMgC+VU6jLJyKoOThvPr9KpUvzj1tKwPu7jpU+acn3/sy/VspWsWg0sjhighqcOzyVBvvMXx752ob49tAOddyNlH3pm87o/vohLiYqoIq567/jmimptXrndUS1XvU1Z9+9gKxQjK9gPjoIcFpJ35hIDq5shGUdhSN7+GTAs/Ne91WrQIf7XvsZ+CqHrA1LbopZ5/icAEsHEH5iJDXAjUntU0mbL4QUusfsM61mila2HTdQ/kzKqoKEN/SzBy6Jpvd1EALHOZoEsHN40lBkPpszFW9VsJOS7Qf+qSJkoI1EJL6Wi9BTIngMvfM4JDQnuLcKx1fvE02ez0ObNGuuDONbsuAC/lhlUm1vjd1Be9dY5Lrc3KVdV4sUbadiB/6Va4MeNdUzkZoZWzbVvrbYoAhGVXdLfEta8QLQ9j6aJYjmU5Fjtf0U6JPU86BsULV1wUxxswlZ/vwyR13XdN/7bLky0DeUahnfw9+bgZCBhT19w4k9UcvzoZRf/PBpEXtxYUr/TUXwu0PlP6zm64X3RAwCxf1DsK3l/riehpzMLBam4r0bzoShuTpzK+5EHxhSTdKTWvE/avhXVPtyR1v5WnefHkUrW6IkdvFxv37jTrPp3Ytjg9xiXHCEmZciLZz9sdgd9wn6mDAHXUKp9hE3p4/SSLfHWnTEnk25NR8g7E7Ab70oYakTSh+CUQbSVHW2A9krzmABywC3b9VWRUTwCRaCIUrmOIceIWFOVXnDIEqxBRP2UfdwjxS7w1XaCtC0ZZ+Q/qyGo3+l/gZGoUGt59tQxFa3FXwNTpcdMvR5/9hwB8X8XRjpEpYwB6+0fElgpskqakFMbOoU83gRX3UoMPfrkZc26H5gLORN7asbsCqj5bCZ26kn0s7IRMZWvfuXsiAanoIrvefTOsk7vWJSVyv2As5qvqOoJLJ+92lQeq7w+dglUOZMKxrxYIOON5NFelmPIJ4j61uUOLlkAVZMMs3GHRJqnlNaSjBJAG7fe20YTgxHpIkSGJ4Z/RkEGgN0HHaiog2Zt+Bz0AozyLggSYmM5+BaoWcGt666nwXAKHyWUA/71TaCcbAryT4NGsei3IgmU1R0lCHgp07GMlOm/bMj3ynOPm/4JgZpGKJinlN9rv2QQpB4kaTJ14u3GKC8lgNNzpip29vOpEXRaiikXpdZcVarpA2kdE0FG+dCASM7W6xzDNQicOYJWD5y33dgBAqqMjLRAGgZ03dQ3DoaijhAVaaCj6Y60XtPDbGGjPnBU7JYhQ8K1jTgOPCYzxpf0hwrxAW48eMHGOlr4VcUS6+JcgeW10LF4gOdrDR5FXOaJXxD9ZByvMZDvjIGbYnrNkUOdn5LbqCo+NAThTISohSe3t0F7CM/j1tuiT94na6IeOlHlVviYdlM0ZmIRhKl/X21Sa3fZckIpJ0oCzaFimqfN3UcIOA90Tbxq3Wnmr2rhP1zNzbacbn6RZdDQNW5lr0eIDsyVovyivOBaDCmQUHOQOk5wKdShNcX0RZeOyUZcdMpTJ/MwAqaESs8d2XxcTJxNI75EDC5kc4hkMHBHYf8fQokK4RcUJnnhiMeBtPIgsYQTroY4P9VeR+TgxMkCoOTVbywNKFHIgh86MyArbp3BK9gH9Pyu3WBGPn61oYUSa5+8V+9HFK7E/csjuosg8t+0RkyAgBqEVuTYs40lZbTS0BLeL1U5eLPjAXQ+ZUcvN67q+JGp2Kod+YwTOQL54sIfZrv0wMOBEk9SUYNm2AMOsBL/IAHyJg9kceRbFfmUqaRfofnsQU67mbBlCIjjxHTjiyIkDv25DUU8eIdyTg/La8XlNys4nlTOjmig1gm91lcc9aCwxh0/Pp4aFRNseOspWWG4Ctu0597GiQ2YYY9kRPZrWWzfJUY0bHdrTmReh6KZ+V112j0Keh1mPeQbC6JR1nns7AJqY+BLui0eMnjRVkttyUSLbPgFTfDSlIbmpYGlQCTPjxLoKpl8SKXyVZh7psJrEPwZFKLs0MgxiecdDsaIDByOpsLhADjBkHezZBKm5KHQMZaViVKx7BekgR/AaQ0QRQA3UMueXLL3IwwY24AC9sXD3SHWXkhjk8s5rAzVIjniGCDz+5M6XEBclUKSDClWWBSOuG5d9rqdsiVaeMuDkFTdkTTV0XR8SNWqQ7V3CdWfwMJPfZCBowyUNm1/o5eTmxgGDUT7v/yA8+ST9/Cb6r15u/ht2NCuhQrt8aLuXWsID4Uykb7/cmaopy49tCv0JxIQWTnn7QVAJP0pEAHmDdY3qnimuHUAsH7o9NLSw3encinSayyOCwdmSk/5D78zWlK99GlP6SPClGUByv3KEQ1gHHhJilxYL3pAVcq0CoBX4y5QPQKRNiwiNReFadN+g4cvI62ShDhbm97hMix8fZZ+3i9tJuSBlRDa81T0Ck4/hPotM6g3TOIOupD1lSygugIB172D1CIx3SLw44t0WxPo6UJ25IT25ZGJg8XnJVKUeZ7SmlYdxGsNhRgW8VEIABN6QMadISZcJwMPQ0BK4Jsn9DnY9Mp+/z8MI0PxjroVYZ1Hy+AqSrF/Uah1hkc4LMHoQo+JrUbUewGdh9L3buF2iZbEMHSpSBlMPMWf/ZeXASor1cy16Saq2bSlhx9tVWGu/Amg13u8cA9v3u1uvS6YGpGm9Qh4gRyxhT1jcYWVWd7OOMnbXXqETEbXRopfFPheDCDir/2q9rCFDEQfR/M7f/AKECU97+cLU2n6jWP11BG+EkoEbktbZG1HJYkBdBUvyQ5xtbHT7Mv3Gn93dmM+hibB/E7INttkw4DLNq9ip4lU07PbqRfDDlVzW0+xKB0VGZMjKLCPMYHNujiQoJ8/uAluCL2rDvYwkrfw/0HSt1YD7lL/iiH1GHRFjDE7yJlfEovnFBs96kyVRz08dvX4CGPO9+thoiTmnZvVmcQ4WsOuupIonE7r28jwSqMoCv8S8b2CmpW6khleBtpfB7zyc2kFhJ1n1RSnX
*/