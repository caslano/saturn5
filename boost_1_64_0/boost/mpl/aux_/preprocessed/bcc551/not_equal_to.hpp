
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
+zM3xqWOWKtVvtM92qX3MdSJmr/L+lCdn7cBZS22TjJwzvQ2Cpp6bSWrvTmpWTs3N5KUjvgbpdbw2VSyqYMuQJqgOJyVSmlxhsqgJSkLKufvNqzdCq02RsMtm8QJ075PdhaGKFXfN59V0b8xy1e9nYJ2xYpt9Jydc4XII7JtP7AQkuKWAgODnsn5RDMJ0RFwIkeu1YV2Djci2As7O1BSZi/tTdGaRFhWOl/IF/MQ/5v8YziUQZBbU5D1DULKAPS+jpc4T7suMVZFYmE8fxMgD12NAW6hqyTfzfMXUYz9i8VTCFhgjjEvlljGQN+kBqyB4wyl5Q+kZV+meAN9lw2CDcpvb6fZVFE+9KYHL/9eECGOOQu+lrEo1FAYrxeQXKLXQ4g2UHh9azKm1YuE8EXBV7Ja/C9ssqVjh0Vu+esulUXupR1Jx3vncv9X5rnHYKBAUKWrSIYSee2thIaLZuzpc2SPlv1al+9eQZZdTEYT1nMzkhsYPsB9pQJO0OzSzstzg0ReFpJJf9bJ5rLr0wiJrSrcwfl0qvMgHDF2nNFMzGPaI0Jx71Zh7OSWLg==
*/