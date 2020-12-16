// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FOR_EACH_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FOR_EACH_HPP

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux2(x, y) (x, y), ~
#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux3(x, y, z) (x, y, z), ~
#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux4(x, y, z, u) (x, y, z, u), ~

#define                                                                      \
BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_BOOST_PARAMETER_AUX_PP_FOR_EACH_END_S
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_SPLIT_FIRST(x)                  \
    BOOST_PP_SPLIT(0, x)
/**/

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head(n, x)                           \
    BOOST_PP_SPLIT(                                                          \
        0                                                                    \
      , BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux, n) x          \
    )
/**/

#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/logical/not.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)                    \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(                                          \
        BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_, x)           \
    )), ~
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux2(x, y)                      \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux3(x, y, z)                   \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux4(x, y, z, u)                \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(n, x)                      \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux, n) x
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred(r, state)                       \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_SPLIT_FIRST(                        \
        BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(                           \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
    )
/**/

#else   // !(BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC())

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred(r, state)                       \
    BOOST_PP_SPLIT(                                                          \
        0                                                                    \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(                           \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
    )
/**/

#endif  // BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_op(r, state)                         \
    (                                                                        \
        BOOST_PP_TUPLE_EAT(BOOST_PP_TUPLE_ELEM(5, 3, state))                 \
            BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
      , BOOST_PP_TUPLE_ELEM(5, 1, state)                                     \
      , BOOST_PP_TUPLE_ELEM(5, 2, state)                                     \
      , BOOST_PP_TUPLE_ELEM(5, 3, state)                                     \
      , BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(5, 4, state))                       \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_macro(r, state)                      \
    BOOST_PP_TUPLE_ELEM(5, 2, state)(                                        \
        r                                                                    \
      , BOOST_PP_TUPLE_ELEM(5, 4, state)                                     \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_head(                                \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
      , BOOST_PP_TUPLE_ELEM(5, 1, state)                                     \
    )
/**/

#include <boost/preprocessor/punctuation/comma_if.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel(z, n, text)       \
    BOOST_PP_COMMA_IF(n) BOOST_PARAMETER_AUX_PP_FOR_EACH_END_S
/**/

#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel_tuple(arity)      \
    (                                                                        \
        BOOST_PP_REPEAT(                                                     \
            arity, BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel, _     \
        )                                                                    \
    )
/**/

#include <boost/preprocessor/repetition/for.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_R(r, arity, list, data, macro)       \
    BOOST_PP_CAT(BOOST_PP_FOR_, r)(                                          \
        (list                                                                \
            BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel_tuple(arity)  \
          , data                                                             \
          , macro                                                            \
          , arity                                                            \
          , 0                                                                \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_pred                                 \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_op                                   \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_macro                                \
    )
/**/

#include <boost/preprocessor/repetition/deduce_r.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH(arity, list, data, macro)            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        BOOST_PP_DEDUCE_R(), arity, list, data, macro                        \
    )
/**/

#endif  // include guard


/* for_each.hpp
50m4wLTux48kf3ZJ/jwj+bNb8udZyZ89kj8/k/zZCx+S4+1y/DT8heTPm5I/b0n+HJH82S/58zv4trg7Ke4+EHcfwt/As+Luc3FH/ih3reERyZ9XJH9wR/5o7gaKu3RxlyHnR8PfwxxxN03cXSXuZN43z6bh/nJ2QuS8b+4Zql51hFlJ2lrM++9OOO/85cj5ypZzlf9v5ykfvTvhf3KussU85f+pOcpn7k5omqd8AfOUU1mcche0mKd8rjnKjZqf3JC5yT0IxyiMF7MWcz9mP+Y9TOq9zFHGjMPMxgQw6zFb722aK9z0ix3/nybj/wP+0rKaNdW1VTPyhnoDAd67pqm9IxLFbSs1Yj9yvP70gsJprv8hP5p+Tb+mX9Ov6df0a/o1/Zp+Tb+mX9Ov6df0a/o17vl/qGuc8dxtfvJ2uayfvfu5EpQ/teK6+alENfrdVZXp9xRPnO2ZXlA8WxtrbLvmUXGdVi+a/kyvZ97w9NGewpwZk+zVHKo0w99DHozRnDRv9qTC4oKZhcUum+PbS7RfFe3UE1HaNusNFL3p8upwrzmuMycWF3lmTSouKsizO556Gu8T3Tf1eDKrWs268DBunVUigh5/Za3N2nqZGicXPK6XYy/lWOUv87Ac0twhF+w7HdZ0uhwPlkkD2+rDmv+pcrxVtG8+GdZ2ohzrce0k6yU8Zc7TWcU5RTX+lSW1vmm+NaHMtVdbr0ObRPurcbWd0U1uLntdmnUjI2yrrl6WrxHdrda6tmrq5ek90Vx30qw5J3fapPm26ulp65W1A2ab42i0i1Qcm+usrntYdJ8z1Vkn22M9fafLxKuWx0V3wZyCwtkjsjz+Wkf0dotekqGnyzkTv8GyPsKZYya9YZm2643Q23vRc+n3N9XurvTV+Jeu8ZT52EaZG15Vjdzt7A2DXpYGtJTxQnHC4NT9davodorQratmAsdSp8pvaorsKXbMpEnu2q2n3282iF67iDiGtjwO1pUuYzkeT2XJCp8z2kmyOM2j9THa/vLKktq6Gp+n0u+1VVsvU9eIdp9T0drLuePUBUvKfbbq6nE+I7pPxMTZHwyynb9KbpvzOlO0V18sE25i8pplA3yVau2epYGS8qDN+nqa14v+tpMW+h5uEA7pVrSS/XCiddOZU1tKftusq9flQ6L714i6zMOBzfVJ18tvLWU6In/LVlTbHD+9LO8VvTsj0rWswsfaPNVaN8qz3OZ+lJ6n42Rm1GWRca0o8VdKC21vnPU6tFt0d9XH6qqY024yNbLUqfZ6lMz5//Vpk766CfqX+stCKV67ptrm8jVCj7toz4vI77mTZhVMnu8pypmVM8MTpDLX1tQFbb9f6WHIlrUAZp0zDNTrmuqqoM3pMEZ/5pcwVJ87DBVVwVrVnDqVFtPba64XnzscXl91bYXdYdDT4lUJw4fHzxmGkrraCk/At9IXsDkcelrMk/UTvOdMiwwyxf6yOVRPCwnDqXOmRYYj2kWXaK6z48efNTLsjbdeBg6J9sfx472iaqXPU+3z1YS6N3anf6ZeBtJkDdT4aeCvrPDVOPWsdFj0r4mvX+50ffTK2hgrzxmGdMfyQi+PRyQck+OHg46QvX3sEXoadNJcL4uvXeL1OtMWGO8/JAx3RtSJ4tkzZ01ypH+ix31JZ831mJMxunIzWFpSF+AGWVJbYXc/v5/eDkoYbraIO42QrZp63Z8ta1bsORGrGagq8fIPvSOecIL2xlnP7/2iv9kizhR0x+pZ/qWyh5xFflPIiXbV8rpqZ7T3ivau49ba9Eptr18j9Hh3ledoC+2Js+epsq6/ISq1OQx6mdsnYfhd/DA48jydqadBN3nHGl+fJ2tPaC1XR/Q=
*/