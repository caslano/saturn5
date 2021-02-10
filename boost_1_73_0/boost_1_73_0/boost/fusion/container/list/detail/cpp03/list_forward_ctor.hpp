/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_LIST_FORWARD_CTOR_07172005_0113)
#define FUSION_LIST_FORWARD_CTOR_07172005_0113

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define FUSION_LIST_CTOR_MAKE_CONS(z, n, type) tie_cons(BOOST_PP_CAT(_, n)
#define FUSION_LIST_CL_PAREN(z, n, type) )

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/list/detail/cpp03/list_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_LIST_CTOR_MAKE_CONS
#undef FUSION_LIST_CL_PAREN

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    list(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : inherited_type(list_to_cons::call(BOOST_PP_ENUM_PARAMS(N, arg)))
    {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* list_forward_ctor.hpp
fA32BaRlcmisAFGdZnB1+4ZeYlLmXOQwv/pkb4LCKvUey766AZu/yqLOZZFm+thxhTN3wS9iUrSeF9oxxEgf1phfWiVVCDJiN0zkATSWn0Ee46kzPb1q/Y3ItN6MYG/lt7NP495l9xEQ/X0wdL94Ev0Ho6isCgOve/bLBKpaULi/Vo2nxeIJXgzGIgdec+Zx8itRUKKdmsN+D1tHjCr0lR0ssmUWMRxNnY/Xgwv8GzaSiWoiTUnyWS6EyNnqqZXPHyG2llZ8NQRt9NtnodXMVk+u6fJbKX7zrBS/eZziN49TvIlM+m8hoU7/F1BLAwQKAAAACAAtZ0pSJ1WHrqsIAAAYGgAAFgAJAGN1cmwtbWFzdGVyL2xpYi9hc3luLmhVVAUAAbZIJGC9WW1PIzkS/s6vsJgPQNSQnf10e7taHWK4G7QsjHi5EdJILafbnfbRsftsNyGr+fH3VLndSSABdm7uMhrouMtV5aeeKpfNO12ZUlXi4+nxh9Or/OT26jw/vr67yD/uvMO4NmrTq/Ho+312xEi8+sn5f44PfvOMT87+SxVhs3SefxXxH2Z9we/XjIzFcsrX/EC8PuWr2OcpeW/lF3rO89cMfSHf6MeYZn7J6REjmEYzT2y7cHpaB7F/ciDe//TTX8Sh+PGH
*/