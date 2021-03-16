
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag, detail::callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_callable_builtin,(T,Tag))
    };
  }
}

#endif


/* is_callable_builtin.hpp
DVCUj7uBztQ4amq/dbMHzXo3W6cRvxno/UADOoz64f8AfUCH64BuBPq4DqMx8iGg24D+DuiLGkfNbRPQ14H+HujbQB8F+hegjwH9BOjjQD/T8dEg9AjQb3QYTVlPAnXBtz4FFCetngaK2h/eR5PmZqApQJ8Fil4yW4AOMqhdDow0qFUOjNXxxxvUqgauMajtDUzT+PUGtayBm3QYe0VoBQOrdRg1S2hRA+sMak8DTxjUhgaeMqgFDbyg4+02qKU=
*/