
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct plus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct plus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct plus2
    : aux::msvc_eti_base< typename apply_wrap2<
          plus_impl<
              typename plus_tag<N1>::type
            , typename plus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, plus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
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

/* plus.hpp
uxPcPbi7s2hwSXB3d3cWl+Du7rq47bJbm7bTmXb60Kf7dt//+e495xnXkYH4bVOecDNXHOsDv8285ejYMEMsQV3YBb/mpI02+V2Djwf6+ih3Y6boMjVcd9BVB2OJ4smHOFZp9R5ZVHn1vklxOnDqaMZIiRHegWbFrtf/l26cGEppJLhA8aDxxao0ZV59wJtpPQG7ngBSfyZ6J259N7VaxZ7aLHqni2d9EU57mstWONsMdxXdUG22S05rlL834n5rVXRcuS9RBDUxGYF9TKwdbB0uJ+3IbYkHbFd9ZnT7oLITN0zDLdHdF0r1ZmP+ZxrsbFo5IM9G2ql4aC9BhxOv62kqwIdZyLMowsHwZdDzpfscmR48+ey/ViqzVS4ocYt5afLL09noszflE+kYoF2OHrx3lt7li/4nb3hL4phv63p6V+n6+MHbxjuF38LDB/5bhQpbp9nfbw3BdIOKEcwUOQY3yZS55u2nxTYsrWGFm/VBbeP9YJQxX0AAWyvgk3IodQ0mxyx5XDvUB0jLPVrrpH9LM744u1j5FPbdP2C7tOHFvK/nm75nJDpGZ0rVCPjjer+BFAvFumOHrqkUUMFQrMylJhcHa5f5T/gM5rkOBHpPqUkcw53VkHDdAPi3cTClzcubuP3V28Bna9SnbvEp31xgyk3A89OgKulbdmLpi8HR/LSwOyw90ajb7QrKM3VbSxFg7gLF0ZmyXz9x
*/