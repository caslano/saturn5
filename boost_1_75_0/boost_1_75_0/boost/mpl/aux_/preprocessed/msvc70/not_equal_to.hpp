
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
    : tag< T,na >
{
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
woEvkHAENr6Co/ethuCH4AfXUXhTMUh2hxXfMCN29U320/dxBzkiAVD1kA1k/OxxloMc3+1iGCDXIq8Ga1YJCUb27HHu+dzq3PLd+jgheoVWZkxuqhss8pjngkufDFgKomv2dPtvEB0R2yq4+D/eIAGE6xKqGO2wns66xKDkPrrV/NjzsH3l7ytNtvWGjlE/Pvn/BJDcsA3ALHjw7K8PZtO1mvmncPjjtAAOmaFtgbetTm3rhEuDgj0WTdZf9/3/qppws4CVXeMzJv/FB4hZpMs9ME9iyPOVDcUzgvyvjzur/+gRNDWtn8o8kpHRra/rdl0VC9ud6ltMfbn0KxBqZzd7Nnlfih0zVuhR2TZz9fHLEgXsfJukTL32oA/BjZak0b8eWYa1c9vDRnMt9lSja6Uem7sGH9ArnBq5VsdYaJXB1GWH/gQqqrD/S0lXzQ+/Noch1lz7Qisl8qUiR/RRBcPL380QK0Zw73LdQb7V1FhefryTktrjBdYolKJQlNVXuXuQKPa0ppApz9It7OagCZ9dopbZbuTmbe46vibPnjiPuNCquwlR9hpUXeHqGYLZ4/S6pWu543eObPt9HrafH4Z9UKrKhgM9sFiTv819XhOxnTpF/yu6SK2w2a9UhaHm63hPuaaRi3fBH6bzT1ZOZnwSdne1ASuqu2e6N/q7Z47u3G0cvq8Xqxx2t0sdvDLskE+lBDH31qkVgrf1
*/