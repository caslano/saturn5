// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the metafunction select, which mimics the effect of a chain of
// nested mpl if_'s.
//
// -----------------------------------------------------------------------------
//
// Usage:
//      
// typedef typename select<
//                      case1,  type1,
//                      case2,  type2,
//                      ...
//                      true_,  typen
//                  >::type selection;
//
// Here case1, case2, ... are models of MPL::IntegralConstant with value type
// bool, and n <= 12.

#ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_SELECT_HPP_INCLUDED   

#if defined(_MSC_VER)
# pragma once
#endif                  
 
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace iostreams { 

typedef mpl::true_ else_;

template< typename Case1 = mpl::true_,
          typename Type1 = mpl::void_,
          typename Case2 = mpl::true_,
          typename Type2 = mpl::void_,
          typename Case3 = mpl::true_,
          typename Type3 = mpl::void_,
          typename Case4 = mpl::true_,
          typename Type4 = mpl::void_,
          typename Case5 = mpl::true_,
          typename Type5 = mpl::void_,
          typename Case6 = mpl::true_,
          typename Type6 = mpl::void_,
          typename Case7 = mpl::true_,
          typename Type7 = mpl::void_,
          typename Case8 = mpl::true_,
          typename Type8 = mpl::void_,
          typename Case9 = mpl::true_,
          typename Type9 = mpl::void_,
          typename Case10 = mpl::true_,
          typename Type10 = mpl::void_,
          typename Case11 = mpl::true_,
          typename Type11 = mpl::void_,
          typename Case12 = mpl::true_,
          typename Type12 = mpl::void_ >
struct select {
    typedef typename
            mpl::eval_if<
                Case1, mpl::identity<Type1>, mpl::eval_if<
                Case2, mpl::identity<Type2>, mpl::eval_if<
                Case3, mpl::identity<Type3>, mpl::eval_if<
                Case4, mpl::identity<Type4>, mpl::eval_if<
                Case5, mpl::identity<Type5>, mpl::eval_if<
                Case6, mpl::identity<Type6>, mpl::eval_if<
                Case7, mpl::identity<Type7>, mpl::eval_if<
                Case8, mpl::identity<Type8>, mpl::eval_if<
                Case9, mpl::identity<Type9>, mpl::eval_if<
                Case10, mpl::identity<Type10>, mpl::eval_if<
                Case11, mpl::identity<Type11>, mpl::if_<
                Case12, Type12, mpl::void_ > > > > > > > > > > >
            >::type type;
};

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED

/* select.hpp
5MuSRuTLpxz5cmi4/ZNmTqsaR75MpGxY4iqjnXYoT4vOhzN7YwuHHRpaHoTfA290jN5T4Gf2e8DpR0kpGWk+a3w693xR+8iabC73+pz5xryWoM+9vil7PzJgw7y+qdZXYVjbDX217qh5Ld2drnT/SUb9doncE4L46fE+Op+61gXV4dVr0BIuzqtwRaTlEdJa5gupX2fk59i5JmTnwuFLQ4s4hp+3I92983SNww6HOoTsZhwL5NJNVTZWC5maxwK5bHZ1HHkp/KwQXvtZ0d9yCZeyjx7Xo8g58d+ZBzMyom3zaLatpG3j7NdR9tmV7Wkf7ovfPpY/fvtY/obbZ1d24vYJ101Gd462z+O4l+m2j/S7hPPQY5424t4EbJSZgI0yG2GjxxpgI12P6hJtoz24l2uwkfSHaDs94Wkn7k/ATrkJ2Cm3EXZ6ogF2CuelDV2j7fQL3Ctw2UlXbcLv2Bg2KkjARgUJ2KigETZ6qgE2CvcZ7OoWbaNf4V6Fw0bmfoOQrapj2KoiAVtVJGCrikbYqroBtgrnpwPdo231LO5VOWzlas8rGz3jaSPuTcBGVQnYqKoRNnqmATY6Mfzu7xFto324V+2ykbS3lX2e87QP9yVgn+oE7FPdCPs81wD76HHTmdH2eRH3akz2kXZwuOx+IYadahKwU00CdqpphJ1eaISdzugVbaff4J4VMNhJF+AhO73kbSfuj99OViB+O1mBhtvppQbYKVzX7pOlx1bxQwfZj3uZITstHV4ode042o+he3yy74i0e7zqSa74ViQQX8IQEV/8kjZIZFkS7B0dt9/b9RxX3KSuXO834dwE4pfbiPjdWk/8dJ+0IX6vEr8CHT9XXTeO764FCcSxoBFx3Bw7jvo53t8nOo6v2fULHUdDXTWO75oVCcSzohHxfCvOtNzVNzqeB+y6gTueuqiq/3thVQJxrGpEHG+KHUddV6zqFx3HP9nvdh1Hz7pivd/iqhOIa3Uj4vpsnGVPRba5XK1xx3Xa+AkT4yhbaxKIX40rfjvi6M+Jt2wN59fC/tHxe8OOc1DHz12XrfebnRWMP45WsOFpuCQ1vjQcPyA6jn+1342uOEpdtN5vYZkJxC+zEfHbGGfZOnhgdPxq7PejMX5Sl4zje1NuAvHMbUQ8h8QZz7RB0fH8G/Es0PE01gXr/Y5TkEA8CxoRz8p64jlUvo0cloV87PMthX2p+OaFvo3YI1sX8WnD0YfM2NjSBeVLVyw3xo/7dPzGdlJ9yKzYXze3aLG6foE1BO1Jpn3pXW58Hqove/ZZo+va/7VoNbN56vZuU9cXqvmVMxDjvnDoOOcV/jSDdCThV6XHM/8oOfQutt2Q+Uh3hP7uc9a0Uer4an18gjpepo9HEE7SS/d3a9vqdMOGnFc21PVybMI5bOLen1Ti7kzfeUNd3x8kfXNC31NKl9rJm0D6cp8pfU3piG786YiuKR2N6SW6+rl4OqX+5+K/bee9x5ntXBt6jsoStXPtV/HbuTaB56X2q/jtLLrazhfH8d3xv2Xnw5yr+hb2zzDP0fKaY9aAfTXU3Ll2szZsmj2u56AvX15pDd56Yqdjt6+GeQ7bf3+/DfNcu2O334Z5LqLXXMHE5+Ydq7mLeg0vVUbxDBrmQD3lXMPrG2+95x16KaKXatB7WOtxLYa/Ox16OeJe23rcy4vh74+da6DF8Pd+h16J9je2e5Ux/P2uUy+Gv5uda75pf2O7tz+Gv5c515oz+Gta861W+xvbPcaFevpbqvWQGP6WONNX3Gtbj3t5Mfy9yZluMfzd6NTT/sZ2rzKGv9OdawTG8HeqM321v7Hd2x/D3+849Api+LvUmb7a39jupfi8/b3HGY8=
*/