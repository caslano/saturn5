
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
4Ld49PW9dK8HNmn9tIN7LC/bMhY5VQlVEba8Hi13lPN5Jd0I2VjekjljbVc5xckQ0NTfzWqNhNe2CYk+29D+iGhTZoOnrRS84njEtXtEwMJ7o5tlT5zEBtSqFOkQmhnPlUT9MM50uvrbALUy5l8BHol6lZDGHU6JkyDhpvsCTlqyeuIld2fE/HDKA8rDIhFXSZ1/OZMdrBL19JA1cz8ctg2my0RNxvmYu9emj8kkGVaWD6KLJ3Qb1thObQtR/F1oLm95R91roJPudaNEqVwgTa2FZu1Ct4XvLbLG/8Z0DNvdri9Y5vO82oFP4Hf7u8mN6gSl6NFohmzy9Mi22xWf/4G2yAcyV2MYsjfmQtsYGRp3WP5VMxxqi3fF3CwpP6DGdHisclCPgrZ0Bma73cax6VgJOCcl2o65b9RZSvK63GdCypG1W1oUDSUD3QWGwCVl2/HQv9FIlXrtR9kL3FHOh9a8lJwdHouF/ggAXwOXJFQMHCvpaKL0nWqVJ7wIH7g9vonxoVZjHvL8fMB40kqMlft8yV1YyL10/Xw96RtejnzXqLck6PN55m+F1+fL1n5J0Qs7PvwGqzc7KCwxrlhS1KEXJkWMiRvvjB/4QA/Hp3J9WDOCDmJXGQ+TGbf5/u348KNZ/rTt3G7tfJF2P83/Gg0aDkhByEj7kPGAj2g+patRfGIavfMJInCXiOYTpIIIdDQ+FY0kSa6U+jY0O/FqyyHo16mY5It6L7YF1r7uToVr3Nvj0ye9y2Xtxe2zYZi94IcEO6J5hQhCKVHEk16wYtw6wSZuHcr7/gR4v+BKj4wbz/VT6X3VOpxX/0Tjrm6g4F31iyOwkVN67m1e58Rg+saSnYYcpLETk8iJUb7PLgbKOibQNa8iSToQVg5XpNBl+2Ree4HhQhr1dbJas9P2+RyvQwbzMr+PHe7UjYH5pAd32qaeXkgg3zWjURK4dYGkfw5tKEPyin9pFkuPMfo9BNR2vQTOki+hoY85ssDcp733qIK6BIo++ryPgzrwHbbmn+Z5KAkSBAwxhAA9sZKNyv6No5gv5DT4CCh6eKdZ6gn2lcqw9qGLND/KdVOhM4dlbaBeATpSeeEA9oOtiveXW+2fCfyqz66HSNR7b+wKzT73PJ3B+0OK4hlLwewQgMzp+lKB2VQkxX6bv9CX7CGX0xbCcTvNARL551ov2PHzgU43w6mg6Bvce8E5wTe4AbGnpxLufzRybhd//wNIp0aE76BPb+LfHe0l+nSTUI9eFdyaCd9ppp3/gH8XczzIvvo5fLttr9w1T/EsKv0bNB5ztSl2TPdfjLpp+LdUpWEsMYbZlP/9t3S7bC9gf6FK8NFfbNCTT2icZM3vQUTxWtTHU1IBah0oTuHPaQAXVOTodxOzFOt2x2v9mw7mdHeP+HJ2x2UDnpmbLZlQ75d5ZrTFXP26t3ugKi2TqL7ZX40SzfqX7tnVm/3Bzm5iEBkV8OKofPe7VNV93Y7Hc7dDWuPGBAroLnuXt1766jBOlzLHuRzmnQz5bkKlRTdW+ldFJdsj96aNN99Sj0rt2LgmK3rEdjFeMUv940KGklKPGrQr6++PZ4XIn91FM/tVabDdCZcWRfwK7y5lzfAYR626bFIFnXpe1XTPIN27bKhHUX2NxJiFvBQ5gzSL/TZX1dgacuTqVBXNjKbMDXzKsnb8RWTsu4R020yUx4nE6edcWRrI9rF0eMmxXLhE2ok0/h3kHxdjNzv1aFnrzQYqlXtNvXXwl8SvLtOAsOBX1g6pXYJ9JNsmkyTw7/C1Gqa0Rd7CnaLfL5wkZ+mKvKtFVA+fs85X1YO6u17Wx3ZXCRDLfMaH1h+bQHZLim4Spx8l75qSVoY0dgC7oR1K3dPyRZ27Ta2BdBV39GQMwtuEjA83PTZdupMFgZ2OaYAKb61vxqwVl/9uy3jqyOxO6uDfqZ8Ppnbytv4NMqZxOfzrffoC/47tINHsO2Hn72X1w4oDYoieWIlxLkT3acUXgFhVSenCh08SxBqkabCRVe4VXbqRsCyqHVpTErfq4hIMdvHSxuiTAneKvE9JiMc6TOS1cJKoj2V4NGFyWAD2IZ64d7mB91gmTQ6tWLLmTA43/bDRsjNc0Hvww4rLk6fYutaFD+L/OxkV4TfltEhUjShCl1lXrPacaIj7yudm3XbxudKrNbsB8L76utt/LHGqKO8ntrR6rFkbQw71lpyvE8RGY79rOINT5ubX4CP+z6O8rgr+t6G2PFrdN7fbTg0XoiGNbf0v5l6jgb/iuwCIqObiNZmP1IAquLfzBnvAGHbmBpDZLbLLh60dbC/JqHdK/FY/SpYVb38Dd8EH7K42lVancgwB78MEL6b8O2SumJvDNVYood6fj3ivKWxRU9cdbtholq1EGdSzFepRvyt9yV+pM6Hv1lw2fXMDJbKmVHD9dO1J0G2T/A+5+tt57aJkYIDzztYoqY9jTZlmnvaKypYmKbOF+fdG3QdV8zX4x0+z/z3g2Si4M3rRb9UddVbZOPf+58dA09jjbV1uhmynnUClpt3vmXSdItyvz/aVNxfuuJg4hPd6GxdMiN6hjj4/FT+aFC8Dv+FxnnxG38jkqlCwXvNwfqs1PqPS8RWeBU9l+26v2eBr4HOtfQBXXEhApElAcY680ss17WH/Vy4u/OyfI21YfzVOnD1b4zsqbzOdN9qdHzfyay9vzCEALy9P/X/0er9Kcgx/M+gNezGv/iPhkCrPOuBTkmPsz1NHWG0v86Jg52xVO8viflU7E2gUOZEvChrkKJtBgRvq1gKc/00AHpbXGdOWH1f81PUFR+hK0uUnp/Tn6RzBOptdNT33dpHcsYsLYW6P146eL/F18XMufelyYsx37bZ8qH5XNepkotmhtHCl54/a0oP8qiNF0CP1aE39QaGVlpkfMD7MX6EIgq0jiDn/CvnzN7/VmeSJy9MVu56/WXmWTHZ9e2jXD3xnWP0cugFUB7lV+0VXEmyhSoO29Kr9gUpAtA5WvI8HtGhFDz3X70Wal637pF2J0ULVgx5CTYMexr7xdQbUI9aCzlkw7G2kMeGJq3THBpLMReeaLSOPe+Jg/Dg7QN9l0A7QgpqvA5oXqxejYKY/w7XRJm+TRZwEuw1Nyqz/0XClDKQeC+N2M23Nta9uv5ed/ZJ1u6ekLWLVYsnEe4c37ELH722XL7HHDNdD6UBivzWuHbkLB/6t7GMVWZVdMsHXVk7Y9j32M6tba++DDLUa68/oXVR7yG7wH1y+iQlHdA6vih1z+jJm3S7uQKwt+ZZHtlPrrR+dMjfJmG78JTlZ8OGOnG3RZ3WEaxwJ0K3GgR7rRX8HdyxvKeK0NMAw50XxAPnCC+3AmS6N1UsQDwGAKVk+CuFoaj1IWt0nQB27A+goaoACCk47bFf3jwTsutAUe1wpHaJLJs5hZhx/ABi2o87lrQf6ub/cnFvfCIlqHglgOjt/DsEi15CuPlLU6qpTgein1qkia9g30R6pT1qNaSS4vrS1ss7byPNpTPnb3KsZdsb1/sFnCHI9a22jNEWOt5kBGea34KvwNZa0W3DXKzNblhtwn88rlfCvbaHww53KU4DzdW3lwRb4bjtd1fKNU4B3uOZLi69DOFlfiiOBxNVDkk9HqK5wNx8pKojwqy28tHFM67DG2uVNHhTAnPNIILaLbM75SUB/FXMU259TJA2sf3nrs+/kq/LUJQpk9/KWh+vlq/LEgg4JV5/mm85un4+Urh7jf7QO//eAWaocv6VINrhsA/bFP0km2BwrL5mof6WRZLEYA3TaufmgOY1vzkq1TUTRsWQIVoBuQonHe+rrGTejot5xaTe8bMPC4tkwoyLwnd3Vx4+8DeVYnih7q5h4wXSaRtacbI1JZjeOTpXSto4FalduD7v5MLnHzE2vvRERCKFoam2jNUUcg2qpyYgjj1MDSSoB16uqEsZjVuLFCJFhlXce6+jCNbXKUpCQF5Opim28n/OoWjIxva0kHdhX1tj1fMlEnjKXpewiYffYZskEQg70lBw+F3ElPxKgMg/tTh1doheXybIb08nlJdiCUr8GVnQ/nIzt0KRmzMD2gB+2AeS3Xau7i1epmlpVQ0pZBcQQz1Z1l0z+e/5TOJgndtPbQk9khbCyzQQXGwQbq5db70m54R6J2MV4xHunwFWj2g/eiaOJy21wmoQD5wS1Gj+XWw0KJdt3isneForPvOJ9V8rpf9/9oUa3Sv6ze0JOyW8obkX8uC/2MViB8Q7Hx15aCNz63e0jcULgGNb7KFtGxGflDGMT5ZPwm2te/JqaLL0LYXUeV6txOv0PQ7p5Sx6wEbnJy9X8pQ4Xv48OjAIk4rjQ138AieHEAh3JS+oyZlbyllCZyZtpiaGk5gcadzuW+GL5uOzI/vjVO+RXAV9na2gj3Pf0VSCsX9EqNM3RS2rUxHWqrXEpuZqja8WXdwKA7+aSLb+bqLMflAhb4kX7f5wDhC1N6tICO3/gT2zYt2dLB9XZZxSRwm2hDVFj5Ym3je5+awPT3TGqsLs6h/55NRfnuoDkhStj/0mhe0y9ct0daMb+Fl/mbIEbbz/TuNgMsWZvfv6xlTDJu9RY6LSYntq+6fprQduB3vOKXKF/VCHuHoVWgD5JcJnMe/RXAibYRTh7+0m9TyrngOeXa+bvTaZ7wL5A7PNH8t5uVTyR9MHUVi899YN/s6dICwevFYda0+cSUk72QqblZCrj3vFO6itA2MqGZFAkFsAUYUzakcWCW/AaBWeFitrxcqlamuDKwHE25zQkU14SJXtxG2lf9lSpmxwfb/4SK7JGDkXZQ2k8OR7FeHO8ILzsXHlMd9C6eDsAkUCTOX4EKA5S+ewSSYF56sRZh0y+Cx2Ew4Xcsq26QAPiYT7prkiXuDXFEeRO9t19TsDl1shSqkj3yhORg6iX+Ssbj9S5WG3ntC3DgthEDrKd+vCjONtzbRqhpQF4rqgVYNXPvZlpf9NbZHvD5dgvlQlzQ+6ui5hVe1vmmoNilTqE/fZakG2WFfWZj+KdGRs6NGbzvpfGv31FvyZFffBm0NMBYhz2dqB304zJhRv95c4pxvDHQrGo4+Wa7AAALP/Tj9OQTc0ihztb/pltwW3SST5cgzKv453f/1FuBNWOp2rO0P29Ln6qUPRTeDQjihD+Opfh73Wd8dMKiYeH6KYi6JoiADvXJb98C0jd8AtbxpCkV0R6WDEX7O2TSgqShd0CgkaCTx0aOlxSDVb7Hfg+65kk7efnsE7JmGsiKFlfr2C7zDesT69fzn2+G1Lx46UYdUvDHSQ21I3AdxedrSGuNattUXXGUSN3F40LeHSKAaXtMS5+r7u79hfP6UTfl+h6lB/azcaczkDdyrJWVZxQRhVuQvO99KSHp+BfxXztpx+LgDHvtzIxcWF3cjTedcSYJcy+c4V/uxv51ex53Ly1kIHi2FNEYvSm9qaWO0dzzjXcqsWI3Xz26E49fJ5rcxRIaxPk8RzjLJwVtYG0j/8i326ZuaoX/6ISU2Jl8TzQk6JZVEuGgH2fViqEY50Se8Ua/kzzMuxFIa/auE3U+sJTyhbLvF+8YhEoi0cCEVp+TviB8DOqPaeiFZup2jD/1ryPwCDNttlHof7MEevotw9hgnmdvINmSux4tX9LSj+dmQg53/UGSjOFcz5Pkwtc6e+k5utk7txf9/7iRv69aeXzmFC+FDwj5hg2aBbfqKoEGp3UlBeX18ituGaCHr5mK2KH82/yTk7LuuU8WdRIDyrQSzy8b40rZ5EpI36Wzuq7yBPKjr8Z857uNPw9S7Hg1pjCPfcCKgnU/pXyn+F6LVPz9/o68v6subabTGjTO2bHyLqn0J/iV6AitXnx5zuff8WEim+V9rG+Jqile4knvW1Um9YJfSLDTlZjOhQzbqt4t4ux71cF1vKj3mxPB8AlWiHg3vrZiz6VAki60CME8iniFB38iDid5pm7pLZZsFdRihrS2yx+3d57WgbUTbZqf2JVoGrNh8HoJ69QKjQI6KIH5Z86lzL4TKh36lnNIxzQVZTCYZI5pHGJ65/kt+/U6A49T5zPcMSoE3vnX0uA9Y9hkQN2G+OXqf2dGjMJ2W7HxWpubeQPiq8lKs1LzWThmj+VHs/GN/ay82u3iRMwB0stR9EuUhtn6SdLqbHh7WRH81G4aDwAuWICB8PbF8TZQCjrubYhcbxpzxzh4gho3/2H/zqgbgU2BdFYtLvKbQ8zsUObwU+GXCa8KXCNDI2mP/ZTf40SvjfN3M5pjJOydgve27i+zapGkcX+/EVuTp3RZ/Kk+YrB5xTCoJ/GgOc86X7Bqgw2WRmqrU8mX6WHZox8fTKpni4xUPHmvJV5kP/ncWP2zy94sWazz6gP417cfvR+irR7A2kFC918CrNWSWgRA6WZxDMxE9bgirHnh/hZRBf2faTDw/VrrtImgafOusL7YgbT/17/72beVNmED0gkaCoxJ+iwlieeKs0/OC3mXt3a1OH+a4yD3F94ZlOjPY7cKu7wUWaCRLbFZuXmbRsIKPjIeLn8OgjYtD3VdteIGAroZ5QPjJWj9y8uqKlUDx3tLDGuFcl6b5sYWvIXDIlr+9F2VXe8KyuG0ujF65v8XYCdYSbCA1hVUTYLGIZDv/CDp43xrWIyYO+MdruNEo/NT/U5u9iJRqTUVWFnkcOg0YTh2JXzxk/ffe49xL0zspm/IsE3syREqbP8lgaVN3DcRdp9xy5ppkGPkWuF3GY7bPexkdIrz1v/lEqoRbMnoq5caYJP+wfPJjRp6Cb9KmVYG9TYkU8UPzBv5A7mjvX9g0Z5rpB80MNvrrBH0e1WnVR7Jm1YhuUWV4gvTOVUDLmtm1pkFcfgNp/uXYubJOcbja/ldgbRCP+Iek4n/Cm37tP4dNzva2ukKeAo0fZYnhv9tDkEm8DyLHwQOUCRvmqzmVwA9BNheh+WKGT9hfNy2EP4ZMXmaff05sEIwwVuFkwlr5bNas3VLKRtRKCQvmtg3BgHMjiGcW96BYJk7IcmjoBIupkXBn+dH4c2lRsuUT91BjjNq1PHmZ7qp5zm3lRIBYsHCTE79aRFB4af+Kk2TNiwPDxVSW+eqv+xplSjEzRC53luI+Ky+arBkMaLOgfTHghlygInSIyMrxAYrWtfbGT93uZNwb1ezPy95zgDWmOeNlyyfVrxNNwn3T2JfzmYv48lJ+SLMHtwlIzSvCdGr4swO70uHdqUbbhE+tpY8FA+hSRXSlDPiADi2JRKDfjbvICG6UFwQBcf52EmaPyUrpk8G9iR1Z7JsHTlAVPXXLboOSEogPt85RQw575H+HavBMkq+tFl3+C8AfFXeFn+eZSm4RIV9R0nzli48ODGcoRsHWHx9KM8pzBPrA/vo7Hn2X5zggI2TSltXDSYj2ePQGlYbbaxgNwhbYR6H0mXP2flVtbGQis2yCPncX8jpfS9y9p9FkJD72wwYT6ei8q+Pv8g4eAvNJNj508+q8chNofSi6/GSv6ijNUjacs7icAjc+kys1gNnrRSQoMt+5vhpjJjuJg5TTxCxnXlCNHhdypGPQDf7sDK9nxzm93+zEQg0B+aDcONSj3GnckPvf//hW3LPmvdokLr/1t8aM2uWyy5FJKDX7maLQ7ilygwPNlVSGeug4AOCsxjYtae68Bo+3tQaXaVSwjdpZPldX6Dyc7FGkYDnaW3yY4z2/SQj489JzmNB1nLT2iMKV1fBhaY5cACKNDvCd8Ck/Gvkc2LngGQGTwNZVAow+yLnmzDDimtb3suJsGqujeRUok2pH/BLtI7iy2lJasjQfXo3gnAxTQJuY7ZcsD9oL1j+92oVLqLislTD8zT3236ZCGkgcj6Gxf+Za8yCVTSUaEL+Nz7jeqRi1w9TvybC833G8r5p7aBWpAXrbk1SqIGwxYW1Lta4mMP1m2br3C8jFDw1mv0qPdvkxGP3yaye69bfYOhQEUBdr2WcYGZ5nEX7HAoyIouF+n6Gz630eXr8dWdXZUQ/KwMKCDYFZTN/fZqpaPuWT3+M/3pusDENrj79fLDaueIpEoxGsyx/P0tef71IIXTl7nMEZqmqXGJkSeBj+35ZlYIdI5l+apBQv0HlodYxI8qhvyDPsu5xtClD0dPoZyxCWG0x89OKU/3aKfh01T2RirmLpQ2HiofZ49orz6p/TTsvkvVkqEcF2unXHeWS7hzRjd0/hIXOwBT+ZT7Uml8DbntPz8aEOW8+TR6hD1y8EvNWPlRtucd+zrh6NT0PgdnHah2LCUBmF2DWf5rnKUUevZVC6LyWp0dyaezNfFi5w/vlmx+0tndMEbNWY/CY0yD1jlj6eC9wkdKASpCMSDjCNBapNaWXtDrBbzN+/0Z4QInAcX0xaFVPXubBVzsA4vy9ybgggqOqYtbXuXjnmJULW02bVbvTOiG6jHQ4LLqrP0e9wFDMQOC1WuTj97OzeJ4KuHspPk/g6IUwivu2xqJuwzWUfQjjEzav0/Fnm1FCnsMKvF+lIgkgumM919h9ijrya2lBTZDhdnpXyDPeH9jhN0ppaLvlvXIvsxYsxaupMXvV/T4SpTSbpgEcWwP0sRrxMHihh+50KO9OfpaUTwWMPEaKC0yktX8ypcDEiv0mxKlXfmk8qlLeVdA1lMdLBt1rt2ntaDqYJ4LebvEj+/UdL6wmJyZdeb+vXL6wbPFjAuOShVm11my+vMu3dQw+jrbOPq6vdqwHMAVxDti9bdZyWz0gtRrRhOBLNUJuLzTslBaj6Vyw6QfPfH7Y4j2IzTKL4lcHEMSyb2NZGUJJx3OreQ2musKQOlEGJIdETCeKx4/yna14U6D3RejwVYshqBnGWi2zXIDqlawfSEX2z5sI1CBkm9AUx3iGjWxBTzS5zXr1BPBt2IDKvzd0NJv5TTCWMl54/wggu74slk3qtyh7gxJ1+WrN1zbYDjnYcU/NGNcegimlF6qDwQ06hYucg+ITvMQmBj+G7HhoIR4KJYmbsKJ25zj/7xxRKH//7Ho1WFRPl/fNNIqLaWApHQ3iIK0dEoIiHR3LClKd0iXgHQ3S0h3N0svvfSyLLv78v29zx/nmjmfEzM795w5Z64dPd2HHiU6oaLCxkGHoncCka/sKscr2crLKmtnHVa//1F69UGWT+65dKquyWc5Ck0Z8kQ1dEoTWdgHkyEASSZibuTV73GHTEb3b7U=
*/