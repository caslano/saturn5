
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* modulus.hpp
VrQp3HHt8qTeXzT1umhZjg0hTXMrqXC5GVjfvfKgpq6/9x4it+0euNmjZ8ZxMFh5nbLqMFXxL3oMWE8Uhv/fcQz3N+iCGDhLmqs8T27uOy3d6Np2p6bF3sOvUzYd7nN8ZVYchO4m/tvL9U0/Km50fCuopY9IvSJGgwwajWuAsd6qNJrdI5ICT/BfFacmEYXAWL/pFZ4jXD6AjUxqNsjrEgxesWMAAHjyhPRU3oeId4UqbuGQ5qHBSO6F2m11dpIkgnzBfWO+tJzHlxbJc6teP9tfNrse2v6OT2gaeh+vJwruNA4T7s0OvEkuanQWgXsZbMoSb2ilPoY5pkLG4qA/2l5idZvVqaGRbfMVDQZa3EHu8uYetcY2ietxrcnNQRp/bB2I26lWKv3O6h6u3evGIYr6trxi5hdcFhCu8vng+05+j7YaaIGuN1qizaqR3AVCQZCYkZS9blg9NOvMzSi0SsHjGfeJfWNb6GiiK505VfNgfcFJPateQH30wk9iSf6X+Vq8ma/KM5lWhv382OM4QGQ/t9uzPDtMxT+6n/8uS6nrofYAwjT3DDorvuSmqy7Ar9ns9XgPWXpRA8jVjLNB1uFFxNBCzwdVfi9Jxyk0AsfHb5NE4lXkTpUFlyEcg774IMp3Rf+KD2VS1y59Qmi27q0DWVfQE/pj5mzMIZSuqbc4837t30Afx1I72727EFL1PGqNPAJPh2Zuj6T1ljzcngbU4XzP4eawxzLrt6Mjk5mRwi7P/1yptSEiWPv2j1Erw0XL6x+psczbiRWjzF3i2zLtz6Cjzc8iU6QUlHCXhqlam9OEz5mmwk/FayLuUNkwr6iNdnfw/XXDnY8DjwMowxSSjvD6kGnK08D6QiWWW7kscq8pPgSujSfYPVzWRdSVf0n/rS/bfSwFunLPq66ouk/uPOfBe46zbuymUoLLqsuCyEMQcf0vOyLFq8ZfnYHfBu+ruom8E61BIkiHyfrk3a4uPonGFGjAUuvou55muYMi4Z1Oab47JW58zK0H+QIuX1FG/9Ps5UvtoDeOEn84uF4a6ZBxjAUuub0/2XuztZYnIN+pH8w/xELB0jyFl37m095sx4oJgRo8+xhjkkuKbAhVvjv1gnGi3OQ/Qlf+QkLbIhaol0t/oHCPiUBtDlfmLlIUCqS/DsO6mpnY4Mfno7dw+8dLN6xvzV+4aF544AVBUq9LP4btTNeFhlBN16cMqlN2heDy5LVO7TCGQlF7qIpIcmf1fBMjw6mpkzvi5lyKtpDlyKMbkqN6j26zfpvXvXeZ2W2y9xx+u0QzizRYPRBi70Gw/WduN0GSxkRbHz7owlDf+vfpuSSkIF5KODs8/oGsAoCUZbrLOCkN/69SggmZdDznLctwKyNHt2M/ihCY/O47z0ae28mbEp0UQxJrj48cjbQuECoa2gmeVqleGuRSYhNbzvsaNyrvx0GKQWGPV0FoEYaXaTXKdbrsF9j4ubFQcPa9xhp90y39ht2O6TcH9VNzUa/G8bYFHZv5iAp3kwoxke7KSjb3+xdmav32HA/TD+5dx8PKeAoF7UsRkFjUYoBcb2rXyb/Xf0VZG3Icw5jeSq9vXB8yZKPjt9wTJJuKHXrb/ML3D+YpGwSwPDCeLTNohjzaXSQ91y6ayK02TAcf8ia/t62R26dPcnk0868f5NghHnksWiK4DGBGxWuFTY4Ng7pNjOtNx95RK1zKrXUtz5hXvdEFIWAAnuQ9JseLdMsjTrMxW8HKOmML2t3TlMRpBdQG0Zzt+xoJdN610Ofe8vL0dA7YCgxrN9gCwqOikfdQZv0SDxXPcwNVuGMwIqlH7jVSDT7AUnZisFN8fDh+/bnfyvL+ktsM+W8nh6sjhhkgDkcBR0Z36QJ92noW6A7hF/yPSOc1i6l6dKJlz6UVlRFuv7cfZvyapjg5NR9apjjxaiF/+VjwPDJTpTPxiyCOzXHA/vMxPHVJqRzQsdYEv6nZJu8R5DlUKO+Wp7PIUR5U9iMh+sqd/JsfSkIuAdzHwdwlrM74kfM3pYfDI2f75mEAK+2zldpIyBzcVGNKyoOVQQhBClW/L5eM9NvY68z3Nh7vynkVnQZdbZZJriA3A/qOchVe85VfUz2eRKLP260ipgGLrC/KScHOXbplGLRvyBaB3qYRH2eQQmLzQDK0QXO/qD35/DMRNxaD7LOgk9Dt6FfyAg3PH+Q/nsD0CIkZENZ+/Ryoik3o5DbbkILyvyTX/PaVCNbODtc+fuWXf117nVVJ5WJVLBp7pVF9gdrv7TroJb5ST/oNFSXdrYcN9MnXFWrst11/n5FUoM6D2vHqv03vw/OLQNoaufqSvPA2ZTgG9CNFoWMXSpsiOTqcRDOSHoK5da9vCxPGI/y5xZK47PCJOObJ7Cc8RjHmkCKtp9tGKb2g8sX1Xb1PY1S2A/2c8qDA/q1V5Ivt93Lg0JAiy+k9XrGaxGzGIEQNEGpZY+5n5tRRyFGXl74dZ037Lf7uKdX/8Zd0T2w2wR1J2sjU0/ybo3YmWHyq5MRzI/F4IpelK8ds2T6T1XZx7p8nK/b2jcwkCuR1yUiWnztr1m8c2z/ecHs06m8HgcZEruKfoYUvAz3+d+fHJ/l7PvAE2RUXpOeWYx/18pLoXRkJHG1alpbvu0+fcNk3fyjSstxUfKX4aXy6axltHeVSOx5b/K5d+4CtUom2WIb6pXXZvvHFwJaghX52LcLDQXj9ihoR+RUOkySGQPofDMSrf8FIBduiNgCBFkifjokjcqOtXBnKhcWfl8mFeyT8J1wovqn8zPCjccHcbExGGkbnzbIm+uJt67sjmkiGsUKtnwWxPqDW09icu6uNwsLRo+UQdoKdG3eGFO3RUMwX5kYnygF+P+ngdf4dMlOsE67NYaKxPY5qiVZMHV30jKXl8T+Ffm+8VIkm7Rk+PCYBykQiBSdPNV1S2rxxhEtRSv5g8N/mF3p5KH675d6vpQcbL3q75R1IF/BKBAp+fZx4pcB2gDXvrkAGNd44+hiXc72iZz0Wu3C+aiu/77mjA9e+UHoeQAgpjF5wQIIn/sj9Nooc0fWbYLfY6uJoZefHq6tM71JsQBFpQ4QA0DklUyjpVqO2b/Nj/aFv2z98wO9yRwpA0NjUgsdlfWMcsFqKpVmW/Yp/HGdtEuykmCIWtPA7FCKSc+VVEm4at95U/5eKF7uJH7ZuNcizSRg4L0GXFlb35NoZqinmWXOntcEIOPNoNEzp1SF+yslWry79Yvz200Ur1YikzEnLdrSMVYFghg83Oa0j74YLW+Qpxc2DwQGk0hdsfhHDrUA788MdbL5NmAgOuffh5gdpDb9IJDfIuK27HK+Upj0YzG6XhEdvd+kLQlv3zkME7u+zFIcwCsP+PXPBjMly2vAH/JKCCGubsgg/QFqR09AM3qmE3t1Vo5V4SvvPOqpUv1WlMZUisy81dCxXVL1a7knZ2dW4w+wddqi5uoI0wTzBsomPMAHLwa1dwXs8oEQFo5JI0uf8jtcAYdxVx4bC+GJjnVjHy6u0yGqzdx16Z6ae75Ou5k32hEPcP8JgnLAjlJMNF7qseu5i8SzZy6mg9K0ugc/HwX9XaDJIubZ3+SHEvr4kMRhEPKyHu+Gk+FHRDx+iV0CNMNgEc+/w4eVENiUZES1tx8rQsPDpfbhWPg4rf2Z8ychwPd/01DDpdvLNlfzS1m6kM+V/NPYR0YeiEdAHQkGGzG+m4cCN++1r1uHNi/5v21/I4VGLkgbudnl5VELhvma8UwW3rg+Hkga5THxF99sfcxxCqMp+7EFiZAq3q/iQOh07vw5p59DK6zybA/rhPeHX+E20RNseMfCtV2RFDjVFCpr//08/R/2FVAQhpeOA4j5ueEkw2zvWb7gFAn972J2MGr75Bn3PCHrHqajAyakoHGc7jBzWRESh02RK5thv2rzKpJqHJtfOy9leU6FnhFwnO/fbwvNswtvCMtdwlZiLa/t93evjq8uFyIOeMzWLmQKFFxDi030DcQHvvoKfXyyq75B+rQR619Defoj28l5/7uAGg14OFfHxbr1Cc3cCarkdNAd2Z8xBCTcEjbafk+PuhhWCl3D724WJvahOA98v19CYd1s8/j0XJInDQLTsTZmdO42uP41GYxRcbtgzmj8j7t4RRq5UlmcbP/qSXHS3vuVKHq4/7lISyCKO5/zVrSmQVbMP79ABMRJHDsPe65EMa1wpMa5YHxIcE3V/+Jr7u0dPdPiNPVufYcixV/ks+sODzaSKrseRU8cXVEKo8SLsezHfjOdW5nhmi5FrGiPfVGo1rXYL4bMHWRP7kMcaTTC4y0NksrkzGmqw0sN4sFb2wCfpQipljBrfE/jA43Fv+qCYd7XCJSrpEv0zzxHiEHEoxKsmjosAveVVy9rkB4rL8WXdHHE2E5tBefGsRqSxI8m/jtzTZydekxTJuimcN6hC/Jj6vhzyRRxd2kbzqsHkhvDBYhC2PryXRX0NG5BiZl58Tqyyf/0xoEdcjFDcwf3y5eDmtwhk8r84T+JV/fW5AaF9N9UU3VUBoWejlLA7XCXSWD7nSMh0z5fdLZXozOTTM28s0Wwdo2cDDByVSpcPabSUAL9Fh9uTrQyRytKkC88GCzVRlyDq8L2dX2+auQgNzY82JkrsljyjH/nHd1Y4yzmVklkOM3DV6ihHLYzD4t08DXR03G/z1LyYk0TPm15m3ibwgceWVHyzRsdoP+17HXLpwh69ucHp3a3rbODAf9BoL+bXSXGwmWlaV/j2uxulyyVdGO6mPmV9DWF1Nr0gHl4g/mi0K4r6ceq+qlSYyX/Z0gkyaCoTdMhyemjMtHaTegA520OMd/eVre7eyBxn+dkDHtUjllQuRf9adSJB00lve1TrMCqQC9xSMOA6NJwXAdPrNJYDvqOmfr8hgk6dZXi0Kd4/Wn1eT4l9o+/G2JWVq4VAn1DuGZYfQGY7jxYA758H2aXazxyv19HOCMFoJe7Xrr+Pwn+hJE3K4q8v0bQpj9qs5yA4JZcTwq6fV4n59SUFxHS2+1d54ooCMHBg0v7wcfUQYLgmuiyC4pADyAcrdQCerJxhKk2ANuE7CJ7SIS3DJBM2YV8drHD2AqX5TLbrzWiTu3pW3dp3jjemZgDDB0CR11PdvrarGLz2UamB5rfYbt65hDlNfOjcbDQ6s97DtUbk640v8wntSwFQbOO1ntMV8uPvj2uz5U8KqToLsUU3NgxTY5FnBVN4g5KMuvTR6s9iuxlMOSK/vZ++YR/b7lGtlGZ/O6y8FiuOj4TNZTo6PJm9+QpKCxobJ+SBXIOpU/b13eTcX5dU1lp9sfNelIp8ffZ237N2ZKKBvHYetRWoPz0evsousjVjiWSC9j3u/RBBCGHsTHn216/nnAkadZC7VWfLr2U/Pf/s0Dx+yUSFrTNrezph5jzNVEQ7yahYZfImee8U/KWq3A3TgIhJc7T5N7Rna5GG86UFlcwJbQzv/Yvcipr9pJymrDjVpoCc45xPCn0udSXgqFrbF2lNVvP0NgcBpA8dC2oZFdXlXQT+sCiH6ihS6bJHY4xIfKcKvDVC714IAtEnjVsq0X3eX0En78p4WUVhJ/bJcGLmx10tgPxmL7TENSRNRJhIb2z/QIQ1Ok+UqhiMihTj2wD0am8F/bYIRb54fzlOwH3fhFbXsC9OuH+bw2FXl0DqJFq/4q6wb/udRmJMKEm/cJ9Ab5hFum+JhPy5MYH9xS7Ww7DO3So/5XbuNYioj9uLQMWvy+va9RgZHyxseZ5jl4GaN1et5c3B+dUipKAggnm0mgzIxL50ekN9U+ryWe9AznnmIslVgaZ3PXb53egACVOciG+S6Ujvczhv++dotGDgBbnHF++m2NChANDgboWLeygujlIDZFu7jaZ7YPjLrlf3AqxQkpmC50VnF3RhSo+AWInvmeZd6aFmH/5Ps/Htig5dxUff3DHNcx/HoDDe+q8fUY7kueXDFH/NHSJ9TLE0uGGIfIUTMWMdPlOAtjSZ+wAzsF+0hOcqMEBkMoqSQJXtVruyOT2ibIjnhm8GdlQt2OWFRfhoegnaGP6yLQzr3jalB6Ian5jmwQmCAfvMzHWB1lsA2195vl4quwDrX3mOFLD670pENKigqtDQPtMtsDCfmiSFZ3p06N5cz5qfEtEUxPIFi5Zw9JtMeWD1JZ8akDrvyhRVKQGBDjTwD+2y2RrGSJGfwl+AYSIzY3UPDD5ZFPL8grugCVTdym49okdy+OW6zWsIVt0GLfpQtsySBnhQ/K/FJ/9fm4xrcBzeU47+P+xnhgwF4zf2/7NfQ3oSu952/NxSMGbtar9tcyrkITJG1X6SvhJ0LCT9n+j9ZZvPsZBn77WY4j/z6eZ/PNh+S/95TXv8H6Xc/xk8mocSu2LEyf6jjKP9n//jr5HEWVI9B4f/McP/hylUyf8P81bc9d//oID/ZhI0OxkD+i8gzf8cEFSLeq/rW9EX/soVw0lnFMjYp9XTaz68PNfhqDZZ7YswY0vH17PuAOMoaoDeXwgJvFxZ6ZA97sT4x6XRXbV1s8ayeIltUU/TpKwnxZBV8RY06CtzWXP04v5F039C8kvllO9deKSSZjd1/qOxtVme95ZOZPf6yJc7/wDAZs+X/afau/1bcx+yNBrOvN/mRwPdbxqZ4qdYv4Z50zqFAG6P30ppcGjGMIsb8Vbe5YhDGbyaomwrOcAyKVNF4slXXr5eXeI0obhxnxyePr9v6oXZXbBQpJTYuQ7BPjaiwgntgCbf3IIzqoWz/6afEKaIP+T7/lC2DroeJUzmeU4IvG6s3htHqPs9jpmKhvBCDHfVYAbGXas7o57zbDwe/x3eUwBVoyTK1BKDjNLxQVqhj2rtjyiGU/CS2NCxQd3KLRvX8R21vCzJ5sYD74gXN67dscuzX++TLmgCPg7NgBYH9mudFz97rVvcACyWkofVlA5zj/Vozo/bOtZC90dEToPpBJrdZk+d05cWppr1Zz0BxcRfY7FIm/uCRg4hdr3rbr+UA22mqCJbJopjCfjK5qV35cXx4uNvqF32Q5uF4LTZwlguPxN1wv5ef/L+UW4D2u//96htkhr6Rjs/CjEpLgeYwuVVA00vnusEaYj5Ni4WHyDFJxtvGyGwUZSMgEHpLygOT/RCtF2sa2tLlqAKpPgl2iAfuJVchQTvYnYqMvPJEotgd1/nyyFaSscL1sM1GIvX65H4Yh8f4//pANKfede2gQfan+6KF20QFqj/Y/V5zMb/fzAH7P/Xvyr4hw5920kz3h6gXXg5/P+djcl+Xl9zrI+DvPxHx6sdeV4LkZnLQKKCCEf/0NW5r76vfD17g81vUkqou41A2o8y8LF0waqXq50xWsLiqzYkwklTd4pdAgLSl8KUA8AeKIWV9ua/CIwhkMWXV6KfeU2bXP+p81BE+ZNdjwMeTv+QXLjADVnhjJsE9ooiw65aX71rV0NW9h78zClt5R8598WKKp991aEo+MMU/966td36ONgHAg60OTI4S3VFCDUCim0LvfvbVg0dEi5bjTrf/ydBjDf12zdrph2c3BtfjfUMLbQBmBHaWa673wbK+bVkzIWzvai90Z8NwU2iF1xco18aipmkFSUP5T4OPZJx877qvOf0IrE/VDwaVhSFWFdu49tVZ1cvjmKy5oK+MXaLJj8INmdrSIQbdLObHd09AZPk4qdhn6DYywJuHBF5xpPVDcrLylI39/C1TXV3lLS1RSmW2axlzJqqX8LdLcJTuo8yp7wVhyvKUm7mD5L6IXT3/hxiyJMLFxJNhKo/np2Haglz7lN8F91RXsDMuTfDlW7nbzQ3z9E/8fENKfvrECY4nLrfj74VQ164zlrBzIF/yY7NRIrFiK8lfOfNjplbHP/OlwkTGKGCDB13qDF8az38VkKms7JLyEmi3ghQYoFxx4kpU82Mf7Ly5lYpUzHxW8GlcQfgPa1OwBs58R9/Q6LjDhfDva8iF53OZx8hFRtRlH717mJVl7/hbU0NrJEm3H3vI/V7oyGVHdv2h+JmS0sgT5frJ5DdK+8tftvdK/fzTe3mVfv95vFr8yX8lO8CQmBK5AniUsexEpxVKBgPsvviuhYz5LDt9l4yJOai71nXMzNUgPrYtUAj9kK2w//2nTpvQjBTyE8jow6K/fXM5M8DLy7aMttxC6rwDYWjl59MyWwjD6u5+r2is3/W8PebLLbJsMcSZafaf/v4oHPKfj9jGQ/+tRG2LEISgqzDvAaNapQBG5WsiWX/OanVgrtDGvBge5CWjea9msrpf+cH4tcqrvBz1mvlVcmE6l2XWsTikx3GqOn2UeLzlOR8K/XPySN/9oPWH+RIr8liOa56GMs8dPdUbZ3Tve40f+G/Xy44J9Jfwjh6gfgbfOJ5EThYFSA+neGKN5SlO8ajPgVMbGuK+cP676xXsS6bm6UvzTw2g5Ubc8IuoPnGjihjkAax3uilkzIhTxhv0vjB3Ptutor9uGh0pSIGET2iBV3uviPSvVRnNuxrtuaOBYoHrsp664v+8uU788anZKuK/PBLzCHzt90mhRtOVvbVDir1MWkdGV2CvAZzWQeezqsdg8Fbxss/GUyQd0esiLNvtFd9mIqLC2tevaslhrJ+X2bV3gvcmPhUn1vZj+O0n1kJVZfaqbhgXGP6pCle6i7P+aJmr12xn1kZhWr/R8jD9738z6Ix+qSwvmqvDQKLco1PiOjNokP9OcVVhBndCqS3Ye2nzB1ex6admN2f2SVbVokxsEC1mB1HpsZu96Cop/Iw7YwItUwKLQb4GGZ7/lk8qk7lEG/TekbQNR0N29cgKtnBpZlHi6ZrIbXbU/tas/t0MXXpHc+G1czNu801SH3Oft3myCps9ovQUtyYedz0r8JzDtuVNhLTAh4ik3y+4RSIWaTY4n43mGLJaBB+ZCzW5ICei/rX7VTZl5vcZycQ8tBhbHpW/oKKnQTAdQTbR849zYeQdYMDD5len2k66s0WGlTO5RAYRVGZD7abv3ohCz2K/4wPrw6VrqAVrDCbgtg7NbhA2U9KIiPOPhHe+KkKiNObMaSxX2+/GZSvkUz/iO0ZRac04jq2Hy/fIQYzghkw6a8ykj3rO3igxdC3K9id9rkXerxPZWiZa7WRV5AUGkD/6RpruhgnmXerLJU99qM2Zw2gaQC5VbX3+TqcS4dU592Xa1M=
*/