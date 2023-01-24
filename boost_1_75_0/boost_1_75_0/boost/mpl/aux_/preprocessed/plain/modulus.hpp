
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
JNp3fUcF5ts/SOtf+9L01akSoqo2A3MA+u5oNAc/iOJicDcs4mCkC28kamm2cwk9VLqwqVDFa0gp1KG6/Geet+45/T9okuBdSoRh7ijLagG9GBmeAOX3+E2nJKk+vyPQGmqUaLm+jX7wja1jd58g+3qcPU8jYCKV/9dhIB5ZHGnfQdDXOddQZfkKZbURmB/rLQVOGG3b7C4m1vf+1u9YAe9PI3S1+PYwJIaCB1vTZJZ6rWLRFePZv11hGG9h5Qw7S8wJIGtpRDjqtG/OhQR9ILhapQlVQg03tw7+EaV76j2HocNu5MYAGiWIiyET83B2IU3Ji/lw4Pb+JPUuhsfdG7hiKNgCfefufmpNbn/tvfLaq9k747VwXMpdliBlVdXEmWAGeQafzJMs9/3zyAwSq7YGgxuq0UE8tq5BasG5ztSWmL2to6Pt5tza3NzGwsIydWS6oUMWFe077o4MUN2U/vhUAuvD+N3ROGki7HyrSxDn1pcvaGvWIjXu6s5yYwMLTiHF8E3KpEXVXGGfn1u63XWTvq1sZbquRdgbEei0aVLjNGUVmh8i4r0YebAQXizau9wdQcoBOXKKTRc10aDGDr3/PT30u+7NAX3wW47bPNLZ+dwn5McR58/l5OLiB2lhH4KP0CCUA33UDR32s9+DkbBAUvFmnRlwj6hOy0wRYkwJiyo2Yj6b0EoyEWsGioyFkk+EweQStmSFYmtC
*/