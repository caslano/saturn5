
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
6MXS/LRUlCJvgiPgocCXZ1WH3JX8OYiHVhrh+SRgZfQ2bAdyW41r1vvjuHBBv8gYHGGWLuPs2e9flvEfL54vY1q+v7lalBc3cxpyO6b0DyqBra7Q6vsW+9Hwm96Z40DhDMOMIIwl1KOfFSMraKW5pYPPKIzXMyhraft875H+a6GEOYynRt75k0/gqpIOsJLOx9D3Coy0m9F3yfRY4SNxFvQoMXr6W/sTUEsDBAoAAAAIAC1nSlKxh3ebkAEAAEIDAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzZVVAUAAbZIJGC9k99Lw0AMx98D/R+ishdBbyoKlqMwpLrBcGOrvt+uqS3b7sbdqfS/N/2xTRAffLEPbdIm+X6SXGUgH7TylICsTGH5sab607rcJzDOsnl7w6c0A12+mzXlmDllfEHuIjXa5pV5g8fRZPqySEGKY64UXbkzOMMluQ+O91VOIB3tNjV/z1VQnYS4urzC6+EQCxaosdWpT6DLirFQa6qCGF7e9+ZK5ZwyhB8gMfaM8GCNIR0qa2LcWmsBriNQEMFkOk2fRtMIVn+7Im6oI27BdUl6/Y/0qpfvdaXop9iO92FTkQn9eHXrcIhvARIoQ9hxwt5FadSWksNa8bMKJTIU/r5f
*/