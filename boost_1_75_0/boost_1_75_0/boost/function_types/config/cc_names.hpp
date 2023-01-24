
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
TNyRj9RkdahyTataxiQkxxh7m8PGXqBrzyGigQf+vnHxtrp3IiGiCSgs7NM/jiQ3DUEF5iySLM3VkTY51XliqjOJFm/lA18elunMH+ZyaN8kmaUXEyZD3i2ccTPRMQryOnIpnHA7CfrVx64VkZiYYo81lu9tMtxuETjQUfuUWqL6bBnP1uXbQ/mOCxmCQpA3lSRaIChUEBTyJoKplguBK0nBx9C2HlSXKgcgfopQkUNTFRCYP6KfAILa1knRyW/bqrAlJinqKIsFZKZlJEWplJS6wci590UQA9uBw+DlIhebx/MCeZfrXSB86YCBY/A9BGnn91fB+66wLjqyiB/jplVCSEsu0g0prDh/cCZoWJ4VEWHC3jac+0FRvSsFvU9ug6qumNhOjKmuJdMjJG7uHKpw89xkDTdfiYm3aWdgLSV2ltjrnYp4fttN1N7MtTpCDBZYj0wmiHUi6qJ9rgRW7o11xOUtIS6vVD8KQ5zG6+iIm5xF145ZHPejTRYt6tjrcDe00eXYtWFk9aAXbfmi6SPlUSEeyK1ZZiFP6abL6nMErfSgTiEnyWnz9NgpzgpgUuZw9digm5RtLG7p9qM6sm6NDbAQPolpwidAG+pmq08Wdmn8k+biE/CQqx9O5R9uQnnY7OsvoPJXnKZ8kihfi5RwSJzxl5fyaeG4xJ0FJDifqtndufFqWviui6uYAbSqfpXdESuFaQMcUpA2
*/