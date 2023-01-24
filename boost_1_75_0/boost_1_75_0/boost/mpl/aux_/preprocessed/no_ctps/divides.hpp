
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
hv0R1mK+fOK4aiL4j9x1Cc53YD7yC8GsoHpQ8va5y8EjhPS5ByZ/HAAt1zYV8Yb4OD4t+0RdrFVf5PQ8vhOeusQDv8PfFnTLPTd53toOOq5djms3fZmt3wq6nOOIqwZcg1+GcWD7LuLdEB5LrsrWC2xVgRwQQN0elpIPcjEFvCz6AByNOp2NoMfjl8Rn2QdnOAW/62Evm0Cj4Msb1Bx3qMtBRpSv8/I+yeCtnX82mKr19irVjcyPY3SD6ASW7OBNV4GkXam4so2iXWNW8gfZ5boqI8jeVP6XQdZLZdDPhDWTdVRhbnerkoBBHnfZ+ZmoaYo5LrrGid7p3s/iJCavhGP6hVipSu9ObfP7Vv88Pi5iej7wFb4tmzqu3G3fy7kjvW7syBHHA701lXulfUiTKDx++1nZlqt8X5CFWJBlRVCuAn9QaOLB1jWBeIjdc1n1hGTBs1D8fGxpmsb5/TLRze8tevUj8ps/85MYLvQOTyEyfikwWUHoyunnwBEjyWW5ZwMeu6sXftNXJAtdwAq3/0+u4nVe/4OujtFUm3rzoXiK+wccsrK3n/C1xrZaroTmyAJn4Z92VOFHw+EAY4cgh58Anlh17PHw2CeKrOW0zmBA3wXL8nUN7JLf+T6oJcTF7OklEYPNpQ7iB1s+uDu/5FhjRzn7fL5+5BB6eAOqWks8rgLh+wJiYERQ9SeTxzw0I8xusM/0PmlS2hrs
*/