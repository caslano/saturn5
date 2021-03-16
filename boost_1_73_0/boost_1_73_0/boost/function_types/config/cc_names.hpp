
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
3SyxQ95Cmxe65gH9wDPk1VQlnEt3oyyldh6gO62T1NO+Rs9o100bzljqI8KmWn1UtoXGh5/TnGPhXLGs+QPqQmBgmQXfsaOLPqGLankyjt3WYbooRZnD4ciCQI2Gl+tOI2uhFDLW6qJ8Vh8rW6ZHPP6aaXwBPW+anQal/dZKUd/5UpTbQAfvgO+7j+44HErBxZHLaDGEzdYm2z1d0/s/QhUGUusbA6kneGf++TBWBzLqp7o9MyTy4oAXTKWHz1A=
*/