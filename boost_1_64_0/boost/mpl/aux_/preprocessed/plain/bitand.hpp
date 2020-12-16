
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
n9gZf8auSJ0s3bAjBmMQ9sA52BMXYW/MwD64FvvieuyPN+JA3IUh+DAOwpdwML6JQ7ACL8b3cRgexlD8FodjDYbhLzgKz2f9jUY/HIPybFFpW9jaHJVOzxZtL9+LjtgKO2FH7IwhGISh2BtHYx+ciX1xPg7ABAzBK3AQbsTBeDsOwTK04h4chl9hKP6Aw/FXHCHf+5HYHkfjYByDwzAcw3EsTsEInI563qq0OaQtUmaatyrtB2xRz+dqGvg59fc7tq7ncyH1fG6/mr/aOOdxPM819ZzH8ZzHaZzzOIc4P3OKCHiJ++cQkUQKUURsJfYSh4hTRMDLnM952XM+xzN4Bs/gGTyDZzhbw+9w/p802MY5/9/VcP1/oLRtB0l//EBimXK+4XnJodWyeBv2LDr1HKHk7brK2eWNOmTKefulRA6fDXnBuTw9qX1xAY+9kfMdPg0oe5xetlvP1Kl9PwGvFkp7+jRxMe8Xq3WUc69O198b87h3yDKOkWUcSeRSp321lpHFi0+MS0xKjs9Ly41LTk1r0HNGXKxj7ZkeyoIlZ8Xnpkje8DtS5wjGG3Pti+V8fwc599cGlzM//32u60jdGnj+r2kLnxe1Z5OY1tUP1brKfC8wnOPPTsrVzovmM51aASUJ23AuMMtbKSB+cRqp5myDHIvDc2YYvGs/z6yAeWW96Lx8DX3WWNMWB140nAuW+rFc1Fd/1ovx+v9I+U5NJMIGsG5fMpTNt8md5zB11fc1/blPTaXfRMppS6xQltFQjvHpiu7k4cu+rW2rKlffH2+H74/js7Ka1j4XW0jdSmvVLSPenXx8qZfDvlzl4tmDV1HWtlpl8bQarqGK42EzZ7IujNt4veQZPCf719PEKsosM5bJntWQ77Oyb81/Wdu3tHsgTKckvcaO3xvbWtP3Q/YPbT8cbb8PhZwPL5I6FhKrlfWiltVEeaSP/WFl7I6Z6epTeBr4HT+33CkvROors3D5LDrn77j+rFTbdBwIs7X8By0HRv83Rsv+L8/tkT8Gf5Ll20QUs3zh5bJ8FKxsA9vCJWRmJDf8b8jVzMf2N1dflgfaMU6Zi3zOX7tXTYJyxxLt/jNZ9jovjs9JGmplvH5sTkzKSchOzcrVn0slz/+RSrWTfbgNsdbK/16RZdEugomzHw7dfiZvvvGaKyk3SLoHImQdjiHWWRlfR7ms0gbs0/rxm2kctluwPEfvtJR5ijio3ITApEze1pur1JJ9cuqr6j6ZnpQep3+PZBupu4J8ZzpoeQL6eNnvtPwUL2/lWcFLtJwjvl+yP8iyOf2tOuX0t0r7myb7Q256lsM6KD6/9vFxPdPve1XyIOQCKi1bpQH5HsY8i+rza+eRlDD/Cqf5k7FS73zt+8+1VskjMSxHbrPa+RzX87kap3LIWGnA/upY3lKr4/OzRhmfn+WU+1Pjoh6lyu+Z15zqQUbLmdTBnlvSVXJajGWn+dUuexPThTiVrWa1uFE267vOvJY953BOUM3DOH3oJZ9bV64unfTx9/Gp87tXck5FHT9xakKHw7En+vlmBVauuvjUC2Z5MOb5Jdf4KOPfWfHu67+evOFEwcbObR8vmX+u+iwPxteMmxaY1+v6kufbhV3vW/nLN+Z5LQ96K+M7vFhYcrpb7HPr8i95dO2zjxwwywsxy79xPy/EJL/HNN/lSXX8/XfdM36Nt9cv4xKGPZDxxbD4xsv7eVMdX10SdHv/8ozTq4/vePrqHZ0fUnMFGJ9Vkb72ZE3P19/dFBHY73DoC2Z5NuZ5Qld7KeO3z37Vu/nanx7uuvuDrr3uvGS0WZ6Qef7NPWo+zc1Pjfrz4e0rPtt227FMy9eDrGb5QO7nG6nP7bA=
*/