
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
aG6cuNf3N6TvN6QIgxXmJsI8uoeNTNB7fSMsMMljnFGho0RQ4g7gUpJ9Ec+gxFgwlw6XhEo6Lah+OS0WoKoFlYBGSUHmToAJfY5yIefJQvgIpurSkWERQejY9VQmlybrC89FccsRsaBY+Qjuwg/GTclthPeQ9Gqle770kx3go6xkdKOeHOuPvC1n3ndMhLwDoP2D3aQAEiY9lgVoco3EtTat6WbOrugl6nUeku2lKRLFUB5frCS6QzeA+xdj12LVuiUVMww7tJcazDWCCUZXQV5uhEeh6UCdteeflBGSEETJ5ZIY/nR976ovmFQ4L+lSPEck7s3glgWfHjssnBvm41D20vPWJGGMO6BMpyzDaW+Gh7ieA5eNCpVjnkYP4jirar8M2vGzKhhbKK7I51rJRBsxoo+yWwDT9jXucLPqPsDxgoxXZPdQSvB31a6QCSCCiRDapLxpwxgN81m70f8EnhZuE3eT+2HN3hA/Q7Th2VjDUFHfanmJT6hAwnaLTccwJdQYyMzeiLeok3LhaIFvh5MNeYVRbD/tZPvmXhuPLgJNn2YvF1/eKXPBhQ==
*/