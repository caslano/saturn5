
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
K7eP6Ac4+Mu4qI5wM30lZZ3lefaNpaksQ1Or1+0fHK2WFxBiFWZLnYTZk4kehsASDwGKo2LKw6AJ1iHZByW02kvpfFjasr9+FGlLf7MjXHYft/yH+u0OaEHSTHUUHMVFylDhyr9WPY0jv6csKrVCmfcBhWdBcpaqjDd9KPuaHLZRZHsqXLLEDRUmHFhSnERME+aiccg8xVA0057HsfZseDKAGrNHV67LqzqiUBroikgtLs8f1MjvqTMQpX3GmoU/JeOaStORr5dNtHYKV6JXdEziLIGr1lDIfhtGbzuYX3U9mRpYegg6/oeavKSV4aLy3KxjjcKxuoCCjVMuXXRfp1gFbhRrw4RO/ZrsG1fdTxEIn6mMAABBvr6rx1tQVHcwWIZodnfsQijYsXSHXLtKyTa4wOh3wanVDfpjIl3/yRmI/dyTDckTQH1ZMdIUl3OglJ58p7ZSxUQuZgFf4E2x6V9wjYS2wJx2Vc778q1hzFlcgQmoOVz+zpkr4dZhuFT+tZI4xT2nsdfsMLfXP/KmJY8JiZ7ZgMhYXaGfzdeQKKdtCzmNhQ4xQg0ARw==
*/