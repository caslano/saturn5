
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
TOzBwLkhzTtvYFbuK86Nsrg148idCcefwPQynPP86OkEewKL7ivEfBEMfzfi9vHrJdlEUuXPm09UXL/I3jfZWrfs/tH3B49D3NGswqFYObjVXPDoJVqWmeXDeKeCdWVhc4fQ+zc46EZYH3LPqkJyO7CeQ+ruOj2B1tZ+1suQLcjSaBEn9eSqp+gATb6m9VZO3wr9dywf4wk+QsltRYK3L8AeWz36DUiL0s+Wzm1djVWMmAm4ipZTNDmqIOsnhXC6ejnZoXqy5P1EC2cxl/v1Sr0SboMQSdncQ8Z5tnp1RxhWzq4ZPDjJ/3atJeiPyM2kflNZdcv8PEtjKBaskSDY2E00I9bNN53514ngeevExYWorWVcCKJaUiKLl6CpXCaTnOR8l0BxbxL4cd+Yi1GXrdyCc0BvsinINQ2QuUy16NCXNYNgNRLrXyRwGQJMud9bl4QMgRcHw1AIP5imF+SSr7a8OzTDnnyPnklPx8LPWrGvZuk8U/bC1U6q+W5sEYXNx/Gk+0cV2lprmlHz6CJApLalCh7TdHfzmXazRZJOJ8mxKHnMo3CTwbG/D7du/QO9JVvN0m+Rps+lIVm7hjgKD+wtnx+CPu7Wm8m2j8rKCKQZP6DU+OetJuYYdqXWJI+lXZj8sZOfS+wja77/BAfkIunCGnLTHDbXl7JGRXEPTk88uZ5MEgWjoLtlFNTmKZGng21tetTAM2UmHobb
*/