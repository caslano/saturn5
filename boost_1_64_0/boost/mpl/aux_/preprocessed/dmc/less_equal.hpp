
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
mfuLu6TpGa71k5lzydOzq4/k3kmOECWsFj8pYJKahMiaX7obXGkztQfP4Hk4MteTNEeIX57gm1RdrCIh5OA1HBXRO/LsVHgvNZuAHPzBzgbanig20zN9lRbBw9AbNomNWFCjburHNapO5HAXUOc/Cc5AWvOF+VvgUwW/sNTLiYRYh0thwKKZ5NbPdHNJsPxWkqviAdIe98TpGJw58G4y3Ci9HugHKLxjPOvKfe3Qsc8gIZno6GsA9YsXXRQUj59Th9zuYfkGQzNSNnJZJtKZpfaArAd9cshMu986XJBsqy8KxLagL2H89oSig20Stfkm/1hUqArbrC71bfj6f+OF1jfPYTGLSWM/hVx6gL1ZtLW021DMWwgCl7+2znfSYA9foy9d9sXDLwa58UbV1UsA0Gy1r/NJrvwoPHh5yiQ2inrtz+g+AV7ROBnIF5S8Wz2/fDB7utRfJeG218x2MF4RpkJYmPmIeqoGaDMDtE1egc47zCQcEde1QRBqVqb1PUgmk8Q8ZlamyhigICVsVAns+daZiUeyyaz2QL1pqHuGGbCnnxKqOUxaC3M1fw==
*/