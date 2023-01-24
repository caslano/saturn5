
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
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
RcWrn92InVZtMARPkT6c8qMS5xDF6xWQ7InYEeF66JX9hway6afREK0HoFHMlVHX+mOHS7OtO11XWuAPDVglvyrJjMjRtWS2gMqRrtJFKUleacy2pAxYlpxVBcxlTzIvdyR0JDQblKQ65G00Hv9pfPM7CKwS/6FBFkHTqD3PAlX3NVrohLH5Snc+dK01kO/6k7UHELOsJsNeBYSAhqgkHWhgEXmIwrWJNreGPxquh2EsMzoGbtUVfmGEa1xBskEmZrncHJlkCKUt01ndI4pvSCqEYWNXFDIO9PlEN2p4IEjNtDQoDzAjBKWD5l6W/EBSNPT6dVOoLcKyE858fEO6sWnToKswblgtDACjQcA7heFWS0XYOuWymypbbiRFgZHduMamP0hUVpwPMiXz1bw1QG4gt+VGTxM1G/TtqOaYUHntxj9B+5ydoKDq3JESJttDH6p4B7bBXaugQJmcKwbSu58m7nQXo2yrc7cvxT1lL5QlDkuFb1qXY0tONOk9Ay3Or9ojB6eb8QJqYtavBHNohm8VPufgl9ZT5DiIgiaDd4urKCG5Y/j6q3/SVaU6j3/lm6FQ7/LUsUY7EjmnICh1mC8I6FPgcBruh/bvTnkDD2lmOLNEs1015kySgWGdGQpdizQMRzMMYiHUO6SNIz2iwYIx6vGVnt2xcOUO/QgZri7D3Vt/0YzUbzQN/rBXaW6hWxPF5KTRlHspnXwP
*/