
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      int N, typename F
    >
struct apply_wrap_impl0;

template<
      typename F
    >
struct apply_wrap_impl0<
          0
        , F
       
        >
{
    typedef typename F::template apply<
         
/// since the defaults are "lost", we have to pass *something* even for nullary
/// metafunction classes
        na
        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          1
        , F
       
        >
{
    typedef typename F::template apply<
         
        na
        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          2
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          3
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          4
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          5
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap0
    : apply_wrap_impl0<
          ::boost::mpl::aux::arity< F,0 >::value
        , F
       
        >::type
{
};

template<
      int N, typename F, typename T1
    >
struct apply_wrap_impl1;

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          1
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          2
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          3
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          4
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          5
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap1
    : apply_wrap_impl1<
          ::boost::mpl::aux::arity< F,1 >::value
        , F
        , T1
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2
    >
struct apply_wrap_impl2;

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          2
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          3
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          4
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          5
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
    : apply_wrap_impl2<
          ::boost::mpl::aux::arity< F,2 >::value
        , F
        , T1, T2
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3;

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          3
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          4
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          5
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
    : apply_wrap_impl3<
          ::boost::mpl::aux::arity< F,3 >::value
        , F
        , T1, T2, T3
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          4
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          5
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
    : apply_wrap_impl4<
          ::boost::mpl::aux::arity< F,4 >::value
        , F
        , T1, T2, T3, T4
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5<
          5
        , F
        , T1, T2, T3, T4, T5
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4, T5

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
    : apply_wrap_impl5<
          ::boost::mpl::aux::arity< F,5 >::value
        , F
        , T1, T2, T3, T4, T5
        >::type
{
};

}}


/* apply_wrap.hpp
53/QmoR/x3qEEo6pw8RKYg0xYLOfIZqYQLRs1seK9aAHPehBD3rQgx70oAc96EEP/57gS1x8ucb/lTGNRhj778DYmUXpDypUxp/yLDlms3qBqc483wNPqM9bMpjpn8ZflTEV9W+zI+gjtL8mKYOBbZLLU9PzoeLz1L8phWSefypjlTyvjLEkqs8vTskzkofknWx/Th2pUfPvLX9LU/+WQ4PwNxJTt1IfctUwOhl7SLoZ6nbqkgJrA9lXFTCvQdLKdreNPVvaUrY1O+Vrykly8UJNSQjD5LUWx9de9IXdpA6F6utS0tKSlBszp2aaM2hRnh8k6RY5peu4pes01zqkySi8Mc+iTXOD6zRlS8c0o+Q1m+u1jbzMqV4dpAxb1O25BXZ6JkMTdfu9WPO87AL1NcpAYJW13GazKWWZUbMPdzjlLa+uy1az7c765XTe3H5c7rbml7fSlGov356656R4dcdliVPa6laadG3tX6puZzQtyWRug7y1DZr2P+CUjuOWjvXqLGke1KaZm5bLe8++bw65TE+2clG+w9q00lbS2pmp2vIddZ2ebOlYPluax7RpmlPSlA8AbZrPu05TtnRd5zJtmqkp5kzN8VjuIj3ZSpuYfV9XqNuvys5cXHcsVtqfq/8ZdNwpfWUrbcLK/Klm7Qz2e07Uypj+ahmXXkm8IYKxrF863OchxWIsZFz64vett80t+YKN5IPWPjatfA6bjCuUp9X5MTUMElaRfz+276rkhx3knhkLI+yvz1u5zDqfxsy2J4hhbNdTttfeB58a2q8ROtKef901QZV7bw+R16VEON57o1i6ZJvKPA9frCaNg47tIDNNLj7Po4Omzqn5ublSF56nfPJ8dkqeRZ5Xy9bsfvKSttPeiyNNMvKn7i2xKRp5veFX2rKp+1s+uq3lK/NgP/Uk5pgtedr5PqmknWe0WOQryX7cxdq/Q5nexQa2eU47aLtkEivk8dsP1O2Xw5r9Qn0c6vS81CmI6KOmY23v4occ6mT9Mk9S8rz4XBL1PjYy3yKymfUPrSX9lrKm76A1fbdfTAYP5qyo96WRfHY65yP1qJB8Gv4C9CwvqRMDz67rVCN5ufli9LpO2c1d1ylgb4P5eFUn27yYMsmru+QVInWKlrwcv7Q8S3uU7Rho4boeyS7Ttpbe07aylf+45HGnpL9Vyr9W8nD4MejBvZ2U91M0aT5PHMbjN9V05F5CHnzOKZ8jJ+U1KRGO87dG+Ltuj5hSF2W1NodXbbFD0u8h6YdKWyRL+k4/hDxK27Yvz7ope7HrtK2l93Bf2vJIbOnmM0PycPWl7enxYnsPP9/SzedFA3l4876y1SW8lZvPCsnHzY8kj/KYaNvfrdx8TuxrMI9L2jdn3dQnWvJy86PUozxs9Ulr7bo+8Q3ncUn1KWvtuj5mycvND06P8rDVZ0iAm/dMw3lcUn12Brh570hern/ke5aHrT6+bdy8dxrMw7vP9bG2Y1vyWir5pBMzInj/OOe1xGix/Uqh8VKyPZi7afvtZSGmZPMqzf3jlpCHpONQ9wBeqIT+Up6+tu+Z/VIe9yfwHt/r8LzT77Wpkvfatq7b/ZgHeV/KZ9dJya+55NdU6lol+bk4mff4N45t/8a2c12nGrd5eFcX23fuAcmnk+TTUeoS8LDkU++E37P0bfUIDHRdj2i36Xv3fpDjjws8u94n8ZKPm84nr66XESd51bqpU7JneXn5+RVgrR91UYJF8jMTMyN43inPujOSlFyL4eL3lax3nuXqvZ7n9F0nZRkl9R9JzGLb0APuypJj9mR/2sqizVd7LFk6WDdWHvhI+7ciRXMD+SatyE0xe5G3j6/k7fTbsULyDpS828o=
*/