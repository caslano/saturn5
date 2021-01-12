
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_type
      : detail::synthesize_func<typename detail::to_sequence<Types>::type, Tag>
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_type,(Types,Tag))
    };
  }
}

#endif
 

/* function_type.hpp
7ocD4RdwMPwKDhdzzTePrv+VNcraP0a6anqX8zzZvAAGw7kwClbAeHgxbAgrYTO4AqbAK2ELOA+2hZfAU9ReD7V3mto7Hc6H/eACOETtnaH2Rqm90XAhPBteCieqvRy1N0XtTYWLYD5cDEvV3hy1N1ft/R4u0fptKVyk9parvSvU3gq4DF6n12/W6+v0uq630fW6jNW4rLeZwHPngefCWjADJsHzYDK8CKbAbNgV5sIz4BQ4
*/