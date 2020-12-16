
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    (/* expand EMPTY */)

#endif // #include guard


/* decl_error.hpp
/HqYrdI6RVsPbuV3rm09HKz8bw67HkwbzMwAW1yVf8pI7G4D+4g1Ykf8rdTXN9C33nf0LJv6ksGFXZ1NmGVbZ/Bst84YUdrXmcS1pOuTI13SvVT5n0TsAXxtJ2vsWnXpK1tnU/YvlX+CuS/JL8rdU7f/mclrHG3oUNp8Za+w21BCbLf4uOSdEmhHSbO5P5heMSYhqQLolthBuzL3Lzlcpb+cPj3WuAWytC9zL6ICFeYF42Jq9l4oqJ2ZZ/wNU+HWqnZ2J/RyJ7c3eecRLtBuPMUfTuqBdmnaSyyVge64tvP6lb1E4eyAdsmGENI4/XoIwunOougDnqPiZpi23ZkZlDGp3QANNiYQx3xf2Ok2zLZ6luLVs8PvaOt7oWgrn8d8CXAhlEV9NAXmqbqmVO09YqkvdcvsF75V4UsoK4fvG0bysnNf375fueA1/ckT964N41vf2n+vTNN/M3g8powUSmRjF+K2+71QTLkcmrZ53wtLPIHfC6vgOSat878XnvB03veCv8wPlQUBTmEwVdp61vFmmSvbIH741WTGNsgeL7Jf17+NFngxDB2OtV3mpfs8siTAAOgO0m8MSl/StuhqaAp6XQ1xpa+VupJ1DNq+XcKa9Xx8mHkI1BEgi0VHQJrcI82gvK6RvG4vjIbJt1lzW1495eUzzI+zTNrSCOIsh1T/bvj79+5m+6Gv1uoSUsF3FN/tfP1pGHXibxMLqVfFTQK45TsqpUojp3xIBb2TzWdjbxVnT2Oo/uxWeNq/l7fC/0Dlrz1HyIy7B+W0ljIqyrCWUxfKydErKTY+JTmtO6/B3jzQ8Um8/XjfHQh0i7GUYfC7ztSj7UcapIAuxRH4HSVlvLPy30/c7Fqq3F2C68T8Vuit/KcaKfw/2Ijv1Hed9dsqp6+cDyWMrpdvq3qbOpSPK9tvq+Uq3s76PTDt6lDawAvKf3ddHRJX+21l6h03SPvZmlrVfFcRv/3vqqRq+a4SWfopd3ftdxW8zO+qRbSlZZkBz11we/J/Vqm2xJdVYnxibELbN9VB+PBVRSbDaWdNKu2ZxqTgdibPwX3K/zTbZ/1q5V9vtsNhKp9dOrV9RfIt5e9LVks7FDAypc9zVQe2w8rSanNUmk755xJhKWR5no32+jxpL7h8Oheer7D7Pf8z09jf5zFZAhwp/V69jazy4Nj2fUtUvN2MbH3fB9/2+75l1fZ9H3HNvu8Dymli/8C+r0dyXCojxpQutNReIT1feG3yLpXGPkig7/uuU/4FZpv7pLr9vu9K5V9I3cB1C/R9B0o95srHRL0wukT6PqOm3XqU0aX9+LKfir+Lri7h3X4fuH2NbR9I3Pb7wIk17faBxG+/D5xZE9gHnl5j3wfCy+wDF/an3x8Q2AdmJsf1iu+eHNeFxpXcJWnHcDvBcNrbtirtWcaRNn1gd+V/lm0f2FX5zzXb44U1/24f6P/ua5L2uBFyQD/IN3aTpT3O9jgxvZ9ZWjXDsNXJvKDCf80ZPY4O54faGwteMdDnsUbk+Ri6zVsBJ7bJc0KbjjCsb27iBu0n6VXvar+5zbCpZljf/Lx2TXAgbwrafC417Vcjh9Sb7px9CattT33ABOX/TsRlbT82kHtSNukB+yuaZWC2p6B17XJuvv57b6UsyGyWsfNKGTtnnWTWqS+BwOGzdfxs9jfjVZyBzPMn6OoanvZj6oA5KtEFFavw3Y3B9CkNeDZv5x9vD/eOtxPi42K3ahtxG+2Ouc09yxXP2fJsOIxXlHuAkS5j8ALSWAn5xuAu7Rh8G5FnTLZfnrq5SYmRjP1D011FmgXZ/nTrrt/csb+/Tk5W6RyOewff+D+MveLDmS+oGOSL6LDwe5E85tY=
*/