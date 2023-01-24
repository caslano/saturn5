
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
{
    typedef typename T::tag type;
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
YT8QVXB8uUE3MMJkIO7a9H77XiCorpx14g0A5ILAgOwg2J3/JeyOb+dzklu/X1Lv00iK6qv+4XJwuhVJvdTLnWGqKLkGFGKCR06i5RZStReCzmDiazSEnqdx89tD6RGwepdMgHLwevji51JW+7jXIMFCY6db0TJKmaWllH8FOAhbYwQ2VuzFMDgXeDe1ahkWMy/r2E+s2DtYcPMFYIIZ9iJf7UjHkfWqWlOXHIsWfh0VDS54OwRfmNcYVv1G9VIQLN1USeY3gQXX6AqaNrfqXXIFib325YquwsgXwKyveffGnLF1WTa3sB9talAYORlGN1GgvwxMeNeeBgZYhQ/sTQCk4+odbu/5wM/vb8sR7TvG1w0QH25Lu2OPHsOiatcD66Z3RMX+IqWtAWYiw9bloT4St3mg0QktTGi26yrX8x2fr3gcTGP7KdQUvZd9CrZppUn6fOcFykCGTVHBQqleJl5gZjubvSOBtN/SQ+ORBEo/j0lcHwcwZiEDgvPY6kJgSVs/fjFDmXvmc76i27DBeJOEWH3Bpn9BbubsBnNi7L8kNv8zcnOx/RO5da2dLF2drf+J3AFOJCN+MBu/wFNzhTTnVf8aqqwUpqQ9UvqoRpMD4Z9FzAqNKqXnoywtezUqjiSuGZvC6imnRz/1nOGf80fr55qvd436HdAHpc6a6b/xsGt8kp5DmbElKpbHodbO5HLtEk/miqvr8zu/
*/