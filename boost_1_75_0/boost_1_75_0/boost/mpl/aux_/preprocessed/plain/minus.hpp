
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
stbZAmz2o6nbgWO8Nnorimg3wOLklL25v1H4L4a9pz/pCoPVk89McLWiHGTu8VUm7nhJ7yv+f2/Uf6/UrlscW66SgsKaed3AuGbjIuNx94jfr6LdXdXfQN7EKm9iHChWlDF0HLQFgCsYSG4hI5bKrA6b2wuDzNR+QUSjcTRECfFmXBhfUKF+P3ZQP0ZFkEUjM3w/2O5Jb2T0nRT7toG5VjTi2gI7830Wjo2j3ECrEKL7GQIwJgBlfU5GZAZyf7venPVZX95uPzESQoBunZBEEuYDINnq57l/gtaV28lITEOiJC+M0eeiiy+hnQfdDi7PpHE0OyJNKi9CDizNDz0QzUMbd6Gd1pOVc53Fa4fDg85CHewXUOlPnwvoh9HsCh5E0yS6weJayfqDy6dyvVC4MP/zw8OEYVDO/lo45jpC+8cbpNCNnx8huL6IQ/kn+i2yrYle/cAW5MVEIfKF3TakUhTeRAPMzMAWJCf0BeQ/fy/TLL2CgfpBq4G3va9NaGvfLlUO2g80YLdStqIs4Zy+OkfdeHuKeq7a6LYtPLvyoHGKco5OpeLQ5U2FuoF9qu7x/eIG6cmKFEEiTMklNeG/6z11iv1kLjpL9CV4e/vlkn2WFGdQSpyVU4DwbYxukHOpVcThpPMw9VZYt4z3eIzOLoyym3erRarT0sS7/6SuUmbLe5yjAH5gM2ZOpvXZDGeD8jIz4av1Et4b0oRL
*/