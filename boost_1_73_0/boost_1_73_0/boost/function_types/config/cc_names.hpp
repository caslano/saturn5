
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_CONFIG_CC_NAMES_HPP_INCLUDED
#define BOOST_FT_CONFIG_CC_NAMES_HPP_INCLUDED

#define BOOST_FT_BUILTIN_CC_NAMES \
  (( IMPLICIT           , implicit_cc , BOOST_PP_EMPTY                ))\
  (( CDECL              , cdecl_cc    , BOOST_PP_IDENTITY(__cdecl   ) ))\
  (( STDCALL            , stdcall_cc  , BOOST_PP_IDENTITY(__stdcall ) ))\
  (( PASCAL             , pascal_cc   , BOOST_PP_IDENTITY(pascal    ) ))\
  (( FASTCALL           , fastcall_cc , BOOST_PP_IDENTITY(__fastcall) ))\
  (( CLRCALL            , clrcall_cc  , BOOST_PP_IDENTITY(__clrcall ) ))\
  (( THISCALL           , thiscall_cc , BOOST_PP_IDENTITY(__thiscall) ))\
  (( IMPLICIT_THISCALL  , thiscall_cc , BOOST_PP_EMPTY                )) 

// append user-defined cc names to builtin ones
#ifdef BOOST_FT_CC_NAMES 
#   define BOOST_FT_CC_NAMES_SEQ BOOST_FT_BUILTIN_CC_NAMES BOOST_FT_CC_NAMES
#   define BOOST_FT_CC_PREPROCESSING 1
#else
#   define BOOST_FT_CC_NAMES_SEQ BOOST_FT_BUILTIN_CC_NAMES
#endif

#endif


/* cc_names.hpp
suUZTWgoeq7NoqRQxttNJXePFCmtA1DZtYLcUVpIr5CUeA86UWBr9W0i9l6GLNuUf6dkD7EXIAVFBW6QwCxxYcsUVx5cztLzaJ3CZbBaBct0A9EZBMvNgHcxW54SNzh5bQFvmxYVRdEC3zU1x+KR8x/a746fnsN0vZpHcZolyXwartJ0E4dwDO7RCfzRCUPtn1xwa741tYcT//jEPySB+ZchU3eZQm2qTD8ilCLM5ByWwSJ0vgV8dQCqwZwYAPquwX2uc7qn0ECakGOreclzptFCJZtlFCezxHnBRV53BcI747unYvXesW5ySfKnIY3MCbysiCQ1ceUb4RAnK9bCSxPK+Bfr7jRMpqtZnM6ipRMzqgODRnKhDUOoKUB0dX1geMIFM+U2hRefhyZjO6SjvqmGg6Elt+jY9pXtjtlWpHZtv76rD0nXNLI1mL2Wsr3oxuHCtTx3T8OVSzS5zbHRzg2xBRKkOyOkLRPK2PoQNShMFkfX1A6mHnDov/GPLUBNbtqx3T41dEZEWx4l8Nrwzip6ZkeST3B06J/8Kx7300H1wVJ4R69cE7ATX0yTF0evDlCYYhS2bZTvOCYXrCEi0y0pIGo6amQhdT+lKKdfEBtLgn0qW0kdCaw0OadKaiM0k8vpKeYPdToL1vPU
*/