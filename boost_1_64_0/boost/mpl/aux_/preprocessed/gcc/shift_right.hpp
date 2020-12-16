
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
fciz/aSFW+efaJm/LacsiDHGx9LBbINq6TBKOoxElhA300uHQOc2eObvWd6qphrfp/tBb1hmtEefvHILinOKSsICqv+Gy6sx1a4+xL2hSZsdlHsd+hRy7Qsjf9hRbaU0jLiFpXNsBaX5tqw8otSP76+NIZ18uyNpyubof5vONfU/U3njNJ4+RraNRpYRZkCKT3mLbcWFRSU5gczlMbXvEs+63KL8VqhvXWQI4VJ98mN+SEC2bdrmDym+fasCDa3upeayt9I4/pORJtJnOeHqrHTB0HkBzG0wl7VM6bdT+pGybcQU7/SpxCD6jZVda5XXAOXVH/m1UY8+edkLg1mP1KqPrFKF5MhmWcgKwtmt8nL0yeDv1+Z5UHosqi49n4OPG3kqnNkezVuE+axPW2LUra+OpcULgrdHQ/estcp/pPIfjlxC3LhU7/yLcwLZw+dYz9xczR2J8NDH8znbV3vrnaE6G4ZcatSZlT62ufnUG1YPst4WSS+L/mecF+Zle9pIOvWSjXqqzVb76rQgd17D+7F628icV5T2xBuvvJL1DAmb6pNXYVEAe4d65qV3MkdajMH2useubWn9DM30ybu0wCjpT2kPDbXHKE0q6yMdeiGriFvuowOzfkoD379qgWV79My7vJVXX5Dtq33yvjCnKIi1mlV2j72zRp2kddrUzrciZYSLmObIK7egJKeoICvP8bZyvJ7dHU3Pbp4xhgVthfz2KCwodr+7G+GL/Lx3HoaJjf37HK3nMfmf92Q9X8n/+sHW8638+S6Dnz9lvZ6xv/WPg/ex/sExL+x3d96dfGl4kx/Gzh32+4IPh1EzLzvCH1odd1u/HQVHL/lq42O/2dj1PuacOHys9pr8y7+u6/n869efFdv3o+FP+l+f2Hqemv/5aDWOeVsvdHrx88EnvXR6ixl3/Lb1ZV8U06CaGNfvmvls+EmXf3d//NY34xPuOGe0Px908D7ir8LIO0y/XfWbdidi3Hd2qFEnab7JONgOjoexcAIcCifCM+FkaIMp8BI4BVbCVPg7OBVug9PgdjgDfgRnwq/gefAwTIdd0eF82BvOgiPgr2AKzICz4AVwNrTBuTATzoNZ7vlP+s2q37I7veY//V7lug92h/fDnrBK5XoQngUfgkvhVrgSPgKvgH8wzduqUj5pysc8b6tS+WyAveBGOBLeDVPgJpgK71F65WH63QifVnrE517BYZr/01f10U/1cZr0HqD6OF31MQReBYfC1XAYvBcOh1VwpOrlDPiEaf4Y6eg3I+1Bepjnxb2m+USvS4/dpniJx4j3luLtUby3TXbMVLxRFnZs3cgZ72TYAkbAlrAN7AHbwpEwErradZXS62/Rri+UHS+Cp8LlsB9cIfuV898EuBJOh5fBWXAVnAuvhAvh1fAaiJTfAK+Ft8IKuAH+Fm6BN8jOa+BL8Eb4CrwJ/gjXwtboeCvsBG+Dp8B16ge3u+er6bcWjEF2esxXg7LTENlpKIyAw2A0HC772JFUpbNC6ZjXF8yVffLUL/LVfgvgZFio9muH58HFMAsWwXmwFC6DS+BFcKl5PUfle7LytZxvqfznucut30GwnUW5o1Xu9ip3DGwNO8BI2FHlpq/pNw5UOs1gstL5q/Kvgy3gl9LjK7XXv8EO8DDsD7+WfumIXenmKN3mcLLSZb1v0kFn6XMCbAebwYGwOUyELeAMeCLMgi2h225Kv5OF3fZJ73el33vufqXfEHCkRb/qIbudAjvAU2Fn2BP2hQlwOOxlsp9d6Z1hYb8usldXGA27wW4wHvaB3eFgeAocZuQHla7e48nLIt0DKt8nqpeDyudT1ctnKvfnaq+H3O1G7+xgvEW76avy94M=
*/