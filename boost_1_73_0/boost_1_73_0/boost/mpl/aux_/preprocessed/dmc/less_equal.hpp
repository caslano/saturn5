
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
U8E3mIwfV3nxtJ6AQpjMrm6mMV2zCXz/eUbqT1Wok/1gw8hf0TTVF/jTAKJyROr1hSK1sNQDKjiztXbEsgvYzGvWTkvdZsyPLjgEh4M7Yo/eQPiflyP2m5RHd+9UPwFJU+Dj18Umf1otR+xOSuxo+YJfjNgoaD5USfmxND/9j/8AUEsDBAoAAAAIAC1nSlL7zz1TJgIAAJkDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzAwMVVUBQABtkgkYG1TXW+jMBB8t5T/sGoVcVeVGHqVqnIIqUqjtro2iQLXd9cshSuxOWxS9d/f2uTj5QQC1p6dnZ01qUVjpTCYsbRRlabXB3596r40GXssinXun/CwKNh68QISe9tUjRQWWcpP0JSP2eycnUOO/Q770DQlgXrs2i8ClMKKkZLHsxiuoghWv9g9ESVQDHgJ0S0s9Y424gji6+T6NiHIw0vBRroEnNTQ+IBX4gPZXCuLyobPqN5tncANYy9a001yxnIp35f3uuZt4+CjLukDglQo7NAjNZHnz5RxitOxWMZqaztzaKvVUrS1Ji2tMDa/W4ZmN+twS6kHfKrEFvf+OevAajimXYLLAzO8/UFpQbQWHBy2wsoazSXMl1BqNKC0HReJeSRMpd5u
*/