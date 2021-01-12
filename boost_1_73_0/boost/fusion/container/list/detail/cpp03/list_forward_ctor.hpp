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
ng77Sloesnz8ncUbTY7jbtI4k7BhmpIHTTpH2vES/1fEH/HTFr1QO2zi4tv8UTIcTkwOJQcD/sxgIJyVEPY3DQbDmYuWEW68zKl5LA2DieaP8ui6j59Iup8h3mW2oz8qS+PfSPyPE86/KC+YFI5vLPVb49N7QzhaI0cXUUU0vqYil3yrI7MvsrRcDBa30yw/Lm24N851mup1hgbRY5DqXGdx6Gg0W2X5LXdb4ln+M+F+kcck
*/