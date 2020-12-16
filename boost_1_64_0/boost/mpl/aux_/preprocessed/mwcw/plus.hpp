
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
nUKLprvymEPwxkm1p+yCmQQtsVlxmjGNqtclTGT/K7ffyt+m8vJUZ0tOVr1nq94t1a5HIFWtkcXuehdNTxs85qxhaeeePuqcoWn5M/KCx4gn+NT929aWzw4fe3tlr7XstUL+zk709Tb2qNuMrPDtmXHgOZmzvTER6wLmggs8x/6J+/ift0782wO57Xf+a2npkA+6PMHAw6YW1vGyz87rdNvkB5tfffiWRrF/v399oDn8QLEAgWIZAsVEhD+3bz/3Hv4cvn0MSMPljjvQ+S3sY1ICxSAEiiUJEMMSMIYicAzLPe7Yipy5jVq2nPXVh+nNrtu5bcCGHwPHqnjn1hfVzK0v8BsLHaix0BTYRnOT6FEX3cd0f0PP/e6dNd45cI2RwXjNcZ+oOe5U2AFOgAnwcs113wg7wwc01/2c5rq3w2PgR5rr/xQmw19hT9iokeZk4YmwAzwJpsCT4VB4ChwJB8j/BIfuR7Cl5rT1/iDFDXo/p/sIdQrwuVVNHHWO8w3gWMI8jfUZ43wb5/mO9W239hFzzC/3SsZyEM/Y3+or7fKBIRwPOP7H36KvYswI8YwFZvPv2cjcMZQF7cYFy66qGRvccZVvzrBm86kTkoJkIquQcsR/vLCKY+ZYYdzVtccLmYhlzJC6wS2IOXa4w/r8NbXHEGM4tgr2gf5jieOv8R1P3N7nEPeY4nyO++cd28Kx8XAH3IfMPo2yr63Ox9IHesYX519bM8a4in9vRDxjjbuuxecFNWOO3RfUjDtmL7Abe/Qbd+QzGxbAgZQFPeOPTa6zGYO0jsGJMJFjTriT+lVybBn/jrfGEf3GIzdcF1ouM8dCzicyETHHJhmYd49ProOeMcotC6vHKfctDD/PWeKi4GOVqYvs850l/9JU45X4vKhmzHId/96FRC+uHr/sDu3GMEctDm0cczh2PGOZrsXV45nL4AD2N8CJsBLuRTxjm/HX0w9hCrQb45zPcSdcAfdxrBzuQKwxzyY3+I57xrO/Dg6B1vhnNtzO/mI4if0yaI6FVt7gOx4at4TzTh0WIKuRzb9ExjAjW2SLbA27NUGmHtDn//yMgsws6/F/v579rdx+Z/DsvfOHxjy7WZnx06bk5PdKL8rIyfHk/hvO35P3eP/u/lsvPuVQ7r+LjPcD7NTYwd/1bP89HI2+83Jz/ROeD8otyJhe/byZEMKzPWseeMbU86bWN0z1i9/P136V39qaSu1n+q1vyNH+Du1naN+zNjMXMdfmTPF7xk93+K1/0vN2NtJC9sZQ96piv7pby4vCyFGQ2i289R/mmIbp3x75l6jxgOOQs5OsoFo//8Jccyz/fGw5VbGligG+AY7DVrm/LWMNanJQW4e2fOIqdKluek6ue/+U+e79rPzM+rdVHWtl1FcwUjBVfcHoW+oLlo1Mv7bP19jRdu0XUQBQf/SeH41NqX+6GyTTuxZvj/FOCLOfzlQ5H2mfkSqftUh71fbxOs/tkHOSrECmmrVIZw0eM2RoGPk7jjTaN5MG9q6n0bEiHTP9yFYegDj5Eav+luzvRz1yXug8+9jbLHuxsheDnIu9VH97Yea88JTfT2v2m6v8ZsgEynfals8AXgjlB7uG9sres7qXPq17abFhL997Lw19zXGge6n3GkEy6YRA/dDb523vn/uM+6Xp//Kmte+HE/G/7FrD/4N0P5wh/03/miinQWedzwT1z5QFhn8NdD/cKVv7dC73wnHYcvrZ0v0w5HMZblvUdb/b43du9xprA821ca4C3qHjN64/Xuv4O6g945HzqGPVQncdMwryZ9b8eAijPROM79o9cGIDvmfk/22d3G/tPSDb3GOzk49pe/FRn9074NCZb84YOmg=
*/