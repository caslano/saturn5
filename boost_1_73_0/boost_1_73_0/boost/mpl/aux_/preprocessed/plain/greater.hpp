
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
gyztfq9MlTLOyTeUR9du+rs2ceb8cNz+czChNfAjjF/zp/UCopmFEOPlKi9essU4z5fZal3EusneH0Vrd6LWLc6md5PwFYA7mM85qWvjkaRjbD9OZERCNHif/CEmKSvoGSDGxWrrwPsG4sMQP8JihENSXYZv6HR96fCg6oAOQoMdAxrlYYtoIPGNDQmTpw5LEuicdaWtSG46I8Vfs6Qkd05Hm5X2attG57cd9YOIuP2Xb1BLAwQKAAAACAAtZ0pSADbV/psBAABBAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDYzOFVUBQABtkgkYI1TTU/DMAy951dYRb0gZQEhITSFXhgITox1wHHKWpdFSz9I0sH+PXG7UgmGxKWpHfv5+dmRHp3PlMOESV0VdTi2uP+obe4Slt4t56ypnefvbe2RqSzDxhdKG6acR6vdlkkxxkvRQ7ATdgIp2h1a7nSOTFpszD4E5MqrhM3astwDVYZCG4SitmCxUiV2zoDTx0lxyOsAb4zGyh8As84IIa4rkzBX+CYkDKZsLGYbzLYJa9AaiNPFzexhIYxeUwlBn8vzs0ljoNzm2kI8f50JU7/1NxdXk+AMeCMMSCLYiwKjKAPxUxgkgV4m3ukEUvRpILO6LFWV
*/