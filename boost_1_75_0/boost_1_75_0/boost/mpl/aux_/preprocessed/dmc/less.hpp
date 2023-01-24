
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
TYsY/GHt9iqA05h4V9GUPtiKhvhCsBaLIrpg+ClW3Qc9dM9l4YdAzTyG7pDvdi9qrBTfnlpiSvXeM90uewqJvJ3VbnWxEKLaoE/7p66CmDd3nBWD4Wc+k2DtZAM2heohH8JbsCj4UyASFEGscAlCrBBAsTAM0jN3QNmkfL+R8GYFaxzJpIeAbvS3lL11fThEcHORgT4ntuXMrq8e12jTvlbdTWjXOUpAgeeHPHq+Qbcfgn7LQiruXIwaWJCWWFDsDw0cHQ9d4xxysqboMsGZNxRVk8RhZmBDbZeDlDm+1mYspT+p2h5nLsWxDyLQQ5hrhuuycfqq9+uKwwu949BfyIfoTntR0hY8cGtLzk02pVY+VqM7eL+1n73asdnaOJvxiIbGGbPwFhJu3GC9cUSLILUmzSMI1aUq2BpWOx6upODV8+1rk7fq3f4F4YY+d9jgr7+Y6hH44lk9CxCf92BYT+CKmlAlGILdfgquCjXAph2Q6Mfp1cNk1cNvNODGGfMtH+BUDy61Y/AdOG5GifqjCdWjxpm5qLWHprngfOOXWFO51Hq9e/G/fsqxR7acqouwCmL+PG5rvByGknqbkTNK5/IpwgWPTd3y3DfzwRnGY5LvMpyB1qFlxj7EIuIAZmEaYeG79s75Ba2QvVE6jk8Ki6tY7kCTN2tTEPlXts2c25aaw6GjQ7+Cd98m1J7WFVUVh4zK/NfUxdUpawT0
*/