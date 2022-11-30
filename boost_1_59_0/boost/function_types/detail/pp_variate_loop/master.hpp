
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif

#if !defined(BOOST_FT_PREPROCESSING_MODE)
#   error "this file is only for two-pass preprocessing"
#endif

#if !defined(BOOST_PP_VALUE)
#   include <boost/preprocessor/slot/slot.hpp>
#   include <boost/preprocessor/facilities/empty.hpp>
#   include <boost/preprocessor/facilities/expand.hpp>
#   include <boost/function_types/detail/encoding/def.hpp>

BOOST_PP_EXPAND(#) define BOOST_FT_mfp 0
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function

#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) if !BOOST_FT_NO_CV_FUNC_SUPPORT
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
BOOST_PP_EXPAND(#) endif


BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function_pointer

#   define  BOOST_PP_VALUE \
      BOOST_FT_pointer|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_pointer|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function_reference

#   define BOOST_PP_VALUE \
      BOOST_FT_reference|BOOST_FT_non_variadic
#   include __FILE__
#   define BOOST_PP_VALUE \
      BOOST_FT_reference|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) undef  BOOST_FT_mfp

BOOST_PP_EXPAND(#) define BOOST_FT_mfp 1
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_member_function_pointer

#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) undef  BOOST_FT_mfp

#   include <boost/function_types/detail/encoding/undef.hpp>
#else 

#   include BOOST_PP_ASSIGN_SLOT(1)

#   define  BOOST_PP_VALUE BOOST_PP_SLOT(1) & BOOST_FT_kind_mask
#   include BOOST_PP_ASSIGN_SLOT(2)

BOOST_PP_EXPAND(#) if !!(BOOST_PP_SLOT(2) & (BOOST_FT_variations))
BOOST_PP_EXPAND(#) if (BOOST_PP_SLOT(1) & (BOOST_FT_cond)) == (BOOST_FT_cond)

#   if ( BOOST_PP_SLOT(1) & (BOOST_FT_variadic) )
BOOST_PP_EXPAND(#)   define BOOST_FT_ell ...
BOOST_PP_EXPAND(#)   define BOOST_FT_nullary_param
#   else
BOOST_PP_EXPAND(#)   define BOOST_FT_ell
BOOST_PP_EXPAND(#)   define BOOST_FT_nullary_param BOOST_FT_NULLARY_PARAM
#   endif

#   if !( BOOST_PP_SLOT(1) & (BOOST_FT_volatile) )
#     if !( BOOST_PP_SLOT(1) & (BOOST_FT_const) )
BOOST_PP_EXPAND(#)   define BOOST_FT_cv 
#     else
BOOST_PP_EXPAND(#)   define BOOST_FT_cv const
#     endif
#   else
#     if !( BOOST_PP_SLOT(1) & (BOOST_FT_const) )
BOOST_PP_EXPAND(#)   define BOOST_FT_cv volatile
#     else
BOOST_PP_EXPAND(#)   define BOOST_FT_cv const volatile
#     endif
#   endif
BOOST_PP_EXPAND(#)   define BOOST_FT_flags BOOST_PP_SLOT(1)
BOOST_PP_EXPAND(#)   include BOOST_FT_variate_file

BOOST_PP_EXPAND(#)   undef BOOST_FT_cv
BOOST_PP_EXPAND(#)   undef BOOST_FT_ell
BOOST_PP_EXPAND(#)   undef BOOST_FT_nullary_param
BOOST_PP_EXPAND(#)   undef BOOST_FT_flags
BOOST_PP_EXPAND(#) endif
BOOST_PP_EXPAND(#) endif
#endif


/* master.hpp
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
*/