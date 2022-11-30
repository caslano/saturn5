
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#ifndef BOOST_FT_PREPROCESSING_MODE
// input:  BOOST_FT_mfp        0 or 1 <=> member function pointer?
// input:  BOOST_FT_type_name  BOOST_FT_type --> "R (* ..._type_name)()" (pass2)
#endif
// input:  BOOST_FT_syntax     type macro to use
// input:  BOOST_FT_cc         empty or cc specifier 
// input:  BOOST_FT_ell        empty or "..."
// input:  BOOST_FT_cv         empty or cv qualifiers
// input:  BOOST_FT_flags      single decimal integer encoding the flags
// output: BOOST_FT_n          number of component types (arity+1)
// output: BOOST_FT_arity      current arity
// output: BOOST_FT_type       macro that expands to the type
// output: BOOST_FT_tplargs(p) template arguments with given prefix
// output: BOOST_FT_params(p)  parameters with given prefix

#ifdef __WAVE__
#   pragma wave option(preserve: 0)
#endif

#ifndef BOOST_FT_ARITY_LOOP_IS_ITERATING

#   define BOOST_FT_AL_PREPROCESSED \
        BOOST_FT_AL_FILE(BOOST_FT_al_path,BOOST_FT_FROM_ARITY,BOOST_FT_mfp)

#   define BOOST_FT_AL_FILE(base_path,max_arity,mfp) \
        BOOST_FT_AL_FILE_I(base_path,max_arity,mfp)
#   define BOOST_FT_AL_FILE_I(base_path,max_arity,mfp) \
        <base_path/arity ## max_arity ## _ ## mfp.hpp>

#   if !defined(BOOST_FT_PREPROCESSING_MODE)

#     if BOOST_FT_MAX_ARITY < 10
#       define BOOST_FT_FROM_ARITY 0 
#     elif BOOST_FT_MAX_ARITY < 20
#       define BOOST_FT_FROM_ARITY 10
#     elif BOOST_FT_MAX_ARITY < 30
#       define BOOST_FT_FROM_ARITY 20
#     elif BOOST_FT_MAX_ARITY < 40
#       define BOOST_FT_FROM_ARITY 30
#     endif

#     if BOOST_FT_FROM_ARITY
#       include BOOST_FT_AL_PREPROCESSED
#     endif

#   elif !defined(BOOST_FT_FROM_ARITY) // single pass preprocessing
#     define BOOST_FT_FROM_ARITY 0

#   elif BOOST_FT_FROM_ARITY > 0       // arity20 includes arity10
BOOST_PP_EXPAND(#) include BOOST_FT_AL_PREPROCESSED
#   endif

#   undef BOOST_FT_AL_PREPROCESSED

#   undef BOOST_FT_AL_FILE
#   undef BOOST_FT_AL_FILE_I

#   if BOOST_FT_MAX_ARITY > BOOST_FT_FROM_ARITY

#     ifndef BOOST_FT_DETAIL_ARITY_LOOP_HPP_INCLUDED
#     define BOOST_FT_DETAIL_ARITY_LOOP_HPP_INCLUDED
#         include <boost/preprocessor/cat.hpp>
#         include <boost/preprocessor/tuple/eat.hpp>
#         include <boost/preprocessor/control/if.hpp>
#         include <boost/preprocessor/arithmetic/inc.hpp>
#         include <boost/preprocessor/facilities/empty.hpp>
#         include <boost/preprocessor/facilities/expand.hpp>
#         include <boost/preprocessor/iteration/iterate.hpp>
#         include <boost/preprocessor/repetition/enum_params.hpp>
#         include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#         include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#     endif

#     define BOOST_FT_AL_INCLUDE_FILE <BOOST_FT_al_path/master.hpp>

#     define BOOST_FT_ARITY_LOOP_PREFIX 1
#     include BOOST_FT_AL_INCLUDE_FILE
#     undef  BOOST_FT_ARITY_LOOP_PREFIX

#     if !BOOST_PP_IS_ITERATING
#       define BOOST_PP_FILENAME_1 BOOST_FT_AL_INCLUDE_FILE
#     elif BOOST_PP_ITERATION_DEPTH() == 1
#       define BOOST_PP_FILENAME_2 BOOST_FT_AL_INCLUDE_FILE
#     else
#       error "loops nested too deeply"
#     endif

#     define BOOST_FT_arity BOOST_PP_ITERATION()
#     define BOOST_FT_n     BOOST_PP_INC(BOOST_FT_arity)

#     define BOOST_FT_type \
          BOOST_FT_syntax(BOOST_FT_cc,BOOST_FT_type_name BOOST_PP_EMPTY)\
               (BOOST_FT_params(BOOST_PP_EMPTY) BOOST_FT_ell) BOOST_FT_cv

#     define BOOST_FT_tplargs(prefx) \
          prefx() R BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_FT_arity,prefx() T)

#     if !BOOST_FT_mfp

#       define BOOST_FT_params(prefx) \
            BOOST_PP_IF(BOOST_FT_arity,BOOST_PP_ENUM_PARAMS, \
                BOOST_FT_nullary_param BOOST_PP_TUPLE_EAT(2))( \
                    BOOST_FT_arity,prefx() T) 
#     else

#       define BOOST_FT_params(prefx) \
            BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_FT_arity,prefx() T)

#     endif

#     if !BOOST_FT_FROM_ARITY 
#       define BOOST_PP_ITERATION_LIMITS (BOOST_FT_mfp, BOOST_FT_MAX_ARITY)
#     else
#       define BOOST_PP_ITERATION_LIMITS \
            (BOOST_FT_FROM_ARITY+1, BOOST_FT_MAX_ARITY)
#     endif

#     define BOOST_FT_ARITY_LOOP_IS_ITERATING 1
#     include BOOST_PP_ITERATE()
#     undef  BOOST_FT_ARITY_LOOP_IS_ITERATING

#     undef BOOST_FT_arity
#     undef BOOST_FT_params
#     undef BOOST_FT_tplargs
#     undef BOOST_FT_type

#     define BOOST_FT_ARITY_LOOP_SUFFIX 1
#     include BOOST_FT_AL_INCLUDE_FILE
#     undef  BOOST_FT_ARITY_LOOP_SUFFIX

#     undef BOOST_FT_AL_INCLUDE_FILE
#   endif

#   undef BOOST_FT_FROM_ARITY

#else
#   error "attempt to nest arity loops"
#endif


/* pp_arity_loop.hpp
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
*/