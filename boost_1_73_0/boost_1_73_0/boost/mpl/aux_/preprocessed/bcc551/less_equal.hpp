
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
AxJUjSO+A3xvyp3gbAzOfKd9Z05qnvIGV2PwBnZp3Ete7biAvCRxlV46vtM5D8JRbzp3A2SFBUtMP8lhisxeqCo7fN91VoOhj2zvtdrLLx2wMosgb2D3nWc1GP/XawJLYNhfPkya10yJVesFa2DvUDcyLw7Bz4ngAvbTM0uVPLF7xIX3jeDGmbvHX6eDyhemCnYjsY7kr5NA5QtJBbuRwNfrr5NU7+LG9emOBL4sIxcEsfvrVG+QC+GN4kabJuGvE0LlC1UFu5E4wPp1Eqh8IalgN5I4O/w6CVS+kFSwu3hlTpUv/4OYnQHXuF3gd8u8SKHbMvByWb/X5l1gdtl/EJJddg3GLrsjqSqHX2eptC80J+CNJ/TTNE5/nemsf+G6gO/jGsYv11jBx7Mk8GGSgy5QJAObo7Aqy6DL/CJE5bOggV01LvrVeyp/TUEA3jz3rvv1Ur+91GsEWYMF0k/EP0FXdVWdxTnmHfBaYL3HVHXRx4XTR4rnuWAfTaYB8yiAE/bi/DX34Ksa+uxd11nTLHJYyWRvJp3b1+ZbxyUDmxE8JKM6rHrhG95tYPfCdxAYpY/j/r+W6TqgCvKd5jt4GgfgRd1HIH3TO3VdLcXuTb22rku4esGnfuhHZn4/uzyFFcIpNjCgb413UpJk
*/