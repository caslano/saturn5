
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
xsyWjCR39d/vWnGTsLexJ+lK51zOOboSAX1Q0mPKRG0qS8svHH5bp33K7sucCX6qBT9A2AUU6F7RzX2tkQmHXTPQtY+HqtUp223yb09QZD83sFotQCqF3kOwEPa1h6puEGgl9ABtr/ag0dSoJ9pNnh9oGXhZ6/U/0otyu/sfehS9WICybSuNBmMD9Eaj88FaTSmc+RR8Mk+Z3DY1mjBlomJxDCVlVeiO1JSBMLLFGDE49H2L0HeNlRqe+zDpOdPtsLUBo3Ki8gMXxKQwNl9zfvl1W5RZvr6krvl2V/Llp88wL6GxL3ykUnkV3gLMb2FOWo5sERMZm36Z/YWdpaykCQEtgyTKeDOafndHrh/R1dUQASCrgI5CRhjHCvbSwzOigZnf2zBj4jViiSY6Z4NVtknZQ7HZgTTWDK3tfcLym6IA8nONb7LtGrwimXT64y5hm7x4TFj5RNORJSy+E8mk3fjgcff9ISsT0ndqTwrhw3L1Ee4ladcwBn5Iej3OCBPonHXKavK1XBH1rBb8XbDgp3/yB1BLAwQKAAAACAAtZ0pSoqxCHPwBAAAgAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIzN1VUBQABtkgkYE1TXWvjMBB8F/Q/LC2FFJK4dnoX
*/