
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
MAzH3wX5DuJKGRRuLht9KW620mXsYHDZJW3p3txY6YUldrCdtvn2VZz0bnueMdiWpZ/0ly0D+VApTynIxtSWlz80vlinfQrfyxykOJ6lmF3gBAtyz+TWvtEE0lHfjnzto7HqdAq7LP/5gMXmd4YX5+dY2a5TRqOxAQejyflgrWbgXyFSLBzG37QNmbDgq3g48FOoQ38ITQGlUR3FatGRHzrSOPStVRofh8ApsW5awp7vGMMunQ3Ujhwn5kCUS3mRfCnE6Y9tUW7yy1NG5ttdKT59vsB1ia19EjM5Gm5wzWUcYmVMMyGvVv94rlII+8Yjz7AnPJtG5VR/tgy2qoAv9MERPllj1FI+APf99QvnmMhTg947wR26I9fUI2oVFKo6kIvs6TVxrzw+Ehlc+b0NK5DP0ZcBvbPBVrZN4bbIdqiMNWNnB59Afl0UyOq/0qvq+pY+siy23n9LIMuLuwTKhzzDTQLxSVkU78rtbt79ut2UCZd3xMtZwX8Lf8dIcdAgjj/2DVBLAwQKAAAACAAtZ0pS3Ymgi7YBAAAzAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIzNlVUBQABtkgkYKVT0WrbMBR9F/gfLimF7SFVyMgegmZa2pQZBvFit6N7U6Xr
*/