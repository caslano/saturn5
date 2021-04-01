
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
n9p3wJ03ws6HV4mpyzhFzhsTiwnB/jJq3MOoBgPhBXmuat3A3qFw+4W2vIX6VOkj09N09BCkKgPx6BHhek/GA/2UzsIZXVWKYwUh7kaPbHxarAYjPEBfJlG4D9Qd4/IhQk7XwDyf3q7G1/i9dC8l1rMKXSEyrxI4F82PmDu6ajmuDC811IqRycBsfh3vB9xwGGF5ewSQJxWJr5VJzCWpoXkd8HhyT7z/aChOAfaJmSc9r89oR9uu16XnTICdaVBsgIvA6yIioJ4kjogjG7VkwwP1HEVN3iaMp+Zzj+GaKo3u6Yh4utzJv0Tp5DuHYmWd+/gqPBj2V104dMTlAUChnRHTGP41vCg/qlIEQxNvUuphcQ4S/61WpjXsUx6wjEfZJxBGWhVxNDzYPtmVg5ki+kUXtp6bmOsSB4DRub5HWshpZvEcbs1rfjUk8AgnsYR8Ng/BEsgpVYyMwryXxdVwpZyaVZWfkG6NFF+Wg4XDfB+/nyBeOsYa2PbbYc0yyVsodNYXUtSnq13OtvCMvMLkhg15hH3yzzHW0xbAxVZJWLbNaVNRL8zOo9b0MA==
*/