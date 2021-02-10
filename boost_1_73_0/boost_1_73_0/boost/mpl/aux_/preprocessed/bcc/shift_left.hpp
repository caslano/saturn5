
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
ERXe1lV2u6LGR73TLEXPhoZtW6E4X/fHitJpHkRvm4/J6cWO843gUDlQylN8hCyDXgmUyJ6qY2+z4nBxsczXJLvVVCaE0+3qJINvVAYXlzPG6C/qwmDmg8F0rw1mmd5N7TXpOEY49s0uMUQWeDOTuzYhz/HiO/AdKQzDdqNu0iqO39sUvh6YuNaNbEmRDsgYugcN6HBcrEmy4Y0djh0zHLaeUIt2sskzR2IMcRoZ2ZY/KjpH2mpdOawzXFnr89lMKJNtkx2nDb/jDpF0Vu5NWn7keMc1cs04PPLSfCNvrEE8WidTZ9XrqGG4NMvHrbuN1mmUh7tkkB73YN/AAs8wG7llp42tT+cNpMkG1COeLwxrPemoCyzeCh2eJzFFBasVwVGiuiS1LBOVdFoXlo422gzIdmRMhgKVbkxxNRn3qGTEL0vNFpHIz7TpFDjlTtcUlZWjZps1E3Koz5zRTJj6AZAiIWqvPYx8pDGD7R3D7qJpsKyxVkisrTvdQhkQA1s26gekcYxZAgey+ZhwR5xTRuk8kXsjYyv6a6msdyXZLAZrxtEf5RWYHVaGAFeItMRxba3yHA54ra/KgTlc+MM5YrszL5t2Bxi3zfoL01H47e6RHva5CUWws83Q8+XCEWJNErJ+2euC/rR023mv
*/