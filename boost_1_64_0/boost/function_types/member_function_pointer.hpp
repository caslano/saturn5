
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> 
    struct member_function_pointer
      : detail::synthesize_mfp< typename detail::to_sequence<Types>::type, Tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,member_function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* member_function_pointer.hpp
snNP1qk/RcaQUexmJIG/cDApwHjN4PJlllXUQSIS4GAF3LJj3s6nxNqTFGXHP9EZAdHFMbI6AGx6eEaW5pKPvtlXfEJ7Zh1ZDb7pUDjsscXnTbC0PZQfZvmrYnvvDrKVs9HO0NlkRrexCnzMMtAUaeKbqIN6kJ2MTG9/7lb/E+tJCPhU9a1G2UTce+K71YzJSAXybn/7LrIXbZzAEN4jNk5RXX3TAZSDO4dQR9WhGMIq5c220x8Krv76uj6EpegNo9/y2WkU23P+rElSCDjb5hAMe6cUpTKNR0SrAtI4aF4vr4ko2uvaWccyTutreOpI9Lsm2xVwOjiCqHNtaPAVnhCSHQss0qxDby51DtFi8LyC8lkNAgTDyNh4GSigFvJybEzrUpnhkE034BpeyLtRmwKfH72efcIKf8pV4SjOoOLWfVCbX95+Jg/Q+Kp9OIOKQuJNgMZHKe2EA7fUKswWcW3ukz8ny84dc9kjbfHn2yP2zjezIWqRr9UZzn0LDf3CvBqZkgb4omrys3EDqgGuu0PVYT2AH6cpZtJlQP41cajSyKAH9CTMoaqbMw==
*/