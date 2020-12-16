
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
KyqJSjhTkhk2+kS0JsJtkztWmPjya6VNTLxNB0NOWV09/o3XIzWw935fNRW9vHywie2aj8/f0xs9Y5OUWv/Ra0Te1zyc9Y/PGzQiys6b8XJ2Wwc6/8x/UgDo1toncO/EvP8aFnketht+5r8NRqasuzyWnZ1KN3a9e4efe5b74OCgf6Mjvu4L94MTnmFjY5HXD3wyPf1stchV6bVvth1W7d3bJa8Q1hWiNEgfjGksH7ATz+Z+qX1Qgt44Yf/hpAPJW+2sHql2Z/l00HiTVq3V+SHjlSsYLWmqS3jDpTKXym8mANiFA2Cw9H0dABn8heqNUx8fNBlgE6Q2EkvdOH1CQWJ6hl+61TQ6FcK+fX19pSfuVfyBkfdeNS0eOuo8J4YjWFovesFqneJ1pINRZ26HExlOsj4toA+sKrx0k9zYtw8Aw8q/6Cdy3PW2YesURAIG7aGV7Y5+bELnlj6esBDy59GeM98PJg2ON1irxwoOB8BPRAUAmAhGvp/MR3szjaRSGXmMhe6kvJxUJE+IqwfNfo9cN09i8g/vOj+eKqAZHSuSEBKeEPFZmflxw+3jd9hzIuj2n3JImo4T9KFIePTtkIPd5/7JWt0eaz+fYKIgzSFm46fvNNxvS498Gk+35o58ffR2nYt6drbjkfN12camJKywQKvV5FCPCr9K3HjDE/PXykuNjxQA+C8lCb26MJ9fh7kteHh8/3p8csKY+/4si+nXHEm6Z11MuR5r0eaTmXMf8SzV1R4w1Nj21kw24cH75mPXancLPRCUnnLXDCpWdBIiettcuof3y0P1GDha/0I5LUgMd2u7AaUdY5snHc6zrlTNING1EFVVzP9YnLb96rkOg02O2XEmur7aWp+n7dj96kXX6izQDnveIK6UzX0zr9YqcWoKLDU+CgBIJbP/Pn89LOdfun9hlf3r8WEcIS7mVhZutuZunz0G3EqOJtObmw+EmNuGmN+zOm91mtG9/LyV/L7k3Jl9pH7tIZOMd0eKZctey1J3Mcs4fBp6qMaboh4Wu6NPa8W3IaJEX7lCpXaJaqYu9ZRTggcp8+0MaElugFqLPmUHfiBTl/yj+LZ6uqcrPCeMVzYtUK4KTduzVzFSX0JPhlOqosXriwMASBHAT+/ZvqMVEJsW+367Yfnua00TKeov2VcX8DoKyFW5btwks1ytvLk4+CsrOFqM3d94ra/FJzwHifXwp+g4EHXUSdrng3Typ6YTx/plPoMxefnNTe8qPoeQhJPYVK3ETQTcOTLCusPJ8mjHVlG1Or6MBKq6o/vpgljGrLM+hQgay31tky0TRgYzubP/lMtgGRzuOscBgMH0JK12d1/qrlOv7DanONXT0RFNK+Z4J4fTeUezmMSzLX2+5AEAQRzgb92jkpPBt1VHN6ukM3zaN/BiIIA1aJufYagA074VCnTgUssb4LH1IFFC/UAgVD5P7Ne5SBETJV+w3jPqYuclj2iWDE/1mUlH87JaGQkjFp1jzjJVwOhNdsLgbO8zq+erDXf4b0KVXlJlJfhtff8n/twvP/EePLLXhYJ7DfScryq1W5XuuM/vgQyTBu/Z92uoREI1vc7KWlEZBHCv0D7/gulUzXYADGvX3c9/JTfgx5dlAvqxL+mlo4uNOy2T6RTkSZgX5rMAAKgCwMYtKqylP85nh9JFBe4FwK81//wA07WwsDLbw+q6d4tdNiv9MyVdHyULHd3xeN00JbpiizaOi926ul+1Y+iyzXUv7ud06n3I6KOyVXrD4GTJc7LDmiWnfWkPR1xQDDgsUSGmy02eEOKy0ZRvkDSAgzF0B1fUR2J3i8HR7vFvOZ6d78Rlt1rRCtJJtjwe5cRepVi/6Ep6M0g=
*/