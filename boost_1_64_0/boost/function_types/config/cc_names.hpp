
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
vPXz7s+eYuIskoahBz0HR5O4yALhnv+AXRXhKfnpUX4Ul8RvNT7NXLrL9fIqN40p5j+NdzCbrsdyuX+pLw6RrahsVIH3hEFitggst8VOn0RVlxr6BP38ramVcopt7K/KoY1XatP8YNmHzS98Tc5MEqxN57aH9wfZcZwXMXjB1PB7xR3VPe2jLXb0eGVC/+rnVPS3m0wm9Zv6G2Zp6qDza9smUOid1TvEd/4WWdMvx1gIih/ZoJfFAxwoMzsxKdNu3AryxkWWpRGmq+Z2/leBk2Zpoc12OS4UQAnhURpehG5WROQ4hE8Yb9qpLWBj+Jd9Bz6qFxlYrEqGt86Lf3Ek/PiJn3ScS5Cxwoiu9UFVM/kGvDw9Wq15+OulLy4BbntlaNb3Fu2L7MYkzzUH7xEX4DiXzNV8yQSpKgyHkBE4OFBRwZtuflu1qv2d5ODCQPFDYvgHEe70ussAlTQVN+ZPuO+6pl0sq20dOIj0ySm0aAeVxXoqq9lmSUNnfNjiHu0oQjvH97I42AGqzmALf2vi0xghvIArkv4iRBCHU5Gpx2ouFvPh1cTodW72xw==
*/