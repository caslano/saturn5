
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