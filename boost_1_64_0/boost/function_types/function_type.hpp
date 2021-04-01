
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
RDUe90k7m0o2VSzOZBkEjWLtoxqv4VKAIAJDan4sSUNZWQqUPnT8hUwEskP+8uYu4OsOebNlvV87ppZ2xVeNy3WuaS/IJUVgcojhGqRzz4cvE7ouEDimWHvFosF02datJPfYussxxHnBMPiHeAm6UbT+l20s/fWZXJvvCg9fUT0kHFxhyyFAqZChxzXMqFTlubeYJPI/K2YUbHqAfAq2fIkl+rxYY7lG6/C3ijBpj9uRMoJpaOzecrofy1cv9A8Nzi6eYsq95QMacOfurmzeQQZZ9jFAl/1GuUa13U5B0Mfw1DGrmwWkBAET5wou4D+9bMLb/+60KdIztuftqci3ZdL6I05hLR4HtyoQIVeojyyqTveX4f8rjqsNlIFN3ZpJMUegmHdUG0kXqG+GkIRkXF5Rk9YDXZdkWZmZcRa9uOVVF2n6IDCFZBkfLfZhutCirv1hunpv8S3twVtJH2+09hM+7BP0O5zFG1CfmLWQp5dzf0J7/fGNqfrpr/rYL4/FKLZWHkQXRQQBqhtiKF2AcP8o3GSWe1gGu7rdLDEWzsx4tP0hnkJh6TtoaA==
*/