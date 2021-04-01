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
QpJxkfAXveHZPIcjiVtwtOpzL45XKqJSnOsp3t/i5NlZ4TN9Vx/H6+EnnAJUW+jssBbmOeRkEKXL/InMa1+4bfPADElVdW/p3dFaUIxRM3Uu8w26MyIkMifUvfc0SC7V0qMJqd3f7W5rHE6kQeUpr6SZMTwEOZBSD+4CkCuqHA7lrR7SIhmhasfTBxugj/mwLIWxiPL//ru8li6Gz2wItUDiJ/Pz4Kr3aLP0ODfRwtB+idWhE3gkWWGu36SoMy1U2xGYVNiQyPt+SnYA6JhsbeLUb+FRuUBa+Ce0K5V+W2j+0zC2ci3J/0NUsLRmVvXyhl/qAlUzg+2w9Y713m67v9IHDkwFVJtggIrx5Lvpl3DWDaDu5TjHecDPLzYNQanWDqsOLVlZByxfvV62EEPfTS8V/ffu3UyCw6W7X3C8+Sgjf1JHDlSAuyrnhH4lXnh5i5Kn9yaCScwsjrzrhwcH2+REk5rRuB3ce7eYTWPjnxCfSBVQJJAyypKAMsqBzlsjtDcXnatrP8QWV3GMxJScyokzqEs6QxUi6MUFz/83yu3+lRr9S1v4/Uit+w==
*/