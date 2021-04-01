
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct not_equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          not_equal_to_impl<
              typename not_equal_to_tag<N1>::type
            , typename not_equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
9tWbZ0DmkSlCWz8E3ufDJvQ6wvM9vTc9H9jhPXR6P9H4teD2opzfsEadKESxJQzqrvD1jmyM6pgT1QUd0L9nyI8L9+TafewEEaJtahcRXRrotIvLwDxhPora4Sbms6yqxiV7lO/NVUov3a2Qo5kSSZFh9+CghZtlraZzjNaCVvllCszurshXCjcTDFHeeREQxuQcHQnCS96Qrvpe1NvbEpnEG+Vk8BP69Kazn8Zcyu1y8n75GZJbIerAmp/kuEkqwrD7F/nA15Ng9jdsf5UGn2GLce9aB0NX0HX1qhkwSJehxTXfWrQzBc2lRWsXKLT88XTWAH2zCQfvBBe5Di+EAxl2VrD95CPR9yUWRjSvym9G79xD9mmlwQWjWIvEgwy3VFXYX5/9smwC7pB9HR0Py4QD6cKGEGsxg+6H4r1XST3nnwBDkjO0tn4fNgBSBjT0CsuyP+8gT5nCiailuLlaijv08nUuxO8Xpph1cswV6DJD+YnPvpO2Be0dglNgNNrjNXSovbhdeOxVqu4H/hq2beU3or3NTGoXQOM/Sp2WdOzBdSlecQE/WFU0sg==
*/