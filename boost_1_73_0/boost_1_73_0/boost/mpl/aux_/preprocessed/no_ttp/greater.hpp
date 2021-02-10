
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
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
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
MTo483YdfgX7u62rlLLdn8NfUEsDBAoAAAAIAC1nSlKKHNvYiAIAAGcEAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTkyVVQFAAG2SCRgXVRhT9swEP1uqf/hVDQNpo1QND6ATLSqDVoloFkbhpDQKpNcqEdiR7YDq9Qfv7NT2m750vhy99753btyh9blwmLMDtgBXGkDbikt+DC9IVg0r2jA4G/MnQ2hJJ1lkOu6Fqr4TEW5LhCkgko+nZ0PoBYvaKG1CLqEvDXVom4rJxdO1qhbd3hEJVT5jlxoylbaATGKp0raJRTCCUJViiilVsfUGpeq1DHjL7h606awMbvKUpZOZxmbZ9MZCxQsdGawJPKC3U7Hw2w4mt7efj0dMB7tSnnUoVEj89DEFysLZNxgU63os+f3WZvfrtG8LuL/MGdJev3QyXF2cgJvSJdRHx0J8bJRSek3wtkD4NGGhLhHlUTlNtx5OGzZYla6ZltKYad1FbNOYop3R+BK1Bi0gKAAeEWCutQfaAVtU2lRUGLUZQLfDC4QXETRh+/TeTZJLz4Qhi+OGuGW0dn5KfhINrlJTqHSz1EHRHEi30LwUlYIHvmy/09SP2Y3eu+BkozlizcNBZMRkq/3orzfnlT5iUaWq84D
*/