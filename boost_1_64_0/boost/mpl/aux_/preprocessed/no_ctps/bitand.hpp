
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

template<> struct bitand_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitand_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_

    : if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitand_2
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitand_2, (N1, N2))

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
mi3jxJaW7fTbxza/HVukkcxcj8zaFE07BY+fkdsHFJ0r9+RnSnw4S7G9yusgNDzHVV1ubkyw0eD+NF5KmSu6cqCD/dJO2qRrbrA3RDn+4DyxqU4Q7SYFhK1LFRgJbqoTfgirzxQYmsutUxa1/y2Tsrwg59Rn5ZzfcnKoLAF1Yaf9rrlPWh9xD7su4jqw0eA+Kd3/NxBr7SlynR2bFyg2z6ma5/FfGjs+VlRbvWXusPpp1NG1Hbm1ttElvgRNZRTnT82f4J47Z86JEeed8X3kvTvSLrcjE7kw+Tbp5d2DyjjX5PU/XsYVkkTpa3JcmRyr7St2Nomdx4qdU+Wa3HKKaqf/oDN1HKj9VK2PrL78Ybtf9Nwj1+bsU0N65laqV+cYjju96/Mo8Xlk2QMJW0T/ShkPp53m1+93nDkiXDVm1oPU1rl0oS+9UOtbJA60aK2rsG079BFfTr74j8pqA+OmYdRNBvaRxObV7FHaTMri3+/tvuhhv3208ZXsF1zTsJD93J6a0FpnSNhamPVS/rFS/tHSzll1/vLrOKE6rn//Pbbkv0Hy316OsW2lfuslfyMnl5nrjtpfc/pF+BZET1NAD0r8fo3KuV5z+QbPEy9KviPF9uGSr29Tvm5Phac2/DzRcR3p3bOrz76kJfOHzS7l6SPtkn266A06/EzOgwq2d12yfns41XxjaIeQT0Xynyd5V0v+daH8/d5DdSJXh3VF/iEfZf4O/GG7WOxfiBRp1+gzgvl3/b18sO5W79C27krYrzWkW9T6T9yOojkm+lpQv4d8XPI5QT4XQlV/hQzIJojucUhZJn/O1NWvuac7vHbo6d8g1+vQGovyuSKiLUp35A/bVvLOxp6wnHycAXs2jffnuSrmemo6PGeqbVFWWaSs+4pUeeVeqe19pl3nPjNF5z4zVb3PFH3r1bKq63ca3StK2ddI2adLW0xBKtjPd7a/7MEggFYHrIY5p8M+rraD2+A+6bBgP+gfSNhP+mFfpFKr93P8uitKHQFX/ZQjjzrCMWZ07mg5RbV/LKeF2ZGdiZ7S8P7ohuq1s1XsSBI7tke82rjP0A7t0I/eBrXspQPalr2a/RoNdZZV1niqaztT9uk6ZV+nY8c8LVZiaAfL9UZhQw15lRZXbjoG+FzEZ7UualP1+0GroQ30ciI/82Jog/B+YO75yGifg9R/ntJ6PrL95yONn2t0ObTvCzPuv/r9VSt2v/6jmXeNPTr+1+ifp+zK5yPzbBJPhIuQBv6Jh8G1nX+U5w5/hn3hLzAFboBZ8Dd4HvwdXgD/gI1wIwzM3ZWYIcyU/NW5u0/LOqrLYV/4DNwFPgv3hCuC66TaJO4n8cAGJJn/l0k+L0g+r0A7XAmz4KvwAPgaPBi+DifAN+Ax8E1YBd+Cp8N34LnwXXgNfA/eDFfBu+D78GX4AWyBH8Iv4Gq4Fn4Mv4OtsBc2fga3hp/DFLgGBp73lBifxP4aIp73nCfr250E+8EFcB94CnwNngrfgqfBb2Ed/BGOt0n8Du4p+W4JR0q+Q3vI856wN9wHJsJ94W5wGEyH+4udPpvE3yQuR35+39kaye9n9O4Af4cD4R9wMPwT7gf/gmPh3zAXbkG+/rgfnA97wgtgL3g53BI2wa3gYzAevgt7w0/g1vA3mAAvwpbt4B3QDu+HyfBxmAI/hjvCX2B/OAD7B8H9YRocBQfDyXAXOAXuDgPr/0oMC96ONESs/3uE9LeJcAScBEfBo+FkmAPz4TFSzinwXDgV3gJzoTyfK3EnbBU96vO5Z2rr58GzpJ7PhsF0jZJuoE668yTd+XAAvEBJ1yLpdtZJd7GkuwQOgvUwcJ6QOAw4Uec8cbPUxyKpj9s=
*/