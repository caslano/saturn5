
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