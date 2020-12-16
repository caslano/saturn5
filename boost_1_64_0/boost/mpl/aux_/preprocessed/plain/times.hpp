
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
VWvxg4kfaSzMcvSpoicpl+WEfs3386iPuz/DMI7+dcexLeGzjS+YlerRx7lSxi75nJfV8Hm3MgZU2yul0j+K7d/BHHRH3t9o+4SCXHugY1G1vVOQc05to+2aObYd+TwEaxq6ne8kNnWvDtQn35ZnkTmXPXAIxTnnNJ9jLWKy5jyZ57Sa9l+BYWHY/rvTbv1xr9Z7kcTbz5R6z4SzsLvqwcZ6n2zLYXlJ8/uMejvPQbXeOY5aK/MOP6GOaMlU51CWiM2Ouq2kXmXYejPfHVylzH+TfAV51ll2qK3fDqlfpJxvEchs7LM91Fg/FueW5Fubd15HuNbqSfz9O+Ucuw2Z42jHBj35mXOt6XML/G9DxzifO7gxfrOjffKUOW/SnzKmPcf8X6QwCzZKG/3p+lxgLbXLd3+4vsssKpoPZe4b++Qb7R9qNNfMaF9Ro/1DjeZ2Ge3vaTQnLvB9aQPdpzXQOXT6+7Ea7asb+P6z+nMAjfaTNd43lnl9fD9h17a44bf9Wrj4udY3551w2mMtt6+r+LjluYHzGqnT+LjHSgzVWHgkjIO94Dg4FMbDRJgAT4aJMAuOh665CxVS/ptSvjp3Ybr40NNgF3gqDIOnwWh4OoyFM2AKnAnPhGfAxTAd3gIz4DqYCV+CWfA1JVZsikWeE+AoseNgmCh2nCj1nAwPgVPgoTAFdoJTYR94ktg1TY3NK+W2k3IlBq1XTOm2cKIcZ7PIfR3MleMOhTlyXIQyt6A3HALD4VAYAaPEjmEwDg6H0+AIeAocCXPgKDhbiYFda5H7vNz/65AQ/q4WvetF7wbpj2rpjyfgYPgkHAmfkn6pgRPg09L/z8KZcCM8Gz4Hr4PPwxvgC/AOWAsfgC/CV+BL8HP4MjwYm16BfeCrcBh8DY6Er8Ox8A2pT9sD5N4vzwTUx7n3wu9Sn9lSnzPhAJgHh8F8GAML4KmwEGZAG1wEz4KXwyKxvwRugPPgM7AUboLnwA/hAvgpLIO/wXNhK2w5D/aEC2F/uEjqcT48HV4As+CFsAwuhtfCi+A98GL4PCyHL8FL4UfwMrgTXg6/g1dIe9AQ8kzAuSDtcTR/71LmHB4Gr4Id4HLYA14D+8Jr4UB4HRwOr4fHwxtlXK2As+DNsADeAu3wVngNrJTz8Tb4MLwDrocr4bPwTmm3u2E9XAV3wfvg73A1PBqb75d2ewCGwwfhUFgl42ENTIYPwzS4Fs6EjzbG3pZnB4lLrom9/Zacl2/DI+A70h4fyflV1zjnSZ4NsF3KUec89ZT2PAb2h33hJNgP2mA4vA0eCzNa+beftcypkbk0DfNmohDXntN5mj2mtftL70LKpujuHS37RvP/iGMOTCWsQrYg6p7PUTAVce3pvBRZidQgynwVde9m2auZ45BSJFT2Y5a9l117Lcsey9iEaPdTXgkXw43I2liI1CF6+yJvOoc5TXApsgJZjVQjW5B6pP24hjkfkUjoON97GEdOd+5dLPsWq3sUq/sTN87nSEa89yE23m94FxIj8zHUORgzEBui7gu8DtmKlMm+v7uROupqWcA8CSQayUDKkOuRKmQTsmOBOW/BTGYyk5nMZCYzmclMZjKTmcxkJtK+jP/v9P+n2/Kt9jktMwegPNjijuWQcoD33qRV/FNxl8RyyMx2biQdiE/6xq7ePlzK8PDh8tnDDxrXid9SOUgbM2iL2DdQ7AtH7u+K3d72pecW+BfHRmunxJrQ2uBuoxzxpw8RGyKRVcewLnCV0wbCIaWXOF2mAehGl+h2+0zFH+rpN5WtVj3bpJX3nq23UZfKO5322PAxpzsbRiZuNKdNGuZLyBgRP3+M6BuF3OroAy99TN4IUFdOsczdkM8=
*/