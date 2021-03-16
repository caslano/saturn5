
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
sWBplsEyLINtF+xVwbQgVKQ8C8DNtZtwDfg8lxDzSjra8pU3h1+GwT/PLWuUAgsUoayR7z9SVOrSvAai4cjw70jrDS1ARbL4XpDjTH3CKD5HVrh5PPzTlziHYop+5ci4LOeQs80FRkUN/G4sQqAnCBYhsBtn/eR0CF1JoVoIdUk24kcxXXs3hMbF8OoAK/7MbKx37Gg2KV5w5j/m1QUls8rmly+cVTY3VsIwG5z6Ud7VwDApqiFOuugnWjqlqis=
*/