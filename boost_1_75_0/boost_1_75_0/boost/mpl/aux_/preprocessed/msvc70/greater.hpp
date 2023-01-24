
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_impl<
              typename greater_tag<N1>::type
            , typename greater_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
BUhx9cc6u5a5uCqx7GVIpeMkQ04McZIdmQdXCTXNRofMmWFdVuqR2x1jw0Vfs3J3kYlALtxOt3RyYs861dhv8e7qLxqF6h1L2tq9/sbZIV8dhNXjf/Q5Yt9qI/llNDzxrXO4hl1PFtfG/iyXUjLXWQWUqyHbK0jEZ2U/07m8ih2/AKQXqQrhDSrIFmV6m6SbasNfWtV+DNTOje02GUc1GaVR+sDqa5oY6+a5hIh77nVUPXQoa8ow74HPv1SmVaU3Nf1Z4GBkd8qFHTkz0o7Gqke+/NqrQBInTLPs6Ea0byuh+hWrvpT5lbXfmSkSPBHOT+QCUF69KJlXmZGvWpAbGRLv6wMwfFGsgNYBadkWnUeq5CBazoFPH+yRbwmL+jA/8KMbKWFHIlzP30p9UlwYpezOjoCTIAgvfrMbZGpYXjTO2FBlGs9YP/YIF1zOt1CazTCMSp9kKsF9lmai2Dw+O7uIDN74mPN3Tra7X+T/jYp6UHyBTcEonhX1YkVoLwWenju1AwdQm+SsR6Y9zzG6VZX6csOorko2rSg5/yigLxfpE/pnQljkXrtx+LzjAkTgosJD3a9EAjulDBv+xK6Wc7qZPT73WGDUuKK3wo1mYXOi6VKYNTzRt/yrN3K86TWH+Za156/JbfH1wi1+3x2ea9KvpU3s159PF6holAMqeZdzf/I+cai+kbEPp1bmkcJURpynEsoCI0XEswg2
*/