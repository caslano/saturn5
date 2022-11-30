
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif


#if !BOOST_PP_IS_ITERATING

#   ifndef BOOST_FT_DETAIL_CC_LOOP_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_CC_LOOP_MASTER_HPP_INCLUDED
#     include <boost/function_types/config/cc_names.hpp>

#     include <boost/preprocessor/cat.hpp>
#     include <boost/preprocessor/seq/size.hpp>
#     include <boost/preprocessor/seq/elem.hpp>
#     include <boost/preprocessor/tuple/elem.hpp>
#     include <boost/preprocessor/iteration/iterate.hpp>
#     include <boost/preprocessor/facilities/expand.hpp>
#     include <boost/preprocessor/arithmetic/inc.hpp>
#   endif

#   include <boost/function_types/detail/encoding/def.hpp>
#   include <boost/function_types/detail/encoding/aliases_def.hpp>

#   define  BOOST_PP_FILENAME_1 \
        <boost/function_types/detail/pp_cc_loop/master.hpp>
#   define  BOOST_PP_ITERATION_LIMITS \
        (0,BOOST_PP_SEQ_SIZE(BOOST_FT_CC_NAMES_SEQ)-1)
#   include BOOST_PP_ITERATE()
#   if !defined(BOOST_FT_config_valid) && BOOST_FT_CC_PREPROCESSING
#     define BOOST_FT_cc_id 1
#     define BOOST_FT_cc_name implicit_cc
#     define BOOST_FT_cc BOOST_PP_EMPTY
#     define BOOST_FT_cond callable_builtin
#     include BOOST_FT_cc_file
#     undef BOOST_FT_cond
#     undef BOOST_FT_cc_name
#     undef BOOST_FT_cc
#     undef BOOST_FT_cc_id
#   elif !defined(BOOST_FT_config_valid) // and generating preprocessed file
BOOST_PP_EXPAND(#) ifndef BOOST_FT_config_valid
BOOST_PP_EXPAND(#)   define BOOST_FT_cc_id 1
BOOST_PP_EXPAND(#)   define BOOST_FT_cc_name implicit_cc
BOOST_PP_EXPAND(#)   define BOOST_FT_cc BOOST_PP_EMPTY
BOOST_PP_EXPAND(#)   define BOOST_FT_cond callable_builtin
#define _()
BOOST_PP_EXPAND(#)   include BOOST_FT_cc_file
#undef _
BOOST_PP_EXPAND(#)   undef BOOST_FT_cond
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc_name
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc_id
BOOST_PP_EXPAND(#) else
BOOST_PP_EXPAND(#)   undef BOOST_FT_config_valid
BOOST_PP_EXPAND(#) endif

#   else
#     undef BOOST_FT_config_valid
#   endif

#   include <boost/function_types/detail/encoding/aliases_undef.hpp>
#   include <boost/function_types/detail/encoding/undef.hpp>

#elif BOOST_FT_CC_PREPROCESSING

#   define BOOST_FT_cc_id  BOOST_PP_INC(BOOST_PP_FRAME_ITERATION(1))
#   define BOOST_FT_cc_inf \
        BOOST_PP_SEQ_ELEM(BOOST_PP_FRAME_ITERATION(1),BOOST_FT_CC_NAMES_SEQ)

#   define BOOST_FT_cc_pp_name BOOST_PP_TUPLE_ELEM(3,0,BOOST_FT_cc_inf)
#   define BOOST_FT_cc_name    BOOST_PP_TUPLE_ELEM(3,1,BOOST_FT_cc_inf)
#   define BOOST_FT_cc         BOOST_PP_TUPLE_ELEM(3,2,BOOST_FT_cc_inf)

#   define BOOST_FT_cond BOOST_PP_CAT(BOOST_FT_CC_,BOOST_FT_cc_pp_name)

#   if BOOST_FT_cond
#     define BOOST_FT_config_valid 1
#     include BOOST_FT_cc_file
#   endif

#   undef BOOST_FT_cond

#   undef BOOST_FT_cc_pp_name
#   undef BOOST_FT_cc_name
#   undef BOOST_FT_cc

#   undef BOOST_FT_cc_id
#   undef BOOST_FT_cc_inf

#else // if generating preprocessed file
BOOST_PP_EXPAND(#) define BOOST_FT_cc_id BOOST_PP_INC(BOOST_PP_ITERATION())

#   define BOOST_FT_cc_inf \
        BOOST_PP_SEQ_ELEM(BOOST_PP_ITERATION(),BOOST_FT_CC_NAMES_SEQ)

#   define BOOST_FT_cc_pp_name BOOST_PP_TUPLE_ELEM(3,0,BOOST_FT_cc_inf)

#   define BOOST_FT_CC_DEF(name,index) \
        name BOOST_PP_TUPLE_ELEM(3,index,BOOST_FT_cc_inf)
BOOST_PP_EXPAND(#) define BOOST_FT_CC_DEF(BOOST_FT_cc_name,1)
BOOST_PP_EXPAND(#) define BOOST_FT_CC_DEF(BOOST_FT_cc,2)
#   undef  BOOST_FT_CC_DEF

#   define BOOST_FT_cc_cond_v BOOST_PP_CAT(BOOST_FT_CC_,BOOST_FT_cc_pp_name)
BOOST_PP_EXPAND(#) define BOOST_FT_cond BOOST_FT_cc_cond_v
#   undef  BOOST_FT_cc_cond_v

#   undef BOOST_FT_cc_pp_name
#   undef BOOST_FT_cc_inf

BOOST_PP_EXPAND(#) if BOOST_FT_cond
BOOST_PP_EXPAND(#)   define BOOST_FT_config_valid 1
#define _()
BOOST_PP_EXPAND(#)   include BOOST_FT_cc_file
#undef _
BOOST_PP_EXPAND(#) endif

BOOST_PP_EXPAND(#) undef BOOST_FT_cond

BOOST_PP_EXPAND(#) undef BOOST_FT_cc_name
BOOST_PP_EXPAND(#) undef BOOST_FT_cc

BOOST_PP_EXPAND(#) undef BOOST_FT_cc_id

#endif


/* master.hpp
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
*/