
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct minus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : aux::msvc_eti_base< typename apply_wrap2<
          minus_impl<
              typename minus_tag<N1>::type
            , typename minus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* minus.hpp
cXsIt4DnLCDbjCzF+QPbY2Nrt2vvN6A4X7BWjfUiPIS4OHwngunvVHJRNX+fOAynDPsQzb7T45y4NTv8NV2PTOnbl0Fy6N+u6zi6DmVx2yfpQSUJeg9vC0Ie3RflQSgIFX1BfxHY6B+8RfZCIomgniN/w+SWt9yzbo6p69N03nTBnBl8cEIwCMnYR+tGg7+r61d/QfHDMYgIjIAH3fQHDsILP8AwdsINf8cBUG8GHUtbEDYAZpb1gR0TQ2/hvYtv4c+sCSFrowJ/NbmGo/K+1ckSvlBG+k997SC5SbxwFqkdtXcJdNWqPXTuiC9IguY1uQBcg6N2raWyyuE6zy98bzLaEZdvpkop+Ta5i1D1jcBctlSFB2nkDqoKYkPI9R9PAwt2sFl+o2yHvnbVVmm1JhfdxZqMnijeHqZaKHzI/bJJOdpbv1p+HQF34i/ta2hT82lUw1UCtUu03vWIijSjqVcs+X9uCjS/plKXwfj0z7+/lvz5M2peBDIXHtHMiV0tWIJj4XnXeRfcybMeEv7qeIWHPvK+wSNC3zz9Bd/Ou9gzFILfAsUPxQKcm+75RV9yEuGRN8A34MnjLj6t8OEbN3m+ScrRamZv3I5N3dmk/JvLpTBYaBqRmx5u8BGeVz8JL8u2zy+Y3ReWfoQT3rd5E4w5It4ZYpAF1qZTD/ilKrk0sSWSIrHOvgfbCgKe4BnwQQw4KAWtbcr4VWau
*/