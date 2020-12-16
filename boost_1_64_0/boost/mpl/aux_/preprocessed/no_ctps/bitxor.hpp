
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
RY/AzHlHZZnb/4z6G8r7AiaJf28bmfPUG1lKftnHBeaLH3XEkUeN9U+7mzJ1tIm5q8F5TqeRhydi7m+T6EoRXcnIYO25tDa63J5i19wKszrDnjnvIXEL0bEvspsdv7Wqg3lbJWU1tZ5qTUHH+Yeee+jbtkxXiL5RMm9xBPKQNm9NXx+rPmo6O57PHJyvqOgMtVlKT1nDXMqoffkIOhPLVZ01UbdZUFeyzE2Lo220HjXHU1sa+Yzawp769ZwVbkPUbdlOXWNQ23db3KLNjwzTObdSbV0z863b6FTnR4rOPqIzUeZfNwZ0Bo5mdKotbFavf86frBNxiX9u2W61Xw254/b7+yx+4tA3P/jOts5oLprRepHRz9XTX+fRaA6i0Vw9o/U6jebwGc01jH4OX7RzDaOdq6c/19Bo/dPo32GhPwfReE7nCoe/Pnv+1uPuC3bLvGPogkOemLjqI6M5hUbre0Y/19BozmggdiXXC4g65rAav6O9d8S7DXIkXYpOuoMk3QiYDA9WYl5eSTdM0qkxr/6SbgBMgKlwKBwE94Vpks9wpFnyGSX5xMEMyWcXibXsDjPgEDgCpofSyzkX9tVJP1bsGCd2HAGT4Hg1hlxuXI69JH2GpB8q5ciScuyjviNC8knWqcdEyScJ2mEfJV2jpOujk66fpEuGiXAHuLinuXdLNM8iDoPordcqa7WyRityRmh91jbvSF3Y/ntSQ2uy5pwZiM04jw5/b6oP/XrvTlXXYR2O5CEJ+cQSkBxkvrxX9Xoo6622eb/qGnnHapy2bircFUp8hzVWjd+3uiT8nauyvqr+u1crsGUkJA4k66gavYu1zdqpsm5q+LtZzyM/4kWyXqq6Vuqmd2tk5LYfQ5qUi37yWZhNGqium7pEWTs17QLs4Xd1vdTm7F7+eNM6vifmRHwn/P2uudDoHa/qmql52ndQ3vUatm5qA58TCuKVdVP13//aciF5sV8eYvQu2IV8p6yZavhu2DS+Ww9HwjwkuCZqM+Juux5qKA62kf9TZrSNhw3ju1UwH8rap8TGNq19uoH/11+MHmxvRF5E1iH22cQbkXykbrYVi7I2a4tl+7fG/65Kt+YA6NT4v7+M/22B8T9ZigOALegD8On4AN5SfAA5Oj6AR8mzubSND2D0UWM6Hte05wNYauADaCnV9wGY1an6AHY18AH4SvV9ACjoMP/2xqUNBj6A7DJjHwA6O+UDSNXxATyOzvownTVRt1mkD+DTXW2BXiVOALXc9QY+gKZwG6Juy/bqOk7fB8ABa+QDQKWJsXh7PoAKAx9A2nHGPgCzei0fgOUDiNYHsMHfT1Z6ty7dedCGHcc2eDLiXj21ePP7AJpLY/MBtJTG5gPwlXaNDyC7rHM+gPqyzvkAmsq6xgdgOy42H0Dacd3jA1jMGGTFbMsHYPkALB9Ad/kAVnN8bUR2dfA+UcSL1COPIq0OywdgbdYW7RaHVHb/+N9bro2pNA9AF7wHQPMBbCzQrt3ecs+J/tFayBGgjfff6WsLjY/PkjF4gYxXZyDLSN/siRyDB/Myv+6RjJ/C1hrC5xBaC+jt/uHrIF2NXpZh8a9R7UO/Zhrfha0rvHGLtmO+J7XxdbGhvQ6q2dT6rGHryUesaejt0dYv8hR6ncZ6a8zEffX8I+NE5zoDX4K32NCXEFJudi0/1aeg1vMyGc+7RHeBjOebdXUrek2sqdjWv9AzyUdZF6PzMD6/q+mAfaSfnJzsbw+yZl+xWdb8d8j3obXN1xYr/Uapy/o4/fJkl+j7J9R2NLNOtF6ZminPgrhAmaaXxF6m0hKlTOo6uL3a+n2aM5HwMsXcJyOPX//xGdFPFvbS98G0lhj4YEI=
*/